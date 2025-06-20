#include<iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;

    Node(int val, Node* next_node = nullptr) : data(val), next(next_node){} 
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
        size--;
        return ans;
    }
    int Top(){
        if(head == nullptr){
            return -1;
        }
        return head->data;
    }
    int get_size(){
        return size;
    }
    bool empty(){
        return head==nullptr;
    }

};

class Queue{
public:
    Stack input, output;

    void Push(int x){
        while(!input.empty()){
            output.Push(input.head->data);
            input.Pop();
        }
        output.Push(x);
        while(!output.empty()){
            input.Push(output.head->data);
        }

    }   

    int Pop(){
        if(input.empty()){
            return -1;
        }
        while(!input.empty()){
            output.Push(input.head->data);
            input.Pop();
        }
        int ans = output.Pop();
        while(!output.empty()){
            input.Push(output.head->data);
            output.Pop();
        }
        return ans;
    }
    
};