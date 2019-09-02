#pragma once

/*
位置类,用于存放学生的位置和大小
位置和大小确定后就不能修改
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
    int m_pos; //位置
    int m_size; //大小
};

