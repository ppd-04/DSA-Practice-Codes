#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>
#include<bits/stdc++.h>
/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here

    void destroyer(Node *trnode)
    {
        if (trnode == nullptr)
            return;
        destroyer(trnode->left);
        destroyer(trnode->right);
        delete trnode;
    }

    // parameter niye jhamela

    bool insertion_helper(Node *&node, Key key, Value value)
    {
        if (node == nullptr)
        {
            node = new Node(key, value);
            return true;
        }
        else if (key < node->key)
        {
            return insertion_helper(node->left, key, value);
        }
        else if (key > node->key)
        {
            return insertion_helper(node->right, key, value);
        }
        else
        {
            return false;
        }
    }

    Node *remove_helper(Node *node, Key key, bool &found)
    {
        if (node == nullptr)
        {
            found = false;
            return nullptr;
        }
        if (key < node->key)
        {
            node->left = remove_helper(node->left, key, found);
        }
        else if (key > node->key)
        {
            node->right = remove_helper(node->right, key, found);
        }
        else
        {
            found = true;
            if (node->left == nullptr)
            {
                Node *sv = node->right;
                delete node;
                return sv;
            }
            else if (node->right == nullptr)
            {
                Node *sv = node->left;
                delete node;
                return sv;
            }
            else
            {
                Node *newSubtreeRoot = find_min_node(node->right);
                node->key = newSubtreeRoot->key;
                node->value = newSubtreeRoot->value;
                node->right = remove_helper(node->right, newSubtreeRoot->key, found);
            }
        }
        return node;
    }

    Node *find_min_node(Node *node) const
    {
        if (node == nullptr)
        {
            throw std::runtime_error("Empty Subtree");
        }
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    bool find_helper(Node *node, Key key) const
    {
        if (node == nullptr)
        {
            return false;
        }
        if (node->key == key)
        {
            return true;
        }
        if (key < node->key)
        {
            return find_helper(node->left, key);
        }
        return find_helper(node->right, key);
    }

    bool get_helper(Node *node, Key key, Value &value) const
    {
        if (node == nullptr)
            return false;
        if (key == node->key)
        {
            value = node->value;
            return true;
        }
        if (key < node->key)
        {
            return get_helper(node->left, key, value);
        }
        return get_helper(node->right, key, value);
    }
    bool update_helper(Node *node, Key key, Value value)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (key == node->key)
        {
            node->value = value;
            return true;
        }
        if (key < node->key)
        {
            return update_helper(node->left, key, value);
        }
        return update_helper(node->right, key, value);
    }

    void print_default(Node *node) const
    {
        if (node == nullptr)
        {
            std::cout << "()";
            return;
        }
        std::cout << "(" << node->key << ":" << node->value;

        if (node->left != nullptr)
        {
            std::cout << " ";
            print_default(node->left);
        }
        if (node->right != nullptr)
        {
            if (node->left == nullptr)
            {
                std::cout << " ()";
            }
            std::cout << " ";
            print_default(node->right);
        }
        std::cout << ")";
    }

    void print_inorder(Node *node, bool &isFirstTime) const
    {
        if (node == nullptr)
            return;
        print_inorder(node->left, isFirstTime);
        if (!isFirstTime)
            std::cout << " ";
        isFirstTime = false;
        std::cout << "(" << node->key << ":" << node->value << ")";
        print_inorder(node->right, isFirstTime);
    }

    void print_preorder(Node *node, bool &isFirstTime) const
    {
        if (node == nullptr)
            return;
        if (!isFirstTime)
            std::cout << " ";
        isFirstTime = false;
        std::cout << "(" << node->key << ":" << node->value << ")";
        print_preorder(node->left, isFirstTime);
        print_preorder(node->right, isFirstTime);
    }

    void print_postorder(Node *node, bool &isFirstTime) const
    {
        if (node == nullptr)
        {
            return;
        }
        print_postorder(node->left, isFirstTime);
        print_postorder(node->right, isFirstTime);
        if (!isFirstTime)
            std::cout << " ";
        isFirstTime = false;
        std::cout << "(" << node->key << ":" << node->value << ")";
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        destroyer(root);
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic

        bool is_done = insertion_helper(root, key, value);
        if (is_done == true)
            node_count++;
        return is_done;
    }

    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic

        bool found = false;
        root = remove_helper(root, key, found);
        if (found == true)
        {
            node_count--;
        }
        return found;
    }

    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic
        return find_helper(root, key);
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        Value value;
        if (get_helper(root, key, value) == true)
        {
            return value;
        }
        throw std::runtime_error("Key not found");
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        if (!update_helper(root, key, value))
        {
            throw std::runtime_error("Key not found");
        }
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        destroyer(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic

        return node_count;
    }

    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return node_count == 0;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic
        if (root == nullptr)
        {
            throw std::runtime_error("Tree is empty");
        }
        Node *cur = root;
        while (cur->left)
        {
            cur = cur->left;
        }
        return cur->key;
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic
        if (root == nullptr)
        {
            throw std::runtime_error("Tree is empty");
        }
        Node *cur = root;
        while (cur->right)
        {
            cur = cur->right;
        }
        return cur->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        if (traversal_type == 'D' || traversal_type == 'd')
        {
            print_default(root);
        }
        else if (traversal_type == 'I' || traversal_type == 'i')
        {
            bool isfirsttime = true;
            print_inorder(root, isfirsttime);
        }
        else if (traversal_type == 'P' || traversal_type == 'p')
        {
            bool isFirsttime = true;
            print_preorder(root, isFirsttime);
        }
        else if (traversal_type == 'O' || traversal_type == 'o')
        {
            bool isFirsttime = true;
            print_postorder(root, isFirsttime);
        }
        else
        {
            throw std::invalid_argument("Invalid");
        }
    }


    Node* ceil(Node* node, Key key, Value val){
        // return find_min_node(node->right, key, val);
        if(node == nullptr){
            std::cout << "Invalid Node" << std::endl;
            return nullptr;
        }
        Node* tmp = node;
        Node* res = nullptr;
        while(tmp){
            if(tmp->key == key){
                return tmp;
            }
            if(tmp->key < key){
                
                tmp = tmp->right;
            }else if(tmp->key > key){
                res = tmp;
                tmp = tmp->left;
            }
        }

        return res;
    }

    Node* floor(Node* node, Key key, Value val){
        if(node == nullptr){
            std::cout << "Invalid Node" << std::endl;
            return nullptr;
        }

        Node* temp = node;
        Node* res = nullptr;

        while(temp){
            if(temp->key == key){
                return temp;
            }
            if(temp->key > key){
                temp = temp->left;
            }
            else if(temp->key < key){
                res = temp;
                temp = temp->right;
            }

        }
        return res;
    }


    // Kth Largest or Smallest element code

    void kthinorderTraversalBrute(Node* node, int* arr, int* idx) {
        if (node == nullptr) return;

        kthinorderTraversal(node->left, arr, idx);
        arr[*idx] = node->key;
        (*idx)++;
        kthinorderTraversalBrute(node->right, arr, idx);
    }

    int* kthLargestSmallestBrute(Node* node, int k, Key key, Value val) {
        if (node == nullptr) return nullptr;

        // Estimate the number of nodes (or use a dynamic structure like vector)
        int maxNodes = 1000; // Adjust as needed
        int* arr = new int[maxNodes];
        int i = 0;

        kthinorderTraversalBrute(node, arr, &i);

        if (k > i) {
            std::cout << "k is larger than the number of nodes." << std::endl;
            delete[] arr;
            return nullptr;
        }

        int* ans = new int[2];
        ans[0] = arr[i - k];  // kth largest
        ans[1] = arr[k - 1];  // kth smallest

        delete[] arr;
        return ans;
    }

    // Optimal Approach

    void reverseInorderkLargest(Node* node, int& counter, int k, int& kLargest){
        if(node == nullptr || counter >= k){
            return;
        }
        reverseInorderkLargest(node->right, counter, k, kLargest);
        
        counter++;

        if(counter == k){
            kLargest = node->value;
            return;
        }

        reverseInorderkLargest(node->left, counter, k, kLargest);

    }

    void inorderkSmallest(Node* node, int& counter, int k, int& kSmallest){
        if(node == nullptr || counter >= k){
            return;
        }

        inorderkSmallest(node->left, counter, k, kSmallest);

        counter++;

        if(counter == k){
            kSmallest = node->value;
            return;
        }

        inorderkSmallest(node->right, counter, k, kSmallest);
    }

    int kLargest(Node* node, int k){
        if(node == nullptr){
            return -1;
        }

        int counter = 0;
        // int kSmallest = INT_MAX;
        int kLargest = INT_MIN;

        reverseInorderkLargest(node, counter, k, kLargest);
        std::cout << "The kth Largest Value: "<< kLargest << std::endl;
        return kLargest;
    }

    int kSmallest(Node* node, int k){
        if(node == nullptr){
            return -1;
        }
        int counter = 0;
        int kSmallest = INT_MAX;
        
        inorderkSmallest(node, counter, k, kSmallest);
        std::cout << "The kth Smallest Value: "<< kSmallest << std::endl;
        return kSmallest;
    }





    // If a tree bst or not
    bool isBST_inorder(Node* root, int& prev){
        if(root == nullptr){
            return true;
        }

        if(!isBST_inorder(root->left, prev)){
            return false;
        }
        
        if(prev >= root->value){
            return false;
        }
        prev = root->value;

        isBST_inorder(root->right, prev);
    }

    bool isBST(Node* root){
        int prev = INT_MIN;
        return isBST_inorder(root, prev);
    } 




    // Find the lowest common ancestor

    Node* LCA(Node* root, Node* n1, Node* n2){
        if(root == nullptr){
            return nullptr;
        }

        if(root->value < n1->value && root->value < n2->value){
            return LCA(root->right, n1, n2);
        }

        if(root->value > n1->value && root->value > n2->value){
            return LCA(root->left, n1, n2);
        }
        return root;

    }




    // Merge 2 BST


    void merge_inorder(Node* root, vector<int>& arr){
        if(!root) return;
        
        merge_inorder(root->left, arr);
        arr.push_back(root->value);
        merge_inorder(root->right, arr);
    }

    void MergeBST(Node* root1, Node* root2){
        
        vector<Node*> v;




    }

    
    bool HasCycle() const {
    bool* visited = new bool[capacity]();
    int* parent = new int[capacity]();
    ListQueue q;

    // Check all nodes to handle disconnected components
    for (int start = 0; start < capacity; start++) {
        if (!exists[start] || visited[start]) continue; // Skip non-existent or visited nodes

        // Start BFS from 'start'
        q.enqueue(start);
        visited[start] = true;
        parent[start] = -1; // No parent for the start node

        while (!q.empty()) {
            int cur = q.dequeue();

            // Check neighbors
            Node* neighbour = adjacentList[cur];
            while (neighbour) {
                int nxt = neighbour->data;
                if (exists[nxt]) { // Only process valid neighbors
                    if (!visited[nxt]) {
                        q.enqueue(nxt);
                        visited[nxt] = true;
                        parent[nxt] = cur;
                    } else if (nxt != parent[cur]) {
                        // Visited node that's not the parent indicates a cycle
                        delete[] visited;
                        delete[] parent;
                        return true;
                    }
                }
                neighbour = neighbour->next;
            }
        }
    }

    delete[] visited;
    delete[] parent;
    return false;
}


    // ends here

};

#endif // LISTBST_H
