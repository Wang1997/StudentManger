#include<cstdlib>
#include <iostream>
#include "Elem.h"
using namespace std;

int main(int argc,char *argv[])
{
    {
        CMyString str("hahah");
        CStudent *stu = new CStudent(str);
        CPostion *pos = new CPostion(0, stu->getTotalSize());
        CElem elem1(stu, pos);
        CElem elem2(new CPostion(4));
        {
            CElem elem3(elem1);
        }
        CElem elem4 = elem2;
        elem4 = elem1;
    }
    system("pause");
}