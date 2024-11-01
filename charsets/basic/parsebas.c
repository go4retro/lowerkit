/*
    parsebas - Convert TRS80 Model 1 BASIC font data into font binary
    Copyright Jim Brain and RETRO Innovations, 2024

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License only.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writerom(FILE *fp, unsigned char *len, unsigned char data) {
  if(fp != NULL) {
    fputc(data, fp);
    (*len)++;
    if(*len == 12) {
      fputc(0, fp);
      fputc(0, fp);
      fputc(0, fp);
      fputc(0, fp);
      (*len) = 0;
    }
  }
}

int main(int argc, char** argv) {
  
    // Opening file
    FILE *file_ptr, *ofp = NULL;
    unsigned char skip = 0;
    unsigned char data = 0;
    unsigned char len = 0;

    unsigned char ch;

    // Opening file in reading mode
    if(argc > 1) {
      file_ptr = fopen(argv[1], "rb");

      if (NULL == file_ptr) {
          printf("%s file can't be opened \n", argv[1]);
            return EXIT_FAILURE;
      }
    } else {
      fprintf(stderr,"%s <basic extract> [<rom_file>]\n",argv[0]);
    }

    // Opening output file in write mode
    if(argc > 2) {
      ofp = fopen(argv[2], "wb+");

      if (NULL == file_ptr) {
          printf("%s file can't be opened \n", argv[2]);
            return EXIT_FAILURE;
      }
    }

    // Printing what is written in file
    // character by character using loop.
    printf("'");
    for(;;) {
      ch = fgetc(file_ptr);
      if(!feof(file_ptr)) {
        //printf("Found: %2.2X\n",ch);
        if(skip && skip < 5) {
          printf("%2.2X, ",ch);
          skip++;
        } else if(ch == ',') {  // done with font line
          writerom(ofp,&len,data);
          printf("'\n'");
          data = 0;
        } else if(ch == 0 && skip == 0) {
          writerom(ofp,&len,data);
          printf("' Ignoring %2.2X, ",ch);
          skip = 1;
        } else if(skip == 5) {
          printf("%2.2X\n'",ch);
          skip = 0;
          data = 0;
        } else {
            data = data<<1;
          if(ch == 0x58) {
            printf(" ");
          } else {
            data++;
            printf("*");
          }
        }
      } else {
        break;
      }
    }
    // Closing the file
    fclose(file_ptr);
    if(ofp != NULL)
      fclose(ofp);
    return 0;
}
