#include "lexicon.h"
char* makesentstr(int wln, wordlist wl, lexic l, int v);


sentence *makesentence(int wln, wordlist wl, lexic l, int v){
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
	z->w =w;}

z=s;
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
	z->w =w;}
s=z;}
return s;}


char* makesentstr(int wln, wordlist wl, lexic l, int v){
sentence *s =makesentence(wln, wl, l, v);

if(v){	printf("\nhello4\n"); fflush(stdout);}
char *sentstr;
int l_ng =0;
for (sentence *z=s;z;z=z->next)
	l_ng +=strlen(z->w->word)+1;
sentstr =(char*)malloc(l_ng+1); sentstr[0]='\0';
char *str =sentstr;
for (sentence *z=s;z;z=z->next){
	str =stpcpy(str, z->w->word);
	if (z->next && !(z->next->w->pre & NOSPACE)){
		*str =' '; str++; *str ='\0';}}

if(v){	printf("hello5/5\n"); fflush(stdout);}
capitalize(sentstr);
punctuate(str);

//freesentence(s);
return sentstr;}
