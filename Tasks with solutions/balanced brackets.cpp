///https://www.hackerrank.com/contests/data-structures-stackqueue/challenges/balanced-brackets/problem

#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool isOpening(char c){
    return (c=='(' || c=='[' || c=='{');
}

bool isPair(char c1, char c2){
    return ((c1==')' && c2=='(') || (c1==']' && c2=='[') || (c1=='}' && c2=='{'));
}

bool isBalanced(string& str){
    stack<char> brackets;
    for(int i=0; i<str.size(); i++){
        if(isOpening(str[i]))brackets.push(str[i]);
        else if(!brackets.empty() && isPair(str[i], brackets.top()))brackets.pop();
        else return false;
    }
    if(!brackets.empty())return false;
    return true;
}


int main()
{
    int n;
    string str;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>str;
        cout<<(isBalanced(str)?"YES":"NO")<<endl;
    }

    return 0;
}
