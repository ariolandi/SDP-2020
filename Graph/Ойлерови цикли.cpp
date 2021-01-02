/**
�������� ���� ����� ���� ������� ������� �����.
������� �����: �����, ���������� �� ����� ����� ����� ������.
������� ���: ���, ���������� �� ����� ����� ����� ������, �� �� �������� �����.
��������: O(N + M)
������������ �� ����������: https://www3.cs.stonybrook.edu/~skiena/combinatorica/animations/euler.html
*/

#include<iostream>
#include<vector>
#include<stack>
#define MAXN 1024
using namespace std;
int n, m;
int a[MAXN][MAXN];
int din[MAXN], dout[MAXN];
vector<int>euler;


void Euler(int v){                                  //��������� �� ���������� ����
    stack<int> sstack;
    int top;
    sstack.push(v);                                //�������� �� � �����
    while(!sstack.empty()){                        //������ ����� �� � ������
        top = sstack.top();                       //������� �� ��������� ������� ����
        int i;
        for(i=1; i<=n; i++){
            if(a[top][i] == 1){                   //��� ���������� ����� ��������� �����
                a[top][i] = 0;                    //�� ��������� ���� �������
                top = i;                          //� ��-����� �� �� ������ � �����
                break;                            //���������� ������ ��� ������� �������� �����
            }
        }
        if(i <= n) sstack.push(top);              //��� ��� ���������� �����, �� �������� � �����
        else{
            euler.push_back(sstack.top());        //�������� ���������� ����� ��� ������� �� ������� �����
            sstack.pop();                         //� �� ��������� �� �����
        }
    }

}

int main ()
{
    int x, y;
    cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>x>>y;
        a[x][y] = 1;
        dout[x]++;                              //�� ����� ���� ����� ���� �����, ����� ������� �� ����
        din[y]++;                               //� ����, ����� ������
    }

    for(int i=1; i<=n; i++){
        if(din[i] != dout[i]){                    //������� �� ����� - �� �� ����� ������� �����, �� ������ ���� �� ��������� � ���������� ����� �� � �����
            cout<<"not Euler!"<<endl;
            return 0;
        }
    }


    cin>>x;                                     //��������� ������� ����
    Euler(x);



    cout<<"Euler circle: ";
    for(int i=euler.size()-1; i>=0; i--)        //��� ������� euler ������� �� ���� ���������!
        cout<<euler[i]<<" ";
    cout<<endl;


    return 0;
}

