#ifndef MY_HEAP_H
#define MY_HEAP_H

template <typename T, typename Comp>
class MyHeap
{
  private:
    T* m_data;
    int m_size;
    int m_maxsize;
    void sift_down(int n);

  public:
    //default constructor -- starts with empty array
    MyHeap() { m_size = 0; m_maxsize = 0; m_data = nullptr; }

    //Constructor that inserts values in arr[] to the heap
    MyHeap(const T arr[], const int size);

    //Copy constructor
    MyHeap(const MyHeap<T, Comp>& src);

    //Destructor
    ~MyHeap() { delete[] m_data; }

    //Makes copy of src and makes calling object the same
    MyHeap<T, Comp>& operator=(const MyHeap<T, Comp>& src);

    //Accesses top element
    T& top();

    //Removes top element
    void pop();

    //Add an element to the heap and sort it properly
    void push(const T& it);

    //Check whether m_size is 0 or not
    bool empty() { return m_size == 0; }

    //Returns m_size
    int size() { return m_size; }

    //Returns m_maxsize
    int max_size() { return m_maxsize; }

    //Grows array if data reaches m_maxsize
    void reserve(int size);

    //Shrinks array if data is 1/4 size of max_size
    void shrink_to_fit();

    //Check if position is parent
    int parent(const int n);

    //Check if position is leaf
    bool is_leaf(const int n);

    //Check if position is right child
    int rc(const int n);

    //Check if position is left child
    int lc(const int n);

    //heapifies contents of heap
    void heapify();

    //prints the heap in order
    void print();
};

#include "MyHeap.hpp"

#endif
