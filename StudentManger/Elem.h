#pragma once
#include "Student.h"
#include "Postion.h"
#include "Ref.h"

class CElem
{
public:
    CElem(CStudent *student, CPostion *postion);
    CElem(int stuId);
    CElem(const CMyString& name);
    CElem(CPostion *postion);
    ~CElem();

    CElem(const CElem& other);
    CElem& operator= (const CElem& other);

    CStudent * getStudent() const;
    CPostion * getPostion() const;

private:
    void initRef(); //初始化引用计数
    void release(); //销毁空间

private:
    CStudent *m_student;
    CPostion *m_postion;
    CRef *m_ref;
};

