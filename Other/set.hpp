#ifndef _SET_H
#define _SET_H
#include<list>
#include<stdexcept>

template <class T>
class Set{
    private:
        std::list<T> l;

    public:
        void add(const T&);
        void remove(const T&);
        bool in_set(const T&)const;
        bool empty()const;

        void union_set(const Set<T>&);
        void join_set(const Set<T>&);

        void print()const{
            for(typename std::list<T>::const_iterator it=l.begin(); it!=l.end(); ++it){
                std::cout<<*it<<" ";
            }
            std::cout<<std::endl;
        }


};

template <class T>
void Set<T>::add(const T& value){
    if(empty()){
        l.push_back(value);
        return ;
    }

    for(typename std::list<T>::iterator it = l.begin(); it != l.end(); ++it){
        if(*it == value) return ;
        if(*it > value) {
            l.insert(it, value);
            return ;
        }
    }
    l.push_back(value);
}

template <class T>
void Set<T>::remove(const T& value){
    for(typename std::list<T>::iterator it = l.begin(); it != l.end(); ++it){
        if(*it == value){
            l.erase(it);
            return ;
        }
    }
}

template <class T>
bool Set<T>::in_set(const T& value) const {
    for(typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it){
        if(*it == value){
            return true;
        }
    }
    return false;

}

template <class T>
bool Set<T>::empty() const{
    return l.empty();
}

template <class T>
void Set<T>::union_set(const Set<T>& other){
    typename std::list<T>::const_iterator this_it = l.begin(), other_it = other.l.begin();
    while(this_it != l.end() && other_it != other.l.end()){
        if(*other_it < *this_it){
            l.insert(this_it, *other_it);
            ++other_it;
        } else if(*other_it == *this_it) ++other_it;
        else ++this_it;
    }
    while(other_it != other.l.end()){
        l.push_back(*other_it);
        ++other_it;
    }
}

template <class T>
void Set<T>::join_set(const Set<T>& other){
    std::list<T> joined;
    typename std::list<T>::const_iterator this_it = l.begin(), other_it = other.l.begin();
    while(this_it != l.end() && other_it != other.l.end()){
        if(*other_it < *this_it){
            ++other_it;
        } else if(*other_it == *this_it) {
            joined.push_back(*this_it);
            ++this_it;
            ++other_it;
        }
        else ++this_it;
    }
    l = joined;
}


#endif // _SET_H
