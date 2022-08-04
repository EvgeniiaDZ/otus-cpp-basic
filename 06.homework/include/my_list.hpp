#pragma once

#include "icontainer.hpp"
#include <utility>
#include <iterator>

template <typename T>
class MyList : public IContainer<T> 
{
public:
    MyList();
    MyList( const MyList& other );
    MyList( MyList&& other );

    MyList& operator=( const MyList& rhs );
    MyList& operator=( MyList&& rhs );

    ~MyList() override;

    void push_back( const T& val ) override;
    int insert( const int& idx, const T& val ) override;
    void erase( const int& idx ) override;
    int size() const override;
    const T& operator[]( const int& idx ) const override;

    struct Node 
    {
        Node* next;
        Node* prev;
        T data;
    };

    class Iterator : public std::iterator<std::input_iterator_tag, T>
    {
    public:
        Iterator( struct Node* node ) noexcept;
        Iterator( const Iterator& other ) noexcept;
        Iterator& operator++();
        Iterator operator++( int );
        bool operator!= ( const Iterator& iterator ) const;
        bool operator== ( const Iterator& iterator ) const;
        T& operator*();
    private:
        struct Node* _node;
    };

    Iterator begin();
    Iterator end();

private:
    Node* _node_last;
    int _size;

    Node* get_node( int idx ) const;
    void init_value( void );
    void swap( MyList& other ) noexcept;
};


template <typename T>
MyList<T>::MyList()
{
    init_value();
}


template <typename T>
MyList<T>::MyList( const MyList<T>& other )
{
    init_value();
    for( int i = 0; i < other.size(); i++ )
    {
        this->push_back( other[i] );
    }
}


template <typename T>
MyList<T>::MyList( MyList<T>&& other )
{
    _node_last = other._node_last;
    _size = other._size;
    other._node_last = nullptr;
    other._size = 0;
}


template <typename T>
MyList<T>& MyList<T>::operator=( const MyList<T>& rhs )
{
    if( this != &rhs )
    {
        MyList temp{rhs};
        swap( temp );
    }
    return *this;
}


template <typename T>
MyList<T>& MyList<T>::operator=( MyList<T>&& rhs )
{
    MyList temp{std::move( rhs )};
    return *this = temp;
}


template <typename T>
MyList<T>::~MyList()
{
    while( _size )
    {
        erase( _size - 1 );
    }
}


template <typename T>
void MyList<T>::push_back( const T& val )
{
    Node* new_node = new Node();
    if( _node_last != nullptr )
    {
        _node_last->next = new_node;        
    }
    new_node->prev = _node_last;
    new_node->next = nullptr;
    new_node->data = val;
    _node_last = new_node;
    ++_size;
}


template <typename T>
int MyList<T>::insert( const int& idx, const T& val )
{
    if( idx > _size )
    {
        return -1;
    }
    
    Node* idx_node = get_node( idx );
    Node* new_node = new Node();
    if( idx_node == nullptr )
    {
        new_node->prev = _node_last;
        new_node->next = nullptr;
        new_node->data = val;
        _node_last->next = new_node;
        _node_last = new_node;
    }
    else
    {
        new_node->prev = idx_node->prev;
        new_node->next = idx_node;
        new_node->data = val;
        if( idx_node->prev )
            idx_node->prev->next = new_node;
        idx_node->prev = new_node;        
    }
    ++_size;
    return 0;
}


template <typename T>
void MyList<T>::erase( const int& idx )
{
    if( idx > _size )
    {
        return;
    }
    
    Node* idx_node = get_node( idx );
    if( idx == 0 )
    {   
        if( idx_node->next )
            idx_node->next->prev = nullptr;
    }
    else if( idx == ( _size - 1 ) )
    {
        _node_last = idx_node->prev;
        _node_last->next = nullptr;
    }
    else
    {
        idx_node->prev->next = idx_node->next;
        idx_node->next->prev = idx_node->prev;
    }
    delete [] idx_node;     
    --_size;   
}


template <typename T>
int MyList<T>::size() const
{
    return _size;
}


template <typename T>
const T& MyList<T>::operator[]( const int& idx ) const
{
    Node* idx_node = get_node( idx );
    return idx_node->data;
} 


template <typename T>
typename MyList<T>::Iterator MyList<T>::begin()
{
    return MyList<T>::Iterator( get_node(0) );
}


template <typename T>
typename MyList<T>::Iterator MyList<T>::end()
{
    return MyList<T>::Iterator( nullptr );
}


template <typename T>
typename MyList<T>::Node* MyList<T>::get_node( int idx ) const 
{
    int len = _size - idx;
    Node* idx_node = _node_last;
    if( len == 0 )
    {
        return nullptr;
    }
    while( --len )
    {
        idx_node = idx_node->prev;
    }  
    return idx_node;
}


template <typename T>
void MyList<T>::init_value( void )
{
    _node_last = nullptr;
    _size = 0;
}


template <typename T>
void MyList<T>::swap( MyList<T>& other ) noexcept
{
    std::swap( _size, other._size );
    std::swap( _node_last, other._node_last );
}   

    
template <typename T>
MyList<T>::Iterator::Iterator( struct Node* node ) noexcept
    : _node( node ) 
{

}


template <typename T>
MyList<T>::Iterator::Iterator( const Iterator& other ) noexcept
    : _node( other._node )
{

}


template <typename T>   
typename MyList<T>::Iterator& MyList<T>::Iterator::operator++()
{
    _node = _node->next;
    return *this;
}


template <typename T>
typename MyList<T>::Iterator MyList<T>::Iterator::operator++( int )
{
    MyList<T>::Iterator temp( *this );
    operator++();
    return temp;
}


template <typename T>
bool MyList<T>::Iterator::operator!= ( const MyList<T>::Iterator& iterator ) const
{
    return _node != iterator._node;
}


template <typename T>
bool MyList<T>::Iterator::operator== ( const MyList<T>::Iterator& iterator ) const 
{
    return _node == iterator._node;
}


template <typename T>
T& MyList<T>::Iterator::operator*()
{
    return _node->data;
}