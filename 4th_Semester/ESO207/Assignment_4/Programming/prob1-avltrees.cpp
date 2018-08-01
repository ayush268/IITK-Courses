#include <iostream>
#include <string>
using namespace std;

typedef struct Tree {
    string data = "0123456789";
    int height;
    int size;
    struct Tree *left;
    struct Tree *right;
} tree;

tree *newTree(string str)
{
    tree *t = (tree *)calloc(1,sizeof(tree));
    t->size = 1;
    t->height = 1;
    t->data = str;
    t->left = NULL;
    t->right = NULL;
    return t;
}

int size(tree *);
int height(tree *);
tree *getMin(tree *);
tree *insert(tree *, string);
tree *remove(tree *, string);
int findrank(tree *, string);
int getDiff(tree *);
int max(int, int);
tree *leftRot(tree *);
tree *rightRot(tree *);
void printTree(tree *, int);

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int q;
    cin >> q;
    string str1, str2;
    tree *head = NULL;
    while(q--)
    {
        cin >> str1;
        cin >> str2;
        if(str1 == "learn")
        {
            head = insert(head, str2);
//            printTree(head, 0);
//            cout << "\n-------------------------";
//            cout << endl;
        }
        else if(str1 == "forget")
        {
            printf("%d\n", findrank(head, str2));
            head = remove(head, str2);
//            printTree(head, 0);
//            cout << "\n-------------------------";
//            cout << endl;
       }
        else
            printf("%d\n", findrank(head, str2));
    }
    return 0;
}

int size(tree *head)
{
    if(head == NULL)
        return 0;
    return head->size;
}

int height(tree *head)
{
    if(head == NULL)
        return 0;
    return head->height;
}

int getDiff(tree *head)
{
    if(head == NULL)
        return 0;
    return height(head->left) - height(head->right);
}

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}

tree *getMin(tree *head)
{
    tree *curr = head;
    while(curr->left != NULL)
        curr = curr->left;
    return curr;
}

tree *leftRot(tree *head)
{
    tree *a;
    a = head->right;
    head->right = a->left;
    a->left = head;
    head->height = 1 + max(height(head->left), height(head->right));
    a->height = 1 + max(height(a->left), height(a->right));
    head->size = 1 + size(head->left) + size(head->right);
    a->size = 1 + size(a->left) + size(a->right);
    return a;
}

tree *rightRot(tree *head)
{
    tree *a;
    a = head->left;
    head->left = a->right;
    a->right = head;
    head->height = 1 + max(height(head->left), height(head->right));
    a->height = 1 + max(height(a->left), height(a->right));
    head->size = 1 + size(head->left) + size(head->right);
    a->size = 1 + size(a->left) + size(a->right);
    return a;
}

tree *insert(tree *head, string str)
{
//    cout << "1" << endl;
    if(head == NULL)
        return newTree(str);
//    cout << "At " << head->data << endl;
//    cout << "2" << endl;
    if(head->data > str)
    {
//        if(head->left == NULL)
//            cout << "NULL" << endl;
        head->left = insert(head->left, str);
//        cout << "Back!" << endl;
    }
    else if(head->data < str)
        head->right = insert(head->right, str);
    else
        return head;
//    cout << "3" << endl;

    head->size += 1;
    head->height = 1 + max(height(head->left), height(head->right));

    int diff = getDiff(head);

    if(diff > 1 && str < head->left->data)
        return rightRot(head);
    else if(diff < -1 && str > head->right->data)
        return leftRot(head);
    else if(diff > 1 && str > head->left->data)
    {
        head->left = leftRot(head->left);
        return rightRot(head);
    }
    else if(diff < -1 && str < head->right->data)
    {
        head->right = rightRot(head->right);
        return leftRot(head);
    }

    return head;
}

tree *remove(tree* head, string str)
{
    if(head == NULL)
        return head;
    head->size -= 1;
    if(head->data > str)
        head->left = remove(head->left, str);
    else if(head->data < str)
        head->right = remove(head->right, str);
    else
    {
        if((head->left == NULL) || (head->right == NULL))
        {
            tree *tmp = head->left ? head->left : head->right;
            tree *t = tmp;
            tmp = head;
            head = t;
//            cout << "Freeing " << tmp->data << endl;
            free(tmp);
        }
        else
        {
            tree *tmp = getMin(head->right);
            head->data = tmp->data;
            head->right = remove(head->right, head->data);
        }
    }

    if(head == NULL)
        return head;

    head->height = 1 + max(height(head->left), height(head->right));

    int diff = getDiff(head);

    if(diff > 1 && getDiff(head->left) >= 0)
        return rightRot(head);
    else if(diff < -1 && getDiff(head->right) <= 0)
        return leftRot(head);
    else if(diff > 1 && getDiff(head->left) < 0)
    {
        head->left = leftRot(head->left);
        return rightRot(head);
    }
    else if(diff < -1 && getDiff(head->right) > 0)
    {
        head->right = rightRot(head->right);
        return leftRot(head);
    }

    return head;
}

int findrank(tree *head, string str)
{
    int r = 1;
    tree *curr = head;

    while(curr)
    {
        if(str < curr->data)
            curr = curr->left;
        else if(str > curr->data)
        {
            r += 1 + size(curr->left);
            curr = curr->right;
        }
        else
        {
            r += size(curr->left);
            return r;
        }
    }
    return -1;
}

void printTree(tree *head, int indent)
{
    if(head == NULL)
        return;

        if (head->left != NULL)
        {
            printTree(head->left, indent + 1);
            cout << "\n";
        }
        for (int i = 0; i < indent; i++)
            cout << "\t";
        cout << head->data;
        cout << " " << size(head->left) << "ln " << head->height << "h";
        if (head->right != NULL)
        {
            cout << "\n";
            printTree(head->right, indent + 1);
        }
}
