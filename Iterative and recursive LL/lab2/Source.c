#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>
//iterativ
/*
typedef struct node {
    int data;
    struct node* next; //bir sonraki düðümü iþaret eden pointer 
};

struct linked_list {
    struct node* head; //baðlý listenin baþlangýç düðümünü iþaret eden pointer 
};

//listenin sonuna eleman ekleme 
void sonaEkle(struct linked_list* list, int data) 
{
    
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

  
    if (list->head == NULL)  //liste boþsa 
        list->head = newNode; //eklenen baþlangýç düðüm olarak ayarlanýyo
    
    else 
    {
        struct node* iter = list->head; //listede eleman varsa 
        while (iter->next != NULL)
        {
            iter = iter->next; //listenin sonuna kadar gidip elemaný öyle ekliyo
        }
        iter->next = newNode;
    }
}

//listenin sýralý olup olmadýðýný kontrol ediyo
bool siraliMi(struct linked_list* list) 
{
    if (list->head == NULL || list->head->next == NULL) 
        return true; //liste boþsa veya bir eleman varsa sýralý kabul edilir


    struct node* current = list->head;
    while (current->next != NULL) 
    {
        if (current->data > current->next->data) 
            return false; //eðer pointerýn olduðu deðer bri sonraki deðerden büyükse liste sýralý deðil 
        
        current = current->next;
    }

    return true;
}

//liste sýralý ise içindeki asal sayýlarý bulan fonksiyon
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

//liste sýralý olduðunda bulunan asal sayýlarý yazan fonksiyon
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

//liste sýralý deðilse harshad sayýlarý bulan fonksiyon
bool harshadMi(int n)
{
    int sum = 0;
    int temp = n;

    while (temp > 0) //sayýnýn rakamlarýný topluyo
    {
        sum += temp % 10;
        temp /= 10;
    }

    return (n % sum == 0); //rakam toplamlarýna tam bölünen sayýlarý dönüyo
}

//bulunan harshad sayýlarýný ekrana yazan fonksiyon
void printHarshad(struct linked_list* list)
{
    struct node* current = list->head;

    while (current != NULL) //liste üzerinde dolaþýp elemanlarý harshad mý deðil mi kontrol ediyo
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


// Düðüm yapýsý
typedef struct node {
    int data;
    struct node* next;
} Node;

// Baðlý liste yapýsý
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

// Listenin sýralý olup olmadýðýný kontrol eden fonksiyon (recursive)
bool siraliMi_recursive(Node* node) 
{
    if (node == NULL || node->next == NULL) 
    {
        return true; // Liste boþ veya tek elemanlýysa sýralý kabul edilir
    }
    if (node->data > node->next->data) 
    {
        return false; // Liste sýralý deðilse false döndür
    }
    return siraliMi_recursive(node->next); // Sonraki düðüme geç
}

// Listenin sýralý olup olmadýðýný kontrol eden fonksiyon
bool siraliMi(LinkedList* list) 
{
    return siraliMi_recursive(list->head);
}

// Bir sayýnýn asal olup olmadýðýný kontrol eden fonksiyon
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

// Liste elemanlarýnýn içindeki asal sayýlarý yazdýran fonksiyon (recursive)
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

// Liste elemanlarýnýn içindeki asal sayýlarý yazdýran fonksiyon
void printAsal(LinkedList* list)
{
    printf("Asal sayilar: ");
    printAsal_recursive(list->head);
    printf("\n");
}

// Bir sayýnýn Harshad sayý olup olmadýðýný kontrol eden fonksiyon
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

// Liste elemanlarýnýn içindeki Harshad sayýlarý yazdýran fonksiyon (recursive)
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

// Liste elemanlarýnýn içindeki Harshad sayýlarý yazdýran fonksiyon
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
