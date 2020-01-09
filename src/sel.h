/*
 *  Copyright 2004,2005 Red Hat, Inc.
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

#ifdef MAKEDEV_SELINUX
#include <selinux/selinux.h>
static char secontextname[PATH_MAX + 2];
static char secontextflag[PATH_MAX + 7];
/* Look up which context should be applied to the given path with the given
 * mode, and store the context name prepended with " -Z" to secontextflag, and
 * with " " to secontextname.  Catch the default cases and use "" as the
 * context.  Return 1 if the file in question is supposed to have a non-default
 * context associated with it. */
static int
secontextlookupone(const char *path, mode_t mode)
{
	static int enabled = -1;
	security_context_t context;
	if (enabled == -1) {
		enabled = is_selinux_enabled();
		strcpy(secontextname, " ");
		strcpy(secontextflag, " ");
	}
	if (enabled != 1) {
		/* Indicate no context found. */
		return 0;
	}
	/* If there's an error determining the context, or it has none, return
 	 * 0 to indicate no such context. */
	context = NULL;
	if ((matchpathcon(path, mode, &context) != 0) ||
	    (context == NULL) ||
	    ((context != NULL) &&
	     (strcmp(context, "<<none>>") == 0))) {
		if (context != NULL) {
			freecon(context);
		}
		context = NULL;
		strcpy(secontextname, " ");
		strcpy(secontextflag, " ");
		return 0;
	}
	/* We've gotten a non-default context. Save it. */
	snprintf(secontextname, sizeof(secontextname), " %s", context);
	snprintf(secontextflag, sizeof(secontextflag), " -Z \"%s\"", context);
	freecon(context);
	return 1;
}
/* Find the context which the file should have.  If it doesn't have one listed,
 * assume that it should have the same context which its parent should have,
 * and keep climbing the tree until we run out of tree. */
static int
secontextlookup(const char *program, const char *path, mode_t mode)
{
	char *wpath, *p;
	int ret;
	wpath = strdup(path);
	if (wpath == NULL) {
		fprintf(stderr, "%s: %s\n", program, strerror(errno));
		exit(1);
	}
	do {
		ret = secontextlookupone(wpath, mode);
		if (ret == 0) {
			p = strrchr(wpath, '/');
			if (p != NULL) {
				*p = '\0';
				mode &= ~S_IFCHR;
				mode &= ~S_IFBLK;
				mode |= S_IFDIR;
				mode |= S_IRUSR;
				mode |= S_IWUSR;
				mode |= S_IXUSR;
				mode |= S_IXGRP;
				mode |= S_IXOTH;
			}
		}
	} while ((ret == 0) && (wpath[0] == '/'));
	free(wpath);
	return ret;
}
/* Check if the path has the correct context for cases where it would have the
 * supplied mode.  Return 0 if it's correct, anything else to require
 * relabeling. */
static int
secontextverify(const char *program, const char *path, mode_t mode)
{
	static int enabled = -1;
	security_context_t context;
	int has_context, should_have_context;
	if (enabled == -1) {
		enabled = is_selinux_enabled();
	}
	if (enabled != 1) {
		/* Nod our head and smile. */
		return 0;
	}
	/* Read the configured context for the file. */
	should_have_context = secontextlookup(program, path, mode);
	/* Read the context of the file on the filesystem. */
	context = NULL;
	if (should_have_context) {
		has_context = (lgetfilecon(path, &context) != -1);
		if (!has_context || (context == NULL)) {
			/* The file should have a specific context and has
 			 * none. */
			if (context != NULL) {
				freecon(context);
			}
			return 1;
		}
		/* Compare the context which the file should have to the one
 		 * which it currently has. */
		if (strcmp(context, secontextname + 1) == 0) {
			freecon(context);
			/* Right context. */
			return 0;
		} else {
			/* Wrong context. */
			freecon(context);
			return 1;
		}
	} else {
		/* The file shouldn't have a context.  Nothing we can do about
		 * that. */
	}
	if (context != NULL) {
		freecon(context);
	}
	return 0;
}
/* Return the command-line option for tools which will set the proper mode for
 * the given path, with a space prefixed for display.  Don't actually invoke
 * other tools using the result of this function. */
static char *
secontextgetflag(const char *program, const char *path, mode_t mode)
{
	if (secontextlookup(program, path, mode) == 1) {
		return secontextflag;
	}
	return "";
}
/* Return the name of the file's context, prefixed with a space for display. */
static char *
secontextgetname(const char *program, const char *path, mode_t mode)
{
	if (secontextlookup(program, path, mode) == 1) {
		return secontextname;
	}
	return "";
}
/* Set the proper file creation context for the given path and the given mode,
 * or reset to the default. */
static void
secontextsetup(const char *program, const char *path, mode_t mode)
{
	static int enabled = -1;
	if (enabled == -1) {
		enabled = is_selinux_enabled();
	}
	if (enabled != 1) {
		return;
	}
	if (secontextlookup(program, path, mode) == 1) {
		if (setfscreatecon(secontextname + 1) != 0) {
			fprintf(stderr, "%s: %s: unable to set file creation "
				"context \"%s\"\n", program, path,
				secontextname);
		}
	} else {
		if (setfscreatecon(NULL) != 0) {
			fprintf(stderr, "%s: %s: unable to reset file creation "
				"context\n", program, path);
		}
	}
}
/* Set the supplied file creation context. */
static void
secontextset(const char *program, char *context)
{
	if (is_selinux_enabled() != 1) {
		fprintf(stderr, "Sorry, -Z can be used only with a "
			"selinux-enabled %s.\n", program);
		exit(1);
	}
	if (setfscreatecon(context) != 0) {
		fprintf(stderr, "%s: unable to set file creation "
			"context \"%s\"\n", program, context);
		exit(1);
	}
}
#else
static int
secontextverify(const char *program, const char *path, mode_t mode)
{
	return 0;
}
static char *
secontextgetflag(const char *program, const char *path, mode_t mode)
{
	return "";
}
static char *
secontextgetname(const char *program, const char *path, mode_t mode)
{
	return "";
}
static void
secontextsetup(const char *program, const char *path, mode_t mode)
{
}
static int
secontextset(const char *program, char *context)
{
	fprintf(stderr, "Sorry, -Z can be used only with a selinux-enabled "
		"%s.\n", program);
	exit(1);
}
#endif
