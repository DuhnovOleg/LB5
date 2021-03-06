#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <stack>
#include <queue>
using namespace std;

typedef struct List
{
	int data;
	List* next;
}List;

typedef struct Queue
{
	int size;
	List* Front;
	List* Back;
}Queue;

typedef struct Node
{
	int vertex;
	Node* Next;
};

typedef struct Graf
{
	int number;
	Node** Array;
};

Node* Initialization(int vert)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->vertex = vert;
	node->Next = NULL;
	return node;
}

Graf* Initialization_Graf(int n)
{
	Graf* graf = (Graf*)malloc(sizeof(Graf));
	graf->number = n;
	graf->Array = (Node**)malloc(n * sizeof(Node*));
	for (int i = 0; i < n; i++)
		graf->Array[i] = NULL;
	return graf;
}

void add_spisok(int i, int j, Graf* graf)
{
	Node* NewNode = Initialization(j);
	if (graf->Array[i] == NULL)
	{
		graf->Array[i] = NewNode;
		NewNode = NULL;
	}
	Node* temp = graf->Array[i];
	while (temp->Next != NULL)
		temp = temp->Next;
	temp->Next = NewNode;
	NewNode = Initialization(i);
	if (graf->Array[j] == NULL)
	{
		graf->Array[j] = NewNode;
		NewNode = NULL;
	}
	temp = graf->Array[j];
	while (temp->Next != NULL)
		temp = temp->Next;
	temp->Next = NewNode;
}

void print(Graf* graf)
{
	for (int i = 0; i < graf->number; i++)
	{
		Node* temp = graf->Array[i];
		printf("%d - ?? ???????: ", i + 1);
		while (temp)
		{
			printf("%d ", temp->vertex + 1);
			temp = temp->Next;
		}
		printf("\n");
	}
}

void init(Queue* Que)
{
	Que->Front = new List;
	Que->Front->next = NULL;
	Que->Back = Que->Front;
	Que->size = 0;
}

bool Empty(Queue* Que)
{
	if (Que->Back == Que->Front)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Push(Queue* Que, int value)
{
	Que->Back->next = new List;
	Que->Back = Que->Back->next;
	Que->Back->data = value;
	Que->Back->next = NULL;
	Que->size++;
}

void Pop(Queue* Que)
{
	List* p;
	p = Que->Front;
	Que->Front = Que->Front->next;
	Que->size--;
	free(p);
}

int _Front(Queue* Que)
{
	return Que->Front->next->data;
}

void BFS_QUEUE(int n, bool* Arr2, int i, int** Arr)
{
	Queue Que;
	init(&Que);
	Push(&Que, 0);
	Arr2[i] = true;

	while (Empty(&Que))
	{
		i = _Front(&Que);
		Pop(&Que);
		printf("%d ", i + 1);

		for (int j = 1; j < n; j++)
		{
			if (Arr[i][j] == 1 && Arr2[j] == false)
			{
				Push(&Que, j);
				Arr2[j] = true;
			}
		}
	}
}

int** create_arr(int n)
{
	int s = 1;
	int** Arr;

	Arr = (int**)malloc(n * sizeof(int*));
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		Arr[i] = (int*)malloc(n * sizeof(int));
		Arr[i][i] = 0;

		for (int j = s; j < n; j++)
		{
			if (rand() % 100 > 70)
			{
				Arr[i][j] = 0;
			}
			else {
				Arr[i][j] = 1;
			}
		}
		s++;
	}
	s = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = s; j < n; j++)
			Arr[j][i] = Arr[i][j];
		s++;
	}

	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);

	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
		{
			printf("%2d ", Arr[i][j]);
		}
	}
	return Arr;
}

void BFS(int n, bool* Arr2, int i, int** Arr)
{
	queue<int> que;
	que.push(i);
	Arr2[i] = true;

	while (!que.empty())
	{
		i = que.front();
		que.pop();
		printf("%d ", i + 1);

		for (int j = 1; j < n; j++)
		{
			if (Arr[i][j] == 1 && Arr2[j] == false)
			{
				que.push(j);
				Arr2[j] = true;
			}
		}
	}
}

void BFS_SPISOK(Graf* graf, int n, bool* Arr2, int i)
{
	queue<int> que;
	que.push(i);
	Arr2[i] = true;
	
	while (!que.empty())
	{
		i = que.front();
		que.pop();
		printf("%d ", i + 1);
		Node* temp = graf->Array[i];
		while (temp)
		{
			if (Arr2[temp->vertex] == false)
			{
				que.push(temp->vertex);
				Arr2[temp->vertex] = true;
			}
			temp = temp->Next;
		}
	}
}

void Free(int** Arr, bool* Arr2, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(Arr[i]);
	}
	free(Arr);
	free(Arr2);
}

//void POSCH(int n, int** Arr)
//{
//	bool* Arr2;
//	Arr2 = (bool*)malloc(n * sizeof(bool));
//
//	for (int i = 0; i < n; i++)
//		Arr2[i] = false;
//
//	for (int i = 0; i < n; i++)
//	{
//		if (Arr2[i] == false)
//			BFS(n, Arr2, i, Arr);
//	}
//}

int main()
{
	setlocale(LC_ALL, "Ru");
	clock_t start, stop, st, end;
	int n, ** t;
	bool* Arr2;

	printf("??????? ?????? ???????: ");
	scanf("%d", &n);
	Arr2 = (bool*)malloc(n * sizeof(bool));

	t = create_arr(n);

	printf("\n\n");
	for (int i = 0; i < n; i++)
		Arr2[i] = false;
	printf("Result obgod v schir arr ochered: ");
	start = clock();
	BFS(n, Arr2, 0, t);
	stop = clock();
	float res = stop - start;
	printf("\ntime in ms: %f", res);

	printf("\n\n");
	for (int i = 0; i < n; i++)
		Arr2[i] = false;
	printf("Result obgod v schir spisok ocered: ");
	st = clock();
	BFS_QUEUE(n, Arr2, 0, t);
	end = clock();
	float result = end - st;
	printf("\ntime in ms: %f", result);

	Graf* graf = Initialization_Graf(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (t[i][j] == 1 && i > j)
				add_spisok(i, j, graf);
		}
	}
	printf("\n");
	print(graf);
	for (int i = 0; i < n; i++)
		Arr2[i] = false;
	printf("Result obgod v schir spisok smegnosti: ");
	BFS_SPISOK(graf, n, Arr2, 0);
	_getch();

	Free(t, Arr2, n);
}
