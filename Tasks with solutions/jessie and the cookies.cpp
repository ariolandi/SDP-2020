//https://www.hackerrank.com/contests/stack-tasks/challenges/jesse-and-cookies

#include<iostream>
#include<queue>
using namespace std;


int main()
{
    int n, k;
    cin>>n>>k;
    priority_queue<int, vector<int>, std::greater<int>> cookies;

    for(int i=0; i<n; i++){
        int c;
        cin>>c;
        cookies.push(c);
    }

    int cnt=0;
    while(!cookies.empty() && cookies.top() < k){
        int c1, c2;
        c1 = cookies.top();
        cookies.pop();
        if(cookies.empty()){
            cout<<-1<<endl;
            return 0;
        }

        c2 = cookies.top();
        cookies.pop();
        cookies.push(c1 + 2*c2);
        cnt++;
    }

    cout<<cnt<<endl;


    return 0;
}
