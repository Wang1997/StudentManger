#include<cstdlib>
#include "Manger.h"
#include "Test.h"
using namespace std;

int main(int argc,char *argv[])
{
    //CTest::test1();
    //CTest::test2();
    //CTest::test3();
    CManger *manger = new CManger();
    manger->start();
    delete manger;
    system("pause");
}