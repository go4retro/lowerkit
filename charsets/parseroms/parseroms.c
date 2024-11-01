/*
    parseroms - First attempt at parsing /CMD encoded ROM files
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

  This is a quick and dirty program to parse the binary char rom files fromi
  the following archives:

  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a][BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a2][BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a3][BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a4][BAS].zip

  and

  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/L/Lowerkit%20II%20ROM%20Development%20v2.0%20(1983)(Dennis%20Bathory-Kitsz-Green%20Mountain%20Micro)[BAS].zip

  (also available at http://cpmarchives.classiccmp.org/trs80/Software/Model%201/C/)

  which look like they run on a TRS-80 Model 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int c, unsigned char ch) {
  unsigned char v = 128;

  printf("CH: %2.2X %2.2X '", c, ch);
  for(char i = 0; i < 8; i++) {
    printf("%s", (ch & v ? "*":" "));
    v=v/2;
  }
  printf("'\n");
}

int main(int argc, char** argv) {
  
    FILE *file_ptr;
    int i = 0;
    int j = 0;
    int k = 0;
    int c = 0;

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
      if(j < 8) {
        printf("Skipping preamble byte %d (%2.2X:'%c')\n",j,ch,ch);
      } else {
        printf("Byte: %4.4X:",j);
        switch(k) {
          case 0x00:
          case 0x01:
          case 0x02:
          case 0x03:
            printf("Ignoring block value %2.2X\n",ch);
            break;
          default:
            i++;
            switch(i) {
              case 16:
                i = 0;
                c++;
                printf("%2.2X Ignored: ",ch);
                print(0, ch);
                break;
              case 13:
                if(c == 0x7f) {
                  c++;
                  i=1;
                  print(c,ch);
                  break;
                }
              case 14:
              case 15:
                printf("%2.2X Ignored: ",ch);
                print(0, ch);
                break;
              default:
                print(c, ch);
                if(c == 0x7f && i==12)
                  printf("End of main char set.  Extra characters follow\n");
                break;
            }
        }
        k++;
        if(k==0x102)
          k = 0;
      }
      j++;
    }

    // Closing the file
    fclose(file_ptr);
    return 0;
}
