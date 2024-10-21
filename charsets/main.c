// C program to read a file using fgetc()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(unsigned char ch) {
  unsigned char v = 128;

  printf("%2.2X '", ch);
  for(char i = 0; i < 8; i++) {
    printf("%s", (ch & v ? "*":" "));
    v=v/2;
  }
  printf("'\n");
}

int main(int argc, char** argv) {
  
    // Opening file
    FILE *file_ptr;
    unsigned char array[4096];
    int i = 0;
    int j = 0;

    // Character buffer that stores the read character
    // till the next iteration
    char ch;

    // Opening file in reading mode
    file_ptr = fopen(argv[1], "rb");

    if (NULL == file_ptr) {
        printf("file can't be opened \n");
          return EXIT_FAILURE;
    }

    // Printing what is written in file
    // character by character using loop.
    do {
      ch = fgetc(file_ptr);
      if(j == 8) {
        array[i++] = ch;
      } else {
        printf("Skipping preamble byte %d (%2.2X)\n",j,ch);
        j++;
      }
    } while (!feof(file_ptr) && i <= 4096);

    printf("Found %4.4X bytes\n",i);

    char l = 0;
    for(int k = 0; k < i; k++) {
      printf("Byte: %4.4X:",k);
      l++;
      switch(l) {
        case 1:
        case 2:
        case 3:
          printf("%2.2X Ignored\n",array[k]);
          break;
        case 4:
          printf("%2.2X Ignored\n",array[k]);
          if(array[k] == 0)
            l = 0;
            break;
        case 16:
          printf("\n");
          l = 0;
            break;
        default:
          print(array[k]);
      }
    }

    // Closing the file
    fclose(file_ptr);
    return 0;
}
