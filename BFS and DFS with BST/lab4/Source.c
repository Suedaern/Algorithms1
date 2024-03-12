#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//aðaç düðüm yapýsý
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

Node* newNode(int data) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//aðaca yeni düðüm ekleyen fonksiyon
void insert(Node** root, int data) 
{
    Node* parent = NULL;
    Node* current = *root;

    while (current != NULL) //boþ olana kadar ilerle
    {
        parent = current;
        if (data < current->data)
            current = current->left; //data, current düðümdekinden küçükse sola git

        else if (data > current->data)
            current = current->right; //data, current düðümdekinden büyükse saða git

        else
            return;
    }

    Node* node = newNode(data);
    if (parent == NULL)
        *root = node; //eðer aðaç boþsa yeni düðüm kök oldu

    else if (data < parent->data)
        parent->left = node; //eklenen köktekinden küçükse sola git 

    else
        parent->right = node; //eklenen köktekinden büyükse saða git
}

//sayýlarýn asallýðýný kontrol ediyo
bool isPrime(int num)
{
    if (num < 2)
        return false;

    for (int i = 2; i * i <= num; i++) 
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

void BFS(Node* root, int k)
{
    if (root == NULL)
        return;

    int level = 0; //adým sayýsý
    int count = 0; //asal sayý sayacý
    Node* queue[100]; //kuyruk dizi olarak uygulandý
    int front = 0, rear = 0; //kuyruðun baþý ve sonu 
    queue[rear++] = root; //kök düðüm kuyruða eklendi

    while (front < rear)  //kuyruk boþ olana kadar devam et 
    {
        int size = rear - front; //seviyedeki düðüm sayýsý
        while (size--)
        {
            Node* current = queue[front++]; //kuyruðun baþýndaki düðüm kuyruktan çýkýyo
            int xorResult = current->data ^ k; // XOR iþlemi

            if (isPrime(xorResult)) //XOR sonucu asal sayý ise 
            {
                printf("%d\t", xorResult);
                count++;
            }

            if (current->left != NULL)
                queue[rear++] = current->left; //eðer sol çocuk varsa kuyruða ekle

            if (current->right != NULL)
                queue[rear++] = current->right; //eðer sað çocuk varsa kuyruða ekle
        }
        level++;
    }
    printf("\nBFS ile %d adimda %d adet asal sayi bulundu.\n", level, count);
}

void DFSUtil(Node* root, int k, int level, int* count) 
{
    if (root == NULL)
        return;

    int xorResult = root->data ^ k; // XOR iþlemi

    if (isPrime(xorResult)) //XOR sonucu asal sayý ise 
    {
        printf("%d\t", xorResult);
        (*count)++;
    }

    DFSUtil(root->left, k, level + 1, count); //sol çocuða git
    DFSUtil(root->right, k, level + 1, count); //sað çocuða git
}

void DFS(Node* root, int k) 
{
    int count = 0;
    DFSUtil(root, k, 0, &count);
    printf("\nDFS ile %d adimda %d adet asal sayi bulundu.\n", count, count);
}

int main() 
{
    Node* root = NULL;
    int num, k;

    printf("\nPozitif bir sayi girin (Cikis icin 0'a basin): ");
    scanf_s("%d\t", &num);

    while (num != 0) 
    {
        insert(&root, num);
        printf("\nPozitif bir sayi girin (Cikis icin 0'a basin): ");
        scanf_s("%d\t", &num);
    }

    printf("\nK sayisini girin: ");
    scanf_s("%d", &k);

    printf("\nBFS ile asal sayilar: ");
    BFS(root, k);

    printf("\nDFS ile asal sayilar: ");
    DFS(root, k);

    return 0;
}
