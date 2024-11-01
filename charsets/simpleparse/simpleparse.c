/*
    simpleparse - Dump binary file data out as potential font bitmap data
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

void print(int c, unsigned char ch) {
  unsigned char v = 128;

  printf("Byte: %4.4X %2.2X '", c, ch);
  for(char i = 0; i < 8; i++) {
    printf("%s", (ch & v ? "*":" "));
    v=v/2;
  }
  printf("'\n");
}

int main(int argc, char** argv) {
  
    FILE *file_ptr;
    int i = 0;

    unsigned char ch;

    // Opening file in reading mode
    file_ptr = fopen(argv[1], "rb");

    if (NULL == file_ptr) {
        printf("file can't be opened \n");
          return EXIT_FAILURE;
    }

    for (;;) {
      ch = fgetc(file_ptr);
      if(feof(file_ptr))
        break;
      print(i++,ch);
    }

    // Closing the file
    fclose(file_ptr);
    return 0;
}
