/*
    drawsvg - Create SVG of font rom binary
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

#define xp 4

void print(int pos, int row, unsigned char ch) {
  unsigned char v = 128;

  if(row < 12) {
    for(char i = 0; i < 8; i++) {
      if(ch & v)
        printf("<rect width=\"%d\" height=\"%d\" y=\"%d\" x=\"%d\" fill=\"darkgreen\" />\n",xp,xp,(pos/32)*13*xp+(row*xp)+xp,(pos%32)*9*xp+(i*xp)+xp);
      else
        printf("<rect width=\"%d\" height=\"%d\" y=\"%d\" x=\"%d\" fill=\"lawngreen\" />\n",xp,xp,(pos/32)*13*xp+(row*xp)+xp,(pos%32)*9*xp+(i*xp)+xp);
      v=v/2;
    }
  }
}

int main(int argc, char** argv) {
  
    FILE *file_ptr;

    unsigned char ch;

    // Opening file in reading mode
    file_ptr = fopen(argv[1], "rb");

    if (NULL == file_ptr) {
        printf("file can't be opened \n");
          return EXIT_FAILURE;
    }

    printf("<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n",32*xp*9+xp,4*13*xp+xp);
    printf("<rect width=\"%d\" height=\"%d\" fill=\"black\" />\n",32*xp*9+xp,4*13*xp+xp);

    for (int i = 0; i < 128;i++) {
      for(int l = 0;l<16;l++) {
        ch = fgetc(file_ptr);
        if(feof(file_ptr))
          break;
        print(i,l,ch);
      }
    }
    printf("Sorry, your browser does not support inline SVG.  \n</svg>\n");

    // Closing the file
    fclose(file_ptr);
    return 0;
}
