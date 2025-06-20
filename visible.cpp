#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    stack<int> st;
    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        st.push(num);
    }
    stack<int> ans;

    while(!st.empty()){
        int cur = st.top();
        st.pop();
        if(ans.empty()){
            ans.push(cur);
            continue;
        }
        if(cur > ans.top()){
            ans.push(cur);
            continue;
        }
    }
    
    while(!ans.empty()){
        st.push(ans.top());
        ans.pop();
    }

    while(!st.empty()){
        cout << st.top() << " ";
        st.pop();
    }

    return 0;
}