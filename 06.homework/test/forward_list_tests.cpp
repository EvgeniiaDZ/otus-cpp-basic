#include "my_forward_list.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <forward_list>

TEST( forward_list, empty )
{
    // Arrange
    MyForwardList<int> list;
    
    // Act( empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
}

TEST( forward_list, push_back )
{
    // Arrange
    const int count = 10;
    MyForwardList<int> list;

    // Act
    for( int i = 0; i < count; ++i )
    {
        list.push_back( i );
    }

    // Assert
    ASSERT_EQ( list.size(), count );
    std::forward_list<int> list_expect = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, insert_back )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );

    // Act
    list.insert( 2, 2 );

    // Assert
    ASSERT_EQ( list.size(), 3 );
    std::forward_list<int> list_expect = {0, 1 , 2};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, insert_front )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );

    // Act
    list.insert( 0, -1 );

    // Assert
    ASSERT_EQ( list.size(), 3 );
    std::forward_list<int> list_expect = {-1, 0 , 1};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, insert_midle )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );

    // Act
    list.insert( 1, 2 );

    // Assert
    ASSERT_EQ( list.size(), 3 );
    std::forward_list<int> list_expect = {0, 2 , 1};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, erase_back )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );

    // Act
    list.erase( 2 );

    // Assert
    ASSERT_EQ( list.size(), 2 );
    std::forward_list<int> list_expect = {0, 1};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, erase_front )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );

    // Act
    list.erase( 0 );

    // Assert
    ASSERT_EQ( list.size(), 2 );
    std::forward_list<int> list_expect = {1, 2};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, erase_midle )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 0 );
    list.push_back( 1 );
    list.push_back( 2 );

    // Act
    list.erase( 1 );

    // Assert
    ASSERT_EQ( list.size(), 2 );
    std::forward_list<int> list_expect = {0, 2};
    ASSERT_TRUE( std::equal( list_expect.begin(), list_expect.end(), list.begin() ) );
}

TEST( forward_list, get_value)
{
    // Arrange
    const int count = 10;
    MyForwardList<int> list;

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

TEST( forward_list, copy )
{
    // Arrange
    MyForwardList<int> list;
    list.push_back( 10 );
    list.push_back( 20 );
    list.push_back( 30 );
    MyForwardList<int> list_copy;

    // Act
    list_copy = list;

    // Assert
    ASSERT_TRUE( std::equal( list.begin(), list.end(), list_copy.begin() ) );
}