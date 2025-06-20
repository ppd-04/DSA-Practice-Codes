#include<bits/stdc++.h>
using namespace std;

int main(){
    queue<int> q;
    stack<int> st;
    
        int x;
        cin >> x;
        for(int i = 0; i < x; i++){
            int num;
            cin >> num;
            q.push(num);
        }
        while(!q.empty()){
            if(st.empty()){
                st.push(q.front());
                q.pop();
                continue;
            }
            if(q.front() >= st.top()){
                st.push(q.front());
                q.pop();
                continue;
            }
            else{
                q.push(st.top());
                st.pop();
                continue;;
            }
        }
        while(!st.empty()){
            q.push(st.top());
            st.pop();
        }

        while(!q.empty()){
            st.push(q.front());
            q.pop();
        }
        while(!st.empty()){
            q.push(st.top());
            st.pop();
        }
        while(!q.empty()){
            cout << q.front() << " ";
            q.pop();
        }
            
    return 0;
}