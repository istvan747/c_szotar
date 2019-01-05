#ifndef __LIST__
#define __LIST__

#include "typeDefAndIncludes.h"

extern int add(WORD);	//k�sz

extern int deleteWord(WORD);	//k�sz

extern int update(WORD);	//k�sz

extern WORD * getByID(ID);	//k�sz

extern WORD * getByHungary(char *);

extern WORD * getByEnglish(char *);

extern long int getCount();	//k�sz

extern void printWord(WORD *, int);	//k�sz

extern WORD * getFirst();	//k�sz

extern WORD * getLast();	//k�sz

extern WORD * getNext();	//k�sz

extern WORD * getPrev();	//k�sz

extern int hasNext();	//k�sz

extern int hasPrev();	//k�sz

extern ID getLastID();	//k�sz

extern void swapWords(WORD *, WORD *);	//k�sz

extern void setPointerFirst(); //k�sz

extern void setPointerLast();	//k�sz

extern long int setPointer(ID id);	//k�sz

extern long int getPointer();	//k�sz

extern void sortBy(signed int, int); //k�sz


/*

index t�bla f�ggv�nyek

*/

extern int addIndex(ID , WORD *); //k�sz

extern int deleteIndex(ID); //k�sz

extern int swapIndex(ID, ID); //k�sz

extern WORD * getByIndex(ID);	//k�sz

#endif // __LIST__
