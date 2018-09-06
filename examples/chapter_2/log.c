#include <helper.h>

#define COMPILE_LOG
#define BUFSIZE 1024
#define MAXLOGSZ 100000


#define LOGPERM (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)

static char buf[BUFSIZE];
int logfd = -1;

int 
initlog(const char *logfile)
{
    struct stat sbuf;
    struct group *gp;

    int fl;

    logfd = open(logfile, O_WRONLY|O_APPEND|O_CREAT, LOGPERM);
    if ( logfd < 0 ) return (-1);

    fl = fcntl(logfd, F_GETFD, 0);

    if ( (fl < 0) || (fcntl(logfd, F_SETFD, fl|FD_CLOEXEC) < 0)){
        close(logfd);
        logfd = -1;
        return (-1);
    }

    gp = getgrnam("daemon");
    if ( gp == NULL ) {
        close(logfd);
        logfd = -1;
        errno = EINVAL;
        return (-1);        
    }

    if (fstat(logfd, &sbuf) < 0){
        close(logfd);
        logfd = -1;
        return (-1);
    }

    if ( (sbuf.st_uid != 0) || (sbuf.st_gid != gp->gr_gid))
        fchown(logfd, 0, gp->gr_gid);

    return (0);
}
void 
log_(const char *fmt, ...)
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

    write(logfd, buf, strlen(buf));

}

