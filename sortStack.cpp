#include<bits/stdc++.h>
using namespace std;
int main(){
    stack<int> st;
    stack<int> helper;
    int x;
    cin >> x;
    for(int i = 0; i < x; i++){
        int num;
        cin >> num;
        st.push(num);
    }
    while(!st.empty()){
        int num = st.top();
        st.pop();
        while(!helper.empty() && helper.top() > num){
            st.push(helper.top());
            helper.pop();
        }
        helper.push(num);


    }
    while(!helper.empty()){
        st.push(helper.top());
        helper.pop();
        
    }
}