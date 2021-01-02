/**
BFS (Breadth-First-Search) - ��������� �� ��������� �� ���� � ������
����������:
* ������ �� ���������� � ������������ ����
* ���-������ ��� �� ���� �����
* ��������� �� ����� �� ���� ������ ������� ����
��������: O(N + M)   ���������: ���� � ���������� ������. ����� ������ �� ������������� �� �����
������������ �� ����������: https://www.cs.usfca.edu/~galles/visualization/BFS.html
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;

void BFS(int v){                                     //BFS ��������� � ������� ���� V
    queue<int> q;                                    //������ �� ������� �� ����������� �� ���������

    used[v] = true;                                  //����������� ����� �� ��������
    q.push(v);                                       //� �� �������� � ��������

    while(!q.empty()){                               //������ �������� �� � ������
        v = q.front();                               //��������� �������� ����
        q.pop();
        cout<<v<<" ";

        for(int i=0; i<graph[v].size(); i++){       //����������� ����� �� �������� �� ���� � ���� �������
            if(!used[graph[v][i]]){                 //��� �� �, �� �� ����������� ���� ����� � �������� � ��������
                used[graph[v][i]] = true;
                q.push(graph[v][i]);
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    used.resize(n+1);

    int v, u;
    for(int i=0; i<m; i++){
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    cin>>v;
    BFS(v);


    return 0;
}
