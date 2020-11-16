///https://www.hackerrank.com/contests/sdp-tasks/challenges/fmi-curse/problem

#include<iostream>
#include<list>
using namespace std;

bool isTrue(list<int> &a)
{
    list<int>::iterator minEl=a.begin();
    list<int>::iterator maxEl=--a.end();
    for(list<int>::iterator it=a.begin(); it != a.end(); ++it)
    {
        if(*it < *minEl)minEl=it;
        if(*it >= *maxEl)maxEl=it;
    }

    a.insert(minEl, 2*(*minEl));
    a.insert(minEl, 2*(*minEl) + 1);
    a.erase(minEl);
    a.insert(maxEl, (*maxEl)/2);
    a.insert(maxEl, (*maxEl)/2 + 1);
    a.erase(maxEl);
    for(list<int>::iterator it=a.begin(); it != --a.end(); ++it)
    {
        list<int>::iterator temp = it;
        if(*it == *(++temp)) return false;
    }
    return true;
}

int main()
{
    int n;
    list<int> a;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int t;
        cin>>t;
        a.push_back(t);
    }
    while(isTrue(a));

    for(list<int>::iterator it=a.begin(); it != a.end(); ++it)cout<<*it;
    cout<<endl;
    return 0;
}
