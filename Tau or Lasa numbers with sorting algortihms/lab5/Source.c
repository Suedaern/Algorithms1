#include <stdio.h>
#include <stdlib.h>


// Çift yönlü baðlý list için düðüm yapýsý
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Yeni bir düðüm oluþturup veriyi ekler
struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Çift yönlü baðlý listeye eleman ekleme
void insertAtEnd(struct Node** head, int data)
{
    struct Node* newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// TAU sayýsýný bulma
int countDivisors(int num)
{
    int count = 0;

    for (int i = 1; i <= num; ++i)
    {
        if (num % i == 0)
            count++;

    }
    return count;
}

// Tersten asal sayý kontrolü
int isReversePrime(int num)
{
    int reverseNum = 0;
    int originalNum = num;

    while (num > 0)
    {
        int digit = num % 10;
        reverseNum = reverseNum * 10 + digit;
        num /= 10;
    }

    if (reverseNum <= 1)
        return 0;

    for (int i = 2; i * i <= reverseNum; ++i)
    {
        if (reverseNum % i == 0)
            return 0;

    }
    return 1;
}

// Insertion Sort algoritmasý
void insertionSort(struct Node** head)
{
    // Listenin baþý boþsa veya tek elemanlýysa zaten sýralýdýr
    if (*head == NULL || (*head)->next == NULL)
        return;

    struct Node* i, * j;

    for (i = (*head)->next; i != NULL; i = i->next)
    {
        int key = i->data;
        j = i->prev;

        while (j != NULL && countDivisors(j->data) > countDivisors(key))
        {
            j->next->data = j->data;
            j = j->prev;
        }
        if (j == NULL)
        {
            (*head)->data = key;
        }
        else
        {
            j->next->data = key;
        }
    }
}

// Bubble Sort algoritmasý
void bubbleSort(struct Node** head)
{
    int swapped, temp;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    if (*head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr)
        {
            if (countDivisors(ptr1->data) < countDivisors(ptr1->next->data))
            {
                temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Selection Sort algoritmasý
void selectionSort(struct Node** head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    struct Node* i, * j, * min;

    for (i = *head; i->next != NULL; i = i->next)
    {
        min = i;

        for (j = i->next; j != NULL; j = j->next)
        {
            if (countDivisors(j->data) < countDivisors(min->data))
            {
                min = j;
            }
        }

        if (min != i)
        {
            int temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
    }
}

// Listeyi yazdýrma
void printList(struct Node* head)
{
    struct Node* temp = head;

    while (temp != NULL)
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


int main() 
{
    int n;
    printf("Eleman sayisini girin:\n ");
    scanf_s("%d\t", &n);

    struct Node* head = NULL;

    // Elemanlarý ekleme
    for (int i = 0; i < n; ++i) 
    {
        int randNum = rand() % 101; // 0-100 arasý rastgele sayý
        insertAtEnd(&head, randNum);
    }

    printf("Olusturulan liste: ");
    printList(head);

    int tauCount = 0;
    int lasaCount = 0;

    // TAU ve LASA sayýlarýný sayma
    struct Node* temp = head;

    printf("\nTAU sayilari: ");

    while (temp != NULL)
    {
        if (countDivisors(temp->data) == 2) 
        {
            tauCount++;
            printf("%d\t", temp->data);
        }

        else if (isReversePrime(temp->data)) 
        {
            lasaCount++;
            printf("%d\t", temp->data);
        }

        temp = temp->next;
    }
    printf("\n");

    printf("\nLASA sayilari: ");
    temp = head;
    while (temp != NULL)
    {
        if (isReversePrime(temp->data))
        {
            printf("%d\t", temp->data);
        }
        temp = temp->next;
    }

    printf("\nTAU sayilarinin sayisi: %d\n", tauCount);
    printf("\nLASA sayilarinin sayisi: %d\n", lasaCount);

    // Sýralama iþlemi
    if (tauCount > lasaCount) 
    {
        insertionSort(&head);
        printf("\nInsertion Sort kullanilarak siralama: ");
    }

    else if (lasaCount > tauCount) 
    {
        bubbleSort(&head);
        printf("\nBubble Sort kullanilarak siralama: ");
    }

    else 
    {
        selectionSort(&head);
        printf("\nSelection Sort kullanilarak siralama: ");
    }

    printList(head);

    return 0;
}
