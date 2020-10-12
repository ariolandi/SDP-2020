#ifndef _STACK_
#define _STACK_
#include <stdexcept>  ///for std::out_of_range exception in C++11

/** A Stack is a linear data structure which follows the LIFO (Last In First Out) principle.
  * The main idea is that only the top element can be modified or removed.
  * There is four main operations - push, pop, top and empty.
  */
template <class T>
class Stack{
private:
    struct Node{
        T value;
        Node *next;
        Node(const T& value_): value(value_), next(nullptr){}
    };

    Node *topElement;

    void cpy_recursive(const Node*);
    void cpy(const Stack<T>&);
    void clear();

public:
    Stack();
    Stack(const Stack<T>&);
    Stack<T>& operator=(const Stack<T>&);
    ~Stack();

    void push(const T&);
    void pop();
    const T& top()const;
    T& top();
    bool empty()const;
};

/** Recursive copy method
  * -----
  * Goes to the bottom of the stack and then pushes elements in the new one.
  * It will overflow the recursive memory for stack with too many elements (1000000 for example).
  */
template <class T>
void Stack<T>::cpy_recursive(const Node* newElement){
    if(newElement == nullptr){ /// if it is the bottom of the stack
        topElement = nullptr;
        return ;
    }

    cpy_recursive(newElement->next);
    push(newElement->value);
}

/** Copy method
  * ------
  * Copies the elements of one stack into another in the same sequence.
  */
template <class T>
void Stack<T>::cpy(const Stack<T>& other){
    cpy_recursive(other.topElement);

    /**
     * Interactive way:
     * -----
     * It is against the stack definition and the class encapsulation concept but there is no limit for the number of stack elements.


    if(empty()){
        topElement = nullptr;
        return ;
    }
    ///Two pointers - one for the last added element in the current stack and one for the element which is to be added from the other stack
    Node *this_ptr, *other_ptr;
    topElement = new Node(other.topElement->value);
    this_ptr = topElement;
    other_ptr = other.topElement->next;
    while(other_ptr != nullptr){
        Node *newElement = new Node(other_ptr->value);
        this_ptr->next = newElement;
        this_ptr = this_ptr->next;
        other_ptr = other_ptr->next;
    }
    ///There is no need to add a NULL pointer for the bottom - this is the defaulft Node->next value.
    */
}

/** Deleting method
  * -----
  * Deletes the elements of the stack.
  */
template <class T>
void Stack<T>::clear(){
    while(!empty())
        pop();
}

/** Constructor
  * -----
  * The stack is empty <=> there is no top element.
  */
template <class T>
Stack<T>::Stack(){
    topElement = nullptr;
}

/** Copy constructor
  */
template <class T>
Stack<T>::Stack(const Stack<T>& other){
    cpy(other);
}

/** Assignment operator
  */
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other){
    if(this != &other){
        clear();
        cpy(other);
    }
    return *this;
}

/** Destructor
  */
template <class T>
Stack<T>::~Stack(){
    clear();
}

/** Element adding method
  * -----
  * Adds a new element on the top of the stack.
  *
  *  |newElement|
  *  |__________|
  *  |topElement|
  *  |          |
  *  |   Stack  |
  *  |__________|
  *
  */
template <class T>
void Stack<T>::push(const T& value){
    Node *newElement = new Node(value);
    newElement->next = topElement;
    topElement = newElement;
}

/** Element removing method
  * -----
  * Removes the top element.
  * Throws an exception if the stack is empty.
  */
template <class T>
void Stack<T>::pop(){
    if(empty())
        throw std::out_of_range("The stack is empty!");

    Node *temp = topElement;
    topElement = topElement->next;
    delete temp;
}

/** Peek method
  * -----
  * Returns a reference to the top element.
  * Throws an exception if the stack is empty.
  * In two different forms&
  * * constant for looking to the value of the top element of a constant stack
  * * not constant for modifying the value of the top element of a not constant stack
  */
template <class T>
T& Stack<T>::top(){
    if(empty())
        throw std::out_of_range("The stack is empty!");

    return topElement->value;
}

template <class T>
const T& Stack<T>::top()const{
    if(empty())
        throw std::out_of_range("The stack is empty!");

    return topElement->value;
}

/** Emptyness checking method
  * -----
  * Returns True if there is no elements in the stack.
  */
template <class T>
bool Stack<T>::empty() const{
    return (topElement == nullptr);
}



#endif // _STACK_
