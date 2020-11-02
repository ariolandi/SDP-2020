#ifndef _LIST_H
#define _LIST_H
#include <stdexcept>

/** A List is a linear data structure with Iterator.
  * All nodes contain a value field and a pointer to the next element.
  * There is six main operations - push_front, pop_front, front, empty, insert and erase.
  * The iterator has an increment operator, two comparison operators and a value getter (operator *).
  * THe list has two basic iterators - begin and end.
  */
template <class T>
class List{
private:
    struct Node{
        T value;
        Node *next;
        Node(const T& value, Node* next = nullptr): value(value), next(next){}
    };

    Node *first;

    void cpy(const List<T>&);
    void dlt();

public:
    List();
    List(const List<T>&);
    List<T>& operator=(const List<T>&);
    ~List();

    void push_front(const T&);
    void pop_front();
    bool empty()const;
    T& front();
    const T front()const;


    class Iterator{
    private:
        Node *current_element;
    public:
        Iterator();
        Iterator(Node*);

        T& operator++();
        bool operator==(const Iterator&)const;
        bool operator!=(const Iterator&)const;
        T& operator*();
        Node* get_node()const; ///next

        const T operator*()const;
    };


    Iterator begin()const;
    Iterator end()const;

    void insert(Iterator, const T&);
    void insert(const int, const T&);
    void erase(Iterator&);

};

/** Copy method
  * ------
  * Copies the elements of one list into another in the same sequence.
  */
template <class T>
void List<T>::cpy(const List<T>& other){
    if(other.empty()){
        first = nullptr;
        return ;
    }

    Node *this_ptr, *other_ptr;
    this_ptr = new Node(other.first->value);
    first = this_ptr;
    other_ptr = other.first->next;

    while(other_ptr != nullptr){
        try {
            this_ptr->next = new Node(other_ptr->value);
        } catch(...) {
            dlt();
            throw std::runtime_error("Cannot create a new node");
        }
        this_ptr = this_ptr->next;
        other_ptr = other_ptr->next;
    }
}

/** Deleting method
  * -----
  * Deletes the elements of the list.
  */
template <class T>
void List<T>::dlt(){
    while(!empty()){
        pop_front();
    }
}

/** Constructor
  * -----
  * The list is empty <=> there is no first element.
  */
template <class T>
List<T>::List(): first(nullptr){}


/** Copy constructor
  */
template <class T>
List<T>::List(const List<T>& other){
    cpy(other);
}

/** Assignment operator
  */
template <class T>
List<T>& List<T>::operator=(const List<T>& other){
    if(this != &other){
        dlt();
        cpy(other);
    }
    return *this;
}


/**Destructor
  */
template <class T>
List<T>::~List(){
    dlt();
}

/** Element adding method
  * -----
  * Adds a new element in the front of the list.
  */
template <class T>
void List<T>::push_front(const T& value){
    Node *new_element = new Node(value, first);
    first = new_element;
}

/** Element removing method
  * -----
  * Removes the fist element.
  * Throws an exception if the list is empty.
  */
template <class T>
void List<T>::pop_front(){
    if(empty()) throw std::out_of_range("The list is empty");

    Node *tmp = first;
    first = first->next;
    delete tmp;
}

/** Emptyness checking method
  * -----
  * Returns True if there is no elements in the list.
  */
template <class T>
bool List<T>::empty() const{
    return first == nullptr;
}

/** Peek method
  * -----
  * Returns a reference to the first element.
  * Throws an exception if the list is empty.
  */
template <class T>
T& List<T>::front(){
    if(empty()) throw std::out_of_range("The list is empty");
    return first->value;
}

template <class T>
const T List<T>::front() const{
    if(empty()) throw std::out_of_range("The list is empty");
    return first->value;
}

///-----------------------------
///ITERATOR

/** Constructor
  * The iterator is not connected with any object.
  */
template <class T>
List<T>::Iterator::Iterator(){
    current_element = nullptr;
}

/** Constructor
  * Connects the iterator with an object.
  * Can be used only inside the list scope.
  */
template <class T>
List<T>::Iterator::Iterator(Node* node){
    current_element = node;
}

/** Prefix form of increment operator
  * Throws an exception if the iterator is not initialized.
  */
template <class T>
T& List<T>::Iterator::operator++(){
    if(current_element == nullptr) throw std::runtime_error("Iterator not initialized");
    current_element = current_element->next;
    return current_element->value;
}


/** Comparison operator - equal
  */
template <class T>
bool List<T>::Iterator::operator==(const List<T>::Iterator& other) const{
    return current_element == other.current_element;
}

 /** Comparison operator - not equal
   */
template <class T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator& other) const{
    return !operator==(other);
}

/** Value getter
  * There is no need for a constant form.
  * Throws an exception if the iterator is not initialized.
  */
template <class T>
T& List<T>::Iterator::operator*(){
    if(current_element == nullptr) throw std::runtime_error("Iterator not initialized");
    return current_element->value;
}

/** Node getter
  * Returns a pointer to the node pointed by the iterator or nullptr if the iterator is not initialized.
  * Can be used only in the list scope.
  */
template <class T>
typename List<T>::Node* List<T>::Iterator::get_node()const{
    return current_element;
}


///--------------------


/** Iterator to the beginning of the list
  */
template <class T>
typename List<T>::Iterator List<T>::begin() const{
    return Iterator(first);
}

/** Iterator to the end of the list
  * Points one element after the last i.e. nullptr.
  */
template <class T>
typename List<T>::Iterator List<T>::end() const{
    return Iterator();
}

/** Inserting method
  * Inserts a new value after the element.
  * Two forms - with iterator and wih position.
  */
template <class T>
void List<T>::insert(List<T>::Iterator it, const T& value){
    Node *insert_after = it.get_node();
    Node *new_element = new Node(value, insert_after->next);
    insert_after->next = new_element;
}


template <class T>
void List<T>::insert(const int position, const T& value){
    int pos=0;
    Node *current_element = first;
    while(pos != position && current_element->next != nullptr){
        current_element = current_element->next;
        pos++;
    }
    Node *new_element = new Node(value, current_element->next);
    current_element->next = new_element;
}

/** Erasing method
  * Erases the element after the pointed one.
  */
template <class T>
void List<T>::erase(List<T>::Iterator& it){
    Node *erase_after = it.get_node();
    ++it;
    Node *to_be_removed = erase_after->next;
    erase_after->next = to_be_removed->next;
    delete to_be_removed;
}



#endif // _LIST_H
