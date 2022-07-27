#pragma once

#include "icontainer.hpp"
#include <utility>
#include "cmath"

template <typename T>
class MyContainer : public IContainer<T> {
public:
    MyContainer() 
        : _data( nullptr )
        , _size( 0 )
        , _size_coef( 1.5 )
        , _capacity( 0 ) {}

    explicit MyContainer( const int& size )
        : _size( size ) 
    {
        _data = new T[_size];
        for( int i = 0; i < _size; i++ ) 
        {
            _data[i] = 0;
        }
    }

    MyContainer( const MyContainer& other )
    {
        _size = other.size();
        _data = new T[_size];
        for( int i = 0; i < _size; i++ )
        {
            _data[i] = other[i];
        }
        _capacity = other._capacity;
        _size_coef = other._size_coef;
    }

    MyContainer( MyContainer&& other )
    {
        _data = other._data;
        other._data = nullptr;
        _size = other._size;
        other._size = 0;
        _size_coef = other._size_coef;
        _capacity = other._capacity;
        other._capacity = 0; 
    }

    MyContainer& operator=( const MyContainer& rhs )
    {
        if( this != rhs )
        {
            MyContainer temp{rhs};
            *this = temp;
        }
        return *this;
    }

    MyContainer& operator=( MyContainer&& rhs )
    {
        MyContainer temp{std::move( rhs )};
        return *this = temp;
    }

    ~MyContainer() override 
    {
        delete [] _data;
    }

    void push_back( const T& val ) override 
    {
        if( _size >= _capacity )
        {
            _capacity = static_cast<int>( ceil( ( _size == 0 ) ? ( 1 ) : ( _size * _size_coef ) ) );
            T* temp = new T[_capacity];
            for( int i = 0; i < _size; i++ ) 
            {
                temp[i] = _data[i];
            }
            delete [] _data;
            _data = temp;
        }            
        _data[_size++] = val;        
    }

    int insert( const int& idx, const T& val ) override 
    {
        
        if( idx > _size )
        {
            return -1;
        }
        if( _size < _capacity )
        {
            for( int i = idx + 1; i < _size; i++ )
            {
                _data[i] = _data[i - 1];
            }
        }
        else 
        {
            _capacity = static_cast<int>( ceil( ( _size == 0 ) ? ( 1 ) : ( _size * _size_coef ) ) );
            T* temp = new T[_capacity];
            int pos = 0;
            for( int i = 0; i < _size; i++ ) 
            {
                ( i < idx ) ? ( pos = i ) : ( pos = i + 1 ) ;
                temp[pos] = _data[i];
            }
            delete [] _data;
            _data = temp;
        }
        _data[idx] = val;
        ++_size;

        return 0;
    }

    void erase( const int& idx ) override 
    {
        if( idx > _size )
        {
            return;
        }        

        for( int i = idx; i < ( _size - 1 ); i++ )
        {
            _data[i] = _data[i + 1];
        }
        --_size;
    }

    int size() const override
    {
        return _size;
    }

    const T& operator[]( const int& idx ) const  override
    {
        return _data[idx];
    }
    
    template <typename T>
    class Iterator {
    public: 
        Iterator() noexcept { _itr_ptr = nullptr; }
        Iterator( T* itr_ptr ) noexcept { _itr_ptr = itr_ptr; }    

        Iterator& operator++() 
        {
            ++_itr_ptr;
            return *this;
        }

        bool operator!=( const Iterator& iterator ) const
        {
            return _itr_ptr != iterator._itr_ptr;
        }

        T& operator*()
        {
            return *_itr_ptr;
        }

    private:
        T* _itr_ptr;
    };

    Iterator<T> begin() 
    {
        return Iterator<T>( _data );
    }

    Iterator<T> end() 
    {
        return  Iterator<T>( _data + _size ); 
    }

private:
    T* _data;
    int _size;
    float _size_coef;
    int _capacity; 
};