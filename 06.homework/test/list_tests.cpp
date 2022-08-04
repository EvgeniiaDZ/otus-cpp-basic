#include "my_list.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <list>

TEST( list, empty )
{
    // Arrange
    MyList<int> list;
    
    // Act( empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
}

TEST( list, push_back )
{
    // Arrange
    const int count = 10;
    MyList<int> list;

    // Act
    for( int i = 0; i < count; ++i )
    {
        list.push_back( i );
    }

    // Assert
    ASSERT_EQ( list.size(), count );
    std::list<int> list_expect = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, insert_back )
{
    // Arrange
    MyList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );

    // Act
    list.insert( 2, 2 );

    // Assert
    ASSERT_EQ( list.size(), 3 );
    std::list<int> list_expect = {0, 1 , 2};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, insert_front )
{
    // Arrange
    MyList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );

    // Act
    list.insert( 0, -1 );

    // Assert
    ASSERT_EQ( list.size(), 3 );
    std::list<int> list_expect = {-1, 0 , 1};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, insert_midle )
{
    // Arrange
    MyList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );

    // Act
    list.insert( 1, 2 );

    // Assert
    ASSERT_EQ( list.size(), 3 );
    std::list<int> list_expect = {0, 2 , 1};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, erase_back )
{
    // Arrange
    MyList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );

    // Act
    list.erase( 2 );

    // Assert
    ASSERT_EQ( list.size(), 2 );
    std::list<int> list_expect = {0, 1};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, erase_front )
{
    // Arrange
    MyList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );

    // Act
    list.erase( 0 );

    // Assert
    ASSERT_EQ( list.size(), 2 );
    std::list<int> list_expect = {1, 2};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, erase_midle )
{
    // Arrange
    MyList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );

    // Act
    list.erase( 1 );

    // Assert
    ASSERT_EQ( list.size(), 2 );
    std::list<int> list_expect = {0, 2};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( list, get_value)
{
    // Arrange
    const int count = 10;
    MyList<int> list;

    // Act
    for( int i = 0; i < count; ++i )
    {
        list.push_back( i );
    }

    // Assert
    ASSERT_EQ( list.size(), count );
    for( int i = 0; i < count; ++i )
    {
        ASSERT_EQ( list[i], i );
    }
}

TEST( list, copy )
{
    // Arrange
    MyList<int> list;
    list.push_back( 10 );
    list.push_back( 20 );
    list.push_back( 30 );
    MyList<int> list_copy;

    // Act
    list_copy = list;

    // Assert
    ASSERT_TRUE( std::equal( list.begin(), list.end(), list_copy.begin() ) );
}