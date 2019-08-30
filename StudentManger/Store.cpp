#include "Store.h"

const char* CStore::READ_MODE = "rb";
const char* CStore::WRITE_MODE = "wb";
const char* CStore::READ_WRITE_MODE = "rb+";

const int CStore::SUCCESS = 1;
const int CStore::FAIL = 0;

CStore::CStore(CMyString& filePath)
    :stream(nullptr), filePath(filePath)
{
    int ret = open(READ_MODE);
    if (ret == FAIL)
    {
        if (!open(WRITE_MODE))
        {
            throw CMyFileException("�ļ���ʧ��");
        }
    }
    close();
}


CStore::~CStore()
{
    close();
}

int CStore::open(const char * mode)
{
    if (stream != nullptr)
    {
        throw CMyFileException("�ļ��Ѵ�");
    }
    stream = fopen(filePath.c_str(),mode);
    if (stream == nullptr)
    {
        return FAIL;
    }
    return SUCCESS;
}

int CStore::close()
{
    if (stream != nullptr)
    {
        if(fclose(stream))
            throw CMyFileException("�ļ��ر�ʧ��");
        stream = nullptr;
    }
    return SUCCESS;
}

int CStore::read(void * buffer,int size)
{
    if(stream == nullptr)
        throw CMyFileException("�ļ��ѹر�");
    return fread(buffer, size, 1, stream);
}

int CStore::write(const void * buffer,int size)
{
    if (stream == nullptr)
        throw CMyFileException("�ļ��ѹر�");
    return fwrite(buffer, size, 1, stream);
}

void CStore::seek(long offset)
{
    if (stream == nullptr)
        throw CMyFileException("�ļ��ѹر�");
    fseek(stream, offset, SEEK_SET);
}

long CStore::getFileSize()
{
    if (stream == nullptr)
        open(READ_MODE);
    fseek(stream, 0, SEEK_END);
    long size = ftell(stream);
    close();
    return size;
}
