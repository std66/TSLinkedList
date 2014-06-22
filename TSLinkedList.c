#include "TSLinkedList.h"

#include <stdlib.h>
#include <string.h>

int L_Loop_Break = 0;

List* L_CreateList() {
	List* Result = (List*) malloc(sizeof(List));
	
	Result->Head = NULL;
	Result->Count = 0;
	
	return Result;
}

void FreeListItem(ListItem* Item) {
	free(Item->Data);
	free(Item);
}

void L_FreeList(List* l) {
	ListItem* CurrentItem = l->Head;
	
	while (CurrentItem != NULL) {
		ListItem* temp = CurrentItem;
		CurrentItem = CurrentItem->Next;
		
		FreeListItem(temp);
	}
	
	free(l);
}

void L_Add(const void* Data, size_t DataLength, List* TargetList) {
	ListItem* NewItem = (ListItem*) malloc(sizeof(ListItem));
	
	NewItem->Size = DataLength;
	NewItem->Data = malloc(DataLength);
	NewItem->Next = NULL;
	
	memcpy(NewItem->Data, Data, DataLength);
	
	ListItem* LastItem = L_GetLast(TargetList);
	NewItem->Previous = LastItem;
	
	if (LastItem == NULL) {
		TargetList->Head = NewItem;
	}
	else {
		LastItem->Next = NewItem;
	}
	
	TargetList->Count++;
}

ListItem* L_GetLast(List* l) {
	ListItem* CurrentItem = l->Head;
	
	if (CurrentItem == NULL) {
		return NULL;
	}
	
	while (CurrentItem != NULL) {
		if (CurrentItem->Next == NULL) {
			return CurrentItem;
		}
		
		CurrentItem = CurrentItem->Next;
	}
}

ListItem* L_Get(int Index, List* l) {
	if (l->Count - 1 < Index)
		return NULL;
	
	ListItem* CurrentItem = l->Head;
	int CurrentIndex = 0;
	
	while (CurrentItem != NULL) {
		if (CurrentIndex == Index)
			return CurrentItem;
		
		CurrentIndex++;
		CurrentItem = CurrentItem->Next;
	}
	
	return NULL;
}

void L_Set(int Index, const void* NewValue, size_t Size, List* l) {
	int CurrentIndex = 0;
	ListItem* CurrentItem = l->Head;
	
	while (CurrentItem != NULL) {
		if (CurrentIndex == Index) {
			free(CurrentItem->Data);
			CurrentItem->Data = malloc(Size);
			memcpy(CurrentItem->Data, NewValue, Size);
			CurrentItem->Size = Size;
			
			break;
		}
		
		CurrentIndex++;
		CurrentItem = CurrentItem->Next;
	}
}

int L_Remove(int Index, List* l) {
	if (l->Count - 1 < Index)
		return 0;
		
	ListItem* ToRemove = L_Get(Index, l);
	
	if (ToRemove == NULL)
		return 0;
	
	ListItem* Next = ToRemove->Next;
	ListItem* Previous = ToRemove->Previous;
	
	FreeListItem(ToRemove);
	
	if (Next != NULL)
		Next->Previous = Previous;
		
	if (Previous != NULL)
		Previous->Next = Next;
	else
		l->Head = Next;
		
	l->Count--;
	
	return 1;
}

List* L_CreateListFromData(const void* Data, size_t Size, int Count) {
	List* Result = L_CreateList();
	
	L_AddFromArray(Data, Size, Count, Result);
	
	return Result;
}

void L_AddFromArray(const void* Data, size_t Size, int Count, List* TargetList) {
	int Current;
	for (Current = 0; Current < Count; Current++) {
		L_Add(Data + Size*Current, Size, TargetList);
	}
}

void L_Foreach(void (*Enumerator)(const ListItem*, int), List* l) {
	L_Loop_Break = 0;

	ListItem* CurrentItem = l->Head;
	int CurrentIndex = 0;
	
	while (CurrentItem != NULL) {
		Enumerator((const void*)CurrentItem, CurrentIndex);
		
		if (L_Loop_Break)
			break;
		
		CurrentIndex++;
		CurrentItem = CurrentItem->Next;
	}
	
	L_Loop_Break = 0;
}

void L_Break() {
	L_Loop_Break = 1;
}

int L_Contains(const void* Value, size_t Size, int (*Comparator)(const void*, const ListItem*), List* l) {
	ListItem* CurrentItem = l->Head;
	
	while (CurrentItem != NULL) {
		if (Comparator(Value, CurrentItem))
			return 1;
		
		CurrentItem = CurrentItem->Next;
	}
	
	return 0;
}

int L_ToInt(const ListItem* Item) {
	return *((int*)Item->Data);
}

void L_AddInt(int Value, List* l) {
	L_Add((void*)&Value, sizeof(int), l);
}

float L_ToFloat(const ListItem* Item) {
	return *((float*)Item->Data);
}

void L_AddFloat(float Value, List* l) {
	L_Add((void*)&Value, sizeof(float), l);
}

double L_ToDouble(const ListItem* Item) {
	return *((double*)Item->Data);
}

void L_AddDouble(double Value, List* l) {
	L_Add((void*)&Value, sizeof(double), l);
}

char L_ToChar(const ListItem* Item) {
	return *((char*)Item->Data);
}

void L_AddChar(char Value, List* l) {
	L_Add((void*)&Value, sizeof(char), l);
}

List* L_Where(int (*Predicate)(const ListItem*, int), List* l) {
	List* Result = L_CreateList();
	
	ListItem* CurrentItem = l->Head;
	int Index = 0;
	while (CurrentItem != NULL) {
		if (Predicate(CurrentItem, Index)) {
			L_Add(CurrentItem->Data, CurrentItem->Size, Result);
		}
		CurrentItem = CurrentItem->Next;
		Index++;
	}
	
	return Result;
}

int L_CountWhere(int (*Predicate)(const ListItem*, int), List* l) {
	int Result = 0;

	ListItem* CurrentItem = l->Head;
	int Index = 0;
	while (CurrentItem != NULL) {
		if (Predicate(CurrentItem, Index)) {
			Result++;
		}
		CurrentItem = CurrentItem->Next;
		Index++;
	}
	
	return Result;
}

void L_Clear(List* l) {
	int Index = l->Count - 1;
	
	while (l->Count > 0) {
		L_Remove(Index, l);
		Index--;
	}
}