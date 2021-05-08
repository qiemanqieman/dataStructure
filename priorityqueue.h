#pragma once

template <class T>
class pQueue{
private:
    int current_size;
    int max_size;
    T *array;
    void double_space();
    void build_heap( );
    void percolate_down( int hole );

public:
    explicit pQueue( int capacity = 100 )
    {
        array = new T[capacity];
        max_size = capacity;
        current_size = 0;
    }
    pQueue( const T data[], int size );
    ~pQueue() { delete [] array; }
    [[nodiscard]] bool is_empty() const { return current_size == 0; }
    T top() { return array[1]; }
    void push( const T & x );
    T pop();
};


template <class T>
void pQueue<T>::double_space() {
    T *tmp = array;
    array = new T[max_size * 2];
    for (int i = 1; i <= current_size; ++i)
        array[i] = tmp[i];
    delete [] tmp;
    max_size *= 2;
}


template <class T>
void pQueue<T>::push( const T & x )
{
    if( current_size == max_size - 1 )  double_space();
    int hole = ++current_size;
    for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
        array[ hole ] = array[ hole / 2 ];
    array[ hole ] = x; // hole == 1 或者 x > array[ hole / 2 ];
}

template <class T>
T pQueue<T>::pop()
{
    T minItem;
    minItem = array[1];
    array[ 1 ] = array[ current_size-- ];  //先保证结构性
    percolate__down( 1 );
    return minItem;
}

template <class T>
void pQueue<T>::percolate_down( int hole )
{  int child;
    T tmp = array[ hole ];

    for( ; hole * 2 <= current_size; hole = child )
    {  child = hole * 2;  //child为最小孩子下标
        if( child != current_size && array[ child + 1 ] < array[ child ] )
            child++;
        if( array[ child ] < tmp )   array[ hole ] = array[ child ];
        else    break;
    }
    array[ hole ] = tmp;
}

template <class T>
void pQueue<T>::build_heap()
{
    for ( int i = current_size / 2; i > 0; i-- )
        percolate_down( i );
}

template <class T>
pQueue<T>::pQueue( const T *items, int size )
        : max_size(size + 10 ),  current_size(size)
{  array = new T[max_size];
    for( int i = 0; i < size; i++ )
        array[ i + 1 ] = items[ i ];
    build_heap();
}


