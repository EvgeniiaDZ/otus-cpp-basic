#include "my_container.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <vector>

TEST( vector, empty )
{
    // Arrange
    MyContainer<int> vector;
    
    // Act( empty for this test)

    // Assert
    ASSERT_EQ(vector.size(), 0);
}

TEST( vector, push_back )
{
    // Arrange
    const int count = 10;
    MyContainer<int> vector;

    // Act
    for( int i = 0; i < count; ++i )
    {
        vector.push_back( i );
    }

    // Assert
    ASSERT_EQ( vector.size(), count );
    std::vector<int> vector_expect = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );
}

TEST( vector, insert_back )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 0 );
    vector.push_back( 1 );

    // Act
    vector.insert( 2, 2 );

    // Assert
    ASSERT_EQ( vector.size(), 3 );
    std::vector<int> vector_expect = {0, 1 , 2};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );
}

TEST( vector, insert_front )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 0 );
    vector.push_back( 1 );

    // Act
    vector.insert( 0, -1 );

    // Assert
    ASSERT_EQ( vector.size(), 3 );
    std::vector<int> vector_expect = {-1, 0 , 1};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );
}

TEST( vector, insert_midle )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 0 );
    vector.push_back( 1 );

    // Act
    vector.insert( 1, 2 );

    // Assert
    ASSERT_EQ( vector.size(), 3 );
    std::vector<int> vector_expect = {0, 2 , 1};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );
}

TEST( vector, erase_back )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 0 );
    vector.push_back( 1 );
    vector.push_back( 2 );

    // Act
    vector.erase( 2 );

    // Assert
    ASSERT_EQ( vector.size(), 2 );
    std::vector<int> vector_expect = {0, 1};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );    
}

TEST( vector, erase_front )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 0 );
    vector.push_back( 1 );
    vector.push_back( 2 );

    // Act
    vector.erase( 0 );

    // Assert
    ASSERT_EQ( vector.size(), 2 );
    std::vector<int> vector_expect = {1, 2};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );    
}

TEST( vector, erase_midle )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 0 );
    vector.push_back( 1 );
    vector.push_back( 2 );

    // Act
    vector.erase( 1 );

    // Assert
    ASSERT_EQ( vector.size(), 2 );
    std::vector<int> vector_expect = {0, 2};
    ASSERT_TRUE( std::equal( vector_expect.begin(), vector_expect.end(), vector.begin() ) );    
}

TEST( vector, get_value)
{
    // Arrange
    const int count = 10;
    MyContainer<int> vector;

    // Act
    for( int i = 0; i < count; ++i )
    {
        vector.push_back( i );
    }

    // Assert
    ASSERT_EQ( vector.size(), count );
    for( int i = 0; i < count; ++i )
    {
        ASSERT_EQ( vector[i], i );
    }
}

TEST( vector, copy )
{
    // Arrange
    MyContainer<int> vector;
    vector.push_back( 10 );
    vector.push_back( 20 );
    vector.push_back( 30 );
    MyContainer<int> vector_copy;

    // Act
    vector_copy = vector;

    // Assert
    ASSERT_TRUE( std::equal( vector.begin(), vector.end(), vector_copy.begin() ) );
}