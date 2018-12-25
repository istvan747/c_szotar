#include "typeDefAndIncludes.h"

extern int add(WORD);	//kész

extern int deleteWord(WORD);	//kész

extern int update(WORD);	//kész

extern WORD * getByID(ID);	//kész

extern WORD * getByHungary(char *);

extern WORD * getByEnglish(char *);

extern long int getCount();	//kész

extern void printWord(WORD * );	//kész

extern WORD * getFirst();	//kész

extern WORD * getLast();	//kész

extern WORD * getNext();	//kész

extern WORD * getPrev();	//kész

extern int hasNext();	//kész

extern int hasPrev();	//kész

extern ID getLastID();	//kész

extern void swapWords(WORD *, WORD *);	//kész

extern void setPointerFirst(); //kész

extern void setPointerLast();	//kész

extern long int setPointer(ID id);	//kész

extern long int getPointer();	//kész

extern void sortByHungaryDecreasing();

extern void sortByHungaryAscendant();

extern void sortByEnglishDecreasing();

extern void sortByEnglishAscendant();


/*

index tábla függvények

*/

extern int addIndex(ID , WORD *); //kész

extern int deleteIndex(ID); //kész

extern int swapIndex(ID, ID); //kész

extern WORD * getByIndex(ID);	//kész
