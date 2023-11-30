// Name: Emilio Maset
// File Name: stack.h
// Date: 23 October, 2023
// Program Description: Header file for stack

using namespace std;

struct Node {
    int content;
    Node* next;
};

class Stack {
private:
    Node* top;
public:
    Stack();
    ~Stack();
    void clear();
    void push(int pushContent);
    int pop();
    bool isEmpty();
};