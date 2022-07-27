#include "icontainer.hpp"
#include "my_container.hpp"
#include "my_list.hpp"
#include "my_forward_list.hpp"

#include <iostream>

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

template <class InpItr>
void TestContainerIterator( const InpItr& itr_begin, const InpItr& itr_end )
{
    std::cout << "Test container iterator" << std::endl;
    auto itr = itr_begin;
    for( ; itr != itr_end; ++itr )
    {
        std::cout << ( *itr ) << " ";
    }
    std::cout << std::endl;
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


MyList<int> get_list( void )
{
    MyList<int> list;
    list.push_back( 10 );
    list.push_back( 20 );
    list.push_back( 30 );
    return list;
}

MyContainer<int> get_container( void )
{
    MyContainer<int> cont;
    cont.push_back( 10 );
    cont.push_back( 20 );
    cont.push_back( 30 );
    return cont;
}

MyForwardList<int> get_list_forward( void )
{
    MyForwardList<int> list_f;
    list_f.push_back( 10 );
    list_f.push_back( 20 );
    list_f.push_back( 30 );
    return list_f;
}


int main()
{
    std::cout << "Sequential container" << std::endl;
    MyContainer<int> container_s = MyContainer<int>();
    ContainerFillInitial( container_s );
    TestContainer( container_s );    
    MyContainer<int> container_s_copy = container_s;
    std::cout << "container copy: " << container_s_copy << std::endl;
    MyContainer<int> container_s_copy_2 = MyContainer<int>(container_s);
    std::cout << "container copy 2: " << container_s_copy_2 << std::endl;
    MyContainer<int> container_s_move = get_container();
    std::cout << "container move assignment: " << container_s_move << std::endl;  
    MyContainer<int> container_s_move_constr{get_container()};
    std::cout << "container move constructor: " << container_s_move_constr << std::endl;
    TestContainerIterator(container_s.begin(), container_s.end());


    std::cout << "List container" << std::endl;
    MyList<int> container_l = MyList<int>();
    ContainerFillInitial( container_l );
    TestContainer( container_l );     
    MyList<int> container_l_copy = container_l;
    std::cout << "container copy: " << container_l_copy << std::endl;
    MyList<int> container_l_copy_2 = MyList<int>(container_l);
    std::cout << "container copy 2: " << container_l_copy_2 << std::endl;  
    MyList<int> container_l_move = get_list();
    std::cout << "container move assignment: " << container_l_move << std::endl;  
    MyList<int> container_l_move_constr{get_list()};
    std::cout << "container move constructor: " << container_l_move_constr << std::endl;  
    TestContainerIterator(container_l_copy_2.begin(), container_l_copy_2.end());


    std::cout << "Forward list container" << std::endl;
    MyForwardList<int> container_fl = MyForwardList<int>();
    ContainerFillInitial( container_fl );
    TestContainer( container_fl );     
    MyForwardList<int> container_fl_copy = container_fl;
    std::cout << "container copy: " << container_fl_copy << std::endl;
    MyForwardList<int> container_fl_copy_2 = MyForwardList<int>(container_fl);
    std::cout << "container copy 2: " << container_fl_copy_2 << std::endl;  
    MyForwardList<int> container_fl_move = get_list_forward();
    std::cout << "container move assignment: " << container_fl_move << std::endl;  
    MyForwardList<int> container_fl_move_constr{get_list_forward()};
    std::cout << "container move constructor: " << container_fl_move_constr << std::endl;
    TestContainerIterator(container_fl_copy_2.begin(), container_fl_copy_2.end());
}