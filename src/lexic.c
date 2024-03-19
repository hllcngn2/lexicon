#include "lexicon.h"
wordgroup *extract_type(wordlist wl, int wln, int type);


lexic	construct(wordlist wl, int wln){
lexic	l =(lexic)malloc(N_GROUPS*sizeof(wordgroup*));
l[0] =extract_type(wl, wln, SUBJECT);
l[1] =extract_type(wl, wln, SPECIAL);
l[2] =extract_type(wl, wln, ARTICLE);
l[3] =extract_type(wl, wln, NOUN);
l[4] =extract_type(wl, wln, ADJECTIVE);
l[5] =extract_type(wl, wln, VERB);
	return l;}



wordgroup *extract_type(wordlist wl, int wln, int type){
  wordgroup *new =(wordgroup*)malloc(sizeof(wordgroup));
new->type =type;
//new->pre =0; new->post =0;
int n=0; for (int i=0;i<wln;i++)
	if (wl[i]->type & type) n++;
new->n =n;
new->list =(wordlist)malloc(n*sizeof(word*));
n=0; for (int i=0;i<wln;i++)
	if (wl[i]->type & type){
		new->list[n] =wl[i]; n++;}
	return new;}


void	freelexic(lexic l){
for (int i=0;i<N_GROUPS;i++){
	free(l[i]->list);
	free(l[i]);}
free(l);	return;}
