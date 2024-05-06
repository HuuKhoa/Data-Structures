// Huu-Khoa Nguyen
// CS 210
// Programming Assignment 1

#include <iostream>
using namespace std;

// Data Class: This is what goes inside your Node
class Process {
public:
    // Initialize Variables
    string processName;
    int totalTime;
    Process (string processName, int totalTime){
        // Fill Constuctor Here
        this->processName = processName;
        this->totalTime = totalTime;
    }

    // Update the total time for Process
    void updateRunTime(int quantumTime) {
        totalTime = totalTime - quantumTime;
    }

    // Print the Process name and Total time
    void print() {
        cout << "Process " << processName << " " << totalTime << " Seconds Remaining";
    }
};

// Node Class: Node for the DoublyLinkedList
template <typename T> class Node {
public:
    // Initialize Variables for the Node class
    T *data;
    Node<T> *next;
    Node<T> *prev;

    // Constructor for the Node Class
    Node (T *data){
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }

    // Print the Data in a Node
    void print(){
        data->print();
    }
};

//CircularDoublyLinkedList Class: Container for Nodes
template <typename T> class CircularDLL {
private:
    // Initialize Variables for the Circular DLL Class
    Node<T> *head;
    Node<T> *curr;
    int length;
public:
    // Constructor for Circular DLL class
    CircularDLL(T *data) {
        Node<T> *newNode = new Node<T>(data);
        head = newNode;
        head->next = head;
        head->prev = head;
        curr = newNode;
        length = 1;
    }

    // Destuctor for Circular DLL Class
    ~CircularDLL() {
        Node<T> *temp = head;
        // For loop to loop through the List
        for(int i = 0; i < length; i++) {
            head = head->next;
            delete temp;
            temp = head;
        }
        length = 0;
    }

    // Print the entire List
    void PrintList() {
        Node<T> *temp = head;

        // Checks if the List is Empty
        if(this->isEmpty()){
            return;
        }

        // Loops through the entire list and prints all the values
        for(int i = 0; i < length; i++){
            temp->print();
            cout << endl;
            temp = temp->next;
        }
    }

    // Method to insert a process into the List
    void insertProcess(T *data) {
        Node<T> *newNode = new Node<T>(data);

        // Checks if the list empty first
        if(this->isEmpty()){
            head = newNode;
            curr = newNode;
            length = 1;
        } else {
            // Inserts the process at the end of the list
            curr = head->prev;
            curr->next = newNode;
            newNode->prev = curr;
            head->prev = newNode;
            newNode->next = head;
            length++;
        }
    }

    // Method to delete a process from the list
    void deleteProcess(T *data) {
        Node<T> *delNode = new Node<T>(data);

        // Checks if we are deleting the head node of the list and moves the pointer to the next node
        if(delNode->data == head->data){
            head = curr->next;
        }

        // Iterates through the list to find the node we are deleting
        while(curr->data != delNode->data){
            curr = curr->next;
        }

        // Deletes the specific node
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        Node<T> *temp = curr->next;
        delete curr;
        curr = temp;
        length--;
    }

    // Method to check if the list is empty
    bool isEmpty(){
        return length == 0;
    }

    // Method to get the value of the current node pointer
    Node<T>* getCurrent(){
        return curr;
    }

    // Method to move to the next point in the list
    Node<T>* setCurrentNext(){
        return curr = curr->next;
    }

    // Method to set the current node pointer to the head node
    Node<T>* setCurrentHead(){;
        return curr = head;
    }

    // Meth to get the length of the list
    int getLength(){
        return length;
    }

};

int main() {

    // Pre generate 5 processes to fill the list with
    Process *a = new Process("A", 10);
    Process *b = new Process("B", 8);
    Process *c = new Process("C", 10);
    Process *d = new Process("D", 12);
    Process *e = new Process("E", 15);


    // Create the list and insert the 5 processes
    CircularDLL<Process> *list = new CircularDLL<Process>(a);
    list->insertProcess(b);
    list->insertProcess(c);
    list->insertProcess(d);
    list->insertProcess(e);

    // Gets the Quantum Time from the User and prints the original list
    list->setCurrentHead();
    cout << endl;
    int quantTime;
    cout << "Please enter Quantum Time for Processes:" << endl;
    cin >> quantTime;
    cout << "Original List" << endl;
    cout << endl;
    list->PrintList();
    cout << endl;

    // The while loop keeps looping until the list is empty
    int count = 1;
    while(!list->isEmpty()){
        cout << "Running Process " << count << endl;
        cout << endl;

        // Updates all the methods currently in the list
        for(int i = 0; i < list->getLength(); i++) {
            list->getCurrent()->data->updateRunTime(quantTime);
            list->setCurrentNext();
        }

        // Checks the entire list after each cycle to see if any of the processes are finished and deletes them
        for(int i = 0; i < list->getLength(); i++) {
            if(list->getCurrent()->data->totalTime <= 0){
                list->deleteProcess(list->getCurrent()->data);
                i--;
            } else {
                list->setCurrentNext();
            }
        }

        // Breaks out of the loop early if the list is empty
        if(list->isEmpty())
            break;

        // Asks the user if they want to add another process
        list->PrintList();
        cout << endl << "After cycle " << count << ", " << count * quantTime << " second elapses." << endl;
        count++;
        cout << endl << "Add a Process? (Y/N):" << endl;
        string yesNo;
        cin >> yesNo;

        // If yes it asks the user for specific info for the new process and generates and adds it to the list
        if(yesNo == "Y") {
            string proName;
            int proTime;
            cout << "Please enter Process Name:" << endl;
            cin >> proName;
            cout << "and Total Time:" << endl;
            cin >> proTime;

            // Creates the new process and adds it to the list
            Process *newPro = new Process(proName, proTime);
            list->insertProcess(newPro);
        }

        cout << endl;

    }

    // Lets the user know all the processes are complete
    cout << "All Processes Complete!" << endl;
    return 0;
}
