#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//a�a� d���m yap�s�
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

//a�aca yeni d���m ekleyen fonksiyon
void insert(Node** root, int data) 
{
    Node* parent = NULL;
    Node* current = *root;

    while (current != NULL) //bo� olana kadar ilerle
    {
        parent = current;
        if (data < current->data)
            current = current->left; //data, current d���mdekinden k���kse sola git

        else if (data > current->data)
            current = current->right; //data, current d���mdekinden b�y�kse sa�a git

        else
            return;
    }

    Node* node = newNode(data);
    if (parent == NULL)
        *root = node; //e�er a�a� bo�sa yeni d���m k�k oldu

    else if (data < parent->data)
        parent->left = node; //eklenen k�ktekinden k���kse sola git 

    else
        parent->right = node; //eklenen k�ktekinden b�y�kse sa�a git
}

//say�lar�n asall���n� kontrol ediyo
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

    int level = 0; //ad�m say�s�
    int count = 0; //asal say� sayac�
    Node* queue[100]; //kuyruk dizi olarak uyguland�
    int front = 0, rear = 0; //kuyru�un ba�� ve sonu 
    queue[rear++] = root; //k�k d���m kuyru�a eklendi

    while (front < rear)  //kuyruk bo� olana kadar devam et 
    {
        int size = rear - front; //seviyedeki d���m say�s�
        while (size--)
        {
            Node* current = queue[front++]; //kuyru�un ba��ndaki d���m kuyruktan ��k�yo
            int xorResult = current->data ^ k; // XOR i�lemi

            if (isPrime(xorResult)) //XOR sonucu asal say� ise 
            {
                printf("%d\t", xorResult);
                count++;
            }

            if (current->left != NULL)
                queue[rear++] = current->left; //e�er sol �ocuk varsa kuyru�a ekle

            if (current->right != NULL)
                queue[rear++] = current->right; //e�er sa� �ocuk varsa kuyru�a ekle
        }
        level++;
    }
    printf("\nBFS ile %d adimda %d adet asal sayi bulundu.\n", level, count);
}

void DFSUtil(Node* root, int k, int level, int* count) 
{
    if (root == NULL)
        return;

    int xorResult = root->data ^ k; // XOR i�lemi

    if (isPrime(xorResult)) //XOR sonucu asal say� ise 
    {
        printf("%d\t", xorResult);
        (*count)++;
    }

    DFSUtil(root->left, k, level + 1, count); //sol �ocu�a git
    DFSUtil(root->right, k, level + 1, count); //sa� �ocu�a git
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
