#include <stdio.h>
#include <stdlib.h>//malloc/free
#include <string.h>//strdup,strcmp
#include "lexicon.h"

char	*freadword(int *len, FILE* f, char delim){
int l=0; for (char c; (c=fgetc(f))!=EOF && c!='\t' && c!='\n'; l++)
	if (delim && c==delim) break;
char *w =(char*)malloc(l+1); w[l]='\0';
fseek(f, -l-1, SEEK_CUR); for (int i=0;i<l;i++) w[i]=fgetc(f);
{char c; if (delim && (c=fgetc(f))!=delim) fseek(f, -1, SEEK_CUR);}
*len=l; return w;}

int	freadtype(FILE *f, int v){
int t=0; {char c; int vv=0;
if(v)		putchar('\t');
do{ int l; char *w =freadword(&l, f, '|');
if	(!strcmp(w, "NONE"))	{t=t|NONE;	vv+=NONE;}
else if (!strcmp(w, "NOUN"))	{t=t|NOUN;	vv+=NOUN;}
else if (!strcmp(w, "ADJECTIVE")){t=t|ADJECTIVE;vv+=ADJECTIVE;}
else if (!strcmp(w, "ARTICLE")) {t=t|ARTICLE;	vv+=ARTICLE;}
else if (!strcmp(w, "SPECIAL")) {t=t|SPECIAL;	vv+=SPECIAL;}
else if (!strcmp(w, "SUBJECT")) {t=t|SUBJECT;	vv+=SUBJECT;}
else if (!strcmp(w, "VERB"))	{t=t|VERB;	vv+=VERB;}
else if (!strcmp(w, "NOSPACE")) {t=t|NOSPACE;	vv+=NOSPACE;}
if(v)		printf("%s", w);
free(w);
}while((c=fgetc(f)) && !fseek(f, -1, SEEK_CUR)
	       && c!='\t' && c!='\n' && ((v && putchar('|'))||1));
if(v)		printf("(%i)", vv);}
return t;}

wordlist	loadwordsfromfile(int *wln, const char *path, int v){
if(v)	printf("-reading words from file '%s'-\n", path);
FILE *f =fopen(path, "r");
int nmax=0; for (char c; (c=fgetc(f))!=EOF;) if(c=='\n') nmax++;
if(v)	printf("max number of words: %i\n", nmax);

wordlist wb =(wordlist)malloc(nmax*sizeof(word*));
for (int i=0;i<nmax;i++) wb[i] =(word*)malloc(sizeof(word));
rewind(f); int n=0; for (int i=0;i<nmax;i++){
	int l; char *w =freadword(&l, f, 0);

	if (w[0]==' '){
	if(v)	printf("l#%i skipped word '%s'\n",i+1,w);
		free(w);}
	else if (l==0){
	if(v)	printf("l#%i skipped empty line\n",i+1);
		free(w);
		fseek(f, -l, SEEK_CUR);}

	else{	if (w[0]=='"'){
			fseek(f, -l+1, SEEK_CUR);
			free(w); w =freadword(&l, f, '"');}
		wb[n]->word =w;
	if(v)	printf("l#%i read word#%i '%s'",i+1,n-1,w);
		skipwhitechars(f); wb[n]->type =freadtype(f,v);
		skipwhitechars(f); wb[n]->pre =freadtype(f,v);
		skipwhitechars(f); wb[n]->post =freadtype(f,v);
		//skipwhitechars(f); wb[n]->spe =freadtype(f);
		n++;
	if(v)	printf("\n");}

	skiptonextline(f);}
if(v)	printf("actual number of words: %i\n\n", n);

wordlist wl =(wordlist)malloc(n*sizeof(word*));
for (int i=0;i<n;i++) wl[i] =wb[i];
for (int i=n;i<nmax;i++) free(wb[i]);
free(wb);
*wln=n; return wl;}




wordlist	loadwords(void){
wordlist wl =(word**)malloc(N_WORDS*sizeof(word*));
for (int i=0;i<N_WORDS;i++) wl[i] =(word*)malloc(sizeof(word));

wl[0]->word =strdup("Ariadre");
wl[1]->word =strdup("it");
wl[2]->word =strdup("darkmage");
wl[9]->word =strdup("Destiny");
wl[0]->type =SUBJECT;
wl[1]->type =SUBJECT;
wl[2]->type =SUBJECT;
wl[9]->type =SUBJECT;
wl[0]->pre =NONE; wl[0]->post =SPECIAL | NONE;
wl[1]->pre =NONE; wl[1]->post =NONE;
wl[2]->pre =NONE; wl[2]->post =SPECIAL | NONE;
wl[9]->pre =NONE; wl[9]->post =SPECIAL | NONE;
wl[0]->spe =POSS;
wl[2]->spe =POSS;
wl[9]->spe =POSS;

wl[3]->word =strdup("she");
wl[3]->type =SUBJECT;
wl[3]->pre =NONE; wl[3]->post =NONE;

wl[4]->word =strdup("'s");
wl[4]->type =SPECIAL;
wl[4]->spe =POSS;
wl[4]->pre =SUBJECT | NOSPACE; wl[4]->post =NOUN;

wl[5]->word =strdup("the");
wl[6]->word =strdup("her");
wl[7]->word =strdup("his");
wl[8]->word =strdup(""); //<==
wl[5]->type =ARTICLE;
wl[6]->type =ARTICLE;
wl[7]->type =ARTICLE;
wl[8]->type =ARTICLE;
wl[5]->pre =NONE; wl[5]->post =NOUN;
wl[6]->pre =NONE; wl[6]->post =NOUN;
wl[7]->pre =NONE; wl[7]->post =NOUN;
wl[8]->pre =NONE; wl[8]->post =NOUN;

wl[10]->word =strdup("insects");
wl[11]->word =strdup("word");
wl[12]->word =strdup("number");
wl[10]->type =SUBJECT | NOUN;
wl[11]->type =NOUN;
wl[12]->type =NOUN;
wl[10]->pre =ARTICLE | SPECIAL | NONE; wl[10]->post =NONE;
wl[11]->pre =ARTICLE | SPECIAL; wl[11]->post =NONE;
wl[12]->pre =ARTICLE | SPECIAL; wl[12]->post =NONE;
wl[10]->spe =POSS;
wl[11]->spe =POSS;
wl[12]->spe =POSS;

return wl;}


void	freewords(wordlist wl, int wln){
for (int i=0;i<wln;i++){
	free(wl[i]->word);
	free(wl[i]);}
free(wl);
return;}
