#pragma once

#include "icontainer.hpp"
#include <utility>
#include <iterator>

template <typename T>
class MyForwardList : public IContainer<T>
{
public:
    MyForwardList();
    MyForwardList( const MyForwardList& other );
    MyForwardList( MyForwardList&& other );

    MyForwardList& operator=( const MyForwardList& rhs );
    MyForwardList& operator=( MyForwardList&& rhs );
   
    ~MyForwardList() override;

    void push_back( const T& val ) override;
    int insert( const int& idx, const T& val ) override;
    void erase( const int& idx )override;
    int size() const override;
    const T& operator[]( const int& idx ) const override;

    struct Node {
        Node* next;
        T data;
    };

    class Iterator : public std::iterator<std::input_iterator_tag, T>
    {
    public:
        Iterator( struct Node* node ) noexcept;
        Iterator( const Iterator& other ) noexcept;
        Iterator operator++( int );
        Iterator& operator++();
        bool operator==( const Iterator& iterator ) const;
        bool operator!=( const Iterator& iterator ) const;
        T& operator*();
    private:
        struct Node* _node;
    };

    Iterator begin();
    Iterator end();
    
private:
    Node* _node_first;
    Node* _node_last;
    int _size;

    void init_value( void );
    Node* get_node( int idx ) const;
    void swap( MyForwardList& other ) noexcept;
};


template <typename T>
MyForwardList<T>::MyForwardList()
{
    init_value();
}


template <typename T>
MyForwardList<T>::MyForwardList( const MyForwardList<T>& other )
{
    init_value();
    for( int i = 0; i < other.size(); i++ )
    {
        this->push_back( other[i] );
    }
}


template <typename T>
MyForwardList<T>::MyForwardList( MyForwardList<T>&& other )
{
    _node_first = other._node_first;
    other._node_first = nullptr;
    _node_last = other._node_last;
    other._node_last = nullptr;
    _size = other._size;
    other._size = 0;
}


template <typename T>
MyForwardList<T>& MyForwardList<T>::operator=( const MyForwardList<T>& rhs )
{
    if( this != &rhs )
    {
        MyForwardList temp{rhs};
        swap( temp );
    }
    return *this;
}


template <typename T>
MyForwardList<T>& MyForwardList<T>::operator=( MyForwardList<T>&& rhs )
{
    MyForwardList temp{std::move( rhs )};
    return * this = temp;
}


template <typename T>
MyForwardList<T>::~MyForwardList()
{
    while( _size )
    {
        erase( _size - 1 );
    }        
}


template <typename T>
void MyForwardList<T>::push_back( const T& val )
{
    Node* node = new Node();
    node->next = nullptr;
    node->data = val;

    if( _node_first == nullptr )
    {
        _node_first = node;
    }
    else 
    {
        _node_last->next = node;           
    }

    _node_last = node; 
    ++_size;
}


template <typename T>
int MyForwardList<T>::insert( const int& idx, const T& val )
{
    if( idx > _size )
    {
        return -1;
    }

    Node* node = new Node();
    node->data = val;

    if( idx == 0 )
    {
        node->next = get_node( idx );
        _node_first = node;
    }
    else if( idx == _size )
    {
        get_node( idx - 1 )->next = node;
        node->next = nullptr;
        _node_last = node;
    }
    else 
    {
        Node* temp = get_node( idx - 1 );
        node->next = temp->next;
        temp->next = node;
    }
    ++_size;
    return 0;
}


template <typename T>
void MyForwardList<T>::erase( const int& idx )
{
    if( idx >= _size )
    {
        return;
    }
    else if( idx == 0 )
    {
        Node* node = _node_first;
        if( _node_first->next )
            _node_first = _node_first->next;
        delete [] node;
    }
    else if( idx == _size - 1 )
    {
        _node_last = get_node( idx - 1 );
        delete [] _node_last->next;
    }
    else
    {
        Node* node = get_node( idx - 1);
        Node* node_idx = node->next;
        node->next = node->next->next;
        delete [] node_idx;
                    
    }
    --_size; 
}


template <typename T>
int MyForwardList<T>::size() const
{
    return _size;
}


template <typename T>
const T& MyForwardList<T>::operator[]( const int& idx ) const
{
    return get_node( idx )->data;
}


template <typename T>
typename MyForwardList<T>::Iterator MyForwardList<T>::begin()
{
    return MyForwardList<T>::Iterator( _node_first );
}


template <typename T>
typename MyForwardList<T>::Iterator MyForwardList<T>::end()
{
    return MyForwardList<T>::Iterator( nullptr );
}


template <typename T>
void MyForwardList<T>::init_value( void )
{
    _node_first = nullptr;
    _node_last = nullptr;
    _size = 0;
}


template <typename T>
typename MyForwardList<T>::Node* MyForwardList<T>::get_node( int idx ) const
{
    Node* ret = _node_first;
    while( idx-- )
    {
        ret = ret->next;
    }
    return ret;
}


template <typename T>
void MyForwardList<T>::swap( MyForwardList<T>& other ) noexcept
{
    std::swap( _node_first, other._node_first );
    std::swap( _node_last, other._node_last );
    std::swap( _size, other._size );
}

template <typename T>
MyForwardList<T>::Iterator::Iterator( const Iterator& other ) noexcept
    : _node( other._node ) 
{

}


template <typename T>
MyForwardList<T>::Iterator::Iterator( struct MyForwardList<T>::Node* node ) noexcept
    : _node( node ) 
{

}


template <typename T>
typename MyForwardList<T>::Iterator& MyForwardList<T>::Iterator::operator++()
{
    _node=_node->next;
    return *this;
}


template <typename T>
typename MyForwardList<T>::Iterator MyForwardList<T>::Iterator::operator++( int )
{
    MyForwardList<T>::Iterator temp( *this );
    operator++();
    return temp;
}


template <typename T>
bool MyForwardList<T>::Iterator::operator!= ( const MyForwardList<T>::Iterator& iterator ) const
{
    return _node != iterator._node;
}


template <typename T>
bool MyForwardList<T>::Iterator::operator== ( const MyForwardList<T>::Iterator& iterator ) const 
{
    return _node == iterator._node;
}

template <typename T>
T& MyForwardList<T>::Iterator::operator*()
{
    return _node->data;
}