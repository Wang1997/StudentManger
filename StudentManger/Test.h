#pragma once

/*
测试文件,主要用于测试数据
*/
class CTest
{
public:
    CTest();
    ~CTest();

    static int test1(); //hash 姓名冲突测试
    static void test2(); //树顺序插入测试
    static void test3(); //树层序插入测试
    static void test4(); //hash数据量测试
};

