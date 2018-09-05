//
// Created by saber on 8/16/18.
//
#include <helper.h>


#define BUFSIZE (8*1024)
static char buf[BUFSIZE];

extern void error(const char *fmt, ...);

int catmap(int);
void catreg(int);


void
main(int argc, char *argv[])
{
  int i, fd;

  for ( i = 1;i < argc;++ i)
  {
    if (( fd = open(argv[i], O_RDONLY)) < 0 ){
      error("cat: cannot open %s", argv[i]);
      continue;
    }
    if ( catmap(fd) < 0 )
      catreg(fd);
    close(fd);
  }
  exit(0);
}

int
catmap(int fd)
{
  int nw;
  caddr_t  addr;
  struct stat sbuf;

  if ( fstat(fd, &sbuf) < 0 ) return -1;
  addr = mmap(0, sbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

  if ( addr == (caddr_t)-1 ) return -1;

  errno = 0;
  nw = write(1, addr, sbuf.st_size);
  if (nw != sbuf.st_size ) {
    if (nw < 0) error("cat: write failed");
    else error("cat: short write");
  }
  munmap(addr, sbuf.st_size);

  return 0;
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