#ifndef LEXICON_H
#define LEXICON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_WORDS 13
#define N_GROUPS 6

//types
#define NONE 1
#define NOSPACE 64
#define SPECIAL 32

#define NOUN 2
#define ARTICLE 4
#define SUBJECT 8
#define ADJECTIVE 16
#define VERB 128

//special cases
#define POSS 2

typedef struct{
	int type;
	int pre, post;
	int spe;
	char *word;
}word;
typedef word** wordlist;

typedef struct{
	int ref;
	int type;
	int pre, post;
	int spe;
	int n;
	wordlist list;
}wordgroup;
typedef wordgroup** lexic;

struct sentence{
	struct sentence *previous, *next;
	word *w;
}; typedef struct sentence sentence;
	

//tools.c
int	rn(int max); //0 to max (non included)
void	capitalize(char*);
void	punctuate(char*);
void	skipwhitechars(FILE*);
void	skiptonextline(FILE*);

//words.c
wordlist	loadwords(void);
wordlist	loadwordsfromfile(int*, const char*, int);
void	freewords(wordlist, int);

//lexic.c
lexic	construct(wordlist, int);
void	freelexic(lexic);

//sentence.c
char* makesentstr(int wln, wordlist wl, lexic l, int v);

#endif
