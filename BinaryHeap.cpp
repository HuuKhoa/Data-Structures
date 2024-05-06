// Huu-Khoa Nguyen
// RedID 823537020
// CS210
// Programming Assignment 3

// Include statements for necessary libraries used in the code
#include <iostream>
#include <queue>
using namespace std;

// Declare global variable VERTEXCOUNT
const int VERTEXCOUNT = 5;

// Class for Nodes
template <typename T> class Node {
private:
    // Private variables used only in the Node class
    T* data;
    Node<T>* leftChild;
    Node<T>* rightChild;
    Node<T>* parent;
public:
    // Constructor for Node Class
    Node (T *data) {
        this->data = data;
        parent = nullptr;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    // Print method for the Node class
    void print(){
        data->print();
    }

    // Compare 2 data values
    bool compare(T* data1, T* data2){
        return *data1 < *data2;
    }

    // Get methods for variables in the Node Class
    T* getData() {return data;}
    Node<T>* getParent() {return parent;}
    Node<T>* getLeftChild() {return leftChild;}
    Node<T>* getRightChild() {return rightChild;}

    // Set methods for variables in the Node Class
    void setData(T *newData) {data = newData;}
    void setParent(Node *newNode) {parent = newNode;}
    void setLeftChild(Node *newNode) {leftChild = newNode;}
    void setRightChild(Node *newNode) {rightChild = newNode;}

};

// Class for the Binary Heap
template <typename T> class BinaryHeap {
private:
    Node<T>* root;
    Node<T>* lastNode;
    int numberOfElements;
    int height;
public:
    // Constructors for Binary Heap
    BinaryHeap() {
        root = nullptr;
        lastNode = nullptr;
        numberOfElements = 0;
        height = 0 ;
    }
    BinaryHeap(T *data){
        Node<T> *newNode = new Node<T>(data);
        root = newNode;
        numberOfElements = 1;
        height = 1;
    }

    // Destructor for Binary Heap
    ~BinaryHeap(){
        for(int i = 0; i < numberOfElements; i++){
            deleteMin();
        }
        numberOfElements = 0;
    }

    // Insert an Element into the heap and heapifies
    void insertElement(T* data) {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* current;

        // Checks if root is null in the heap
        if(root == nullptr) {
            root = newNode;
            lastNode = newNode;
        } else {
            // Create a queue for level order traversal to keep track of where to insert the new node
            queue<Node<T>*> q;
            q.push(root);

            // Uses level order traversal to make sure that the node is inserted at the correct position
            while (!q.empty()) {
                current = q.front();
                q.pop();

                // Checks the left side of a node and inserts it there if it is a valid insertion point
                if (current->getLeftChild() == nullptr) {
                    current->setLeftChild(newNode);
                    newNode->setParent(current);
                    lastNode = newNode;
                    break;
                } else {
                    q.push(current->getLeftChild());
                }

                // Checks the right side of a node and inserts it there if it is a valid insertion point
                if (current->getRightChild() == nullptr) {
                    current->setRightChild(newNode);
                    newNode->setParent(current);
                    lastNode = newNode;
                    break;
                } else {
                    q.push(current->getRightChild());
                }
            }
        }
        // Heapifies up and updates the number of elements
        heapifyUp(newNode);
        numberOfElements++;
    }

    // Deletes the smallest node in a heap and then heapifies
    T* deleteMin() {
        T* temp = root->getData();
        if(root == lastNode){
            delete root;
            root = nullptr;
            lastNode = nullptr;
        } else {
            // Swaps the last node in the heap and the root
            swap(lastNode, root);

            // Deletes the appropriate node after the values have been swapped
            if (lastNode->getParent()->getLeftChild() == lastNode) {
                lastNode->getParent()->setLeftChild(nullptr);
            } else {
                lastNode->getParent()->setRightChild(nullptr);
            }
        }
        // Down heapifies and updates the number of elements
        heapifyDown(root);
        numberOfElements--;
        return temp;
    }

    // Method to swap two nodes
    void swap(Node<T>* node1, Node<T>* node2) {
        T* temp = node1->getData();
        node1->setData(node2->getData());
        node2->setData(temp);
    }

    // Method to heapify up
    void heapifyUp(Node<T>* node) {
        while(node != nullptr && node->getParent() != nullptr && node->compare(node->getData(), node->getParent()->getData()) == true) {
            swap(node, node->getParent());
            node = node->getParent();
        }
    }

    // Method to heapify down
    void heapifyDown(Node<T>* node){
        if (node == nullptr) {
            return;
        }
        while(node != nullptr) {
            Node<T>* smallest = node;
            // Checks the left side to see if a swap needs to be made
            if (node->getLeftChild() != nullptr && node->compare(node->getLeftChild()->getData(), smallest->getData())) {
                smallest = node->getLeftChild();
            }
            // Checks the right side to see if a swap needs to be made
            if (node->getRightChild() != nullptr && node->compare(node->getRightChild()->getData(), smallest->getData())) {
                smallest = node->getRightChild();
            }
            // If a swap is necessary swap the two nodes
            if (smallest != node) {
                swap(node, smallest);
                node = smallest;
            } else {
                break;
            }
        }
    }

    // Updates the last node to keep track of it
    void updateLastNode() {
        queue<Node<T>*> q;
        q.push(root);
        Node<T>* last;
        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->getLeftChild()) {
                q.push(last->getLeftChild());
            }
            if (last->getRightChild()) {
                q.push(last->getRightChild());
            }
        }
        lastNode = last;
    }

    // Get methods for variables in the BST Class
    Node<T>* getRoot() {return root;}
    int getNumElements() {return numberOfElements;}
    int getHeight() {return height;}

    // Set methods for variables in the BST Class
    void setRoot(T *data) {root = new Node<T>(data);}
    void setNumElements(int num) {numberOfElements = num;}
    void setHeight(int num) {height = num;}
};

class Data {
private:
    int sourceVertex;
    int destinationVertex;
    int edgeCost;
public:
    // Constructor for the Data class
    Data(int source, int destination, int edge) {
        sourceVertex = source;
        destinationVertex = destination;
        edgeCost = edge;
    }

    // Print method for the data class
    void print() {
        cout << sourceVertex << " - " << destinationVertex << " -> " << edgeCost << endl;
    }

    // Compare operator used in the Node class
    bool operator<(const Data& other) const {
        return edgeCost < other.edgeCost;
    }

    // Getters for the Data Class
    int getSource() {return sourceVertex;}
    int getDestination() {return destinationVertex;}
    int getEdgeCost(){return edgeCost;}

    // Setters for the Data Class
    void setSource(int newSource){sourceVertex = newSource;}
    void setDestination(int newDestination){destinationVertex = newDestination;}
    void setEdgeCost(int newEdgeCost){edgeCost = newEdgeCost;}
};

// Runs the Prims algorithm
void runPrims(int G [VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data> binHeap) {
    // Keeps track of the visited nodes
    vector<bool> visited(VERTEXCOUNT, false);
    binHeap.insertElement(new Data(0, 0, 0));
    int numVerticesInMST = 0;
    while (binHeap.getRoot() != nullptr && numVerticesInMST < VERTEXCOUNT) {
        Data* minEdge = binHeap.deleteMin();
        int v = minEdge->getDestination();
        if (!visited[v]) {
            if (minEdge->getSource() != v) {
                minEdge->print();
            }
            visited[v] = true;
            numVerticesInMST++;
            for (int u = 0; u < VERTEXCOUNT; u++) {
                if (G[v][u] != 0 && !visited[u]) {
                    binHeap.insertElement(new Data(v, u, G[v][u]));
                }
            }
        }
    }
}


int main() {
    // Initialize the graph
    int G[VERTEXCOUNT][VERTEXCOUNT] = {{0,  3,  65, 0,  0},
                   {3,  0,  85, 20, 45},
                   {65, 85, 0,  41, 77},
                   {0,  20, 41, 0,  51},
                   {0,  45, 77, 51, 0}};
    // Initialize the Binary Heap
    BinaryHeap<Data> binHeap;
    cout << "Prim's MST is Edge -> Cost" << endl;
    // Run the prims algorithm
    runPrims(G, binHeap);
    return 0;
}