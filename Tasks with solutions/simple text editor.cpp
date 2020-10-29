//https://www.hackerrank.com/contests/stack-tasks/challenges/simple-text-editor

#include<iostream>
#include<string>
#include<stack>
using namespace std;

void append(stack<string>& s){
    string to_append;
    cin>>to_append;
    s.push(s.top() + to_append);
}

void dlt(stack<string>& s){
    int k;
    cin>>k;
    string to_delete = s.top();
    int len = to_delete.size();
    to_delete = to_delete.substr(0, len-k);
    s.push(to_delete);
}

void print(stack<string> s){
    int k;
    cin>>k;
    cout<<s.top()[k-1]<<endl;
}

void undo(stack<string>& s){
    s.pop();
    if(s.empty())s.push("");
}


int main()
{
    stack<string> s;
    s.push("");

    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        int code;
        cin>>code;
        switch(code){
            case 1: append(s); break;
            case 2: dlt(s); break;
            case 3: print(s); break;
            case 4: undo(s); break;
        }
    }




    return 0;
}
