/**
Алгоритъм на Флойд (Флойд-Уоршол) за най-къс път в граф от всеки до всеки връх.
Сложност: O(N^3)
Визуализация: https://www.cs.usfca.edu/~galles/visualization/Floyd.html
*/

#include<iostream>
#define INF 9999999
#define MAXN 1024
using namespace std;
int n, m, graph[MAXN][MAXN];

int main()
{
    cin>>n>>m;

    for(int i=1; i<=n; i++){                                        //първоначално инициализиране на графа
        for(int j=1; j<=n; j++)
            graph[i][j] = INF;
        graph[i][i] = 0;
    }

    int v, u, w;
    for(int i=0; i<m; i++){
        cin>>v>>u>>w;
        graph[v][u] = w;
        graph[u][v] = w;
    }

    for(int k=1; k<=n; k++){                                        //търсене дали съществува по-кратък път от връх I до връх J пред връх K
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(graph[i][j] > graph[i][k]+graph[k][j])
                    graph[i][j] = graph[i][k]+graph[k][j];
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            cout<<(graph[i][j]!=INF?graph[i][j]:-1)<<" ";
        cout<<endl;
    }



    return 0;
}
