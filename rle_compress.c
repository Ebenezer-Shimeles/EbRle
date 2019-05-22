#include <stdio.h>
#include <string.h>
void die(char *msg){
     perror(msg);
     exit(0); //fix this 
}
//this compressor cannot compress file that contain 0xfe
int main(int argc, char *argv[]){
    char *infile = argv[2];
    char *outfile = argv[1];
    if(!infile || !outfile){ printf("Error in argumetns usage: %s inputfile outputfile", argv[0]);return -1;}
    FILE *in = fopen(infile, "r");
    FILE *out = fopen(outfile, "w+");
    if(!in) die("Error input file is empty");
    unsigned char xc = (unsigned char)0x00;
    unsigned char tmp = 0xfe;
    char output =0;
    unsigned char count = 0x01; //cannot be 255 max 254
    while(xc != (unsigned char)EOF){
             output =0;
             xc = fgetc(in);
             if(xc == (unsigned char)EOF){
                   if(count == 0x01) fprintf(out, "%c", tmp);
                   if(output==0){
                       unsigned char j = 0x00;
                       //while(j<count){ fprintf(out, "%c", tmp);j++;}
                       if(count >= 0x03){ fprintf(out, "%c%c%c", 0xfe, count, tmp); output=1;}
                       else if(count < 0x03){
                            unsigned char j = 0x00;
                            for(;j<count;j++){ fprintf(out, "%c", tmp); output=1;}
                       }
                   } 
                   exit(0);
              }
             if(xc == 0xfe) die("Error could not compress file");
             if(tmp == xc){count ++;if(count==254) goto OUT;} //fix 255
             else if(tmp != xc){
                  puts("New stuff gotten");
                  if(tmp == 0xfe){tmp =xc; }//begining
                  else if(tmp !=0xfe){
                       OUT:
                       //check for relevancy of compression
                       if(count >= 0x03){ fprintf(out, "%c%c%c", 0xfe, count, tmp); output=1;}
                       else if(count < 0x03){
                            unsigned char i = 0x00;
                            for(;i<count;i++){ fprintf(out, "%c", tmp); output=1;}
                       }
                       count = 0x01;
                       tmp = xc;
                  }
             }
    }
}
