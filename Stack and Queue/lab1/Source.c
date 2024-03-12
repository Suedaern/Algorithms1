#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define MAX_SIZE 101

typedef struct node {
	int x;
	struct node* next; //bir sonraki d���m� i�aret eden pointer 
} node;

int n;

// Diziyi olu�turup ekrana yazd�ran fonksiyon
void array(int dizi[]) 
{
	int i, j;
	printf("Dizi:\n");
	srand(time(NULL)); //rastgele say� �retimi 

	for (i = 0; i < n; i++) 
	{
		j = rand() % 100; //0 ile 100 aras�nda rastgele
		dizi[i] = j; //0. indeksten ba�lay�p olu�turulan say�y� diziye atar 
		printf("%d\t", dizi[i]);
	}
}

// Ba�l� listeyi ekrana yazd�ran fonksiyon
void print(node* r) 
{
	printf("\nLinkedList:\n");

	while (r != NULL)  //next pointer null olana kadar ilerle demek 
	{
		printf("%d\t", r->x);
		r = r->next;
	}
}

int rear = -1, front = -1, top = -1;
int arrayy[MAX_SIZE];

// Kuyru�a eleman eklemek i�in fonksiyon
void enq(int x) 
{
	if (rear == MAX_SIZE - 1)
		printf("\nQueue is full\n");

	else if (front == -1 && rear == -1) //kuyruk bo� 
		front = rear = 0; //hem ba� hem de son indeksleri 0a �ekti

	else 
	{
		rear = rear + 1; //kuyruk sonunu bir sonraki indekse atad�
		arrayy[rear] = x; //rear indeksine eleman� ekledi
	}
}

// Kuyru�u ekrana yazd�ran fonksiyon
void printQue() 
{
	printf("\nQueue:\n");

	for (int i = front; i <= rear; i++)
		printf("%d\t", arrayy[i]);

	printf("\n");
}

// Y���na eleman eklemek i�in fonksiyon
void push(int x) 
{
	if (top == MAX_SIZE - 1)
		printf("\nStack is full\n");

	else
		arrayy[++top] = x;
}

// Y����n� ekrana yazd�ran fonksiyon
void printStack() 
{
	printf("\nStack:\n");

	for (int i = 0; i <= top; i++)
		printf("%d\t", arrayy[i]);

	printf("\n");
}

int main() 
{
	int i, j;

	// Kullan�c�dan dizinin eleman say�s�n� al�r
	printf("Dizinin eleman sayisini girin:\n");
	scanf_s("%d", &n);

	int* dizi = (int*)malloc(n * sizeof(int));
	array(dizi);

	printf("\n");

	node* root = (node*)malloc(sizeof(node));
	root->x = dizi[0];
	node* iter = root;

	// Ba�l� listeyi olu�turur
	for (i = 1; i < n; i++) 
	{
		iter->next = (node*)malloc(sizeof(node));
		iter = iter->next;
		iter->x = dizi[i];
		iter->next = NULL;
	}
	print(root);

	// Diziyi kuyru�a ekler
	for (i = n - 1; i >= 0; i--) 
	{
		enq(dizi[i]);
	}
	printQue();

	int k;

	// Kullan�c�dan bir K de�eri al�r
	printf("Bir K degeri giriniz:\n");
	scanf_s("%d", &k);

	// �lk K eleman� y���na ekler
	for (i = 0; i < k; i++) 
	{
		push(dizi[i]);
	}

	printStack();

	return 0;
}
