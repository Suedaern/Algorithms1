#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>
//iterativ
/*
typedef struct node {
    int data;
    struct node* next; //bir sonraki d���m� i�aret eden pointer 
};

struct linked_list {
    struct node* head; //ba�l� listenin ba�lang�� d���m�n� i�aret eden pointer 
};

//listenin sonuna eleman ekleme 
void sonaEkle(struct linked_list* list, int data) 
{
    
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

  
    if (list->head == NULL)  //liste bo�sa 
        list->head = newNode; //eklenen ba�lang�� d���m olarak ayarlan�yo
    
    else 
    {
        struct node* iter = list->head; //listede eleman varsa 
        while (iter->next != NULL)
        {
            iter = iter->next; //listenin sonuna kadar gidip eleman� �yle ekliyo
        }
        iter->next = newNode;
    }
}

//listenin s�ral� olup olmad���n� kontrol ediyo
bool siraliMi(struct linked_list* list) 
{
    if (list->head == NULL || list->head->next == NULL) 
        return true; //liste bo�sa veya bir eleman varsa s�ral� kabul edilir


    struct node* current = list->head;
    while (current->next != NULL) 
    {
        if (current->data > current->next->data) 
            return false; //e�er pointer�n oldu�u de�er bri sonraki de�erden b�y�kse liste s�ral� de�il 
        
        current = current->next;
    }

    return true;
}

//liste s�ral� ise i�indeki asal say�lar� bulan fonksiyon
bool asalMi(int n) 
{
    if (n <= 1) 
        return false;
    
    int i;
    for (i = 2; i <= sqrt(n); i++) 
    {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//liste s�ral� oldu�unda bulunan asal say�lar� yazan fonksiyon
void printAsal(struct linked_list* list) 
{
    struct node* current = list->head;
    while (current != NULL) 
    {
        if (asalMi(current->data)) 
        {
            printf("Asal sayilar:\n");
            printf("%d\t ", current->data);
        }
        current = current->next;
    }
    printf("\n");
}

//liste s�ral� de�ilse harshad say�lar� bulan fonksiyon
bool harshadMi(int n)
{
    int sum = 0;
    int temp = n;

    while (temp > 0) //say�n�n rakamlar�n� topluyo
    {
        sum += temp % 10;
        temp /= 10;
    }

    return (n % sum == 0); //rakam toplamlar�na tam b�l�nen say�lar� d�n�yo
}

//bulunan harshad say�lar�n� ekrana yazan fonksiyon
void printHarshad(struct linked_list* list)
{
    struct node* current = list->head;

    while (current != NULL) //liste �zerinde dola��p elemanlar� harshad m� de�il mi kontrol ediyo
    {
        if (harshadMi(current->data))
        {
            printf("Harshad sayilari\n");
            printf("%d\t", current->data);
        }
        current = current->next;
    }
    printf("\n");
}
int main() 
{
    struct linked_list list;
    list.head = NULL;

    int n;
    printf("Linked listin boyutunu girin:\t ");
    scanf_s("%d", &n);
  
    for (int i = 0; i < n; i++) 
    {
        int data;
        printf("Dizinin elemanlarini girin %d: ", i + 1);
        scanf_s("%d", &data);
        sonaEkle(&list, data);
    }

    printf("\n");
    int asalMi = 0;

    if (siraliMi(&list))
    {
        printf("\nListe sirali\n");
        printAsal(&list);
    }
    else 
    {
        printf("\nListe sirali degil\n");
        printHarshad(&list);
    }

    return 0;
}
*/






//recursive


// D���m yap�s�
typedef struct node {
    int data;
    struct node* next;
} Node;

// Ba�l� liste yap�s�
typedef struct linked_list {
    Node* head;
} LinkedList;

// Listenin sonuna eleman ekleyen fonksiyon (recursive)
void sonaEkle_recursive(Node** headRef, int data) 
{
    if (*headRef == NULL) 
    {
        *headRef = (Node*)malloc(sizeof(Node));
        (*headRef)->data = data;
        (*headRef)->next = NULL;
    }
    else
    {
        sonaEkle_recursive(&((*headRef)->next), data);
    }
}

// Listenin s�ral� olup olmad���n� kontrol eden fonksiyon (recursive)
bool siraliMi_recursive(Node* node) 
{
    if (node == NULL || node->next == NULL) 
    {
        return true; // Liste bo� veya tek elemanl�ysa s�ral� kabul edilir
    }
    if (node->data > node->next->data) 
    {
        return false; // Liste s�ral� de�ilse false d�nd�r
    }
    return siraliMi_recursive(node->next); // Sonraki d���me ge�
}

// Listenin s�ral� olup olmad���n� kontrol eden fonksiyon
bool siraliMi(LinkedList* list) 
{
    return siraliMi_recursive(list->head);
}

// Bir say�n�n asal olup olmad���n� kontrol eden fonksiyon
bool asalMi(int n) 
{
    if (n <= 1) 
    {
        return false;
    }
    int i;
    for (i = 2; i <= sqrt(n); i++) 
    {
        if (n % i == 0) 
        {
            return false;
        }
    }
    return true;
}

// Liste elemanlar�n�n i�indeki asal say�lar� yazd�ran fonksiyon (recursive)
void printAsal_recursive(Node* node)
{
    if (node == NULL) 
    {
        return;
    }
    if (asalMi(node->data)) 
    {
        printf("%d ", node->data);
    }
    printAsal_recursive(node->next);
}

// Liste elemanlar�n�n i�indeki asal say�lar� yazd�ran fonksiyon
void printAsal(LinkedList* list)
{
    printf("Asal sayilar: ");
    printAsal_recursive(list->head);
    printf("\n");
}

// Bir say�n�n Harshad say� olup olmad���n� kontrol eden fonksiyon
bool harshadMi(int n) 
{
    if (n == 0) 
    {
        return false;
    }

    int sum = 0;
    int temp = n;

    while (temp > 0) 
    {
        sum += temp % 10;
        temp /= 10;
    }
    return (n % sum == 0);
}

// Liste elemanlar�n�n i�indeki Harshad say�lar� yazd�ran fonksiyon (recursive)
void printHarshad_recursive(Node* node) 
{
    if (node == NULL) 
    {
        return;
    }
    if (harshadMi(node->data))
    {
        printf("%d\t", node->data);
    }
    printHarshad_recursive(node->next);
}

// Liste elemanlar�n�n i�indeki Harshad say�lar� yazd�ran fonksiyon
void printHarshad(LinkedList* list)
{
    printf("Harshad sayilar: ");
    printHarshad_recursive(list->head);
    printf("\n");
}

int main() 
{
    LinkedList list;
    list.head = NULL;

    int n;
    printf("Linked listin boyutunu girin: ");
    scanf_s("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int data;
        printf("\nDizinin elemanlarini girin %d: ", i + 1);
        scanf_s("%d", &data);
        sonaEkle_recursive(&(list.head), data);
    }

    printf("\n");

    if (siraliMi(&list))
    {
        printf("\nListe sirali.\n");
        printAsal(&list);
    }
    else
    {
        printf("\nListe sirali degil.\n");
        printHarshad(&list);
    }

    return 0;
}
