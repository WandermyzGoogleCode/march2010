/*
 * lock.h
 *
 *  Created on: 2010-5-17
 *      Author: spaceflyer
 */

#ifndef LOCK_H_
#define LOCK_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>

static int getExclusiveFd(const char* filename){
	int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR, S_IWUSR);
	flock(fd, LOCK_EX);
	return fd;
}

#endif /* LOCK_H_ */
