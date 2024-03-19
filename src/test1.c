#include "lexicon.h"

int	main(int ac, char **av){
srand((unsigned int)time(NULL));
int v=0;

char *filename;
if (ac >1)	filename =strdup(av[1]);
else		filename =strdup("ng.wl");
char *filepath =(char*)malloc(10+strlen(filename)+1);
strcpy(filepath,"wordlists/");
strcat(filepath,filename);
free(filename);
if(v)	printf("hello1\n");

int wln; wordlist wl =loadwordsfromfile(&wln, filepath, 0);
free(filepath);
if(v){	printf("hello2\n");
	printf("wln=%i\n", wln);
	for (int i=0;i<wln;i++)
		printf("'%s' %i %i-%i\n",wl[i]->word,wl[i]->type,
		wl[i]->pre,wl[i]->post);
	fflush(stdout);}

lexic l =construct(wl, wln);
if(v){	printf("\nhello3");
	for (int i=0;i<N_GROUPS;i++){
	printf("\ngroup no%i:",i);
	for (int j=0;j<l[i]->n;j++)
		printf("'%s',",l[i]->list[j]->word);}
	fflush(stdout);}

printf("-hllcngn's lexicon - test 1-\n");
for (int x=0; x<10; x++){
char *sentstr =makesentstr(wln, wl, l, v);
printf("%s ",sentstr);
free(sentstr);}

freelexic(l);
freewords(wl, wln);
if(v){	printf("\nall good\n"); fflush(stdout);}
return 0;}
