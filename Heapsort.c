#include <stdio.h>
#include <stdlib.h>

typedef struct heap{
	int* head;//stores the pointer to the head of the int arr
	int capacity;//stores the maximum number of elements that can be stored
	int presentElem;//gives the value of the number of elements present in the array
}heap;

void heapify(heap** H,int index);
heap* deleteKey(heap* h, int index);
int parent(int i);
heap* insertKey(heap* h, int data);
heap* BuildHeap(heap* h, int capacity);

int main()
{
	heap* h = NULL;
	int arr[] = {12, 11, 13, 5, 6, 7}, n = 6;//n is the size of the arr
	h = BuildHeap(h, 6);//now create the heap with the array elements
	h->presentElem = h->capacity; //since we initially just copy the arr[] into h->head[]
	int startIdx;
	int capacity = h->capacity;

	//copy the arr[] into h->head[]
	for(int i = 0;i<n;i++)
		h->head[i] = arr[i];

	for(startIdx = n/2; startIdx>=0;startIdx--)
		heapify(&h, startIdx);

	for(int l = 0;l < capacity; l++)
	 	printf("%d ", h->head[l]);
}

int parent(int i)
{
	//return the parent of the elem index
	//0 is the parent of itself
	//else (i-1)/2 is the parent of i
	return (i<=0) ? 0 : (i-1)/2;
}
heap* insertKey(heap* heap, int data)
{
	int presentElem = heap->presentElem;
	int capacity = heap->capacity;
	if(presentElem == capacity)
	{
		printf("No more data could be stored\n");
		return heap;
	}
	heap->head[presentElem] = data;
	heap->presentElem++;
	while(parent(presentElem) > 0)
	{
		int par = parent(presentElem);
		if(heap->head[par] > heap->head[presentElem])
		{
			//then the min_heap property has been
			//violated, and we have to sift up the inserted element
			//until the heap property is no more violated
			int temp = heap->head[par];
			heap->head[par] = heap->head[presentElem];
			heap->head[presentElem] = temp;
		}
		presentElem = par;
	}
	int par = parent(presentElem);
	if(heap->head[par] > heap->head[presentElem])
	{
		int temp = heap->head[par];
		heap->head[par] = heap->head[presentElem];
		heap->head[presentElem] = temp;	
	}
	return heap;
}

heap* deleteKey(heap* h, int index)
{
	//first swap the lastElement to the present index
	//then just heapify the present index
	int presentElem = h->presentElem;
	int capacity = h->capacity;
	if(index > capacity)
		return h;
	else
	{
		h->head[index] = h->head[presentElem-1];
		h->presentElem--;
		heapify(&h, index);
		return h;
	}
}
void heapify(heap** H,int index)
{
	heap* h = *H;
	int l = 2*index + 1;
	int r = 2*index + 2;
	int n = h->capacity;
	int smallest = index;

	if(l<n && h->head[l] < h->head[smallest])
		smallest = l;
	if(r<n && h->head[r] < h->head[smallest])
		smallest = r;
	if(smallest!=index)
	{
		//swap the index
		//with the present smallest
		int temp = h->head[smallest];
		h->head[smallest] = h->head[index];
		h->head[index] = temp;
		heapify(H, smallest);
	}
}
heap* BuildHeap(heap* h, int capacity)
{
	h = (heap*)malloc(sizeof(heap));
	h->capacity = capacity;
	h->head = (int*)malloc(capacity*sizeof(int));
	h->presentElem = 0;
	return h;
}