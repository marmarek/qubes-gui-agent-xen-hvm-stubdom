/*
 * The Qubes OS Project, http://www.qubes-os.org
 *
 * Copyright (C) 2010  Rafal Wojtczuk  <rafal@invisiblethingslab.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
int get_cmd_socket(int domid)
{
	struct sockaddr_un sockname;
	int s;
	char socket_address[40];

	snprintf(socket_address, sizeof(socket_address),
		 "/var/run/qubes/cmd_socket.%d", domid);
	unlink(socket_address);
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	memset(&sockname, 0, sizeof(sockname));
	sockname.sun_family = AF_UNIX;
	memcpy(sockname.sun_path, socket_address, strlen(socket_address));

	if (bind(s, (struct sockaddr *) &sockname, sizeof(sockname)) == -1) {
		printf("bind() failed\n");
		close(s);
		exit(1);
	}
//      chmod(sockname.sun_path, 0666);
	if (listen(s, 5) == -1) {
		perror("listen() failed\n");
		close(s);
		exit(1);
	}
	return s;
}

char *get_line_from_cmd_socket(int s)
{
	static char data[256];
	struct sockaddr_un peer;
	char *ret;
	unsigned int addrlen;
	int fd;
	FILE *file;
	addrlen = sizeof(peer);
	fd = accept(s, (struct sockaddr *) &peer, &addrlen);
	if (fd == -1) {
		perror("unix accept");
		exit(1);
	}
	file = fdopen(fd, "r");
	if (!file) {
		perror("unix fdopen");
		exit(1);
	}
	ret = fgets(data, sizeof(data) - 1, file);
	fclose(file); // this close the "fd", too
	return ret;
}