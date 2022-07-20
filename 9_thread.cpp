//
// Created by hk003ros on 2021/12/7.
//
//https://blog.csdn.net/sevenjoin/article/details/82187127

#include <iostream>
#include <thread>
#include <mutex>
#include <stdlib.h>

int cnt = 20;
std::mutex m;

void t1()
{
    while( cnt > 0 )
    {
        std::lock_guard<std::mutex> lockGuard( m );
        //std::m.lock();
        if( cnt > 0 )
        {
            //sleep( 1 )
            --cnt;
            std::cout << cnt << std::endl;
        }
        //std::m.unlock();
    }
}
void t2()
{
    while( cnt > 0 )
    {
        std::lock_guard<std::mutex> lockGuard( m );
        //std::m.lock();
        if( cnt > 0 )
        {
            --cnt;
            std::cout << cnt << std::endl;
        }
        //std::m.unlock();
    }
}

int main( void )
{
    std::thread th1( t1 );
    std::thread th2( t2 );

    th1.join();
    th2.join();

    std::cout << "here is the main()" << std::endl;

    return 0;
}





/*
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void t1()
{
    for( int i = 0; i < 10; ++i )
    {
        cout << "t1111\n" ;
        sleep( 1 );
    }
}

void t2()
{
    for( int i = 0; i < 20; ++i )
    {
        cout << "t2222\n" ;
        sleep( 1 );
    }

}

int main()
{
    thread th1( t1 );
    thread th2( t2 );

    th1.join();
    th2.join();

    cout << "here is main\n\n";

    return 0;
}
*/





















