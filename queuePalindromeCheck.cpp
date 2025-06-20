#include<bits/stdc++.h>
using namespace std;

int main(){
    queue<char> q;
    string str;
    cin >> str;
    for(int i = 0; str[i] != '\0'; i++){
        q.push(str[i]);
    }
    stack<char> st;

    int sz = q.size();
    for(int i = 0; i < sz; i++){
        char x = q.front();
        st.push(q.front());
        q.pop();
        q.push(x);
    }

    while(!q.empty()){
        if(q.front() != st.top()){
            cout << "False" << endl;
            return 0;
        }
        q.pop();
        st.pop();
    }

    cout << "True" << endl;
    return 0;

}