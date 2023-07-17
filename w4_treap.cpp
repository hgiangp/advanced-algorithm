#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Node
{
public:
    int key;
    int pri;
    Node *left, *right;

public:
    Node(int key, int pri)
    {
        this->key = key;
        this->pri = pri;
        this->left = nullptr;
        this->right = nullptr;
    }
};

Node *rightRotate(Node *t)
{
    Node *s = t->left;
    t->left = s->right;
    s->right = t;
    return s; // new root of the subtree
}

Node *leftRotate(Node *t)
{
    Node *s = t->right;
    t->right = s->left;
    s->left = t;
    return s; // new root of the subtree
}

Node *insert(Node *t, int key, int pri)
{
    if (t == nullptr)
    {
        return new Node(key, pri);
    }
    // search the corresponding place recursively
    if (key == t->key)
    {
        return t; // ignore duplicate keys
    }

    if (key < t->key)
    {                                        // move to the left child
        t->left = insert(t->left, key, pri); // update the pointer to the left child
        if (t->pri < t->left->pri)
        { // if the left child has higher priority
            t = rightRotate(t);
        }
    }
    else
    {                                          // move to the right child
        t->right = insert(t->right, key, pri); // update the pointer to the right child
        if (t->pri < t->right->pri)
        { // if the right child has higher priority
            t = leftRotate(t);
        }
    }
    return t;
}

Node *erase(Node *t, int key)
{
    // seach the target recursively
    if (t == nullptr)
    {
        return nullptr;
    }

    if (key == t->key) // if t is the target node
    {
        if (t->left == nullptr && t->right == nullptr) // if t is a leaf
        {
            return nullptr;
        }
        else if (t->left == nullptr) // if t has only the right child
        {
            t = leftRotate(t); // left rotate to make it left leaf
        }
        else if (t->right == nullptr) // if t has only the left child
        {
            t = rightRotate(t); // right rotate to make it right leaf
        }
        else // if t has both the left and right child
        {
            // pull up the child with higher priority
            if (t->left->pri > t->right->pri)
            {
                t = rightRotate(t);
            }
            else
            {
                t = leftRotate(t);
            }
        }
        return erase(t, key);
    }
    // search the target recursively
    if (key < t->key)
    {
        t->left = erase(t->left, key);
    }
    else
    {
        t->right = erase(t->right, key);
    }

    return t;
}

void print_inorder(Node *t)
{
    if (t == nullptr)
    {
        return;
    }

    // first recursive on the left child
    print_inorder(t->left);
    cout << " " << t->key; 
    print_inorder(t->right);
    // printf("\n"); 
}

void print_preorder(Node *t) 
{
    if (t == nullptr) 
        return; 
    cout << " " << t->key; 
    print_preorder(t->left);
    print_preorder(t->right);
}

bool search(Node *t, int key)
{
    if (t == nullptr)
        return false;

    if (t->key == key)
        return true;

    if (key < t->key)
        return search(t->left, key);

    return search(t->right, key);
}

int main() {
    int num_op;
    string op;  
    int key, pri; 
    
    Node* t = nullptr; 

    cin >> num_op; 
    for (int i = 0; i < num_op; i++) {
        cin >> op; 
        if (op == "insert") {
            cin >> key >> pri;
            t = insert(t, key, pri); 
        }
        if (op == "print") {
            print_inorder(t); 
            cout << endl; 
            print_preorder(t); 
            cout << endl; 
        }

        if (op == "find") {
            cin >> key; 
            bool rs = search(t, key); 
            if (rs == true) {
                cout << "yes" << endl; 
            }
            else{
                cout << "no" << endl; 
            }
        }
        if (op == "delete") {
            cin >> key; 
            t = erase(t, key); 
        }
    }
}
