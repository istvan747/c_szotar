#include "typeDefAndIncludes.h"
#include "stringfv.h"
#include<math.h>

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
    return 0;
}
