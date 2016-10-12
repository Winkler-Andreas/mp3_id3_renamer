#include <stdio.h>
#include <dirent.h>
#include "main.h"

#define WIN
//#define NIX

/********TO-DO***************
- if(de->d_type == 8) is working for Linux
  -> windows equivalent needed

- fread() -> volle Länge des möglich ID3 Tags auslesen
  auf ID3 checken und dann ID3 Tag auslesen


*** Help stuff / research ***
The stat() function tells you all about a particular file.
fread() to open file and read first bytes

****************************/


NEWFILE * filelist_creation(NEWFILE *);
NEWFILE * file_checker(NEWFILE *);



int main()
{
  NEWFILE *file_array = filelist_creation(&file_array);   // return value is the pointer to the first entry
  NEWFILE *filelist_start = file_array;
  NEWFILE *error_files;

  printf("*******************************************************\n");
  printf("MAKE SURE THAT THERE ARE ___ONLY___ FILES IN THE FOLDER\n");
  printf("*******************************************************\n\n");
  printf("*******************************************************\n");
  printf("MAKE SURE THAT THERE ARE ___ONLY___ FILES IN THE FOLDER\n");
  printf("*******************************************************\n\n");
  printf("*******************************************************\n");
  printf("MAKE SURE THAT THERE ARE ___ONLY___ FILES IN THE FOLDER\n");
  printf("*******************************************************\n\n");


  printf("> Following files are available in the current folder:\n");
  while(file_array->next != NULL)
  {
    printf("%s\n",file_array->filename);
    file_array = file_array->next;
  }

  printf("\n> Scanning files for mp3s.\n");
 // error_files = file_checker(filelist_start);

  return 0;
}

// function creates a linked list with all files
// return value is the pointer to the first entry
NEWFILE * filelist_creation(NEWFILE *file_array_f)
{
  file_array_f = malloc(sizeof(NEWFILE));
  NEWFILE *array_start = file_array_f;

  FILE *rm;
  char buf[4];


    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("."); //(.) -> öffent aktuelles Verzeichnis

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
    else
    {
      while ((de = readdir(dr)) != NULL)  // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
      {
        #ifdef NIX
        if(de->d_type == 8) // not working with windows
        #endif
        {
          if(strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0) continue; // excluding . and ..


          rm = fopen(de->d_name, "r");
          //printf("Checking file \"%s\":\n",de->d_name);
          if (rm != NULL)
          {
            fread(buf, 1, 4, rm);
            buf[(sizeof buf)-1] = 0;
            fclose(rm);

            if(strcmp(buf, "ID3") != 0)
            {
              if(debug == 1) printf("DEBUG: X File %s: NOT added to the list.\n", de->d_name);
              continue;
              /*
              search for MP3 Frame header to check if it is an MP3 file.
              if(es ist keine MP3) continue; //ansonsten wird es in der Liste aufgenommen.
              */
            }

          }
          if(debug == 1) printf("DEBUG: OK File %s: identified as MP3 -> added to the list.\n", de->d_name);
          strcpy(file_array_f->filename, de->d_name);
          #ifdef NIX
          printf("%i\n", de->d_type);
          #endif
          file_array_f->next = malloc(sizeof(NEWFILE));
          file_array_f = file_array_f->next;
        }
      }
      file_array_f->next=NULL;
      //file_array_f = array_start;
      closedir(dr);
    }
  printf("\n\n");
  return array_start;
}

NEWFILE * file_checker(NEWFILE *file_array_f)
{
  FILE *rm;
  char buf[4];

  while(file_array_f->next != NULL)
  {
    rm = fopen(file_array_f->filename, "r");
    printf("Checking file \"%s\":\n",file_array_f->filename);
    if (rm != NULL)
    {
      fread(buf, 1, 4, rm);
      buf[(sizeof buf)-1] = 0;
      //printf("%s", buf);
      fclose(rm);
    }
    else
    {
      printf("Not a file / File Not Found / Could not open.\n\n");
      file_array_f = file_array_f->next;
      continue;
    }

    if(strcmp(buf, "ID3") == 0)
    {
      printf("ID3 Tag found\n\n");
    }
    else
    {
      printf("No ID3 Tag\n\n");
    }
    file_array_f = file_array_f->next;
  }

 return 0;

}
