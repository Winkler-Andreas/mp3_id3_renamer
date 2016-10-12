#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
  typedef struct
  {
    char filename[128];
    struct NEWFILE *next;
  }NEWFILE;

  unsigned char debug = 1;

#endif // MAIN_H_INCLUDED
