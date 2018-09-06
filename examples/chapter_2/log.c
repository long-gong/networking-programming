#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>
#include <stdarg.h>
#include <string.h>


#define BUFSIZE 1024
#define MAXLOGSZ 100000


static char buf[BUFSIZE];
extern int logfd;

void 
log(const char *fmt, ...)
{
    time_t t;
    char *tm;
    struct stat sbuf;
    va_list ap;

    time(&t);
    tm = ctime(&t);

    tm[24] = '\t';

    strncpy(buf, tm, 25);

    va_start(ap, fmt);
    vsprintf(buf + 25, fmt, ap);
    va_end(ap);


    strcat(buf, "\n");

    if ( fstat(logfd, &sbuf) == 0 ){
        if ( sbuf.st_size > MAXLOGSZ ) 
            ftruncate(logfd, 0);
    }

    write(logfd, buf, strlen(buf);

}

