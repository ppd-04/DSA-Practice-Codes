#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    
    Node* left;
    Node* right;

    Node(){
        data = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(int data){
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
    Node(int data, Node* left, Node* right){
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

void preorder(Node* node){
    if(node == NULL) return;

    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void inorder(Node* node){
    if(node == NULL) return;

    inorder(node->left);
    cout << node->data <<  " ";
    inorder(node->right);
}

void postorder(Node* node){
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

void levelorder(Node* node){
    vector<vector<int>> ans;
    if(node == NULL) return;

    queue<Node*> q;

}





int main(){

}