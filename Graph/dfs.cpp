/**
DFS (Depth-First-Search) - алгоритъм за обхождане на граф в дълбочина
Приложения:
* броене на компоненти в граф
* намиране на цикли в граф
* намиране на мостове
Сложност: O(N + M) Забележка: това е оптималния случай. Силно зависи от представянето на графа
Визуализация на алгоритъма: https://www.cs.usfca.edu/~galles/visualization/DFS.html
*/


#include<iostream>
#include<vector>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;

voidDFS(int v){                                //DFS алгоритъм с връх V
    used[v] = true;                             //отбелязваме върха като обходен
     cout<<v<<" ";

    for(int i=0; i<graph[v].size(); i++){       //проверяваме всеки от съседите му дали е вече обходен
        if(!used[graph[v][i]]){                  //ако не е, то продължаваме рекурсивно към него
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
