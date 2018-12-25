#ifndef __TYPES__
#define __TYPES__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned long int ID;

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


#endif
