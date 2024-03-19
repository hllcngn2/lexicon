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

void	freewords(wordlist wl, int wln){
for (int i=0;i<wln;i++){
	free(wl[i]->word);
	free(wl[i]);}
free(wl);
return;}
