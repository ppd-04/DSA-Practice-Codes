#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include<list>
#include<unordered_set>
#include <ctime>

using namespace std;
const int INF = 1e9;


const int INIT_SIZE = 13;
const double MAX_LOAD = 0.5;
const double MIN_LOAD = 0.25;


bool isPrime(int n);
int nextPrime(int n);
int prevPrime(int n);


class HashMain{
public:
    int size;
    int count;
    int collisions;
    int lastHits;
    int konFunction;

    int koytaInsertAfterResize;
    int koytaDeleteAfterResize;
    int sizeAtLastResize;

    HashMain(int s, int konFunction){
        size = s;
        count = 0;
        collisions = 0;
        lastHits = 0;
        koytaDeleteAfterResize=0;
        koytaInsertAfterResize=0;
        this->konFunction=konFunction;
        sizeAtLastResize=0;
    }
    virtual ~HashMain(){}


    int hashFunction(string key){
        int hash = 0;
        int p = 31;

        for(char c : key){
            hash = (hash*p+c)%size;
        }
        return hash;
    }
    int hashFunction2(string key){
        int hash = 0;
        int p = 17;
        for(char c : key){
            hash = (hash*p+c)%size;
        }
        return (hash%(size-1) +1) ;
    }

    double loadFactor(){
        return (double)count/size;
    }

    virtual void insert(string, int)=0;
    virtual void remove(string)=0;
    virtual bool search(string)=0;
    virtual void reHash(int newSize)=0;

};


class DoubleHashTable:public HashMain{
public:
    vector<pair<string, int>> table;
    vector<int> used;
    // int koytaInsertAfterResize;
    // int koytaDeleteAfterResize;

    DoubleHashTable(int s, int k) : HashMain(s, k){
        table.resize(s);
        used.resize(s, 0);
        // koytaDeleteAfterResize=0;
        // koytaInsertAfterResize= 0;
    }

    void reHash(int newSize){
        // hashingOrNot = true;
        vector<pair<string, int>> oldTable = table;
        vector<int> oldUsed = used;
        int oldSize = size;

        table.clear();
        used.clear();
        size = newSize;
        table.resize(newSize);
        used.resize(newSize, 0);

        sizeAtLastResize=count;
        count = 0;
        // collisions=0;
        koytaDeleteAfterResize=0;
        koytaInsertAfterResize=0;

        for(int i = 0; i < oldSize; i++){
            if(oldUsed[i]==1){
                int h1 = (konFunction == 1) ? hashFunction(oldTable[i].first) : hashFunction2(oldTable[i].first);
                int h2 = (konFunction == 1) ? hashFunction2(oldTable[i].first) : hashFunction(oldTable[i].first);
                if(h2 == 0) h2 = 1;

                for(int j=0; j<size; j++){
                    int idx = (h1 + j*h2)%size;

                    if(used[idx] == 1){
                        collisions++;
                    }
                    if(used[idx] == 0){
                        table[idx] = oldTable[i];
                        used[idx] = 1;
                        count++;
                        // if(j>0) collisions++;
                        break;
                    }
                }
            }
        }
    }    

    void insert(string key, int value){
        int lastThreshold;
        if(sizeAtLastResize==0){
            lastThreshold=count/2;
        }else{
            lastThreshold=sizeAtLastResize/2;
        }
        if(loadFactor() > MAX_LOAD && koytaInsertAfterResize >= lastThreshold){
            reHash(nextPrime(size*2));
            // koytaInsertAfterResize = 0;
            // koytaDeleteAfterResize = 0;
            
        }

        int h1 = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        int h2 = (konFunction == 1) ? hashFunction2(key) : hashFunction(key);
        if(h2 == 0) h2 = 1;

        // int idx = hashFunction(key);
        int firstDel = -1;


        for(int i = 0; i < size; i++){
            int idx = (h1+i*h2)%size;
            //changing
            if(used[idx] == 1){
                collisions++;
            }
            if(used[idx]==0){
                if(firstDel != -1){
                    idx = firstDel;
                }
                table[idx] = {key, value};
                used[idx] = 1;
                count++;
                koytaInsertAfterResize++;
                // if(i > 0) collisions++;
                //changing
                // if(used[idx] == 1){
                //     collisions++;
                // }

                // cout << "Inserted " << key << endl;
                return;
            }
            if(used[idx]==2 && firstDel == -1){
                firstDel = idx;
            }
            if(used[idx]==1 && table[idx].first == key){
                return;
            }
        }
    }

    bool search(string key){
        // int idx = hashFunction(key);
        lastHits = 0;
        int h1 = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        int h2 = (konFunction == 1) ? hashFunction2(key) : hashFunction(key);
        if(h2 == 0) h2 = 1;

        for(int i = 0; i < size; i++){
            int idx = (h1+i*h2)%size;
            lastHits++;
            if(used[idx]==0){
                return false;
            }
            if(used[idx]==1 && table[idx].first == key){
                // cout << "Found " << key << endl;
                return true;
            }
        }
        return false;
    }

    void remove(string key){
        // int idx = hashFunction(key);
        int h1 = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        int h2 = (konFunction == 1) ? hashFunction2(key) : hashFunction(key);
        if(h2 == 0) h2 = 1;

        for(int i = 0; i < size; i++){
            int idx = (h1+i*h2)%size;
            if(used[idx]==0){
                return; // naikisu
            }
            if(used[idx]==1 && table[idx].first==key){
                used[idx] = 2;
                count--;
                koytaDeleteAfterResize++;


                int lastThreshold;

                if(sizeAtLastResize==0){
                    lastThreshold=count/2;
                }else{
                    lastThreshold=sizeAtLastResize/2;
                }
                
                if(loadFactor() < MIN_LOAD && size > INIT_SIZE && koytaDeleteAfterResize>=lastThreshold){
                    reHash(prevPrime(size/2));
                    // koytaDeleteAfterResize = 0;
                    // koytaInsertAfterResize = 0;
                }
                return;
            }
        }
        // cout << "Key not Found" << endl;
    }
    
};

class CustomProbeHashTable : public HashMain{
public:
    vector<pair<string, int>> table;
    vector<int> used;
    int C1 = 1;
    int C2 = 3;

    CustomProbeHashTable(int s, int k):HashMain(s, k){
        table.resize(s);
        used.resize(s, 0);
    }


    void reHash(int newSize){
        vector<pair<string, int>> oldTable = table;
        vector<int> oldUsed = used;
        int oldSize = size;

        table.clear(); used.clear();
        size = newSize;
        table.resize(newSize);
        used.resize(newSize, 0);
        
        sizeAtLastResize = count;
        count = 0;
        // collisions = 0;
        koytaInsertAfterResize = 0;
        koytaDeleteAfterResize = 0;

        for(int i=0; i<oldSize; i++){
            if(oldUsed[i] == 1){
                int h1 = (konFunction == 1) ? hashFunction(oldTable[i].first) : hashFunction2(oldTable[i].first);
                int h2 = (konFunction == 1) ? hashFunction2(oldTable[i].first) : hashFunction(oldTable[i].first);
                if(h2 == 0) h2 = 1;

                for(int j=0; j<size; j++){
                    int chkchk = C1 * j * h2 + C2 * j * j;
                    int idx = (h1 + chkchk) % size;

                    if(used[idx] == 1){
                        collisions++;
                    }

                    if(used[idx] == 0){
                        table[idx] = oldTable[i];
                        used[idx] = 1;
                        count++;
                        // if(j>0) collisions++;
                        break;
                    }
                }
            }
        }
    }

    void insert(string key, int val){


        int lastThreshold;
        if(sizeAtLastResize==0){
            lastThreshold=count/2;
        }else{
            lastThreshold=sizeAtLastResize/2;
        }

        if(loadFactor() > MAX_LOAD && koytaInsertAfterResize>= lastThreshold){
            reHash(nextPrime(size*2));
        }
        int h1 = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        int h2 = (konFunction == 1) ? hashFunction2(key) : hashFunction(key);
        if(h2 == 0) h2 = 1;

        for(int i = 0; i < size; i++){
            // int chkchk = C1*i*h2+C2*i*i;
            int idx = (h1+C1*i*h2 + C2*i*i)%size;

            if(used[idx] == 1){
                collisions++;
            }
            if(used[idx] == 0){
                table[idx]={key, val};
                used[idx] = 1;
                count++;
                koytaInsertAfterResize++;
                // if(i > 0) collisions++;
                // if(used[idx] == 1){
                //     collisions++;
                // }
                return;

            }

            if(used[idx] == 1 && table[idx].first == key) return;
        }
    }
    bool search(string key){
        // int idx = hashFunction(key);
        lastHits = 0;
        int h1 = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        int h2 = (konFunction == 1) ? hashFunction2(key) : hashFunction(key);
        if(h2 == 0) h2 = 1;

        for(int i = 0; i < size; i++){
            int idx = (h1+C1*i*h2+C2*i*i)%size;
            lastHits++;
            if(used[idx]==0){
                return false;
            }
            if(used[idx]==1 && table[idx].first == key){
                // cout << "Found " << key << endl;
                return true;
            }
        }
        return false;
    }

    void remove(string key){
        // int idx = hashFunction(key);
        int h1 = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        int h2 = (konFunction == 1) ? hashFunction2(key) : hashFunction(key);
        if(h2 == 0) h2 = 1;

        for(int i = 0; i < size; i++){
            int idx = (h1+C1*i*h2+C2*i*i)%size;
            if(used[idx]==0){
                return; // naikisu
            }
            if(used[idx]==1 && table[idx].first==key){
                used[idx] = 2;
                count--;
                koytaDeleteAfterResize++;
                // if(loadFactor() < MIN_LOAD && size > INIT_SIZE && koyTaDeleteAfterResize>=count/2){
                //     reHash(prevPrime(size/2));
                //     koyTaDeleteAfterResize = 0;
                //     koyTaInsertAfterResize = 0;
                // }
                return;

                int lastThreshold;
                if(sizeAtLastResize == 0){
                    lastThreshold = count/2;
                }else{
                    lastThreshold = sizeAtLastResize/2;
                }
                if(loadFactor() < MIN_LOAD && size > INIT_SIZE && koytaDeleteAfterResize >= lastThreshold){
                    reHash(prevPrime(size/2));
                }
                return;
            }
        }
        // cout << "Key not Found" << endl;
    }
};

class ChainingHashTable : public HashMain{
public:
    vector<list<pair<string, int>>> table;
    ChainingHashTable(int s, int k):HashMain(s, k){
        table.resize(s);
    }



    void reHash(int newSize) {
        vector<list<pair<string, int>>> oldTable = table;
        
        size = newSize;
        table.clear();
        table.resize(newSize);
        
        sizeAtLastResize = count;
        count = 0;
        // collisions = 0;
        koytaInsertAfterResize = 0;
        koytaDeleteAfterResize = 0;

        for(auto &lst : oldTable){
            for(auto &p : lst){
                int idx = (konFunction == 1) ? hashFunction(p.first) : hashFunction2(p.first);
                if(!table[idx].empty()) collisions++;
                table[idx].push_back(p);
                count++;
            }
        }
    }

    void insert(string key, int value){
        int lastThreshold;
        if(sizeAtLastResize==0){
            lastThreshold=count/2;
        }else{
            lastThreshold=sizeAtLastResize/2;
        }
        if(loadFactor() > MAX_LOAD && koytaInsertAfterResize >= lastThreshold){
            reHash(nextPrime(size*2));           
        }
        int idx = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);

        for(auto &p : table[idx]){
            if(p.first == key) return;
        }
        if(!table[idx].empty()){
            collisions++;
        }
        table[idx].push_back({key, value});
        count++;
        koytaInsertAfterResize++;
    }
    bool search(string key){
        lastHits=0;
        int idx = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        for(auto &x : table[idx]){
            lastHits++;
            if(x.first==key){
                return true;
            }
        }
        return false;
    }

    void remove(string key){
        int idx = (konFunction == 1) ? hashFunction(key) : hashFunction2(key);
        for(auto it=table[idx].begin();it!=table[idx].end();it++){

            if(it->first==key){

                table[idx].erase(it);
                count--;
                koytaDeleteAfterResize++;
                int threshold = (sizeAtLastResize == 0) ? count/2 : sizeAtLastResize/2;
                if(loadFactor() < MIN_LOAD && size > INIT_SIZE && koytaDeleteAfterResize >= threshold){
                    reHash(prevPrime(size/2));
                }
                return;
            }
        }
    }

};

bool isPrime(int n){
    if(n<=1) return false;
    for(int i = 2; i < n; i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

int nextPrime(int n){
    // n++;
    while(!isPrime(n)){
        n++;
    }
    return n;
}

int prevPrime(int n){
    n--;
    while(n>2 && !isPrime(n)){
        n--;
    }
    return n;
}

string WordGenerator(int n){
    string s = "";
    for(int i = 0; i < n; i++){
        char c = 'a' + rand()%26;
        s.push_back(c);
    }
    return s;
}

int main() {
    srand(time(0));
    const int TOTAL = 10000;
    const int SEARCH_COUNT = 1000;
    const int WORDLEN = 10;

    cout << "Generating words..." << endl;

    vector<string> allWords;
    unordered_set<string> uniqueGen;
    while(allWords.size() < TOTAL){
        string w = WordGenerator(WORDLEN);
        if(uniqueGen.find(w) == uniqueGen.end()){
            uniqueGen.insert(w);
            allWords.push_back(w);
        }
    }
    vector<string> searchWords;
    for(int i = 0; i < SEARCH_COUNT; i++){
        searchWords.push_back(allWords[rand() % TOTAL]);
    }


    int c_col1 = 0, d_col1 = 0, cp_col1 = 0;
    int c_col2 = 0, d_col2 = 0, cp_col2 = 0;
    double c_hits1 = 0, d_hits1 = 0, cp_hits1 = 0;
    double c_hits2 = 0, d_hits2 = 0, cp_hits2 = 0;

    for(int method = 0; method < 3;method++) {
        for(int hashMode = 1; hashMode <= 2; hashMode++) {
            // mainly 2 tar jonno emn
            HashMain* ht = nullptr;

            if(method == 0) ht = new ChainingHashTable(INIT_SIZE, hashMode);
            else if(method == 1) ht = new DoubleHashTable(INIT_SIZE, hashMode);
            else ht = new CustomProbeHashTable(INIT_SIZE, hashMode);
            for(int i = 0; i < TOTAL; i++) {
                ht->insert(allWords[i], i + 1);
            }
            // duitar collision ekshathe
            int collisions = ht->collisions;

            
            long long totalHits = 0;
            for(int i = 0; i < SEARCH_COUNT; i++) {
                ht->search(searchWords[i]);
                totalHits += ht->lastHits;
            }

            
            double avgHits = (double)totalHits / SEARCH_COUNT;


            if (method == 0) { 
                if (hashMode == 1) { c_col1 = collisions; c_hits1 = avgHits; }
                else{
                     c_col2 = collisions; c_hits2 = avgHits; 
                    }
            }
            else if (method == 1) { 
                if (hashMode == 1) { d_col1 = collisions; d_hits1 = avgHits; }
                else {
                     d_col2 = collisions; d_hits2 = avgHits; 
                    }
            }
            else { 
                if (hashMode == 1) {cp_col1 = collisions; cp_hits1 = avgHits; }
                else{
                     cp_col2 = collisions; cp_hits2 = avgHits; 
                    }
            }

            delete ht;
        }
    }


    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "Method\t\tHash1(Col)\tHash1(Hits)\tHash2(Col)\tHash2(Hits)" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    cout << "Chaining\t" << c_col1 << "\t\t" << c_hits1 << "\t\t" << c_col2 << "\t\t" << c_hits2 << endl;
    cout << "Double Hash\t" << d_col1 << "\t\t" << d_hits1 << "\t\t" << d_col2 << "\t\t" << d_hits2 << endl;
    cout << "Custom Probe\t" << cp_col1 << "\t\t" << cp_hits1 << "\t\t" << cp_col2 << "\t\t" << cp_hits2 << endl;
    
    cout << "----------------------------------------------------------------" << endl;

    return 0;
}