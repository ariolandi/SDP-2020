#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#include <stdexcept>

template <class T>
class DoubleLinkedList{
private:
    struct Node{
        T value;
        Node *prev, *next;
        Node(const T& value, Node* prev = nullptr, Node* next = nullptr): value(value), prev(prev), next(next){}
    };

    Node *first, *rear;

    void cpy(const DoubleLinkedList<T>&);
    void clear();

public:
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList<T>&);
    DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>&);
    ~DoubleLinkedList();

    void push_back(const T&);
    void pop_back();
    void push_front(const T&);
    void pop_front();
    bool empty()const;


    class Iterator{
        private:
            Node *ptr;
            Iterator(Node*);
        public:
            Iterator();

            T operator*();
            Iterator operator++();
            Iterator operator--();
            bool operator==(const Iterator&)const;
            bool operator!=(const Iterator&)const;

        friend DoubleLinkedList;
    };


    DoubleLinkedList<T>::Iterator begin()const;
    DoubleLinkedList<T>::Iterator end()const;

    void insert(const T&, DoubleLinkedList<T>::Iterator);
    void insert_after(const T&, DoubleLinkedList<T>::Iterator);

    void erase(DoubleLinkedList<T>::Iterator);

};

template <class T>
void DoubleLinkedList<T>::cpy(const DoubleLinkedList<T>& other){
    first = rear = nullptr;
    if(other.empty()){
        return ;
    }

    Node* ptr = other.first;
    while(ptr != nullptr){
        push_back(ptr->value);
        ptr = ptr->next;
    }
}

template <class T>
void DoubleLinkedList<T>::clear(){
    while(!empty()){
        pop_back();
    }
    first = rear = nullptr;
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(){
    first = rear = nullptr;
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other){
    cpy(other);
}

template <class T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other){
    if(this != &other){
        clear();
        cpy(other);
    }
    return *this;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    clear();
}

template <class T>
void DoubleLinkedList<T>::push_back(const T& value){
    if(empty()){
        Node *temp = new Node(value);
        first = temp;
        rear = temp;
        return ;
    }
    ///list is not empty => rear
    Node *temp = new Node(value, rear);
    rear->next = temp;
    rear = temp;
}

template <class T>
void DoubleLinkedList<T>::pop_back(){
    if(empty()) throw std::out_of_range("The list is empty");

    Node *temp = rear;
    rear = rear->prev;
    delete temp;
    if(rear == nullptr) first = nullptr;
    else rear->next = nullptr;
}

template <class T>
void DoubleLinkedList<T>::push_front(const T& value){
    if(empty()){
        Node *temp = new Node(value);
        first = temp;
        rear = temp;
        return ;
    }

    Node *temp = new Node(value, nullptr, first);
    first->prev = temp;
    first = temp;
}

template <class T>
void DoubleLinkedList<T>::pop_front(){
    if(empty()) throw std::out_of_range("The list is empty");

    Node *temp = first;
    first = first->next;
    delete temp;
    if(first == nullptr) rear = nullptr;
    else first->prev = nullptr;
}

template <class T>
bool DoubleLinkedList<T>::empty() const{
    return first == nullptr && rear == nullptr;
}


template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const{
    return Iterator(first);
}

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const{
    return Iterator(rear);
}

template <class T>
void DoubleLinkedList<T>::insert(const T& value, DoubleLinkedList<T>::Iterator it){
    if(it == begin()){
        push_front(value);
        return ;
    }

    Node *temp = new Node(value, it.ptr->prev, it.ptr);
    it.ptr->prev->next = temp;
    it.ptr->prev = temp;
}

template <class T>
void DoubleLinkedList<T>::insert_after(const T& value, DoubleLinkedList<T>::Iterator it){
    if(it == end()){
        push_back(value);
        return ;
    }

    Node *temp = new Node(value, it.ptr, it.ptr->next);
    it.ptr->next->prev = temp;
    it.ptr->next = temp;
}

template <class T>
void DoubleLinkedList<T>::erase(DoubleLinkedList<T>::Iterator it){
    if(it == DoubleLinkedList<T>::Iterator())return ;
    if(it == begin()){
        pop_front();
        return ;
    }
    if(it == end()){
        pop_back();
        return ;
    }

    ///Here we have prev and next element for it.ptr
    Node *temp = it.ptr;
    it.ptr->prev->next = it.ptr->next;
    it.ptr->next->prev = it.ptr->prev;
    --it;
    delete temp;
}

///---------------------------------------------

template <class T>
DoubleLinkedList<T>::Iterator::Iterator(Node* node){
    ptr = node;
}

template <class T>
DoubleLinkedList<T>::Iterator::Iterator(){
    ptr = nullptr;
}

template <class T>
T DoubleLinkedList<T>::Iterator::operator*(){
    if(ptr == nullptr) throw std::runtime_error("No value");

    return ptr->value;
}

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator++(){
     if(ptr == nullptr) throw std::runtime_error("No element");

     ptr = ptr->next;
     return Iterator(ptr);
}

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator--(){
     if(ptr == nullptr) throw std::runtime_error("No element");

     ptr = ptr->prev;
     return Iterator(ptr);
}

template <class T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& other)const{
    return ptr == other.ptr;
}

template <class T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other)const{
    return ptr != other.ptr;
}




#endif // _LINKED_LIST_H
