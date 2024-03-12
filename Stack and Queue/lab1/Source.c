#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define MAX_SIZE 101

typedef struct node {
	int x;
	struct node* next; //bir sonraki düðümü iþaret eden pointer 
} node;

int n;

// Diziyi oluþturup ekrana yazdýran fonksiyon
void array(int dizi[]) 
{
	int i, j;
	printf("Dizi:\n");
	srand(time(NULL)); //rastgele sayý üretimi 

	for (i = 0; i < n; i++) 
	{
		j = rand() % 100; //0 ile 100 arasýnda rastgele
		dizi[i] = j; //0. indeksten baþlayýp oluþturulan sayýyý diziye atar 
		printf("%d\t", dizi[i]);
	}
}

// Baðlý listeyi ekrana yazdýran fonksiyon
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

// Kuyruða eleman eklemek için fonksiyon
void enq(int x) 
{
	if (rear == MAX_SIZE - 1)
		printf("\nQueue is full\n");

	else if (front == -1 && rear == -1) //kuyruk boþ 
		front = rear = 0; //hem baþ hem de son indeksleri 0a çekti

	else 
	{
		rear = rear + 1; //kuyruk sonunu bir sonraki indekse atadý
		arrayy[rear] = x; //rear indeksine elemaný ekledi
	}
}

// Kuyruðu ekrana yazdýran fonksiyon
void printQue() 
{
	printf("\nQueue:\n");

	for (int i = front; i <= rear; i++)
		printf("%d\t", arrayy[i]);

	printf("\n");
}

// Yýðýna eleman eklemek için fonksiyon
void push(int x) 
{
	if (top == MAX_SIZE - 1)
		printf("\nStack is full\n");

	else
		arrayy[++top] = x;
}

// Yýðýýný ekrana yazdýran fonksiyon
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

	// Kullanýcýdan dizinin eleman sayýsýný alýr
	printf("Dizinin eleman sayisini girin:\n");
	scanf_s("%d", &n);

	int* dizi = (int*)malloc(n * sizeof(int));
	array(dizi);

	printf("\n");

	node* root = (node*)malloc(sizeof(node));
	root->x = dizi[0];
	node* iter = root;

	// Baðlý listeyi oluþturur
	for (i = 1; i < n; i++) 
	{
		iter->next = (node*)malloc(sizeof(node));
		iter = iter->next;
		iter->x = dizi[i];
		iter->next = NULL;
	}
	print(root);

	// Diziyi kuyruða ekler
	for (i = n - 1; i >= 0; i--) 
	{
		enq(dizi[i]);
	}
	printQue();

	int k;

	// Kullanýcýdan bir K deðeri alýr
	printf("Bir K degeri giriniz:\n");
	scanf_s("%d", &k);

	// Ýlk K elemaný yýðýna ekler
	for (i = 0; i < k; i++) 
	{
		push(dizi[i]);
	}

	printStack();

	return 0;
}
