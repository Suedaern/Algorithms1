#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// D���m yap�s�
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

// BST yap�s�
typedef struct bst {
    Node* root;
} BST;

// D���m olu�turma fonksiyonu
Node* createNode(int data) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// BST'ye eleman ekleme fonksiyonu
void insert(BST* tree, int data) 
{
    // E�er a�a� bo�sa, yeni d���m� k�k olarak ekle
    if (tree->root == NULL) 
    {
        tree->root = createNode(data);
        return;
    }

    Node* current = tree->root;
    Node* parent = NULL;

    // Ekleme yeri bulunana kadar gez
    while (current != NULL) 
    {
        parent = current;
        if (data < current->data) 
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }

    // Yeni d���m� ekleyerek ba�la
    if (data < parent->data)
    {
        parent->left = createNode(data);
    }
    else 
    {
        parent->right = createNode(data);
    }
}

// BST'yi inorder olarak gezerek yazd�rma fonksiyonu
void inorderTraversal(Node* node) 
{
    if (node == NULL)
    {
        return;
    }
    inorderTraversal(node->left);
    printf("%d\t", node->data);
    inorderTraversal(node->right);
}

// BST'yi serbest b�rakma fonksiyonu
void freeBST(Node* root) 
{
    if (root == NULL)
    {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

// BST'de belirtilen aral�k d���ndaki elemanlar� silen �zyinelemeli fonksiyon
Node* deleteOutsideRange(Node* root, int min, int max) 
{
    if (root == NULL)
    {
        return NULL;
    }

    // �lgili alt a�a�lar� yeniden yap�land�r
    root->left = deleteOutsideRange(root->left, min, max);
    root->right = deleteOutsideRange(root->right, min, max);

    // K�k d���m de aral���n d���ndaysa, d���m� serbest b�rak ve sa� alt a�ac� geri d�n
    if (root->data < min || root->data > max)
    {
        Node* temp = root;
        root = NULL;
        free(temp);
        return root;
    }

    return root;
}

int main() 
{
    BST tree;
    tree.root = NULL;

    // Rastgele say� �retmek i�in srand fonksiyonunu kullanarak rastgele bir tohum belirle
    srand(time(NULL));

    int N;
    printf("Dizinin boyutunu girin: ");
    scanf_s("%d", &N);

    // -1000 ile 1000 aras�nda rastgele say�lar �reterek BST'ye ekleyin
    for (int i = 0; i < N; i++) {
        int randomNum = rand() % 2001 - 1000; // -1000 ile 1000 aras�nda rastgele say� �ret
        insert(&tree, randomNum);
    }

    printf("\nBST Inorder Siralamasi: ");
    inorderTraversal(tree.root);
    printf("\n");

    int min, max;
    printf("\nAlt sinir (min) degerini girin: ");
    scanf_s("%d", &min);
    printf("\nUst sinir (max) degerini girin: ");
    scanf_s("%d", &max);

    // Belirtilen aral�k d���ndaki elemanlar� sil
    tree.root = deleteOutsideRange(tree.root, min, max);

    printf("\nGuncellenmis BST Inorder Siralamasi: ");
    inorderTraversal(tree.root); //g�ncellenmi� halini yazm�yo :(
    printf("\n");

    // BST'yi serbest b�rak
    freeBST(tree.root);

    return 0;
}
