#ifndef _TSLinkedList_h
#define _TSLinkedList_h

#include <stdlib.h>

typedef struct LItem {
	struct LItem* Previous;
	struct LItem* Next;
	void* Data;
	size_t Size;
} ListItem;

typedef struct {
	ListItem* Head;
	int Count;
} List;

List* L_CreateList();
List* L_CreateListFromData(const void* Data, size_t Size, int Count);
void L_FreeList(List* l);
void L_Clear(List* l);

void L_Add(const void* Data, size_t DataLength, List* TargetList);
void L_AddFromArray(const void* Data, size_t Size, int Count, List* TargetList);
int L_Remove(int Index, List* l);

ListItem* L_GetLast(List* l);
ListItem* L_Get(int Index, List* l);
void L_Set(int Index, const void* NewValue, size_t Size, List* l);
void L_Foreach(void (*Enumerator)(const ListItem*, int), List* l);
void L_Break();
List* L_Where(int (*Predicate)(const ListItem*, int), List* l);
int L_CountWhere(int (*Predicate)(const ListItem*, int), List* l);
int L_Contains(const void* Value, size_t Size, int (*Comparator)(const void*, const ListItem*), List* l);

int L_ToInt(const ListItem* Item);
float L_ToFloat(const ListItem* Item);
double L_ToDouble(const ListItem* Item);
char L_ToChar(const ListItem* Item);

void L_AddInt(int Value, List* l);
void L_AddFloat(float Value, List* l);
void L_AddDouble(double Value, List* l);
void L_AddChar(char Value, List* l);

#include "TSLinkedList.c"

#endif