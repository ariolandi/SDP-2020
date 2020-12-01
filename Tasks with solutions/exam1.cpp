#include<iostream>
#include<stdexcept>
#include<stack>
#include<list>
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T>* next;
};

template <class T>
Node<T>* make_node(const T& data, Node<T>* next = nullptr){
    Node<T> *node = new Node<T>;
    node->data = data;
    node->next = next;
    return node;
}

template<class T>
void deleteList(Node<T>* node){
    if(node == nullptr)
        return ;
    deleteList(node->next);
    delete node;
}

template <class T>
int listsize(Node<T>* head){
    int cnt = 0;
    Node<T> *current = head;
    while(current != nullptr){
        cnt++;
        current = current->next;
    }
    return cnt;
}

template <class T>
Node<T>* next(Node<T>* head, const int n){
    Node<T> *current = head;
    for(int i=0; i<n && current != nullptr; i++)
        current = current->next;
    return current;
}

//-------------------------

int sum(const int& a, const int& b){
    return a+b;
}

template <class T>
T reduce(Node<T> *head, T(*f)(const T&, const T&)){
    if(head == nullptr)
        throw std::length_error("Empty list");

    T result = head->data;
    Node<T>* current = head->next;
    while(current != nullptr){
        result = f(result, current->data);
        current = current->next;
    }
    return result;
}

//-------------------------

void equalize(stack<int>& bigger, stack<int>& smaller){
    while(bigger.size() > smaller.size()){
        smaller.push(bigger.top());
        bigger.pop();
    }
}

void equalize(list<stack<int> >& L){
    if(L.size() == 0)
        return ;

    list<stack<int> >::iterator biggest = L.begin(), smallest = L.begin();
    for(list<stack<int> >::iterator it = L.begin(); it != L.end(); ++it){
        if(it->size() > biggest->size()) biggest = it;
        if(it->size() < smallest->size()) smallest = it;
    }
    if(biggest->size() <= smallest->size()+1)
        return;
    equalize(*biggest, *smallest);
    equalize(L);
}

///this is also a valid solution:
/*
void equalize(list<stack<int> >& L){
    stack<int> all;
    int n=0;
    list<stack<int> >::iterator it;

    for(it = L.begin(); it != L.end(); ++it){
        while(!it->empty()){
            all.push(it->top());
            it->pop();
        }
    }

    while(!all.empty()){
        for(it = L.begin(); it != L.end() && !all.empty(); ++it){
            it->push(all.top());
            all.pop();
        }
    }

}
*/


//-------------------------

template <class T>
void shuffle(Node<T>*& head){
    int n = listsize(head);
    int middle = n/2 + n%2;
    Node<T> *middle_element = next(head, middle-1);
    Node<T> *current = middle_element->next;

    while(current != nullptr){
        Node<T> *next = current->next;
        current->next = head;
        head = current;
        current = next;
    }
    middle_element->next = nullptr;
}



int main(){
    Node<int> *emptyL = nullptr;
    Node<int> *l = make_node(1, make_node(2, make_node(3, make_node(4, make_node(5)))));

    ///expecting an error
    //cout<<reduce(emptyL, sum)<<endl;
    cout<<reduce(make_node(5), sum)<<endl;
    cout<<reduce(l, sum)<<endl;
    cout<<"---\n";

    stack<int> s1, s2, s3, s4;
    s1.push(5);
    s1.push(4);
    s1.push(3);
    s1.push(2);
    s1.push(1);
    s2.push(7);
    s2.push(6);
    s3.push(11);
    s3.push(10);
    s3.push(9);
    s3.push(8);
    s4.push(12);
    list<stack<int> > emptySL, sl;
    sl.push_back(s1);
    sl.push_back(s2);
    sl.push_back(s3);
    sl.push_back(s4);

    equalize(emptySL);
    equalize(sl);

    for(list<stack<int> >::iterator it = sl.begin(); it != sl.end(); ++it){
        while(!it->empty()){
            cout<<it->top()<<" ";
            it->pop();
        }
        cout<<endl;
    }
    cout<<"---\n";

    shuffle(l);
    Node<int> *current = l;
    while(current != nullptr){
        cout<<current->data<<" ";
        current = current->next;
    }
    cout<<endl;



    deleteList(l);

    return 0;
}
