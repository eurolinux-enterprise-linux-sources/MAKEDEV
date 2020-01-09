/*
 *  Copyright 2001 Red Hat, Inc.
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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "sel.h"

static void
usage(void)
{
	fprintf(stderr, "Usage: mksock -V\n");
	fprintf(stderr, "       mksock [-v] [-Z context] PATH [...]\n");
}

int
main(int argc, char **argv)
{
	struct sockaddr_un sun;
	int sockfd, r, i, verbose;

	verbose = 0;
	while ((r = getopt(argc, argv, "vVZ:")) != -1) {
		switch (r) {
		case 'v':
			verbose++;
			break;
		case 'Z':
			secontextset("mksock", optarg);
			break;
		case 'V':
			printf("mksock version " VERSION "\n");
			return 0;
		default:
			fprintf(stderr, "mksock version " VERSION "\n");
			usage();
			return 1;
			break;
		}
	}

	if (optind == argc) {
		usage();
		return 1;
	}

	for (i = optind; i < argc; i++) {
		memset(&sun, 0, sizeof(sun));
		sun.sun_family = AF_UNIX;
		snprintf(sun.sun_path, sizeof(sun.sun_path), "%s", argv[i]);

		sockfd = socket(PF_UNIX, SOCK_STREAM, 0);

		r = bind(sockfd, (struct sockaddr*)&sun, sizeof(sun));
		if (r != 0) {
			fprintf(stderr, "mksock: error making %s: %s\n",
				sun.sun_path, strerror(errno));
			exit(1);
		}
		if (verbose) {
			printf("%s\n", argv[i]);
		}
		close(sockfd);
	}

	return 0;
}
