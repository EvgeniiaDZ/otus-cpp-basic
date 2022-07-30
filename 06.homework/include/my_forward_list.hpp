#pragma once

#include "icontainer.hpp"
#include <utility>

template <typename T>
class MyForwardList : public IContainer<T>
{
public:
    MyForwardList()
    {
        init_value();
    }

    MyForwardList( const MyForwardList& other )
    {
        init_value();
        for( int i = 0; i < other.size(); i++ )
        {
            this->push_back( other[i] );
        }
    }

    MyForwardList( MyForwardList&& other )
    {
        _node_first = other._node_first;
        other._node_first = nullptr;
        _node_last = other._node_last;
        other._node_last = nullptr;
        _size = other._size;
        other._size = 0;
    }

    MyForwardList& operator=( const MyForwardList& rhs )
    {
        if( this != &rhs )
        {
            MyForwardList temp{rhs};
            swap( temp );
        }
        return *this;
    }

    MyForwardList& operator=( MyForwardList&& rhs )
    {
        MyForwardList temp{std::move( rhs )};
        return * this = temp;
    }

    ~MyForwardList() override
    {
        while( _size )
        {
            erase( _size - 1 );
        }        
    }

    void push_back( const T& val ) override
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

    int insert( const int& idx, const T& val ) override
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

    void erase( const int& idx )override
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

    int size() const override
    {
        return _size;
    }

    const T& operator[]( const int& idx ) const override
    {
        return get_node( idx )->data;
    }

    struct Node {
        Node* next;
        T data;
    };

    template <typename T>
    class Iterator
    {
    public:
        Iterator() noexcept
            : _node( nullptr ) {}
        Iterator( struct Node* node ) noexcept
            : _node( node ) {}
        Iterator& operator++()
        {
            _node=_node->next;
            return *this;
        }
        bool operator!= ( const Iterator& iterator ) const
        {
            return _node != iterator._node;
        }
        T& operator*()
        {
            return _node->data;
        }
    private:
        struct Node* _node;
    };

    Iterator<T> begin()
    {
        return Iterator<T>( _node_first );
    }

    Iterator<T> end()
    {
        return Iterator<T>( _node_last );
    }
private:
    Node* _node_first;
    Node* _node_last;
    int _size;

    void init_value( void )
    {
        _node_first = nullptr;
        _node_last = nullptr;
        _size = 0;
    }

    Node* get_node( int idx ) const
    {
        Node* ret = _node_first;
        while( idx-- )
        {
            ret = ret->next;
        }
        return ret;
    }

    void swap( MyForwardList::Node& lhs, MyForwardList::Node& rhs ) noexcept
    {
        std::swap( lhs.data, rhs.data );
        std::swap( lhs.next, rhs.next );
    }

    void swap( MyForwardList& other ) noexcept
    {
        std::swap( _node_first, other._node_first );
        std::swap( _node_last, other._node_last );
        std::swap( _size, other._size );
    }
};