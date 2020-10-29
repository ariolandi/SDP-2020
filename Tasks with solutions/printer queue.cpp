//https://www.hackerrank.com/contests/stack-tasks/challenges/printer-queue-5

#include<iostream>
#include<queue>
#include<utility>
using namespace std;

int solution(){
    int n, k;
    cin>>n>>k;
    queue<pair<int, int> >jobs;
    priority_queue<int>priority;

    for(int i=0; i<n; i++){
        int x;
        cin>>x;
        jobs.push(make_pair(x, i));
        priority.push(x);
    }

    bool done = false;
    int cnt = 0;
    while(!done){
        pair<int, int> p = jobs.front();
        jobs.pop();
        if(priority.top() > p.first)jobs.push(p);
        else{
            if(p.second == k) done = true;
            priority.pop();
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    int t;
    cin>>t;
    for(int i=0; i<t; i++){
        cout<<solution()<<endl;
    }

    return 0;
}

