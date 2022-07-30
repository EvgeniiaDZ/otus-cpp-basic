#include "icontainer.hpp"
#include "my_container.hpp"
#include "my_list.hpp"
#include "my_forward_list.hpp"

#include <iostream>
#include <utility>

template <typename T>
void ContainerFillInitial( IContainer<T> & cont )
{
    for( int i = 0; i <= 9; i++ )
    {
        cont.push_back(i);
    }    
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const IContainer<T>& cont)
{
    for( int i = 0; i < cont.size(); i++ )
    {
        os << cont[i] << ' ';    
    }
    return os;
}

template <typename T>
void TestContainer( IContainer<T>& container )
{
    std::cout << "container: " << container << std::endl;
    std::cout << "size = " << container.size() << std::endl;
    container.erase( 2 );
    container.erase( 3 );
    container.erase( 4 );
    std::cout << "container: " << container << std::endl;
    container.erase( 0 );
    container.erase( container.size() - 1 );
    std::cout << "container: " << container << std::endl;
    container.insert( 0, 10 );
    std::cout << "container: " << container << std::endl;
    container.insert( container.size() / 2, 20 );
    std::cout << "container: " << container << std::endl;
    container.insert( container.size(), 30 );
    std::cout << "container: " << container << std::endl;
}


int main()
{
    std::cout << "Sequential container" << std::endl;
    MyContainer<int> container_s = MyContainer<int>();
    ContainerFillInitial( container_s );
    TestContainer( container_s );    


    std::cout << "List container" << std::endl;
    MyList<int> container_l = MyList<int>();
    ContainerFillInitial( container_l );
    TestContainer( container_l );     


    std::cout << "Forward list container" << std::endl;
    MyForwardList<int> container_fl = MyForwardList<int>();
    ContainerFillInitial( container_fl );
    TestContainer( container_fl );         
}