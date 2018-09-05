//
// Created by saber on 8/16/18.
//

#include <helper.h>

static void
_cmnerr(const char *fmt, va_list ap)
{
  int err = errno;
  vfprintf(stderr, fmt, ap);
  if ( err != 0 )
    fprintf(stderr, ": %s", strerror(err));
  putc('\n', stderr);
}

void
error(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  _cmnerr(fmt, ap);
  va_end(ap);
}

void
fatal(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  _cmnerr(fmt, ap);
  va_end(ap);
  exit(1);
}