// Huu-Khoa Nguyen
// CS 210
// Programming Assignment 2

#include <iostream>
using namespace std;

// Node Class: Nodes for the BST
template <typename T> class Node {
private:
    // Initalize Private Variables for Node class
    T* data;
    Node<T>* leftChild;
    Node<T>* rightChild;
    Node<T>* parent;
public:
    // Constructor for Node class
    Node (T *data){
        this->data = data;
        parent = nullptr;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    // Print method for the Node class
    void print(){
        data->print();
    }

    // Get methods for variables in the Node Class
    T* getData() {
        return data;
    }
    Node<T>* getParent() {
        return parent;
    }
    Node<T>* getLeftChild() {
        return leftChild;
    }
    Node<T>* getRightChild() {
        return rightChild;
    }

    // Set methods for variables in the Node Class
    void setData(T *newData) {
        data = newData;
    }
    void setParent(Node *newNode) {
        parent = newNode;
    }
    void setLeftChild(Node *newNode) {
        leftChild = newNode;
    }
    void setRightChild(Node *newNode) {
        rightChild = newNode;
    }

};

// Binary Search Tree Class: Container for the Nodes
template <typename T> class BinarySearchTree {
private:
    // Initailizes Variables for the Binary Search Tree Class
    Node<T>* root;
    int numberOfElements;
    int height;
    int count;
public:
    // Constructor for the BST class
    BinarySearchTree(T *data){
        Node<T> *newNode = new Node<T>(data);
        root = newNode;
        numberOfElements = 1;
        height = 1;
        count = 1;
    }

    // Destructor for the BST class
    ~BinarySearchTree() {
        for(int i = 0; i < numberOfElements; i++){
            deleteElement(root->getData());
        }
        numberOfElements--;
    }

    // Insert Method for BST class
    void insertElement(T *data) {
        Node<T> *newNode = new Node<T>(data);
        Node<T> *temp = root;
        // Default values for if the BST is empty
        if(numberOfElements == 0) {
            root = newNode;
            numberOfElements = 1;
            height = 1;
        } else {
            int counter = 0;
            // Move through the BST to the insertion point
            while(temp != nullptr) {
                if (newNode->getData()->getValue() < temp->getData()->getValue()) {
                    // Insert the node into the BST
                    if(temp->getLeftChild() == nullptr){
                        temp->setLeftChild(newNode);
                        newNode->setParent(temp);
                        temp = temp->getLeftChild();
                    }
                    temp = temp->getLeftChild();
                } else {
                    if(temp->getRightChild() == nullptr){
                        temp->setRightChild(newNode);
                        newNode->setParent(temp);
                        temp = temp->getRightChild();
                    }
                    temp = temp->getRightChild();
                }
                counter++;
            }
            numberOfElements++;
            if(counter > height){
                height = counter;
            }
        }
    }

    // Delete Method for BST class
    void deleteElement(T *data) {
        Node<T> *delNode = new Node<T>(data);
        Node<T> *temp = root;
        // If the BST is empty
        if(numberOfElements == 0) {
            cout << "Number does not exist" << endl;
        } else {
            // Move to the node that we want to delete
            while(temp->getData()->getValue() != delNode->getData()->getValue() && temp != nullptr){
                if (delNode->getData()->getValue() < temp->getData()->getValue()) {
                    temp = temp->getLeftChild();
                } else {
                    temp = temp->getRightChild();
                }
                // If the values for deletion is not in the BST
                if(temp == nullptr){
                    cout << "Number does not exist" << endl;
                    return;
                }
            }
            // Cases for if the Node is a leaf node, has one child, or 2 children
            if(temp->getLeftChild() == nullptr && temp->getRightChild() == nullptr) { // Leaf node
                if (temp->getData()->getValue() > temp->getParent()->getData()->getValue()){
                    temp->getParent()->setRightChild(nullptr);
                } else {
                    temp->getParent()->setLeftChild(nullptr);
                }
                delete temp;
                numberOfElements--;
            } else if (temp->getLeftChild() != nullptr && temp->getRightChild() == nullptr) { // 1 Child
                if(temp == root){
                    root = root->getRightChild();
                }else if(temp->getData()->getValue() > temp->getParent()->getData()->getValue()) {
                    temp->getParent()->setRightChild(temp->getLeftChild());
                }else{
                    temp->getParent()->setLeftChild(temp->getLeftChild());
                }
                temp->getLeftChild()->setParent(temp->getParent());
                delete temp;
                numberOfElements--;
            } else if (temp->getLeftChild() == nullptr && temp->getRightChild() != nullptr) { // 1 Child
                if(temp == root){
                    root = root->getRightChild();
                }else if(temp->getData()->getValue() > temp->getParent()->getData()->getValue()) {
                    temp->getParent()->setRightChild(temp->getRightChild());
                }else{
                    temp->getParent()->setLeftChild(temp->getRightChild());
                }
                temp->getRightChild()->setParent(temp->getParent());
                delete temp;
                numberOfElements--;
            } else { // 2 Children
                delNode = temp;
                temp = temp->getLeftChild();
                while(temp->getRightChild() != nullptr) {
                    temp = temp->getRightChild();
                }
                if(temp->getLeftChild() != nullptr) {
                    temp->getParent()->setLeftChild(temp->getLeftChild());
                    temp->getLeftChild()->setParent(temp->getParent());
                }
                temp->getParent()->setRightChild(nullptr);
                delNode->setData(temp->getData());
                delete temp;
                numberOfElements--;
            }
        }
    }

    // Print method for the BST
    void print() {
        printHelper(root);
        cout << endl;
    }

    // Finds the kth element in the ascending order of the tree and prints it
    void findKthElement(int k) {
        int count = 0; // This will keep track of the count of nodes processed
        Node<T>* result = findHelper(root, k, count);
        if (result != nullptr) {
            result->print();
            cout << endl;
        } else {
            cout << "Element does not exist for k = " << k << endl;
        }
    }

    // Finds the smallest element in the tree and prints it
    void findSmallest() {
        Node<T> *temp = root;
        while(temp->getLeftChild() != nullptr) {
            temp = temp->getLeftChild();
        }
        temp->print();
        cout << endl;
    }

    // Finds the biggest element in the tree and prints it
    void findBiggest() {
        Node<T> *temp = root;
        while(temp->getRightChild() != nullptr) {
            temp = temp->getRightChild();
        }
        temp->print();
        cout << endl;
    }

    // Prints all the elements stored in the BST in ascending order
    // Written recursively
    void sortAscending() {
        ascHelper(root);
        cout << endl;
    }

    // Prints all the elements stored in the BST in descending order
    // Written recursively
    void sortDescending() {
        desHelper(root);
        cout << endl;
    }

    // Get methods for variables in the BST Class
    Node<T>* getRoot() {
        return root;
    }
    int getnumberOfElements() {
        return numberOfElements;
    }
    int getHeight() {
        return height;
    }

    // Set methods for variables in the BST Class
    void setRoot(T *data) {
        root = new Node<T>(data);
    }
    void setnumberOfElements(int num) {
        numberOfElements = num;
    }
    void setHeight(int num) {
        height = num;
    }

    // Helper method for the print statement. Called recursively
    void printHelper(Node<T> *temp) {
        if(temp == nullptr){
            return;
        }else{
            temp->print();
            printHelper(temp->getLeftChild());
            printHelper(temp->getRightChild());
        }
    }

    // Helper method for the sort acsending method. Called recursively
    void ascHelper(Node<T> *temp) {
        if(temp == nullptr){
            return;
        }else{
            ascHelper(temp->getLeftChild());
            temp->print();
            ascHelper(temp->getRightChild());
        }
    }

    // Helper method for the sort descending method. Called recursively
    void desHelper(Node<T> *temp) {
        if(temp == nullptr){
            return;
        }else{
            desHelper(temp->getRightChild());
            temp->print();
            desHelper(temp->getLeftChild());
        }
    }

    // Helper for find kth element
    Node<T>* findHelper(Node<T>* node, int k, int& count) {
        if (node == nullptr) {
            return nullptr; // Base case: node is null
        }

        // Left (Smaller values)
        Node<T>* left = findHelper(node->getLeftChild(), k, count);
        if (left != nullptr) {
            return left; // Found in left subtree
        }

        // Current Node
        count++; // Increment count when visiting a node
        if (count == k) {
            return node; // If count equals k, this is the kth smallest element
        }

        // Right (Larger values)
        return findHelper(node->getRightChild(), k, count); // Continue to right subtree
    }
};

class Data {
private:
    int value;
public:
    // Constuctor for the Data class
    Data(int num) {
        value = num;
    }

    // Print method for data class
    void print() {
        cout << value << " ";
    }

    // Get methods for variables in the BST Class
    int getValue() {
        return value;
    }

    // Set methods for variables in the BST Class
    void setValue(int num) {
        value = num;
    }

};



int main() {
    int a[] = {10,45,23,67,89,34,12,99};
    Data* newData = new Data(a[0]);
    BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(newData);
    for(int i=1;i< (sizeof(a)/sizeof(int));i++)
    {
        newData = new Data(a[i]);
        newBST->insertElement(newData);
    }
    newBST->print();
    newBST->findSmallest();
    newBST->findBiggest();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete root
    newBST->print();
    newData = new Data(45);
    newBST->deleteElement(newData); //delete with two children
    newBST->print();
    newData = new Data(12);
    newBST->deleteElement(newData); //delete with one child
    newBST->print();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete a number that doesnt exist. What will you print?
    newBST->print();
    newBST->findKthElement(1); //first element
    newBST->findKthElement(2); //last element
    newBST->findKthElement(3); // some element in between
    newBST->findKthElement(4); // Edge case where item does not exist. What will you print?

    newBST->findKthElement(5); //first element
    newBST->findKthElement(6); //last element
    newBST->findKthElement(7); // some element in between
    newBST->findKthElement(8); // Edge case where item does not exist. What will you print?
    newBST->findKthElement(9);
    newBST->findKthElement(10);
    newBST->sortAscending();
    newBST->sortDescending();
    return 0;

}
