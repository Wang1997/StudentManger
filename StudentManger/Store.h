#pragma once
#include "MyException.h"
#include "MyString.h"
#include <cstdio>

class CStore
{
public:
    CStore(CMyString& filePath);
    ~CStore();

    int open(const char*mode);
    int close();
    int read(void *buffer,int size);
    int write(const void *buffer,int size);
    void seek(long offset);
    long getFileSize();
public:
    FILE *stream;
    CMyString filePath;
public:
    static const char* READ_MODE;
    static const char* WRITE_MODE;
    static const char* READ_WRITE_MODE;
    static const int SUCCESS;
    static const int FAIL;
};

