#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Düðüm yapýsý
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

// BST yapýsý
typedef struct bst {
    Node* root;
} BST;

// Düðüm oluþturma fonksiyonu
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
    // Eðer aðaç boþsa, yeni düðümü kök olarak ekle
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

    // Yeni düðümü ekleyerek baðla
    if (data < parent->data)
    {
        parent->left = createNode(data);
    }
    else 
    {
        parent->right = createNode(data);
    }
}

// BST'yi inorder olarak gezerek yazdýrma fonksiyonu
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

// BST'yi serbest býrakma fonksiyonu
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

// BST'de belirtilen aralýk dýþýndaki elemanlarý silen özyinelemeli fonksiyon
Node* deleteOutsideRange(Node* root, int min, int max) 
{
    if (root == NULL)
    {
        return NULL;
    }

    // Ýlgili alt aðaçlarý yeniden yapýlandýr
    root->left = deleteOutsideRange(root->left, min, max);
    root->right = deleteOutsideRange(root->right, min, max);

    // Kök düðüm de aralýðýn dýþýndaysa, düðümü serbest býrak ve sað alt aðacý geri dön
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

    // Rastgele sayý üretmek için srand fonksiyonunu kullanarak rastgele bir tohum belirle
    srand(time(NULL));

    int N;
    printf("Dizinin boyutunu girin: ");
    scanf_s("%d", &N);

    // -1000 ile 1000 arasýnda rastgele sayýlar üreterek BST'ye ekleyin
    for (int i = 0; i < N; i++) {
        int randomNum = rand() % 2001 - 1000; // -1000 ile 1000 arasýnda rastgele sayý üret
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

    // Belirtilen aralýk dýþýndaki elemanlarý sil
    tree.root = deleteOutsideRange(tree.root, min, max);

    printf("\nGuncellenmis BST Inorder Siralamasi: ");
    inorderTraversal(tree.root); //güncellenmiþ halini yazmýyo :(
    printf("\n");

    // BST'yi serbest býrak
    freeBST(tree.root);

    return 0;
}
