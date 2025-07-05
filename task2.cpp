#include <iostream>
#include <fstream>
#include <string>
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
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1) {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2) {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Phil's words
        // Start your code here

        string word;
        in_file >> word;

        if(bst1->find(word)){
            int counter = bst1->get(word);
            bst1->update(word, counter + 1);
        }else{
            bst1->insert(word,1);
        }

        // End your code here
    }
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        string word;
        in_file >> word;

        if(bst2->find(word)){
            int counter = bst2->get(word);
            bst2->update(word, counter+1);
        }else{
            bst2->insert(word,1);
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here

    cout << "Phil's words:" << endl;
    cout << "BST (In-order): ";
    bst1->print('I');
    cout << endl;
    
    cout << "Claire's words: " << endl;
    cout << "BST (In-order): ";
    bst2->print('I');
    cout << endl;


    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true) {
        //adding it later
        bool won = false;


        string word;
        in_file >> word;
        if(!in_file){
            break;
        }
        
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here
        bool phil_played = false;
        bool claire_played = false;

        // there should be a part when there is no word in the file

        if(bst1->find(word)){
            int counter = bst1->get(word);

            if(counter > 1){
                bst1->update(word, counter-1);
            }else{
                bst1->remove(word);
            }
            phil_played = true;
        }

        if(bst2->find(word)){
            int counter = bst2->get(word);

            if(counter > 1){
                bst2->update(word, counter-1);
            }else{
                bst2->remove(word);
            }
            claire_played = true;
        }


        if(phil_played){
            cout << "Phil has " << word << "!" << endl;
        }
        if(claire_played){
            cout << "Claire has " << word << "!" << endl;
        }

        // cout << "Phil's remaining words:" << endl;
        // cout << "BST (In-order): ";
        // bst1->print('I');
        // cout << endl;
        // cout << endl;

        // cout << "Claire's remaining words:" << endl;
        // cout << "BST (In-order): ";
        // bst2->print('I');
        // cout << endl;
        // cout << endl;

        // if(bst1->empty() && bst2->empty()){
        //     break;
        // }
        // else if(bst1->empty()){
        //     cout << "Phil wins!" << endl;
        // }
        // else if(bst2->empty()){
        //     cout << "Claire wins!" << endl;
        // }

        if(bst1->empty() && bst2->empty()){
            cout << endl;
            cout << "Phil's remaining words:" << endl;
            cout << "BST (In-order): ";
            bst1->print('I');

            cout << endl;
            cout << "\nClaire's remaining words:" << endl;
            bst2->print('I');
            cout << endl;
            break;
        }
        else if(bst1->empty()){


            // adding this condition later
            // if(won == false){
            //     cout << "\nPhil's remaining words:" << endl;
            //     cout << "BST (In-order): ";
            //     bst1->print('I');

            //     cout << "\n\nClaire's remaining words:" << endl;
            //     cout << "BST (In-order): ";
            //     bst2->print('I');
            // }






            // cout << "\nPhil's remaining words:" << endl;
            // cout << "BST (In-order): ";
            // bst1->print('I');

            // cout << "\n\nClaire's remaining words:" << endl;
            // cout << "BST (In-order): ";
            // bst2->print('I');

            // phil wim korbe, 

            // cout << "\n\nPhil wins!" << endl;
            cout << "Phil wins!" << endl;
            won = true;
            // addingbreak here
            break;


        }
        else if(bst2->empty()){
            // cout << "\nPhil's remaining words:\nBST (In-order): ";
            // bst1->print('I');


            // cout << " \n\nClaire's remaining words:\nBST (In-order): ";
            // bst2->print('I');
            cout << " \n\nClaire wins!\n";
            won = true;

            // addingbreakheretoo
            break;
        }

        if(won == false){
            cout << "\nPhil's remaining words:" << endl;
            cout << "BST (In-order): ";
            bst1->print('I');

            cout << "\n\nClaire's remaining words:\n";
            cout << "BST (In-order): ";
            bst2->print('I');
            
            cout << " \n\n==============================\n";
        }
        // cout << "\nPhil's remaining words:" << endl;
        // cout << "BST (In-order): ";
        // bst1->print('I');

        // cout << "\n\nClaire's remaining words:\n";
        // cout << "BST (In-order): ";
        // bst2->print('I');
        
        // cout << " \n\n==============================\n";


        // cout << "==============================\n";
        // End your code here
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}

