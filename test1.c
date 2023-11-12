#include <stdio.h>
#include <stdlib.h>//malloc,srand
#include <string.h>//strdup,strlen,stpcpy
#include <time.h>//srand
#include "lexicon.h"

int	main(int ac, char **av){
srand((unsigned int)time(NULL));
int v=0;
char *filename;
if (ac >1)	filename =strdup(av[1]);
else		filename =strdup("ng.wl");
if(v)	printf("hello1\n");

int wln; wordlist wl =loadwordsfromfile(&wln, filename, 0);
free(filename);
//wordlist wl =loadwords(); wln=N_WORDS;
if(v){	printf("hello2\n");
	printf("wln=%i\n", wln);
	for (int i=0;i<wln;i++) printf("'%s' %i %i-%i\n",wl[i]->word,wl[i]->type,
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

int n =rn(wln);
sentence *s =(sentence*)malloc(sizeof(sentence));
s->previous = s->next = NULL;
s->w =wl[n];

if(v){	printf("\nhello31\n"); fflush(stdout);}
{sentence *z=s;
while(	!(z->w->post & NONE) //sentence can't end here
	|| ((z->w->post - NONE) && rn(2))){ //coin test
	int g; do{ g =rn(N_GROUPS);
	}while(!(z->w->post & l[g]->type));
	word *w=NULL; do{
		int m =rn(l[g]->n);
		w =l[g]->list[m];
if(v)	printf("trying appending '%s'\n",w->word);
	}while(!(w->pre & z->w->type));
	z->next =(sentence*)malloc(sizeof(sentence));
	z->next->previous =z; z->next->next =NULL;
	z =z->next;
	z->w =w;
}z=s;
if(v){	printf("\nhello32\n"); fflush(stdout);}
while(	!(z->w->pre & NONE) //sentence can't end here
	|| ((z->w->pre - NONE) && rn(2))){ //coin test
	int g; do{ g =rn(N_GROUPS);
	}while(!(z->w->pre & l[g]->type));
	word *w=NULL; do{
		int m =rn(l[g]->n);
		w =l[g]->list[m];
	}while(!(w->post & z->w->type));
	z->previous =(sentence*)malloc(sizeof(sentence));
	z->previous->previous =NULL; z->previous->next =z;
	z =z->previous;
	z->w =w;
}s=z;}


if(v){	printf("\nhello4\n"); fflush(stdout);}
char *nominal_group;
int l_ng =0;
for (sentence *z=s;z;z=z->next)
	l_ng +=strlen(z->w->word)+1;
nominal_group =(char*)malloc(l_ng+1); nominal_group[0]='\0';
char *str =nominal_group;
for (sentence *z=s;z;z=z->next){
	str =stpcpy(str, z->w->word);
	if (z->next && !(z->next->w->pre & NOSPACE)){
		*str =' '; str++; *str ='\0';}}


if(v){	printf("hello5/5\n"); fflush(stdout);}
capitalize(nominal_group);
punctuate(str);
//printf("\nyour word group:  %s", nominal_group); fflush(stdout);
printf("%s ",nominal_group);

free(nominal_group);
//free sentence

}

freelexic(l);
freewords(wl, wln);
if(v){	printf("\nall good\n"); fflush(stdout);}
return 0;}
