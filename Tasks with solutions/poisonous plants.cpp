//https://www.hackerrank.com/contests/stack-tasks/challenges/poisonous-plants

#include<iostream>
#include<queue>
using namespace std;

int poisonousPlants(queue<int>& q){
    int days=0;
    bool dead;
    do{
        dead = false;
        int left = q.front();
        q.pop();
        q.push(left);
        while(q.front() != -1){
            int x = q.front();
            q.pop();
            if(x > left)dead = true;
            else q.push(x);
            left = x;
        }
        days++;
        q.pop();
        q.push(-1);
    }while(dead);

    return days - 1;
}



int main()
{
    int n;
    cin>>n;
    queue<int> flowers;
    for(int i=0; i<n; i++){
        int fl;
        cin>>fl;
        flowers.push(fl);
    }
    flowers.push(-1);
    cout<<poisonousPlants(flowers)<<endl;

    return 0;
}
