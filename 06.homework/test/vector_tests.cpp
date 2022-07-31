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
}
