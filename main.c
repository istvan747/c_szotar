#include "typeDefAndIncludes.h"
#include "list.h"
#include "stringfv.h"


int main(void){
    char * aword = "á";
    char * bword = "halihoo";

	printf("%s compare %s: %d", aword, bword, compare(aword, bword));

	exit(0);
}
