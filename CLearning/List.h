#pragma once

#include "Math.h"

#pragma region Create lists
List CreateList(unsigned int startCount, unsigned int varSize)
{
	List l;

	l.l = calloc(startCount, varSize);

	l.count = startCount;
	l.varSize = varSize;

	return l;
}

VoidList CreateVoidList(unsigned int startCount)
{
	VoidList l;

	l.l = (void**)calloc(startCount, sizeof(void*));

	l.count = startCount;

	return l;
}

UIntList CreateUIntList(uint startCount)
{
	UIntList l;

	l.l = (uint*)calloc(startCount, sizeof(uint));

	l.count = startCount;

	return l;
}

Vec3List CreateVec3List(unsigned int startCount)
{
	Vec3List l;

	l.l = (Vec3*)calloc(startCount, sizeof(Vec3));

	l.count = startCount;

	return l;
}

TriList CreateTriList(unsigned int startCount)
{
	TriList l;

	l.l = (Tri*)calloc(startCount, sizeof(Tri));

	l.count = startCount;

	return l;
}

VertexList CreateVertexList(unsigned int startCount)
{
	VertexList l;

	l.l = (Vertex*)calloc(startCount, sizeof(Vertex));

	l.count = startCount;

	return l;
}

ChunkList CreateChunkList(unsigned int startCount)
{
	ChunkList l;

	l.l = (Chunk*)calloc(startCount, sizeof(Chunk));

	l.count = startCount;

	return l;
}


VertexListList CreateNullVertexListList()
{
	VertexListList l;
	l.l = malloc(0);
	l.offsets.l = malloc(0);
	l.offsets.count = 0;
	l.total = 0;
}

#pragma endregion


#pragma region Add to list
void AddToVoidList(VoidList* l, void* item)
{
	l->l = (void**)realloc(l->l, (l->count + 1) * sizeof(void*));
	l->l[l->count] = item;
	l->count++;
}

void AddToUIntList(UIntList* l, uint item)
{
	l->l = (uint*)realloc(l->l, (l->count + 1) * sizeof(uint));
	l->l[l->count] = item;
	l->count++;
}

void AddToVec3List(Vec3List* l, Vec3 item)
{
	l->l = (Vec3*)realloc(l->l, (l->count + 1) * sizeof(Vec3));
	l->l[l->count] = item;
	l->count++;
}

void AddToTriList(TriList* l, Tri item)
{
	l->l = (Tri*)realloc(l->l, (l->count + 1) * sizeof(Tri));
	l->l[l->count] = item;
	l->count++;
}

void AddToVertexList(VertexList* l, Vertex item)
{
	l->l = (Vertex*)realloc(l->l, (l->count + 1) * sizeof(Vertex));
	l->l[l->count] = item;
	l->count++;
}

void AddToChunkList(ChunkList* l, Chunk item)
{
	l->l = (Chunk*)realloc(l->l, (l->count + 1) * sizeof(Chunk));
	l->l[l->count] = item;
	l->count++;
}

#pragma endregion


#pragma region Increase lists
void IncreaseList(List* l, unsigned int amount)
{
	l->l = realloc(l->l, (l->count + amount) * l->varSize);
	l->count += amount;
}

void IncreaseVoidList(VoidList* l, unsigned int amount)
{
	l->l = (void**)realloc(l->l, (l->count + amount) * sizeof(void*));
	l->count += amount;
}

void IncreaseUIntList(UIntList* l, uint amount)
{
	l->l = (uint*)realloc(l->l, (l->count + amount) * sizeof(uint));
	l->count += amount;
}

void IncreaseVec3List(Vec3List* l, unsigned int amount)
{
	l->l = (Vec3*)realloc(l->l, (l->count + amount) * sizeof(Vec3));
	l->count += amount;
}

void IncreaseTriList(TriList* l, unsigned int amount)
{
	l->l = (Tri*)realloc(l->l, (l->count + amount) * sizeof(Tri));
	l->count += amount;
}

void IncreaseVertexList(VertexList* l, unsigned int amount)
{
	l->l = (Vertex*)realloc(l->l, (l->count + amount) * sizeof(Vertex));
	l->count += amount;
}

void IncreaseChunkList(ChunkList* l, unsigned int amount)
{
	l->l = (Chunk*)realloc(l->l, (l->count + amount) * sizeof(Chunk));
	l->count += amount;
}


uint FindTotalOfVertexListList(VertexListList l);
void SetTotalOfVertexListList(VertexListList* l, uint value);

void IncreaseVertexListList(VertexListList* l, uint count)
{
	SetTotalOfVertexListList(l, FindTotalOfVertexListList(*l) + count);

	AddToUIntList(&l->offsets, FindVertCountOfVertexListList(*l));

	l->l = (Chunk*)realloc(l->l, FindTotalOfVertexListList(*l) * sizeof(Vertex));
}

#pragma endregion

#pragma region Find values in list

uint FindVertCountOfVertexListList(VertexListList l)
{
	return l.offsets.l[l.offsets.count - 1];
}

void SetTotalOfVertexListList(VertexListList* l, uint value)
{
	l->offsets.l[l->offsets.count - 1] = value;
}

uint FindVertCountOfChunk(VertexListList l, uint chunkIndex)
{

}

#pragma endregion

#pragma region
void RemoveFromVoidList(VoidList* l, unsigned int index)
{
	l->count--;

	for (int i = index; i < l->count; i++)
		l->l[i] = l->l[i + 1];

	l->l = (void**)realloc(l->l, l->count * sizeof(void*));
}

void RemoveFromVec3List(Vec3List* l, unsigned int index)
{
	l->count--;

	for (int i = index; i < l->count; i++)
		l->l[i] = l->l[i + 1];

	l->l = (Vec3*)realloc(l->l, l->count * sizeof(Vec3));
}

void RemoveFromTriList(TriList* l, unsigned int index)
{
	l->count--;

	for (int i = index; i < l->count; i++)
		l->l[i] = l->l[i + 1];

	l->l = (Tri*)realloc(l->l, l->count * sizeof(Tri));
}

void RemoveFromVertexList(VertexList* l, unsigned int index)
{
	l->count--;

	for (int i = index; i < l->count; i++)
		l->l[i] = l->l[i + 1];

	l->l = (Vertex*)realloc(l->l, l->count * sizeof(Vertex));
}

void RemoveFromChunkList(ChunkList* l, unsigned int index)
{
	l->count--;

	for (int i = index; i < l->count; i++)
		l->l[i] = l->l[i + 1];

	l->l = (Chunk*)realloc(l->l, l->count * sizeof(Chunk));
}

#pragma endregion

void ClearList(List* l)
{
	free(l->l);
	l->count = 0;
	l->varSize = 0;
}

void ClearVoidList(VoidList* l)
{
	free(l->l);
	l->count = 0;
}


// Not really related to lists, but it's used in similar cercumstances.
var CreateVar(unsigned short varSize)
{
	var v;
	v.varSize = varSize;
	v.p = malloc(varSize);
	return v;
}