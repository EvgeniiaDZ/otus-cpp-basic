#pragma once

#include "icontainer.hpp"


template <typename T>
class MyContainer : public IContainer<T> {
public:
    MyContainer() 
        : _data( nullptr )
        , _size( 0 ) {}

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
    }

    MyContainer& operator=( const MyContainer& other )
    {
        if( this != other )
        {
            _size = other.size();
            _data = new T[_size];
            for( int i = 0; i < _size; i++ )
            {
                _data[i] = other[i];
            }
        }
        return *this;
    }

    ~MyContainer() override 
    {
        delete [] _data;
    }

    void push_back( const T& val ) override 
    {
        T* temp = new T[_size + 1];
        for( int i = 0; i < _size; i++ ) 
        {
            temp[i] = _data[i];
        }
        delete [] _data;
        _data = temp;
        _data[_size] = val;
        ++_size;
    }

    int insert( const int& idx, const T& val ) override 
    {
		if( idx > _size )
		{
			return -1;
		}

        T* temp = new T[_size + 1];
        int pos = 0;
        for( int i = 0; i < _size; i++ ) 
        {
            ( i < idx ) ? ( pos = i ) : ( pos = i + 1 ) ;
            temp[pos] = _data[i];
        }
        delete [] _data;
        _data = temp;
		++_size;
        _data[idx] = val;
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

private:
    T* _data;
    int _size;
};
