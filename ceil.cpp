// #include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here

        if(c == 'F'){
            int key;
            in_file >> key;
            if(bst->find(key)){
                cout << "Key " << key << " found in BST." << endl;  
            }else{
                cout << "Key " << key << " not found in BST." << endl;
            }
        }
        else if(c == 'E'){
            if(bst->empty()){
                cout << "Empty" << endl;
            }else{
                cout << "Not empty" << endl;
            }
        }
        else if(c == 'I'){
            int key;
            in_file >> key;
            if(bst->insert(key,key)){
                cout << "Key " << key << " inserted into BST, BST (Default): ";
                bst->print('D');
                cout << endl;
            }
            else{
                cout << "Insertion failed! Key " << key << " already exists in BST, BST (Default): ";
                bst->print('D');
                cout << endl;
            }
        }
        else if(c == 'D'){
            int key;
            in_file >> key;
            if(bst->remove(key)){
                cout << "Key " << key << " removed from BST, BST (Default): ";
                bst->print('D');
                cout << endl;
            }else{
                cout << "Removal failed! Key " << key << " not found in BST, BST (Default): ";
                bst->print('D');
                cout << endl;
            }
        }
        else if(c == 'M'){
            string str;
            in_file >> str;
            if(str == "Min"){
                int minimumKey = bst->find_min();
                cout << "Minimum value: " << minimumKey << endl;
            }
            else if(str == "Max"){
                int maximumKey = bst->find_max();
                cout << "Maximum value: " << maximumKey << endl;
            }
        }
        else if(c == 'T'){
            string whichTraversal;
            in_file >> whichTraversal;

            cout << "BST (" << whichTraversal << "-order): ";
            if(whichTraversal == "In"){
                bst->print('I');
            }else if(whichTraversal == "Pre"){
                bst->print('P');
            }else if(whichTraversal == "Post"){
                bst->print('O');
            }
            cout << endl;
        }

        else if(c == 'S'){
            cout << "Size: " << bst->size() << endl;
        }



        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}
