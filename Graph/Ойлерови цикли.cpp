/**
Проверка дали даден граф съдържа ойлеров цикъл.
Ойлеров цикъл: цикъл, преминаващ по всяко ребро точно веднъж.
Ойлеров път: път, преминаващ по всяко ребро точно веднъж, но не затварящ цикъл.
Сложност: O(N + M)
Визуализация на алгоритъма: https://www3.cs.stonybrook.edu/~skiena/combinatorica/animations/euler.html
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


void Euler(int v){                                  //започваме от произволен връх
    stack<int> sstack;
    int top;
    sstack.push(v);                                //добавяме го в стека
    while(!sstack.empty()){                        //докато стека не е празен
        top = sstack.top();                       //взимаме си последния добавен връх
        int i;
        for(i=1; i<=n; i++){
            if(a[top][i] == 1){                   //ако съществува негов непосетен съсед
                a[top][i] = 0;                    //го маркираме като посетен
                top = i;                          //и по-късно ще го сложим в стека
                break;                            //прекъсваме цикъла при първото намерено ребро
            }
        }
        if(i <= n) sstack.push(top);              //ако има непосетено ребро, го добавяме в стека
        else{
            euler.push_back(sstack.top());        //добавяме последното ребро във вектора за ойлеров цикъл
            sstack.pop();                         //и го изваждаме от стека
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
        dout[x]++;                              //за всеки връх пазим броя ребра, които излизат от него
        din[y]++;                               //и тези, които влизат
    }

    for(int i=1; i<=n; i++){
        if(din[i] != dout[i]){                    //теорема на Ойлер - за да имаме ойлеров цикъл, то трябва броя на влизащите и излизащите ребра да е равен
            cout<<"not Euler!"<<endl;
            return 0;
        }
    }


    cin>>x;                                     //въвеждаме начален връх
    Euler(x);



    cout<<"Euler circle: ";
    for(int i=euler.size()-1; i>=0; i--)        //във вектора euler цикълът се пази наобратно!
        cout<<euler[i]<<" ";
    cout<<endl;


    return 0;
}

