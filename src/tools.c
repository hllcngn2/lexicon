#include "lexicon.h"

int rn(int max){ //0 to max (non included)
/*int n;
do { n =rand() /(RAND_MAX /max+1);
} while (n >max);
return n;}*/
return rand()%max;}

void capitalize(char *str){
if (str[0]>='a'&&str[0]<='z')
	str[0]+='A'-'a';
return;}
void punctuate(char *end_str){
if (rn(3)) *end_str ='.';
else *end_str ='!';
return;}

void	skipwhitechars(FILE *f){
char c; while((c=fgetc(f))==' '||c=='\t');
fseek(f, -1, SEEK_CUR);
return;}
void	skiptonextline(FILE *f){
char c; while((c=fgetc(f))!=EOF && c!='\n');
return;}
