#include "typeDefAndIncludes.h"
#include "list.h"
#include "stringfv.h"

WORD * head = NULL;
WORD * tail = NULL;
ID id = 0;
long int count = 0;
long int pointer = -1;

WORD ** indexTable = NULL;


int add(WORD word){
	if(head == NULL){
		head = (WORD*)calloc(1, sizeof(WORD));
		if(head == NULL)
			return FALSE;
		head->hungary = (char*) calloc(strlen(word.hungary) + 1, sizeof(char));
		head->english = (char*) calloc(strlen(word.english) + 1, sizeof(char));
		if(head->hungary == NULL || head->english == NULL)
			return FALSE;
		head->prev = NULL;
		head->next = NULL;
		tail = head;
		head->id = id;
		strcpy(head->hungary, word.hungary);
		strcpy(head->english, word.english);
	}else{
		tail->next = (WORD*)calloc(1, sizeof(WORD));
		if(tail->next == NULL)
			return FALSE;
		tail->next->hungary = (char*)calloc(strlen(word.hungary) + 1, sizeof(char));
		tail->next->english = (char*)calloc(strlen(word.english) + 1, sizeof(char));
		if(tail->next->hungary == NULL || tail->next->english == NULL)
			return FALSE;
		tail->next->prev = tail;
		tail->next->next = NULL;
		tail = tail->next;
		strcpy(tail->hungary, word.hungary);
		strcpy(tail->english, word.english);
		tail->id = id;
	}
	addIndex(tail->id, tail);
	id++;
	count++;
	return TRUE;
}

int deleteWord(WORD word){
	WORD * deleteWord = getByID(word.id);
	int result = FALSE;
	if(deleteWord != NULL){
		if(deleteWord == head && deleteWord == tail){
			deleteIndex(deleteWord->id);
			free(head);
			head = NULL;
			tail = NULL;
			count--;
			result = TRUE;
		}else if(deleteWord == head){
			head = deleteWord->next;
			head->prev = NULL;
			deleteIndex(deleteWord->id);
			free(deleteWord);
			count--;
			result = TRUE;
		}else if(deleteWord == tail){
			tail = tail->prev;
			tail->next = NULL;
			deleteIndex(deleteWord->id);
			free(deleteWord);
			count--;
			result = TRUE;
		}else{
			WORD * tmpPrev;
			WORD * tmpNext;
			tmpPrev = deleteWord->prev;
			tmpNext = deleteWord->next;
			tmpPrev->next = tmpNext;
			tmpNext->prev = tmpPrev;
			deleteIndex(deleteWord->id);
			free(deleteWord);
			count--;
			result = TRUE;
		}
	}
	return result;
}

int update(WORD word){
	WORD * updatedWord = getByID(word.id);
	int result = FALSE;
	if(updatedWord != NULL){
		if(word.hungary == NULL){
			free(updatedWord->hungary);
			updatedWord->hungary = "";
		}else{
			strcpy(updatedWord->hungary, word.hungary);
		}
		if(word.english == NULL){
			free(updatedWord->english);
			updatedWord->english = "";
		}else{
			strcpy(updatedWord->english, word.english);
		}
		result = TRUE;
	}
	return result;
}

WORD * getByID(ID retID){
	WORD * word = NULL;
	if(retID < id && retID >= 0){
		word = getByIndex(retID);
	}
	return word;
}

long int getCount(){
	return count;
}

ID getLastID(){
	return id - 1;
}


WORD * getByHungary(char * hungaryWord){
	WORD * word;
	word = NULL;
	long int tmpPointer = getPointer();
	short flag = FALSE;
	setPointerFirst();
	while(hasNext()){
        word = getNext();
        if(compare(hungaryWord, word->hungary) == 0){
            flag = TRUE;
            break;
        }
	}
	if(flag == FALSE)
        word = NULL;
    setPointer(tmpPointer);
	return word;
}


WORD * getByEnglish(char * englishWord){
	WORD * word;
	word = NULL;
	long int tmpPointer = getPointer();
	short flag = FALSE;
	setPointerFirst();
	while(hasNext()){
        word = getNext();
        if(compare(englishWord, word->english) == 0){
            flag = TRUE;
            break;
        }
	}
	if(flag == FALSE)
        word = NULL;
    setPointer(tmpPointer);
	return word;
}


void printWord(WORD * word, int mode){
	if(word != NULL){
        printf("\n");
        switch(mode){
        case 0:
            printf("address: %p\n", word);
            printf("next:    %p\n", word->next);
            printf("prev:    %p\n", word->prev);
        case 1:
            printf("ID:      %lu\n", word->id);
        case 2:
            printf("hun:     %s\n", word->hungary);
            printf("en:      %s\n", word->english);
            break;
        default:
            printf("address: %p\n", word);
            printf("ID:      %lu\n", word->id);
            printf("hun:     %s\n", word->hungary);
            printf("en:      %s\n", word->english);
            printf("next:    %p\n", word->next);
            printf("prev:    %p\n", word->prev);
        }

	}else{
		printf("NULL\n");
	}
}

WORD * getFirst(){
	return head;
}

WORD * getLast(){
	return tail;
}

int hasNext(){
    if(pointer < 0){
        if(head != NULL)
            return TRUE;
        else
            return FALSE;
    }
    WORD * tmp = getByID(pointer);
    if(tmp != NULL){
        if(tmp->next != NULL)
            return TRUE;
    }
    return FALSE;
}

int hasPrev(){
    if(pointer > tail->id){
        if(tail != NULL)
            return TRUE;
        else
            return FALSE;
    }
    WORD * tmp = getByID(pointer);
    if(tmp != NULL){
        if(tmp->prev != NULL)
            return TRUE;
    }
    return FALSE;
}

WORD * getNext(){
    WORD * result = NULL;
    if(pointer < 0){
        if(head != NULL){
            result = head;
        }
    }else{
        WORD * tmp = getByID(pointer);
        if(tmp != NULL){
            result = tmp->next;
        }
    }
    if(result != NULL){
        if(result == tail)
            pointer = tail->id + 1;
        else
            pointer = result->id;
    }
    return result;
}

WORD * getPrev(){
    WORD * result = NULL;
    if(tail != NULL){
        if(pointer > tail->id){
            result = tail;
        }else{
            WORD * tmp = getByID(pointer);
            if(tmp != NULL){
                result = tmp->prev;
            }
        }
        if(result != NULL){
            if(result == head)
                pointer = -1;
            else
                pointer = result->id;
        }
    }
    return result;
}

void setPointerFirst(){
	pointer = -1;
}

void setPointerLast(){
	pointer = tail->id + 1;
}

long int setPointer(ID pointerID){
	if(pointerID >= 0 && pointerID < id)
		pointer = pointerID;
	return pointer;
}

long int getPointer(){
	return pointer;
}

void swapWords(WORD * aWord, WORD * bWord){
	if(aWord != bWord && aWord != NULL && bWord != NULL){
		ID aID = aWord->id;
		ID bID = bWord->id;
		WORD * tmpAPrev = aWord->prev;
		WORD * tmpANext = aWord->next;
		WORD * tmpBPrev = bWord->prev;
		WORD * tmpBNext = bWord->next;
		swapIndex(aID, bID);
		aWord->id = bID;
		bWord->id = aID;
		if(aWord == head && aWord->next == bWord && bWord != tail){
            head = bWord;
            bWord->next = aWord;
            aWord->next = tmpBNext;
            tmpBNext->prev = aWord;
            aWord->prev = bWord;
            bWord->prev = NULL;
		}else if(bWord == head && bWord->next == aWord && aWord != tail){
            head = aWord;
            aWord->next = bWord;
            bWord->next = tmpANext;
            tmpANext->prev = bWord;
            bWord->prev = aWord;
            aWord->prev = NULL;
		}else if(aWord == tail && aWord->prev == bWord && bWord != tail){
            tail = bWord;
            tmpBPrev->next = aWord;
            aWord->next = bWord;
            bWord->next = NULL;
            bWord->prev = aWord;
            aWord->prev = tmpBPrev;
		}else if(bWord == tail && bWord->prev == aWord && aWord != tail){
            tail = aWord;
            tmpAPrev->next = bWord;
            bWord->next = aWord;
            aWord->next = NULL;
            aWord->prev = bWord;
            bWord->prev = tmpAPrev;
		}else if(aWord->next == bWord){
            tmpAPrev->next = bWord;
            bWord->next = aWord;
            aWord->next = tmpBNext;
            tmpBNext->prev = aWord;
            aWord->prev = bWord;
            bWord->prev = tmpAPrev;
		}else if(bWord->next == aWord){
            tmpBPrev->next = aWord;
            aWord->next = bWord;
            bWord->next = tmpANext;
            tmpANext->prev = bWord;
            bWord->prev = aWord;
            aWord->prev = tmpBPrev;
		}else{
            aWord->prev = tmpBPrev;
            aWord->next = tmpBNext;
            bWord->prev = tmpAPrev;
            bWord->next = tmpANext;
            if(aWord == head && bWord != tail){
                tmpBPrev->next = aWord;
                tmpBNext->prev = aWord;
                tmpANext->prev = bWord;
                head = bWord;
            }else if(aWord == head && bWord == tail){
                tmpBPrev->next = aWord;
                tmpANext->prev = bWord;
                head = bWord;
                tail = aWord;
            }else if(aWord != head && aWord != tail && bWord != head && bWord != tail){
                tmpAPrev->next = bWord;
                tmpBPrev->next = aWord;
                tmpBNext->prev = aWord;
                tmpANext->prev = bWord;
            }else if(aWord != tail && bWord == head){
                tmpAPrev->next = bWord;
                tmpANext->prev = bWord;
                tmpBNext->prev = aWord;
                head = aWord;
            }else if(aWord != head && bWord == tail){
                tmpAPrev->next = bWord;
                tmpBPrev->next = aWord;
                tmpANext->prev = bWord;
                tail = aWord;
            }else if(aWord == tail && bWord == head){
                tmpAPrev->next = bWord;
                tmpBNext->prev = aWord;
                head = aWord;
                tail = bWord;
            }else if(aWord == tail && bWord != head){
                tmpBPrev->next = aWord;
                tmpAPrev->next = bWord;
                tmpBNext->prev = aWord;
                tail = bWord;
            }
		}
	}
}


void sort(signed int order, int according){
    if(order > 1 || order < -1 || order == 0)
        order == -1;
    if(according < 1 || according > 2)
        according = 1;
    if(tail != NULL){
        long int lastID = tail->id;
        long int i = 0;
        long int j = 0;
        for(i = lastID; i > 0; i--){
            WORD * pivot = getByID(i);
            if(pivot == NULL)
                continue;
            for(j = i - 1; j >= 0; j--){
                WORD * tmp = getByID(j);
                if(tmp == NULL)
                    continue;
                if(according == 1){
                    if(compare(pivot->hungary, tmp->hungary) == order)
                        pivot = tmp;
                }else{
                    if(compare(pivot->english, tmp->english) == order)
                        pivot = tmp;
                }
            }
            if(pivot != getByID(i))
                swapWords(pivot, getByID(i));
        }
    }
}

/*

index tábla függvények

*/

int addIndex(ID newID , WORD * word){
	WORD ** newIndex = (WORD**)malloc((newID + 1) * sizeof(WORD*));
	if(newIndex == NULL)
		return FALSE;
	if(indexTable == NULL){
		newIndex[0] = word;
	}else{
		int i = 0;
		for(i = 0; i < newID; i++)
			newIndex[i] = indexTable[i];
		newIndex[i] = word;
	}
	indexTable = newIndex;
	return TRUE;
}

int deleteIndex(ID deleteID){
	if(deleteID < id){
		indexTable[deleteID] = NULL;
		return TRUE;
	}
	return FALSE;
}

int swapIndex(ID aID, ID bID){
	if(aID < id && bID < id){
		WORD * tmp;
		tmp = indexTable[aID];
		indexTable[aID] = indexTable[bID];
		indexTable[bID] = tmp;
		return TRUE;
	}
	return FALSE;
}

WORD * getByIndex(ID retID){
	if(retID < id && retID >= 0)
		return indexTable[retID];
	return NULL;
}
