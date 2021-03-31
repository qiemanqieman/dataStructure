//
// Created by q on 3/31/21.
//

#ifndef DATASTRUCTURE_SEQLIST_H
#define DATASTRUCTURE_SEQLIST_H


template <class T>
class seqList: public list<T>{
private:
    int max_size, current_size;
    T *elem;
    void double_space();

public:
    explicit seqList(int init_size = 10){max_size = init_size; current_size = 0; elem = new T[init_size];}
    ~seqList(){ delete [] elem;}
    [[nodiscard]] bool empty() {return current_size == 0;}
    int search(const T & x) const;
    T visit(int i) const;
    void traverse() const;
    [[nodiscard]] int length() const { return current_size;}
    void clear() {current_size = 0;}
    void insert(int i, const T &x);
    void remove(int i);
};


template <class T>
void seqList<T>::double_space() {
    T *tmp = elem;
    max_size *= 2;
    elem = new T[max_size];
    for (int i = 0; i < current_size; ++i)
        elem[i] = tmp[i];
    delete [] tmp;
}

template <class T>
int seqList<T>::search(const T &x) const {
    for (int i = 0; i < current_size; ++i)
        if (elem[i] == x) return i;
    return -1;
}

template <class T>
T seqList<T>::visit(int i) const{
    if (i < 0 or i > current_size - 1) throw OutOfBoundError();
    return elem[i];
}

template <class T>
void seqList<T>::traverse() const {
    std::cout << std::endl << "Traverse the list:\n";
    for (int i = 0; i < current_size; ++i)
        std::cout << elem[i] << ' ';
    std::cout << std::endl;
}

template <class T>
void seqList<T>::insert(int i, const T &x) {
     if (i < 0 or i > current_size) throw OutOfBoundError();
     if (current_size == max_size) double_space();
     for (int j = current_size; j > i; --j)
         elem[j] = elem[j - 1];
     elem[i] = x;
     ++current_size;
}

template <class T>
void seqList<T>::remove(int i) {
    if (i < 0 or i > current_size - 1) throw OutOfBoundError();
    for (; i < current_size - 1; ++i)
        elem[i] = elem[i + 1];
    --current_size;
}
#endif //DATASTRUCTURE_SEQLIST_H
