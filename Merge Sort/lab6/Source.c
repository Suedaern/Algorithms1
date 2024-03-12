#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Yeni düðüm oluþturma fonksiyonu
struct Node* newNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Bellek tahsis edilemedi\n");
        exit(1);
    }
    //düðümün veri alanýný ve next alanýný belirleme
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Tek yönlü baðlý listeye eleman ekleme fonksiyonu
void insertAtEnd(struct Node** head, int data)
{
    struct Node* new_node = newNode(data); //yeni düðüm oluþturma 

    if (*head == NULL) //liste boþsa yeni düðümü listenin baþýna ekler
    {
        *head = new_node;
    }

    else
    {
        struct Node* temp = *head; //listenin sonuna kadar ilerler son gelen elemaný ekler
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Tek yönlü baðlý listeyi yazdýrma fonksiyonu
void printList(struct Node* head)
{
    printf("Liste: ");

    while (head != NULL) //listenin sonuna giderek her düðümün deðerini yazar 
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Listeyi ikiye bölen fonksiyon
void splitList(struct Node* head, struct Node** front, struct Node** back)
{
    struct Node* slow = head;
    struct Node* fast = head->next;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    *front = head; //ilk yarým liste
    *back = slow->next; //ikinci yarým liste 
    slow->next = NULL; //ilk yarým listenin sonunu belirleme
}

// Ýki sýralý listeyi birleþtiren fonksiyon
struct Node* merge(struct Node* list1, struct Node* list2)
{
    if (list1 == NULL) //list1 boþ ise diðer listeyi döndür
        return list2;

    if (list2 == NULL) //list2 boþ ise diðer listeyi döndür
        return list1;

    if (list1->data < list2->data) //listenin baþýndaki düðümleri karþýlaþtýrarak birleþtirme
    {
        list1->next = merge(list1->next, list2);
        return list1;
    }
    else
    {
        list2->next = merge(list1, list2->next);
        return list2;
    }
}

// Merge Sort algoritmasý
void mergeSort(struct Node** head)
{
    struct Node* temp = *head; //baþlangýçta listenin baþýný belirleme 

    //iki yarým listeyi göstermek için iþaretçiler
    struct Node* front = NULL;
    struct Node* back = NULL;

    if (temp == NULL || temp->next == NULL) //liste boþ veya tek elemanlý ise sýralama gerekmez
        return;

    splitList(temp, &front, &back);//listeyi ikiye böler 

    //her iki yarým listeyi ayrý ayrý sýralar
    mergeSort(&front);
    mergeSort(&back);

    //sýralý iki listeyi birleþtirir
    *head = merge(front, back);
}

int main()
{
    struct Node* head = NULL;
    int num;

    printf("Pozitif sayilari girin (Cikis icin 0): \n");

    while (1)
    {
        scanf_s("%d", &num);
        if (num == 0)
            break;
        insertAtEnd(&head, num);
    }

    printf("Girdi: ");
    printList(head);

    struct Node* evenList = NULL; //çift pozisyondaki sayýlarýn olduðu liste
    struct Node* oddList = NULL; //tek pozisyondaki sayýlarýn olduðu liste
    struct Node* current = head; //mevcut düðümü göstermek için iþaretçi
    int index = 1; //eðer 0dan baþlatýrsam çýktý farklý olur

    while (current != NULL)
    {
        if (index % 2 == 0)
            insertAtEnd(&evenList, current->data);
        else
            insertAtEnd(&oddList, current->data);

        current = current->next;
        index++;
    }

    printf("Cift pozisyonlardaki sayilarin artan sirasi: ");
    mergeSort(&evenList);
    printList(evenList);

    printf("Tek pozisyonlardaki sayilarin azalan sirasi: ");
    mergeSort(&oddList);
    printList(oddList);

    return 0;
}
