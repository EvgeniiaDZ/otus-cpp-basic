#pragma once

#include "icontainer.hpp"
#include <utility>
#include "cmath"

template <typename T>
class MyContainer : public IContainer<T> {
public:
    MyContainer();
    explicit MyContainer( const int& size );
    MyContainer( const MyContainer& other );
    MyContainer( MyContainer&& other );

    MyContainer& operator=( const MyContainer& rhs );
    MyContainer& operator=( MyContainer&& rhs );
    
    ~MyContainer() override;

    void push_back( const T& val ) override; 
    int insert( const int& idx, const T& val ) override;
    void erase( const int& idx ) override;
    int size() const override;
    const T& operator[]( const int& idx ) const  override;

    class Iterator {
    public: 
        Iterator() noexcept;
        Iterator( T* itr_ptr ) noexcept; 

        Iterator& operator++(); 
        bool operator!=( const Iterator& iterator ) const;
        T& operator*();
    private:
        T* _itr_ptr;
    };

    Iterator begin(); 
    Iterator end();

private:
    void swap( MyContainer& other ) noexcept;

    T* _data;
    int _size;
    float _size_coef;
    int _capacity; 
};


template <typename T>
MyContainer<T>::MyContainer()
    : _data( nullptr )
    , _size( 0 )
    , _size_coef( 1.5 )
    , _capacity( 0 ) 
{

}


template <typename T>
MyContainer<T>::MyContainer( const int& size )
    : _size( size ) 
{
    _data = new T[_size];
    for( int i = 0; i < _size; i++ ) 
    {
        _data[i] = 0;
    }
}


template <typename T>
MyContainer<T>::MyContainer( const MyContainer<T>& other )
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


template <typename T>
MyContainer<T>::MyContainer( MyContainer<T>&& other )
{
    _data = other._data;
    other._data = nullptr;
    _size = other._size;
    other._size = 0;
    _size_coef = other._size_coef;
    _capacity = other._capacity;
    other._capacity = 0; 
}


template <typename T>
MyContainer<T>& MyContainer<T>::operator=( const MyContainer<T>& rhs )
{
    if( this != &rhs )
    {
        MyContainer temp{rhs};
        swap( temp );
    }
    return *this;
}


template <typename T>
MyContainer<T>& MyContainer<T>::operator=( MyContainer<T>&& rhs )
{
    MyContainer temp{std::move( rhs )};
    return *this = temp;
}


template <typename T>
MyContainer<T>::~MyContainer()
{
    delete [] _data;
}


template <typename T>
void MyContainer<T>::push_back( const T& val )
{
    if( _size >= _capacity )
    {
        _capacity = static_cast<int>( ceil( ( _size == 0 ) ? ( 1 ) : ( _size * _size_coef ) ) );
        if( _capacity == _size )
            ++_capacity;
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


template <typename T>
int MyContainer<T>::insert( const int& idx, const T& val )
{
    
    if( idx > _size )
    {
        return -1;
    }
    if( _size < _capacity )
    {
        for( int i = _size; i > idx; --i )
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


template <typename T>
void MyContainer<T>::erase( const int& idx )
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


template <typename T>
int MyContainer<T>::size() const
{
    return _size;
}


template <typename T>
const T& MyContainer<T>::operator[]( const int& idx ) const
{
    return _data[idx];
}


template <typename T>
typename MyContainer<T>::Iterator MyContainer<T>::begin() 
{
    return MyContainer<T>::Iterator( _data );
}


template <typename T>
typename MyContainer<T>::Iterator MyContainer<T>::end() 
{
    return MyContainer<T>:: Iterator( _data + _size ); 
}


template <typename T>
void MyContainer<T>::swap( MyContainer<T>& other ) noexcept
{
    std::swap( _data, other._data );
    std::swap( _size, other._size );
    std::swap( _size_coef, other._size_coef );
    std::swap( _capacity, other._capacity );
}


template <typename T>
MyContainer<T>::Iterator::Iterator() noexcept
    :_itr_ptr{ nullptr} 
{ 
     
}


template <typename T>
MyContainer<T>::Iterator::Iterator( T* itr_ptr ) noexcept  
    : _itr_ptr{ itr_ptr }    
{

}


template <typename T>
typename MyContainer<T>::Iterator& MyContainer<T>::Iterator::operator++() 
{
    ++_itr_ptr;
    return *this;
}


template <typename T>
bool MyContainer<T>::Iterator::operator!=( const MyContainer<T>::Iterator& iterator ) const
{
    return _itr_ptr != iterator._itr_ptr;
}


template <typename T>
T& MyContainer<T>::Iterator::operator*()
{
    return *_itr_ptr;
}