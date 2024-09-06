#include <iostream>
#include <stdlib.h>
using namespace std;

class Node
{
	int data;
	Node *left, *right;

public:
	// Default constructor.
	Node();

	// Parameterized constructor.
	Node(int);
  Node* minValueNode(Node* root);
	// Insert function.
	Node* Insert(Node*, int);
  Node* deleteNode(Node*, int);

	//Traversal functions
	void Inorder(Node*);
    void Preorder(Node*);
    void Postorder(Node*);
};

// Default Constructor definition.
Node ::Node()
	: data(0)
	, left(NULL)
	, right(NULL)
{
}

// Parameterized Constructor definition.
Node ::Node(int value)
{
	data = value;
	left = right = NULL;
}

Node* Node ::minValueNode(Node* root)
{
    Node* current = root;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 

// Insert function definition.
Node* Node ::Insert(Node* root, int value)
{
	if (root == NULL)
	{
		// Insert the first node, if root is NULL.
		return new Node(value);
	}

	// Insert data.
	if (value > root->data)
	{
		// Insert right node data, if the 'value'
		// to be inserted is greater than 'root' node data.

		// Process right nodes.
		root->right = Insert(root->right, value);
	}
	else
	{
		// Insert left node data, if the 'value'
		// to be inserted is greater than 'root' node data.

		// Process left nodes.
		root->left = Insert(root->left, value);
	}

	// Return 'root' node, after insertion.
	return root;
}

/* Given a binary search tree and a value, this function
deletes the value and returns the new root */
Node* Node::deleteNode(Node* root, int value)
{
 // base case
    if (root == NULL)
        return root;
 
    // If the value to be deleted is
    // smaller than the root's
    // value, then it lies in left subtree
    if (value < root->data)
        root->left = deleteNode(root->left, value);
 
    // If the value to be deleted is
    // greater than the root's
    // value, then it lies in right subtree
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
 
    // if value is same as root's value, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
  


// Inorder traversal function.
// This gives data in sorted order.
void Node ::Inorder(Node* root)
{
	if (root == NULL) {
		return;
	}
    
    //LEFT --> VISIT --> RIGHT
	Inorder(root->left);
	cout << root->data <<" ";
	Inorder(root->right);

}

//Pre-Order traversal
void Node ::Preorder(Node* root)
{
	if (root == NULL) {
		return;
	}

    //VISIT --> LEFT --> RIGHT
    cout << root->data << " ";
	Preorder(root->left);
	Preorder(root->right);

}

//Post-Order Traversal
void Node ::Postorder(Node* root)
{
	if (root == NULL) {
		return;
	}

    //LEFT --> RIGHT --> VISIT
	Postorder(root->left);
    Postorder(root->right);
	cout << root->data <<" ";

}

// Driver code
int main()
{
    /*
	root = root->Insert(root, 50);
	root->Insert(root, 30);
	root->Insert(root, 20);
	root->Insert(root, 40);
	root->Insert(root, 70);
	root->Insert(root, 60);
	root->Insert(root, 80);
  
	root->Inorder(root);
     cout << "\n";
     root->Insert(root, 25);
  
	root->Inorder(root);
     cout << "\n";
     root->deleteNode(root, 25);
 
     root->Inorder(root);
     cout << "\n";
    */

    //create a new node called root
    Node *root = new Node();
    //give it an empty value
    root = NULL;

    //create in-order output
    root = root->Insert(root, 4);
    root->Insert(root, 2);
    root->Insert(root, 6);
    root->Insert(root, 1);
    root->Insert(root, 3);
    root->Insert(root, 5);
    root->Insert(root, 7);

    //display in-order output
    cout << "In-order Output:" << endl;
    root->Inorder(root);
    cout << endl << endl;

    //display pre-order output
    cout << "Pre-order Output:" << endl;
    root->Preorder(root);
    cout << endl << endl;

    //display post-order output
    cout << "Post-order Output:" << endl;
    root->Postorder(root);
    cout << endl << endl;
    
	return 0;
}