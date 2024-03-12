#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Yeni d���m olu�turma fonksiyonu
struct Node* newNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Bellek tahsis edilemedi\n");
        exit(1);
    }
    //d���m�n veri alan�n� ve next alan�n� belirleme
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Tek y�nl� ba�l� listeye eleman ekleme fonksiyonu
void insertAtEnd(struct Node** head, int data)
{
    struct Node* new_node = newNode(data); //yeni d���m olu�turma 

    if (*head == NULL) //liste bo�sa yeni d���m� listenin ba��na ekler
    {
        *head = new_node;
    }

    else
    {
        struct Node* temp = *head; //listenin sonuna kadar ilerler son gelen eleman� ekler
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Tek y�nl� ba�l� listeyi yazd�rma fonksiyonu
void printList(struct Node* head)
{
    printf("Liste: ");

    while (head != NULL) //listenin sonuna giderek her d���m�n de�erini yazar 
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Listeyi ikiye b�len fonksiyon
void splitList(struct Node* head, struct Node** front, struct Node** back)
{
    struct Node* slow = head;
    struct Node* fast = head->next;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    *front = head; //ilk yar�m liste
    *back = slow->next; //ikinci yar�m liste 
    slow->next = NULL; //ilk yar�m listenin sonunu belirleme
}

// �ki s�ral� listeyi birle�tiren fonksiyon
struct Node* merge(struct Node* list1, struct Node* list2)
{
    if (list1 == NULL) //list1 bo� ise di�er listeyi d�nd�r
        return list2;

    if (list2 == NULL) //list2 bo� ise di�er listeyi d�nd�r
        return list1;

    if (list1->data < list2->data) //listenin ba��ndaki d���mleri kar��la�t�rarak birle�tirme
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

// Merge Sort algoritmas�
void mergeSort(struct Node** head)
{
    struct Node* temp = *head; //ba�lang��ta listenin ba��n� belirleme 

    //iki yar�m listeyi g�stermek i�in i�aret�iler
    struct Node* front = NULL;
    struct Node* back = NULL;

    if (temp == NULL || temp->next == NULL) //liste bo� veya tek elemanl� ise s�ralama gerekmez
        return;

    splitList(temp, &front, &back);//listeyi ikiye b�ler 

    //her iki yar�m listeyi ayr� ayr� s�ralar
    mergeSort(&front);
    mergeSort(&back);

    //s�ral� iki listeyi birle�tirir
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

    struct Node* evenList = NULL; //�ift pozisyondaki say�lar�n oldu�u liste
    struct Node* oddList = NULL; //tek pozisyondaki say�lar�n oldu�u liste
    struct Node* current = head; //mevcut d���m� g�stermek i�in i�aret�i
    int index = 1; //e�er 0dan ba�lat�rsam ��kt� farkl� olur

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
