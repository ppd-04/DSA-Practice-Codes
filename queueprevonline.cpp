#include<bits/stdc++.h>
using namespace std;

int main(){
    queue<int> q;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        q.push(x);
    }
    queue<int> helper;

    int mid = n/2;

    for(int i = 0; i < mid; i++){
        helper.push(q.front());
        q.pop();
    }
    for(int i = 0; i < mid; i++){
        int a = helper.front();
        helper.pop();
        int b = q.front();
        q.pop();
        q.push(a);
        q.push(b);
    }
    if(n%2 != 0){
        q.push(q.front());
        q.pop();
    }
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}