/*
 *  Copyright 2000,2001,2004,2005 Red Hat, Inc.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions of the
 * GNU General Public License v.2.  This program is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
 * including the implied warranties of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. Any Red Hat
 * trademarks that are incorporated in the source code or documentation are not
 * subject to the GNU General Public License and may only be used or replicated
 * with the express permission of Red Hat, Inc.
 *
 * Red Hat Author(s): Nalin Dahyabhai <nalin@redhat.com>
 */

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <limits.h>
#include <obstack.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sel.h"

#ifndef CFGDIR
#define CFGDIR "/etc/makedev.d"
#endif

#ifndef DEVDIR
#define DEVDIR "/dev"
#endif

#define VERBOSE		(1 << 0)
#define FAKE		(1 << 1)
#define DELETE		(1 << 2)
#define IGNORE		(1 << 3)
#define MANIFEST	(1 << 4)
#define SCRIPT		(1 << 5)
#define EXACT		(1 << 6)
#define UDEVPERMS	(1 << 7)
#define ALWAYSCREATE	(1 << 8)
#define NOFOLLOW	(1 << 9)

enum entry_type {
	BLOCK = 'b',
	CHAR = 'c',
	LINK = 'l',
	ALIAS = 'a',
	SOCKET = 's',
	MACRO = '=',
};

struct device_entry {
	enum entry_type type;
	unsigned int perms;       /* permissions */
	const char *user;         /* device owner */
	const char *group;        /* device group */
	unsigned int major;       /* device major number */
	int minor;                /* minor number of the first device */
	int minor_step;           /* difference between minor one and two */
	unsigned int num;         /* number of devices to create */
	const char *name;         /* format string for the devices */
	int name_prefix_length;
				  /* the length of the portion of the name
				   * which will not change for any device which
				   * this entry will create */
	unsigned int base;        /* number to start formatting names with */
	unsigned int modulo;	  /* if using two format specifiers, number
				     of second number increases before first
				     number is increased */
	unsigned int base2;	  /* base for the second number if two format
				     specifiers are used */
	const char *link_target;  /* target for a symlink, if it is one */
	struct device_entry *next;
};

struct dirlist_entry {
	char *path;
	struct dirlist_entry *next;
};

struct macro {
	const char *name, *expansion;
	unsigned int name_len, expansion_len;
	struct macro *next;
};

struct device_entry *devices = NULL, *last_device = NULL;
struct dirlist_entry *dirlist = NULL;
struct macro *macros = NULL;
struct obstack config_obstack;

static void *xmalloc(size_t size)
{
	void *ret = malloc(size);
	if (ret == NULL) {
		fprintf(stderr, "could not allocated memory\n");
		exit(7);
	}
	return ret;
}
#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free

static void makedevices(const char *directory, const char *contextdirectory,
			const char *fragment,
			int max, int flags);

/* Check if the directory list contains a particular directory. */
static int
dirlist_contains(const char *directory)
{
	struct dirlist_entry *entry = dirlist;
	while (entry != NULL) {
		if (strcmp(entry->path, directory) == 0) {
			return 1;
		}
		entry = entry->next;
	}
	return 0;
}

static void
dirlist_add(const char *directory)
{
	struct dirlist_entry *entry = NULL;
	entry = malloc(sizeof(struct dirlist_entry));
	if (entry == NULL) {
		fprintf(stderr, "couldn't allocate buffer\n");
		exit(5);
	}
	entry->path = strdup(directory);
	entry->next = dirlist;
	dirlist = entry;
}

/* Make the device files and links associated with this entry. */
static int
makenodes(const char *directory, const char *contextdirectory,
	  const char *fragment, struct device_entry *entry, int max, int flags)
{
	struct passwd *pwd;
	struct group *grp;
	uid_t uid;
	gid_t gid;
	struct stat st;
	char path[PATH_MAX], pattern[PATH_MAX], tmp[PATH_MAX], ctx[PATH_MAX];
	mode_t mode;
	dev_t dev;
	unsigned int mul, num1, num2, frlen, dirlen, i;
	int ret = 0;

	/* Compute the lengths of our fixed-length strings, because we'll be
	 * using them a lot. */
	frlen = strlen(fragment);
	dirlen = strlen(directory);

	/* Limit the number of devices we'll create per entry. */
	num1 = 0;
	num2 = 0;
	for (mul = 0; (max != 0) && (mul < entry->num); max--, mul++) {
		/* Build the file name. */
		snprintf(pattern, sizeof(pattern), "%%s/%s", entry->name);

		/* If this is not the first device, and there's not some format
		 * specifier in there, append a "%d", which makes things like
		 * hda/hda1 really easy to do. */
		if (mul > 0) {
			if (strchr(pattern + 3, '%') == NULL) {
				strncat(pattern, "%d",
					sizeof(pattern) - 1 - strlen(pattern));
			}
		}
		if (entry->modulo) {
			/* Similarly, when using 2 format specifiers and
			   the string contains %|, ignore everything afterwards
			   if num1 is 0.  */
			char *p = pattern + 2;
			while ((p = strchr (p + 1, '%')) != NULL
			       && p[1] != '|')
				;
			if (p) {
				if (num1 == 0)
					*p = '\0';
				else
					memmove (p, p + 2, strlen(p + 2) + 1);
			}
		}
		snprintf(path, sizeof(path), pattern, directory,
			 num2 + entry->base, num1 + entry->base2);

		if (entry->modulo) {
			num1++;
			if (num1 == entry->modulo) {
				num1 = 0;
				num2++;
			}
		} else
			num2++;

		/* Check if the target matches the fragment. */
		if (strncmp(fragment, path + dirlen + 1, frlen) != 0) {
			continue;
		}

		/* If the device is in a subdirectory, go ahead and create the
		 * subdirectory if it doesn't already exist.  Subdirectories
		 * are always owned by the superuser. */
		for (i = 0; path[i] != '\0'; i++) {
			if ((i == 0) || (path[i] != '/')) {
				continue;
			}
			memcpy(tmp, path, i);
			tmp[i] = '\0';
			if ((lstat(tmp, &st) != -1) || (errno != ENOENT)) {
				snprintf(ctx, sizeof(ctx), "%s",
					 contextdirectory);
				if (i > dirlen) {
					snprintf(ctx, sizeof(ctx), "%s/%s",
						 contextdirectory,
						 tmp + dirlen + 1);
				}
				if (secontextverify("MAKEDEV", ctx,
						    st.st_mode) == 0) {
					continue;
				}
			}
			if (dirlist_contains(tmp)) {
				continue;
			}
			dirlist_add(tmp);
			if (flags & MANIFEST) {
				printf("%%attr(0%o, %s, %s) %%dir %s\n", 0755,
				       "root", "root", tmp);
			} else
			if (flags & SCRIPT) {
				printf("mkdir%s -p -m 0%o %s\n",
				       secontextgetflag("MAKEDEV", ctx,
							S_IFDIR | 0755),
				       0755, tmp);
				printf("chown %s:%s %s\n", "root", "root", tmp);
			} else
			if (flags & VERBOSE) {
				printf("mkdir%s %s\n",
				       secontextgetflag("MAKEDEV", ctx,
							S_IFDIR | 0755),
				       tmp);
			}

			if (!(flags & (FAKE | SCRIPT))) {
				secontextsetup("MAKEDEV", ctx, S_IFDIR | 0755);
				if (mkdir(tmp, 0755) != 0) {
					fprintf(stderr,
						"MAKEDEV: mkdir: %s\n",
						strerror(errno));
				} else {
					if (chown(tmp, 0, 0) != 0) {
						fprintf(stderr,
							"MAKEDEV: chown: %s\n",
							strerror(errno));
					}
				}
			}
		}

		/* Check if the target exactly matches the given name. */
		if (flags & EXACT) {
			if (strcmp(fragment, path + dirlen + 1) != 0) {
				continue;
			}
		}
		ret = 1;

		/* Set the mode. */
		assert((entry->type == BLOCK) ||
		       (entry->type == CHAR) ||
		       (entry->type == LINK) ||
		       (entry->type == ALIAS) ||
		       (entry->type == SOCKET));
		mode = entry->perms;
		if (entry->type == BLOCK) {
			mode |= S_IFBLK;
		} else
		if (entry->type == CHAR) {
			mode |= S_IFCHR;
		} else
		if (entry->type == LINK) {
			mode |= S_IFLNK;
		}

		/* Determine the IDs of the owner and her group, if we'll need
		 * them. */
		if ((flags & MANIFEST) || (entry->type == ALIAS) ||
		    (entry->type == LINK)) {
			/* In manifest mode, we can let RPM handle the
			 * ownership and permissions.
			 * If this is an alias entry, then there is no
			 * owner/group defined. */
			uid = -1;
			gid = -1;
		} else {
			/* Block and character special devices and sockets all
			 * need owners and groups to be defined. */
			pwd = getpwnam(entry->user);
			if (pwd == NULL) {
				/* No fair! */
				fprintf(stderr, "MAKEDEV: no such user: %s\n",
					entry->user);
				exit(10);
			}
			uid = pwd->pw_gid;
			grp = getgrnam(entry->group);
			if (grp == NULL) {
				/* No fair! */
				fprintf(stderr, "MAKEDEV: no such group: %s\n",
					entry->group);
				exit(10);
			}
			gid = grp->gr_gid;
		}

		/* Generate the name which we'll use to look up the file
		 * context. */
		snprintf(ctx, sizeof(ctx), "%s/%s",
			 contextdirectory, path + dirlen + 1);

		/* Actually create device files. */
		if ((entry->type == BLOCK) || (entry->type == CHAR)) {
			/* Set the major/minor numbers. */
			dev = makedev(entry->major,
				      entry->minor + (mul * entry->minor_step));

			/* Check that we aren't trying anything unnecessary. */
			if (!(flags & ALWAYSCREATE))
			if (lstat(path, &st) == 0)
			if (((entry->type == CHAR) && S_ISCHR(st.st_mode)) ||
			    ((entry->type == BLOCK) && S_ISBLK(st.st_mode)))
			if (st.st_rdev == dev)
			if ((flags & MANIFEST) || (st.st_uid == uid))
			if ((flags & MANIFEST) || (st.st_gid == gid))
			if ((st.st_mode & 0777) == entry->perms)
			if (secontextverify("MAKEDEV", ctx, st.st_mode) == 0) {
				/* We know how to create this, but we didn't
				 * need to create it because it was already
				 * exactly what we wanted. */
				ret = 1;
				continue;
			}

			/* Log a message if we're being verbose. */
			if (flags & UDEVPERMS) {
				/* We print nothing for symlinks; udev doesn't
				 * create them. */
				if ((entry->type == CHAR) ||
				    (entry->type == BLOCK) ||
				    (entry->type == SOCKET)) {
					printf("%s:%s:%s:%04o\n",
					       path + dirlen + 1,
					       entry->user, entry->group,
					       entry->perms & 0777);
				}
			} else
			if (flags & MANIFEST) {
				printf("%%attr(0%o, %s, %s)", entry->perms,
				       entry->user, entry->group);
				printf(" %%dev(%c, %d, %d)",
				       (entry->type == CHAR) ? 'c' :
				       ((entry->type == BLOCK) ? 'b' : '?'),
				       entry->major,
				       entry->minor +
				       (mul * entry->minor_step));
				printf(" %s\n", path);
			} else
			if (flags & SCRIPT) {
				printf("mknod%s -m 0%o %s %c %d %d\n",
				       secontextgetflag("MAKEDEV", ctx, mode),
				       entry->perms, path,
				       (entry->type == CHAR) ? 'c' :
					((entry->type == BLOCK) ? 'b' : '?'),
				       entry->major,
				       entry->minor +
				       (mul * entry->minor_step));
				printf("chown %s:%s %s\n",
				       entry->user, entry->group, path);
			} else
			if (flags & VERBOSE) {
				printf("create %-30s %c %3d %3d %s:%s %3o%s\n",
				       path + dirlen + 1,
				       (entry->type == CHAR) ? 'c' :
				       ((entry->type == BLOCK) ? 'b' : '?'),
				       entry->major,
				       entry->minor + (mul * entry->minor_step),
				       entry->user,
				       entry->group,
				       mode & 0777,
				       secontextgetname("MAKEDEV", ctx, mode));
			}

			/* Create the node.  RPM can take the device
			 * description, so we don't have to do anything if
			 * we're in manifest mode. */
			if (!(flags & (FAKE | SCRIPT | MANIFEST))) {
				int r, made = 0;
				/* First, create it with a different name. */
				strcpy(pattern, path);
				strcat(pattern, "-");
				secontextsetup("MAKEDEV", ctx, mode);
				r = mknod(pattern, mode,
					  makedev(entry->major,
						  entry->minor +
						  mul * entry->minor_step));
				/* Well, we created something, so keep track of
				 * that fact in case things go awry. */
				if (r != -1) {
					made = 1;
				}
				/* Set permissions. */
				if (r != -1) {
					r = chmod(pattern, mode);
				}
				/* Set ownership. */
				if (r != -1) {
					r = chown(pattern, uid, gid);
				}
				/* Finally rename it to the right place. */
				if (r != -1) {
					r = rename(pattern, path);
				}
				/* Report any errors. */
				if (r != 0) {
					fprintf(stderr,
						"MAKEDEV: error making %s: "
						"%s\n", path, strerror(errno));
					exit(8);
				} else {
					/* Clean up. */
					if (made) {
						unlink(pattern);
					}
				}
			}
		}

		/* We're creating symlinks today. */
		if (entry->type == LINK) {
			ssize_t len;
			/* Check that we aren't trying anything unnecessary. */
			if (lstat(path, &st) == 0
			    && S_ISLNK(st.st_mode)
			    && (len = readlink(path, tmp, sizeof(tmp) - 1)) != -1
			    && (tmp[len] = '\0',
				strcmp(tmp, entry->link_target)) == 0
			    && secontextverify("MAKEDEV", ctx, st.st_mode) == 0) {
				/* We know how to create this, but didn't need
				 * to, as it was already there. */
				ret = 1;
				continue;
			}

			/* Mark that we're going to make a symlink. */
			if (flags & MANIFEST) {
				printf("%%attr(0%o, %s, %s) %s\n", 0777,
				       "root", "root", path);
			} else
			if (flags & SCRIPT) {
				printf("ln -s %s %s\n", path + dirlen + 1,
				       entry->link_target);
			} else
			if (flags & VERBOSE) {
				printf("symlink %s -> %s\n", path + dirlen + 1,
				       entry->link_target);
			}

			/* Make the symlink. */
			if (!(flags & (FAKE | SCRIPT))) {
				int r;
				secontextsetup("MAKEDEV", ctx, mode);
				r = symlink(entry->link_target, path);
				if ((r != 0) && (errno == EEXIST)) {
					unlink(path);
					r = symlink(entry->link_target, path);
				}
				if (r != 0) {
					fprintf(stderr, "error making %s: %s\n",
						path, strerror(errno));
					exit(9);
				}
			}
		}

		if (entry->type == SOCKET) {
			struct sockaddr_un sun;
			int sockfd, r;

			memset(&sun, 0, sizeof(sun));
			sun.sun_family = AF_UNIX;
			snprintf(sun.sun_path, sizeof(sun.sun_path),
				 "%s/%s", directory, entry->name);

			/* Check that we aren't trying anything unnecessary. */
			if (lstat(sun.sun_path, &st) == 0)
			if (S_ISSOCK(st.st_mode))
			if ((flags & MANIFEST) || (st.st_uid == uid))
			if ((flags & MANIFEST) || (st.st_gid == gid))
			if ((st.st_mode & 0777) == entry->perms)
			if (secontextverify("MAKEDEV", ctx, st.st_mode) == 0) {
				/* We know how to create this, but we didn't
				 * need to bother. */
				ret = 1;
				continue;
			}

			/* Log a message if we're being verbose. */
			if (flags & MANIFEST) {
				printf("%%attr(0%o, %s, %s) %s\n", entry->perms,
				       entry->user, entry->group, sun.sun_path);
			} else
			if (flags & SCRIPT) {
				printf("mksock%s -m 0%o %s\n",
				       secontextgetflag("MAKEDEV", ctx,
							entry->perms |
							S_IFSOCK),
				       entry->perms, sun.sun_path);
				printf("chmod %s.%s %s\n",
				       entry->user, entry->group, sun.sun_path);
			} else
			if (flags & VERBOSE) {
				printf("bind    %-30s %14s:%s %3o%s\n",
				       entry->name, entry->user, entry->group,
				       entry->perms,
				       secontextgetname("MAKEDEV", ctx,
							entry->perms |
							S_IFSOCK));
			}

			sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
			if (sockfd == -1) {
				fprintf(stderr,
					"MAKEDEV: error making %s: %s\n",
					sun.sun_path, strerror(errno));
				exit(11);
			}
			if (!(flags & (FAKE | SCRIPT))) {
				secontextsetup("MAKEDEV", ctx,
					       entry->perms | S_IFSOCK);
				r = bind(sockfd,
					 (struct sockaddr*)&sun, sizeof(sun));

				if (r != -1) {
					r = chmod(sun.sun_path, entry->perms);
				}
				if (r != -1) {
					if (!(flags & MANIFEST)) {
						r = chown(sun.sun_path,
							  uid, gid);
					}
				}
				if (r != 0) {
					fprintf(stderr,
						"MAKEDEV: error making %s: "
						"%s\n", path, strerror(errno));
					exit(11);
				}
			}
			close(sockfd);
		}

		/* We're executing an aliased item. */
		if (entry->type == ALIAS) {
			/* ... unless it's a zero-length fragment and we're in
			 * always-create mode, in which case whatever this
			 * alias resolves to is already going to be handled. */
			if ((strlen(fragment) > 0) && !(flags & ALWAYSCREATE)) {
				makedevices(directory, contextdirectory,
					    entry->link_target, max, flags);
			}
		}
	}
	return ret;
}

static void
makedevices(const char *directory, const char *contextdirectory,
	    const char *fragment, int max, int flags)
{
	struct device_entry *entry = NULL;
	int matched = 0, entrymatched, relevant = 0;
	char buf[PATH_MAX];

	while ((fragment[relevant] != '\0') &&
	       (isalnum(fragment[relevant]) || (fragment[relevant] == '/'))) {
		relevant++;
	}

	for (entry = devices;
	     (entry != NULL) && (entry->name != NULL);
	     entry = entry->next) {
		if ((entry->name_prefix_length == -1) ||
		    (strncmp(entry->name, fragment,
			     entry->name_prefix_length < relevant ?
			     entry->name_prefix_length : relevant) == 0)) {
			entrymatched = makenodes(directory, contextdirectory,
						 fragment, entry, max, flags);
			matched += entrymatched;
			if (((flags & NOFOLLOW) == 0) &&
			    (entry->type == LINK)) {
				char *p = buf;
				size_t len = strlen(entry->name);
				/* Build the link target's name. */
				if (len >= sizeof(buf))
					len = sizeof(buf) - 1;
				memcpy(buf, entry->name, len);
				buf[len] = '\0';
				if ((p = strrchr(buf, '/')) != NULL)
					p++;
				else
					p = buf;
				len = strlen(entry->link_target);
				if ((p - buf) + len >= sizeof(buf))
					len = sizeof(buf) - 1 - (p - buf);
				memcpy(p, entry->link_target, len);
				p[len] = '\0';
				/* Strip out empty path components. */
				while ((p = strstr(buf, "//")) != NULL) {
					memmove(p, p + 1, strlen(p));
				}
				/* Replace "/foo/../" with "/" by removing the
				 * "foo/../" part. */
				if (strlen(buf) > 0) {
					p = buf + strlen(buf) - 1;
					while (p > buf) {
						if (strncmp(p, "/../", 4) == 0) {
							if (strchr(buf, '/') < p) {
								char *q;
								q = p - 1;
								while (*q != '/') {
									q--;
								}
								memmove(q + 1, p + 4, strlen(p + 4) + 1);
							}
						}
						p--;
					}
				}
				if (flags & EXACT) {
					/* If the link target matches the
					 * fragment, then create the link
					 * target if we wouldn't have
					 * otherwise. */
					if ((entrymatched == 0) &&
					    (strcmp(buf, fragment) == 0)) {
						makedevices(directory,
							    contextdirectory,
							    entry->name,
							    1,
							    flags | NOFOLLOW);
					}
					/* If the we made a link, make the
					 * target of the link. */
					if (entrymatched > 0) {
						makedevices(directory,
							    contextdirectory,
							    buf,
							    1,
							    flags | NOFOLLOW);
					}
#if 0
				} else {
					/* If the link target matches the
					 * fragment, then create the link
					 * target if we wouldn't have
					 * otherwise. */
					if ((entrymatched == 0) &&
					    (strncmp(buf, fragment,
						     relevant) == 0)) {
						makedevices(directory,
							    contextdirectory,
							    entry->name,
							    entrymatched,
							    flags | NOFOLLOW);
					}
					/* If the we made a link, make the
					 * target of the link. */
					if (entrymatched > 0) {
						makedevices(directory,
							    contextdirectory,
							    buf,
							    entrymatched,
							    flags | NOFOLLOW);
					}
#endif
				}
			}
		}
	}

	if (matched == 0) {
		fprintf(stderr, "don't know how to make device \"%s\"\n",
			fragment);
	}
}

static char *
stralloc (const char *p, const char *q)
{
	char *ret;
	if (q == p)
		return NULL;
	ret = obstack_alloc(&config_obstack, q - p + 1);
	memcpy(ret, p, q - p);
	ret[q - p] = '\0';
	return ret;
}

static void
read_config_line(const char *path, const char *pline, size_t pline_len)
{
	const char *p, *q;
	char *tmp, *r;
	char buf[LINE_MAX], buf2[LINE_MAX];
	struct device_entry *entry = NULL;
	struct macro *macro = NULL;
	enum entry_type type = -1;
	size_t len;

	/* Expand macros. This is not as elegant as it could be, but it should
	 * suffice for our use here. */
	tmp = buf;
	p = pline;
	while ((p = strchr(p, '$')) != NULL) {
		for (macro = macros; macro != NULL; macro = macro->next) {
			if (!strncmp(p + 1, macro->name, macro->name_len)) {
				break;
			}
		}
		if (macro == NULL) {
			fprintf(stderr, "unrecognized macro at \"%s\"\n",
				pline);
			exit(6);
		}
		r = mempcpy(tmp, pline, p - pline);
		len = macro->expansion_len;
		if ((r - tmp) + len >= sizeof(buf))
			len = sizeof(buf) - (r - tmp) - 1;
		r = mempcpy(r, macro->expansion, len);
		len = pline_len - (p - pline) - 1 - macro->name_len;
		if ((r - tmp) + len >= sizeof(buf))
			len = sizeof(buf) - (r - tmp) - 1;
		r = mempcpy(r, p + 1 + macro->name_len, len);
		*r = '\0';
		pline_len += macro->expansion_len - macro->name_len - 1;
		if (pline_len >= sizeof(buf))
			pline_len = sizeof(buf) - 1;
		p = tmp + (p - pline);
		pline = tmp;
		if (tmp == buf)
			tmp = buf2;
		else
			tmp = buf;
	}

	/* First, skip leading whitespace. */
	for (p = pline; (*p != '\0') && isspace(*p); p++) {
		continue;
	}

	/* If it's a comment of some kind, ignore it. */
	if (*p == '\0') return;
	if (*p == '\n') return;
	if (*p == '\r') return;
	if (*p == '#') return;

	/* Now determine what kind of entry this is. */
	if (*p == BLOCK) {
		type = BLOCK;
	} else
	if (*p == CHAR) {
		type = CHAR;
	} else
	if (*p == LINK) {
		type = LINK;
	} else
	if (*p == ALIAS) {
		type = ALIAS;
	} else
	if (*p == SOCKET) {
		type = SOCKET;
	} else
	if (*p == MACRO) {
		type = MACRO;
	} else
	{
		fprintf(stderr, "error at \"%s\"\n", pline);
		exit(6);
	}

	/* Allocate memory. */
	switch (type) {
	case BLOCK:
	case CHAR:
	case LINK:
	case ALIAS:
	case SOCKET:
		entry = obstack_alloc(&config_obstack,
				      sizeof(struct device_entry));
		memset(entry, 0, sizeof(struct device_entry));
		entry->type = type;
		entry->name_prefix_length = -1;
		macro = NULL;
		break;
	case MACRO:
		macro = obstack_alloc(&config_obstack, sizeof(struct macro));
		memset(macro, 0, sizeof(struct macro));
		break;
	}

	if (macro) {
		/* Read the macro name. */
		for (p++; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		macro->name_len = q - p;
		macro->name = stralloc(p, q);
		if (macro->name == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"bad macro name in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		/* Now read the expansion. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		macro->expansion = strdup(p);

		if ((macro->expansion == NULL) ||
		    ((macro->expansion_len = strlen(macro->expansion)) == 0)) {
			fprintf(stderr, "error parsing \"%s\": "
				"bad expansion in \"%s\"\n", path, pline);
			exit(7);
		}

		macro->next = macros;
		macros = macro;

		return;
	}

	else if ((entry->type == BLOCK) || (entry->type == CHAR)) {
		/* Now read the permissions. */
		for (p++; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		while (isdigit(*p) && (*p != '\0')) {
			entry->perms *= 8;
			entry->perms += (*p - '0');
			p++;
		}

		/* Now read the owner. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->user = stralloc(p, q);
		if (entry->user == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown user in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		/* Now read the group. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->group = stralloc(p, q);
		if (entry->group == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown group in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		/* And now the major number. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		while (isdigit(*p) && (*p != '\0')) {
			entry->major *= 10;
			entry->major += (*p - '0');
			p++;
		}
		if (entry->major <= 0) {
			fprintf(stderr, "error parsing \"%s\": "
				"bad major in \"%s\"\n", path, pline);
			exit(7);
		}

		/* And now the minor number. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		while (isdigit(*p) && (*p != '\0')) {
			entry->minor *= 10;
			entry->minor += (*p - '0');
			p++;
		}
		if (entry->minor < 0) {
			fprintf(stderr, "error parsing \"%s\": "
				"bad minor in \"%s\"\n", path, pline);
			exit(7);
		}

		/* And now the minor step number. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		while (isdigit(*p) && (*p != '\0')) {
			entry->minor_step *= 10;
			entry->minor_step += (*p - '0');
			p++;
		}
		if (entry->minor_step < 0) {
			fprintf(stderr, "error parsing \"%s\": "
				"bad step in \"%s\"\n", path, pline);
			exit(7);
		}

		/* And now the number of devices we can create this way. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		while (isdigit(*p) && (*p != '\0')) {
			entry->num *= 10;
			entry->num += (*p - '0');
			p++;
		}
		if (entry->num <= 0) {
			fprintf(stderr, "error parsing \"%s\": "
				"bad count in \"%s\"\n", path, pline);
			exit(7);
		}

		/* Now read the device's (root) name. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->name = stralloc(p, q);
		if (entry->name == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown name in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		entry->name_prefix_length = strcspn(entry->name, "%");

		/* Now read the (optional) base. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}

		if (strncmp(entry->name + entry->name_prefix_length, "%c", 2)
		    == 0)
			entry->base = p[0];
		else
			entry->base = atoi(p);

		if (q != p) {
			p = q;

			/* Now read the (optional) modulo. */
			for (; (*p != '\0') && isspace(*p); p++) {
				continue;
			}
			for (q = p; (*q != '\0') && !isspace(*q); q++) {
				continue;
			}
			entry->modulo = atoi(p);

			if (entry->modulo) {
				p = q;

				/* Now read the (optional) second base. */
				for (; (*p != '\0') && isspace(*p); p++) {
					continue;
				}
				for (q = p; (*q != '\0') && !isspace(*q); q++) {
					continue;
				}

				if (strstr(entry->name
					   + entry->name_prefix_length + 1,
					   "%c"))
					entry->base2 = p[0];
				else
					entry->base2 = atoi(p);
			}
		}
	}

	else if (entry->type == LINK || entry->type == ALIAS) {
		/* Read the link's (or alias') name. */
		for (p++; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->name = stralloc(p, q);
		if (entry->name == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown name in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		entry->name_prefix_length = strcspn(entry->name, "%");

		/* Read the link's (or alias') target's name. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->link_target = stralloc(p, q);
		if (entry->link_target == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown link target in \"%s\"\n", path, pline);
			exit(7);
		}
		entry->num = 1;
	}

	else if (entry->type == SOCKET) {
		/* Now read the permissions. */
		for (p++; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		while (isdigit(*p) && (*p != '\0')) {
			entry->perms *= 8;
			entry->perms += (*p - '0');
			p++;
		}

		/* Now read the owner. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->user = stralloc(p, q);
		if (entry->user == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown user in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		/* Now read the group. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->group = stralloc(p, q);
		if (entry->group == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown group in \"%s\"\n", path, pline);
			exit(7);
		}
		p = q;

		/* Now read the socket's name. */
		for (; (*p != '\0') && isspace(*p); p++) {
			continue;
		}
		for (q = p; (*q != '\0') && !isspace(*q); q++) {
			continue;
		}
		entry->name = stralloc(p, q);
		if (entry->name == NULL) {
			fprintf(stderr, "error parsing \"%s\": "
				"unknown name in \"%s\"\n", path, pline);
			exit(7);
		}

		entry->name_prefix_length = strcspn(entry->name, "%");

		entry->num = 1;
	}

	/* Add it to the end of the list. */
	if (devices == NULL) {
		devices = entry;
		last_device = entry;
	} else {
		last_device->next = entry;
		last_device = entry;
	}
}

static void
read_config_single_file(const char *path)
{
	FILE *fp = NULL;
	char buf[LINE_MAX];

	fp = fopen(path, "r");
	if (fp == NULL) {
		fprintf(stderr, "error opening %s: %s\n",
			path, strerror(errno));
		exit(4);
	}

	while (fgets_unlocked(buf, sizeof(buf), fp) != NULL) {
		size_t l = strlen(buf);

		while ((l > 0) &&
		       ((buf[l - 1] == '\n') || (buf[l - 1] == '\r'))) {
			l--;
			buf[l] = '\0';
		}

		read_config_line(path, buf, l);
	}

	fclose(fp);
}

static int
screen_out_bad(const struct dirent *ent)
{
	size_t l;
	if (ent->d_name[0] == '.') {
		return 0;
	}

	l = strlen(".rpmsave");
	if (ent->d_reclen > l) {
		if (strcmp(ent->d_name + ent->d_reclen - l, ".rpmsave") == 0) {
			return 0;
		}
	}

	l = strlen(".rpmorig");
	if (ent->d_reclen > l) {
		if (strcmp(ent->d_name + ent->d_reclen - l, ".rpmorig") == 0) {
			return 0;
		}
	}

	l = strlen(".rpmnew");
	if (ent->d_reclen > l) {
		if (strcmp(ent->d_name + ent->d_reclen - l, ".rpmnew") == 0) {
			return 0;
		}
	}

	return 1;
}

static void
read_configs(const char *configdir, int flags)
{
	struct dirent **ent;
	struct stat st;
	char path[PATH_MAX];
	int i, count;

	obstack_init(&config_obstack);
	count = scandir(configdir, &ent, screen_out_bad, alphasort);
	if (count == -1) {
		if ((flags & IGNORE)) {
			fprintf(stderr, "warning: ");
		} else {
			fprintf(stderr, "error: ");
		}
		fprintf(stderr, "%s is not a directory\n", configdir);
		if (!(flags & IGNORE)) {
			exit(1);
		}
		return;
	}

	for (i = 0; i < count; i++) {
		snprintf(path, sizeof(path), "%s/%s",
			 configdir, ent[i]->d_name);
		if (stat(path, &st) != -1) {
			if (S_ISREG(st.st_mode)) {
				read_config_single_file(path);
			} else {
				if (!S_ISDIR(st.st_mode)) {
					if ((flags & IGNORE)) {
						fprintf(stderr, "warning: ");
					} else {
						fprintf(stderr, "error: ");
					}
					fprintf(stderr,
						"%s is not a regular file\n",
						path);
					if (!(flags & IGNORE)) {
						exit(2);
					}
				}
			}
		} else {
			if ((flags & IGNORE)) {
				fprintf(stderr, "warning: ");
			} else {
				fprintf(stderr, "error: ");
			}
			fprintf(stderr, "failure reading %s: %s\n",
				path, strerror(errno));
			if (!(flags & IGNORE)) {
				exit(3);
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int c, i, flags = 0;
	int max = -1;
	const char *cfgdir = CFGDIR, *devdir = DEVDIR, *contextdir = NULL, *arg;
	char *p;

	/* Scan arguments. */
	while ((c = getopt(argc, argv, "ac:d:m:inuvxD:MNSV")) != -1) {
		switch (c) {
		case 'a':
			flags |= ALWAYSCREATE;
			break;
		case 'c':
			cfgdir = strdup(optarg);
			break;
		case 'd':
			devdir = strdup(optarg);
			p = strrchr(devdir, '/');
			if ((p != NULL) && (*(p + 1) == '\0')) {
				*p = '\0';
			}
			break;
		case 'D':
			contextdir = strdup(optarg);
			p = strrchr(contextdir, '/');
			if ((p != NULL) && (*(p + 1) == '\0')) {
				*p = '\0';
			}
			break;
		case 'm':
			max = strtol(optarg, &p, 10);
			if ((p != NULL) && (*p != '\0')) {
				fprintf(stderr,
					"-m requires a numeric argument\n");
				return -1;
			}
			break;
		case 'i':
			flags |= IGNORE;
			break;
		case 'n':
			flags |= (FAKE | VERBOSE);
			break;
		case 'u':
			flags |= (FAKE | UDEVPERMS);
			printf("# permission/ownership map for udev\n");
			printf("# generated by MAKEDEV\n");
			break;
		case 'v':
			flags |= VERBOSE;
			break;
		case 'M':
			flags |= MANIFEST;
			break;
		case 'S':
			flags |= (FAKE | SCRIPT);
			break;
		case 'V':
			printf("MAKEDEV version " VERSION "\n");
			return 0;
		case 'x':
			flags |= EXACT;
			break;
		default:
			break;
		}
	}

	/* Usage message. */
	if (optind >= argc) {
		printf("Usage: MAKEDEV -V\n"
		       "       MAKEDEV [-c configdir] [-d devicedir] [-D contextdir] [-m maxdevices]\n"
		       "       [-a] [-i] [-n] [-v] [-M] [-S] [-u] [-x] name\n");
		return 0;
	}

	/* Read our configuration files. */
	read_configs(cfgdir, flags);

	/* Do the hard work now. */
	for (i = optind; i < argc; i++) {
		/* Strip off the device directory name if the device name was
		 * given as an absolute path. */
		arg = argv[i];
		if (arg[0] == '/') {
			if (strncmp(arg, devdir, strlen(devdir)) == 0) {
				arg += strlen(devdir);
				while (arg[0] == '/') {
					arg++;
				}
			}
		}
		/* If we're outputting permissions files for udev, make a
		 * comment about which argument triggered this block of
		 * permissions. */
		if (flags & UDEVPERMS) {
			printf("# MAKEDEV %s%s\"%s\"\n",
			       flags & EXACT ? "-x " : "",
			       flags & ALWAYSCREATE ? "-a " : "",
			       arg);
		}
		/* Do the heavy lifting. */
		makedevices(devdir, contextdir ? contextdir : devdir,
			    arg, max, flags);
	}

	return 0;
}
