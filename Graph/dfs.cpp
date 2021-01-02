/**
DFS (Depth-First-Search) - ��������� �� ��������� �� ���� � ���������
����������:
* ������ �� ���������� � ����
* �������� �� ����� � ����
* �������� �� �������
��������: O(N + M) ���������: ���� � ���������� ������. ����� ������ �� ������������� �� �����
������������ �� ����������: https://www.cs.usfca.edu/~galles/visualization/DFS.html
*/


#include<iostream>
#include<vector>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;

voidDFS(int v){                                //DFS ��������� � ���� V
    used[v] = true;                             //����������� ����� ���� �������
     cout<<v<<" ";

    for(int i=0; i<graph[v].size(); i++){       //����������� ����� �� �������� �� ���� � ���� �������
        if(!used[graph[v][i]]){                  //��� �� �, �� ������������ ���������� ��� ����
            dfs(graph[v][i]);
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
    DFS(v);


    return 0;
}
