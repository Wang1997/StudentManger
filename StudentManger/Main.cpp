#include<cstdlib>
#include "Manger.h"
#include "Test.h"
using namespace std;

#define MYDEBUG

int main(int argc,char *argv[])
{
#ifdef MYDEBUG //²âÊÔÊý¾Ý
    //CTest::test1();
    //CTest::test2();
    //CTest::test3();
    CTest::test4();
#else
    CManger *manger = new CManger();
    manger->start();
    delete manger;
#endif
    system("pause");
}