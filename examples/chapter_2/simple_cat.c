//
// Created by saber on 8/16/18.
//

#include <helper.h>

#define BUFSIZE (8*1024)
static char buf[BUFSIZE];


extern void error(const char *fmt, ...);
void catreg(int);

void 
main(int argc, char* argv[])
{
 int i, fd;
 for ( i = 1;i < argc; ++ i) {
   if ( (fd = open(argv[1], O_RDONLY)) < 0 ) {
     error("cat: can not open %s", argv[i]);
     continue;
   }
   catreg(fd);
   
 }
  exit (0);
}

void 
catreg(int fd)
{
  int nr, nw;
  
  for (;;) {
    nr = read(fd, buf, BUFSIZE);
    if ( nr > 0 ) {
      errno = 0;
      nw = write(1, buf, nr);
      if ( nw != nr ){
        if ( nw < 0 )
          error("cat: write failed");
        else
          error("cat: short write");
        break;
      }
    } else {
      if ( nr != 0 ) error("cat: read failed");
      break;
    }
  }
}