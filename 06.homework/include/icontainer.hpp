#pragma once

template <typename T>
class IContainer {
public:
    virtual ~IContainer() {};
    virtual void push_back( const T& val ) = 0;
    virtual int insert( const int& idx, const T& val ) = 0;
    virtual void erase( const int& idx ) = 0;
    virtual int size() const = 0;
    virtual const T& operator[]( const int& idx ) const = 0; 
};