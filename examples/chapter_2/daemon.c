#include <helper.h>

extern int logfd;
extern void log_(const char *fmt,...);
extern void fata(const char *fmt,...);
void daemonize(const char *cmd);

int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        fprintf(stderr, "expect 2 arguments");
        exit(1);
    }
    daemonize(argv[1]);

    return 0;
}

void daemonize(const char *cmd)
{
    int i;
    pid_t pid;
    struct rlimit rl;
    char filename[256];

    umask(0);

    sprintf(filename, "/tmp/%s.log", cmd);
    if ( initlog(filename) < 0 )
        fatal("%s: cannot create log file", cmd);
    if ( getrlimit(RLIMIT_NOFILE, &rl) < 0 ){
        fatal("%s: can not get file limit", cmd);
    }
    if ( (pid = fork()) < 0 )
        fatal("%s: cannot fork", cmd);
    else if (pid != 0)
        exit(0);
    setsid();

    sigset(SIGHUP, SIG_IGN);

    if ( (pid = fork()) < 0 )
        fatal("%s: cannot fork", cmd);
    else if (pid != 0)
        exit(0);   

    if ( rl.rlim_max == RLIM_INFINITY )
        rl.rlim_max = 1024;
    for (i = 0;i < rl.rlim_max;++ i)
        if ( i != logfd ) close(i);

    errno = 0;

    if (chdir("/") < 0){
        log_("cannot chdir to /: %s", strerror(errno));
        exit(1);
    }

    if ( (i == open("/dev/null", O_RDWR)) != 0 ){
        if (i < 0) log_("error opening /dev/null: %s", strerror(errno));
        else log_("open /dev/null: expected fd 0, got %d", i);
        exit(1);
    }
    if ( ( i = dup(0) ) != 1 ){
        if ( i < 0 ) log_("dup failed: %s", strerror(errno));
        else log_("dup(0) expected fd 1, got %d",i );
        exit(1);
    }
    if ( ( i = dup(0)) != 2 ) {
        if ( i < 0 ) log_("dup failed: %s", strerror(errno));
        else log_("dup(0) expected fd 2, got %d", i);
        exit(1);
    }

}