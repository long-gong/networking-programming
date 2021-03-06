//
// Created by gtuser on 8/14/18.
//

#ifndef NETWORKING_PROGRAMMING_COMMON_H
#define NETWORKING_PROGRAMMING_COMMON_H

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <wait.h>
#include <setjmp.h>
#include <sys/resource.h>
#include <syslog.h>
#include <stdarg.h>
#include <grp.h>


void error(const char *fmt, ...);
void fatal(const char *fmt, ...);
int initlog(const char *logfile);
void log_(const char *fmt, ...);


#endif //NETWORKING_PROGRAMMING_COMMON_H
