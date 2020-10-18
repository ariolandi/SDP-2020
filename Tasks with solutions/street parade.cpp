///https://www.hackerrank.com/contests/data-structures-stackqueue/challenges/street-parade-2-1

#include<iostream>
#include<stack>
#include<queue>
using namespace std;


int main()
{
    int n;
    queue<int> street1;
    stack<int> street2;

    cin>>n;
    for(int i=0; i<n; i++){
        int x;
        cin>>x;
        street1.push(x);
    }

    int next=1;
    while(!street1.empty()){
        int x=street1.front();
        if(x == next) {
            street1.pop();
            next++;
        }
        else {  /// x>next
            if(!street2.empty() && street2.top() == next){
                street2.pop();

                next ++;
            } else {
                street1.pop();
                street2.push(x);
            }
        }
    }

    bool isPossible = true;
    while(!street2.empty() && isPossible){
        int x = street2.top();
        street2.pop();
        if(x == next)next++;
        else isPossible = false;
    }

    cout<<(isPossible? "yes":"no")<<endl;

    return 0;
}
