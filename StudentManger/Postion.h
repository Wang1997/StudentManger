#pragma once

/*
λ����,���ڴ��ѧ����λ�úʹ�С
λ�úʹ�Сȷ����Ͳ����޸�
*/
class CPostion
{
public:
    CPostion();
    CPostion(int pos,int size);
    CPostion(int size);
    ~CPostion();

public:
    int getPos() const;
    int getSize() const;
    
    CPostion& operator++ ();
    CPostion& operator++ (int);

private:
    int m_pos; //λ��
    int m_size; //��С
};

