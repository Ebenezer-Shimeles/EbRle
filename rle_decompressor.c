#include <stdio.h>

void die(char *msg){
     perror(msg);
     exit(0); //fix this 
}
int main(int argc, char *argv[]){
    char *infile = argv[2];
    char *outfile = argv[1];
    if(!infile || !outfile){ printf("Error in argumetns usage: %s inputfile outputfile", argv[0]);return -1;}
    FILE *in = fopen(infile, "r");
    FILE *out = fopen(outfile, "w+");
    if(!in) die("Error input file is empty");
    unsigned char xc = 0x00;
    while(xc!=(unsigned char)EOF){
          xc = fgetc(in);
          if(xc == (unsigned char)EOF) exit(0);
          if(xc == 0xfe){
                unsigned char count = fgetc(in);
                unsigned char sig = fgetc(in);
                unsigned char i = 0x00;
                for(;i<count;i++) fprintf(out, "%c", sig);
          }
          else if(xc != 0xfe){
               fprintf(out, "%c", xc);
          }
    }
}
