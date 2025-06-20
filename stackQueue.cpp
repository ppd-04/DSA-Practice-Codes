#include<iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node(int value, Node* next_node = nullptr) : data(value), next(next_node){}
    
};

class Queue{
public:
    Node* front;
    Node* rear;
    int size;

    Queue(){
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    ~Queue(){
        while(front){
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void Push(int x){
        Node* newNode = new Node(x);
        if(front == nullptr){
            front = newNode;
            rear = newNode;
        }else{
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    int Pop(){
        if(front == nullptr){
            return -1;
        }
        int ans = front->data;
        Node* temp = front;
        front = front->next;
        delete temp;
        if(front == nullptr){
            rear = nullptr;
        }
        size--;
        return ans;
    }

    int front(){
        if(front == nullptr){
            return -1;
        }
        return front->data;
    }
    int rear(){
        if(front == nullptr){
            return -1;
        }
        return rear->data;
    }
    int size(){
        return size;
    }

};

class Stack{
public:
    Node* head;
    int size;

    Stack(){
        head = nullptr;
        size = 0;
    }
    ~Stack(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
    }
        
    void Push(int x){
        Node* newNode = new Node(x, head);

        head = newNode;
        size++;
    }

    int Pop(){
        if(head == nullptr){
            return -1;
        }
        int ans = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return ans;   
    }

    int Top(){
        if(head == nullptr){
            return -1;
        }
        return head->data;
    }
    int size(){
        return size;
    }


};