#include <bits/stdc++.h>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to perform BFS (level-order traversal)
vector<int> bfs(Node* root, vector<int>adj, int size) {
    if (root == nullptr) return;

    queue<int> q;
    vector<int> v;
    int visited[size] = {0};
    q.push(root->data);

    while(!q.empty()){
        int node = q.front();
        q.pop();
        v.push_back(node);

        for(auto it : adj[node]){
            if(!visit[it]){
                visited[it] = 1;
                q.push(it);
            }
        }
    }
    return v;

}

int main() {
    // Example BST:
    //       4
    //     /   \
    //    2     6
    //   / \   / \
    //  1   3 5   7

    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(6);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right->left = new Node(5);
    root->right->right = new Node(7);

    bfs(root);

    return 0;
}