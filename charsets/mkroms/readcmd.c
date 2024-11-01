/*
    readcmd - Read CMD file containing font data and create font rom binary
    Copyright Jim Brain and RETRO Innovations, 2024

    This program is heavily based on readcmd:

// readcmd
// Dump the record information for a TRS-80 /CMD
// executable file
//
// License: MIT / X11
// Copyright (c) 2009, 2015, 2023 by James K. Lawless
// See license at https://github.com/jimlawless/readcmd/blob/main/LICENSE
// Source: https://github.com/jimlawless/readcmd
// https://jiml.us
//

  This program is designed to parse /CMD encoded character font files from
  the following archives:

  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a][BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a2][BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a3][BAS].zip
  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/C/Character%20Development%20Program%20for%20Lowerkit%20ROMs%20(1981)(Dennis%20Bathory-Kitsz)[a4][BAS].zip

  and

  http://cpmarchives.classiccmp.org//trs80/Software/Model%201/L/Lowerkit%20II%20ROM%20Development%20v2.0%20(1983)(Dennis%20Bathory-Kitsz-Green%20Mountain%20Micro)[BAS].zip

  (also available at http://cpmarchives.classiccmp.org/trs80/Software/Model%201/C/)

  which are for a TRS-80 Model 1.
*/

#include <stdio.h>

void dumpfontline(unsigned char data) {

  printf("%2.2X '", data );
  for(char i = 0; i < 8; i++) {
    printf("%s", (data & 128 ? "*":" "));
    data = data << 1;
  }
  printf("'\n");
}
 
int main(int argc,char **argv) {
    FILE *fp, *ofp = NULL;
    unsigned char buff[258];
    unsigned int len;
    unsigned short address;
    unsigned char line = 0;
    printf("mkroms v1.00 by Jim Brain\n");
    printf("https://github.com/go4retro/lowerkit\n");
    printf("based on readcmd v1.20 by Jim Lawless\n");
    printf("https://jiml.us/posts/trs80-cmd/\n\n");
    if(argc > 1) {
      fp = fopen(argv[1],"rb");
      if(fp==NULL) {
          fprintf(stderr,"Cannot open file %s\n",argv[1]);
         return 1;
      }
      if(argc > 2) {
        ofp = fopen(argv[2],"wb+");
        if(ofp == NULL) {
          fprintf(stderr,"Cannot open file %s\n",argv[1]);
          return 2;
        }
      }
      for(;;) {
          if(!fread(buff,1,1,fp))
              break;
              // record type is "load block"
          if(*buff==1) {
              fread(buff,1,1,fp);
              len=*buff;
                  // compensate for special values 0,1, and 2.
              if(len<3)
                  len+=256;
                  // read 16-bit load-address
              fread(&address,1,2,fp);
              printf("Reading 01 block, addr %x, length = %u.\n",address,len-2);
              fread(buff,1,len-2,fp);
              for(unsigned int i = 0;i < len - 2;i++) {
                if(line < 12) {
                  dumpfontline(buff[i]);
                } else {
                  printf("%2.2X Ignored\n", buff[i]);
                }
                if(ofp != NULL)
                  fputc(buff[i], ofp);
                line = (line + 1) % 16;
              }
          }
          else
              // record type is "entry address"
          if(*buff==2) {
              fread(buff,1,1,fp);
              len=*buff;
              printf("Reading 02 block length = %u.\n",len);
              fread(&address,1,len,fp);
              if(ofp != NULL) {
                fclose(ofp);
                ofp = NULL;
              }
              printf("Entry point is %d %x\n",address,address);
              printf("Extra ROM data below\n");
              for(;;) {
                if(!fread(buff,1,1,fp))
                  break;
                dumpfontline(buff[0]);
              }
              break;
          }
          else
              // record type is "load module header"
          if(*buff==5) {
              fread(buff,1,1,fp);
              len=*buff;
              printf("Reading 05 block length = %u.\n",len);
              fread(buff,1,len,fp);
              printf("Name: %s\n",buff);
          }
          else {
              printf("Unknown code %u at %lx\n",*buff,ftell(fp)-1L);
              break;
          }
      }
      fclose(fp);
    } else { // not enough parms
      fprintf(stderr, "Usage: %s <cmd_file> [<output>]\n", argv[0]);
    }
}
