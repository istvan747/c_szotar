#include "typeDefAndIncludes.h"
#include "stringfv.h"
#include<math.h>
/*
    ha egyenlõ akkor 0
    ha strA hamarabb van az ABC-ben, akkor 1
    egyébbként -1

*/
signed int compare(char * strA, char * strB){
    int strALength = strlen(strA);
    int strBLength = strlen(strB);
    int minLength = (strALength < strBLength)?strALength:strBLength;
    int i = 0;
    for(i = 0; i < minLength; i++){
        if(strA[i] == strB[i])
            continue;
        if(strA[i] < strB[i])
            return 1;
        else
            return -1;
    }
    if(strALength < strBLength)
        return 1;
    if(strALength > strBLength)
        return -1;
    return 0;
}
