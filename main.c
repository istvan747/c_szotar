#include "typeDefAndIncludes.h"
#include "list.h"
#include "stringfv.h"

//35 byte

//  4294967295

int main(void){
    WORD word;
    word.hungary = "magyar";
    word.english = "angol";

    unsigned long int n = 4000000000;

    printf("lefoglalas...\n");
    unsigned int i = 0;
    for(i = 0; i < n; i++){
        if(add(word) == FALSE){
            printf("nincs eleg memoria...\n");
            break;
        }
    }

    //printf("count: %d db szo eltarolva\n", getCount());
    //sort(ASC, HUN);

    setPointerFirst();
    while(hasNext())
            printWord(getNext(), ALL);


	exit(0);
}
