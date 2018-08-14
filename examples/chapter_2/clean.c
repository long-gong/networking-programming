//
// Created by gtuser on 8/14/18.
//

#include <helper.h>

int clean(FILE *, int);

void
main(int argc, char *argv[])
{
  int c, i, err, verbose, xchar;
  FILE *fp;
  char *fname;

  opterr = err = verbose = 0;
  xchar = EOF;

  while (( c = getopt(argc, argv, "vx:")) != EOF ) {
    switch (c){
      case 'v':
        verbose ++;
        break;
      case 'x':
        if ( xchar != EOF ) {
          err ++;
          break;
        }
        xchar = atoi(optarg);
        if ( (xchar > 255) || (xchar < 0)){
          fprintf(stderr, "-x value out of range\n");
          exit(1);
        }
        break;
      default:
        err ++;
    }
  }

  if ( err ) {
    fprintf(stderr, "usage: clean [-v] [-x char] [files]\n");
    exit(1);
  }

  if ( optind == argc ) {
    c = clean(stdin, xchar);
    if ( verbose )
      fprintf(stderr, "stdin: %d chars cleaned\n", c);
    exit(0);
  }

  for ( i = optind;i < argc;++ i) {
    if ( argv[i][0] == '-' && argv[i][1] == '\n' ) {
      fp = stdin;
      fname = "stdin";
    } else {
      fname = argv[i];
      fp = fopen(fname, "r");
      if ( fp == NULL ) {
        fprintf(stderr, "Cannot open %s: %s\n", fname, strerror(errno));
        continue;
      }
    }
    c =clean(fp, xchar);
    if ( verbose ) fprintf(stderr, "%s: %d chars cleaned\n", fname, c);

    if ( fp != stdin ) fclose(fp);
  }

  exit(err);
}

int
clean(FILE *fp, int xchar)
{
  int c, np;
  np = 0;
  while ((c = getc(fp)) != EOF)
    if (isprint(c) || (c == '\n') || c == '\t' || c == xchar)
      putchar(c);
    else
      np++;
  return (np);
}