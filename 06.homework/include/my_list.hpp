#pragma once

#include "icontainer.hpp"
#include <utility>

template <typename T>
class MyList : public IContainer<T> 
{
public:
    MyList()
    {
        init_value();
    }

    MyList( const MyList& other )
    {
        init_value();
        for( int i = 0; i < other.size(); i++ )
        {
            this->push_back( other[i] );
        }
    }

    MyList( MyList&& other )
    {
        _node_last = other._node_last;
        _size = other._size;
        other._node_last = nullptr;
        other._size = 0;
    }

    MyList& operator=( const MyList& rhs )
    {
        if( this != &rhs )
        {
            MyList temp{rhs};
            swap( temp );
        }
        return *this;
    }

    MyList& operator=( MyList&& rhs )
    {
        MyList temp{std::move( rhs )};
        return *this = temp;
    }

    ~MyList() override
    {
        while( _size )
        {
            erase( _size - 1 );
        }
    }

    void push_back( const T& val ) override
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

    int insert( const int& idx, const T& val ) override
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
            idx_node->prev = new_node;        
        }
        ++_size;
		return 0;
    }

    void erase( const int& idx ) override
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

    int size() const override
    {
        return _size;
    }

    const T& operator[]( const int& idx ) const override
    {
        Node* idx_node = get_node( idx );
        return idx_node->data;
    } 

    struct Node 
    {
        Node* next;
        Node* prev;
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
            _node = _node->next;
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
        return Iterator<T>( get_node(0) );
    }

    Iterator<T> end()
    {
        return Iterator<T>( _node_last );
    }

private:

    Node* _node_last;
    int _size;

    Node* get_node( int idx ) const 
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

    void init_value( void )
    {
        _node_last = nullptr;
        _size = 0;
    }

    void swap( MyList::Node& lhs, MyList::Node& rhs ) noexcept
    {
        std::swap( lhs.data, rhs.data );
        std::swap( lhs.next, rhs.next );
        std::swap( lhs.prev, rhs.prev );
    }

    void swap( MyList& other ) noexcept
    {
        std::swap( _size, other._size );
        swap( *_node_last, *other._node_last );
    }
};

