/**
BFS (Breadth-First-Search) - алгоритъм за обхождане на граф в ширина
Приложения:
* броене на компоненти в неориентиран граф
* най-кратък път по брой ребра
* разделяне на графа на нива спрямо начален връх
Сложност: O(N + M)   Забележка: това е оптималния случай. Силно зависи от представянето на графа
Визуализация на алгоритъма: https://www.cs.usfca.edu/~galles/visualization/BFS.html
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;

void BFS(int v){                                     //BFS алгоритъм с начален връх V
    queue<int> q;                                    //опашка за следене на поредността на обхождане

    used[v] = true;                                  //отбелязваме върха за обхожден
    q.push(v);                                       //и го добавяме в опашката

    while(!q.empty()){                               //докато опашката не е празна
        v = q.front();                               //извличаме поредния връх
        q.pop();
        cout<<v<<" ";

        for(int i=0; i<graph[v].size(); i++){       //проверяваме всеки от съседите му дали е вече обходен
            if(!used[graph[v][i]]){                 //ако не е, то го отбелязваме като такъв и добавяме в опашката
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
