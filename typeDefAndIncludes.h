#ifndef __TYPES__
#define __TYPES__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef long int ID;

typedef int BOOL;

typedef struct word{
	ID id;
	char * hungary;
	char * english;
	struct word * next;
	struct word * prev;
} WORD;

#define FALSE 0

#define TRUE 1

#define ASC -1

#define DESC 1

#define HUN 1

#define EN 2

#define ALL 0

#define WORD_WITH_ID 1

#define WORDS 2


#endif
