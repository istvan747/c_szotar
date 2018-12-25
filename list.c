#include "typeDefAndIncludes.h"
#include "list.h"

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
	if(retID < id){
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

	return word;
}


WORD * getByEnglish(char * englishWord){
	WORD * word;
	word = NULL;

	return word;
}


void printWord(WORD * word){
	if(word != NULL){
		printf("address: %p\n", word);
		printf("ID:      %lu\n", word->id);
		printf("hun:     %s\n", word->hungary);
		printf("en:      %s\n", word->english);
		printf("next:    %p\n", word->next);
		printf("prev:    %p\n", word->prev);
	}else{
		printf("%p\n", word);
	}
}

WORD * getFirst(){
	return head;
}

WORD * getLast(){
	return tail;
}

int hasNext(){
	int i;
	for(i = (pointer+1); i < id; i++){
		if(indexTable[i] != NULL){
			return TRUE;
		}
	}
	return FALSE;
}

int hasPrev(){
	int i;
	for(i = (pointer - 1); i > -1; i--){
		if(indexTable[i] != NULL){
			return TRUE;
		}
	}
	return FALSE;
}

WORD * getNext(){
	WORD * result = NULL;
	while(result == NULL && hasNext()){
			pointer++;
			result = getByID(pointer);
	}
	return result;
}

WORD * getPrev(){
	WORD * result = NULL;
	while(result == NULL && hasPrev()){
		pointer--;
		result = getByID(pointer);
	}
	return result;
}

void setPointerFirst(){
	pointer = -1;
}

void setPointerLast(){
	pointer = id;
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
		aWord->prev = tmpBPrev;
		aWord->next = tmpBNext;
		bWord->prev = tmpAPrev;
		bWord->next = tmpAPrev;
		aWord->id = bID;
		bWord->id = aID;
		if(aWord == head && bWord != tail){
			tmpBPrev->next = aWord;
			tmpBNext->prev = aWord;
			tmpANext->prev = bWord;
		}else if(aWord == head && bWord == tail){
			tmpBPrev->next = aWord;
			tmpANext->prev = bWord;
		}else if(aWord != head && aWord != tail && bWord != head && bWord != tail){
			tmpAPrev->next = bWord;
			tmpBPrev->next = aWord;
			tmpBNext->prev = aWord;
			tmpANext->prev = bWord;
		}else if(aWord != tail && bWord == head){
			tmpAPrev->next = bWord;
			tmpANext->prev = bWord;
			tmpBNext->prev = aWord;
		}else if(aWord != head && bWord == tail){
			tmpAPrev->next = bWord;
			tmpBPrev->next = aWord;
			tmpANext->prev = bWord;
		}else if(aWord == tail && bWord == head){
			tmpAPrev->next = bWord;
			tmpBNext->prev = aWord;
		}else if(aWord == tail && bWord != head){
			tmpBPrev->next = aWord;
			tmpAPrev->next = bWord;
			tmpBNext->prev = aWord;
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
	if(retID < id)
		return indexTable[retID];
	return NULL;
}
