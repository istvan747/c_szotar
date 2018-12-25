#include "typeDefAndIncludes.h"
#include "list.h"


int main(void){
	WORD word;

	word.id = 7;
	word.hungary = "macska";
	word.english = "cat";
	word.next = NULL;
	word.prev = NULL;

	add(word);

	printWord(getByID(0));

	exit(0);
}
