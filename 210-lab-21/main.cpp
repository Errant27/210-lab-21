// 210 | lab 21 | Neil Orton
// IDE used: Xcode
#include <iostream>
#include <string>
#include <random>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
//const int SIZE = 15;

class Goat {

private:
    int age;
    string name;
    string color;
    string names[5] = {"Teen", "Mature", "Senior", "Godlike", "Ascended"};
    string colors[5] = {"Yellow", "Red", "Mauve", "Gold", "White"};
    
    
public:
    Goat() { // Default constructor
        random_device randAge;
        uniform_int_distribution<int>age_Range(1, 20);    // Random number chosen for age
        random_device randName_Color;
        uniform_int_distribution<int>nc_Range(0, 5);    // Random number chosen for color/name array
        
        age = age_Range(randAge);
        name = names[nc_Range(randName_Color)];
        color = colors[nc_Range(randName_Color)];
    }
    
    Goat(int a, string n, string c) : age{ a }, name{ n }, color{ c }    // Parameter constructor
    {}
    
    const int getAge() { return age; }
    const string getName() { return name; }
    const string getColor() { return color; }

    
};    //End of Goat class

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat g, Node* p = nullptr, Node* n = nullptr) {
            data = g;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat g) {
        Node* newNode = new Node(g);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat g) {
        Node* newNode = new Node(g);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat g, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(g);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data.getAge() != value.getAge() && temp->data.getName() != value.getName() && temp->data.getColor() != value.getColor())
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data.getName() << " (Color: " << current->data.getColor() << ", Age: " << current->data.getAge() << ")" << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data.getName() << " (Color: " << current->data.getColor() << ", Age: " << current->data.getAge() << ")" << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};    // End of DoublyLinkedList class

// Driver program
int main() {
    DoublyLinkedList list;
    random_device randSize;
    uniform_int_distribution<int>size_Range(5, 20);
    
    int size = size_Range(randSize);    //Random size generated between 1 - 20
    

    for (int i = 0; i < size; ++i) {
        Goat goat;
        list.push_back(goat);
    }
    cout << "List forward: " << endl;
    list.print();

    cout << "List backward: " << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
