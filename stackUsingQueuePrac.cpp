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

    void Push(int x){
        Node* newNode = new Node(x);

        if(front == nullptr){
            front = newNode;
            rear = newNode;
        }
        else{
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

    int get_front(){
        if(front == nullptr){
            return -1;
        }
        return front->data;
    }
    
    int get_rear(){
        if(front == nullptr){
            return -1;
        }
        return rear->data;
    }
    int get_size(){
        return size;
    }

};

class Stack{
public:
    Queue q;

    void Push(int x){
        q.Push(x);  
        int sz = q.get_size();

        for(int i = 1; i < sz; i++){
            q.Push(q.get_front());
            q.Pop();
        }
    }

    int Pop(){
        if(q.get_size() == 0){
            return -1;
        }
        return q.Pop();
    }

    int get_size(){
        return q.get_size();
    }
};