///https://www.hackerrank.com/contests/data-structures-stackqueue/challenges/challenge-2671


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void generate_next_prime(vector<int>& primes){
    if(primes.empty()){
        primes.push_back(2);
        return ;
    }

    int number = primes[primes.size()-1];
    bool isPrime = false;
    while(!isPrime){
        number ++;
        isPrime = true;
        for(int i=0; i<primes.size() && isPrime; i++){
            isPrime = (number % primes[i] != 0);  ///if(number % primes[i] == 0) isPrime = false;
        }
    }
    primes.push_back(number);
}

void generate_password(queue<int>& numbers, vector<int>& primes){
    if(numbers.empty()){
        cout<<endl;
        return ;
    }

    queue<int> buffer;
    int p = primes[primes.size() - 1];
    while(!numbers.empty()){
        int x = numbers.front();
        numbers.pop();

        if(x % p == 0)cout<<x<<" ";
        else buffer.push(x);
    }

    generate_next_prime(primes);
    generate_password(buffer, primes);
}


int main(){
    vector<int> primes;
    int n;
    queue<int> numbers;

    cin>>n;
    for(int i=0; i<n; i++){
        int x;
        cin>>x;
        numbers.push(x);
    }

    generate_next_prime(primes);
    generate_password(numbers, primes);


    return 0;
}
