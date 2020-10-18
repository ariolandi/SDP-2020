#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdexcept>  ///for std::out_of_range exception in C++11


/** A Queue is a linear data structure which follows the FIFO (First In First Out) principle.
  * The main idea is that only the front element can be removed and the new elements are added in the rear end.
  * There is four main operations - push, pop, top/front/ and empty.
  */
template <class T>
class Queue{
private:
    struct Node{
        T value;
        Node *next;
        Node(const T& value_): value(value_), next(nullptr){}
    };

    Node *front, *tail;

    void cpy(const Queue<T>&);
    void clear();

public:
    Queue();
    Queue(const Queue<T>&);
    Queue<T>& operator=(const Queue<T>&);
    ~Queue();

    void push(const T&);
    void pop();
    const T& top()const;
    T& top();
    bool empty()const;
};

/** Copy method
  * ------
  * Copies the elements of one queue into another in the same sequence.
  */
template <class T>
void Queue<T>::cpy(const Queue<T>& other){
    front = nullptr;
    tail = nullptr;
    Node *current_element = other.front;
    while(current_element != nullptr){
        push(current_element->value);
        current_element = current_element->next;
    }
}

/** Deleting method
  * -----
  * Deletes the elements of the queue.
  */
template <class T>
void Queue<T>::clear(){
    while(!empty())
        pop();
}


/** Constructor
  * -----
  * The queue is empty <=> there is no front or rear element.
  */
template <class T>
Queue<T>::Queue(): front(nullptr), tail(nullptr){}

/** Copy constructor
  */
template <class T>
Queue<T>::Queue(const Queue<T>& other){
    cpy(other);
}

/** Assignment operator
  */
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){
    if(this != &other){
        clear();
        cpy(other);
    }
    return *this;
}

/** Destructor
  */
template <class T>
Queue<T>::~Queue(){
    clear();
}

/** Element adding method
  * -----
  * Adds a new element in the tail of the queue.
  *
  *   ____________________________
  *  |front |   tail   |newElement|
  *  |______|__________|__________|
  *
  */
template <class T>
void Queue<T>::push(const T& value){
    Node *new_element = new Node(value);

    if(empty()){
        front = tail = new_element;
        return ;
    }
    tail->next = new_element;
    tail = tail->next;
}

/** Element removing method
  * -----
  * Removes the front element.
  * Throws an exception if the queue is empty.
  */
template <class T>
void Queue<T>::pop(){
    if(empty())throw std::out_of_range("The queue is empty");

    Node *temp = front;
    front = front->next;
    delete temp;
    if(front == nullptr) tail = nullptr;
}

/** Peek method
  * -----
  * Returns a reference to the fromnt element.
  * Throws an exception if the queue is empty.
  * In two different forms:
  * * constant for looking to the value of the front element of a constant queue
  * * not constant for modifying the value of the front element of a not constant queue
  */
template <class T>
T& Queue<T>::top(){
    if(empty())throw std::out_of_range("The queue is empty");
    return front->value;
}

template <class T>
const T& Queue<T>::top()const{
    if(empty())throw std::out_of_range("The queue is empty");
    return front->value;
}

/** Emptyness checking method
  * -----
  * Returns True if there is no elements in the queue.
  */
template <class T>
bool Queue<T>::empty() const{
    return (front == nullptr);
}


#endif // _QUEUE_H_
