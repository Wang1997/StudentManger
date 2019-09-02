#include "Elem.h"

CElem::CElem(CStudent * student, CPostion * postion)
    :m_student(student),m_postion(postion)
{
    initRef();
}

CElem::CElem(int stuId)
    :m_postion(nullptr)
{
    m_student = new CStudent(stuId);
    initRef();
}

CElem::CElem(const CMyString& name)
    :m_postion(nullptr)
{
    m_student = new CStudent(name);
    initRef();
}

CElem::CElem(CPostion * postion)
    :m_student(nullptr), m_postion(postion)
{
    initRef();
}

CElem::~CElem()
{
    m_ref->subRef();
    if (m_ref->checkIsEmpty())
    { //最后一个引用就释放资源
        release();
    }
}

CElem::CElem(const CElem & other)
    :m_student(other.m_student),m_postion(other.m_postion),
     m_ref(other.m_ref)
{
    //浅拷贝
    m_ref->addRef(); //计数+1
}

CElem & CElem::operator=(const CElem & other)
{
    if (&other == this)
        return *this;

    //使用引用计数
    if (!m_ref->checkIsLast())
    { //不是最后一个就计数-1
        m_ref->subRef();
    }
    else
    { //否则释放资源
        release();
    }
    //浅拷贝
    memcpy(this, &other, sizeof(CElem));
    m_ref->addRef(); //计数+1
    return *this;
}

CStudent * CElem::getStudent() const
{
    return m_student;
}

CPostion * CElem::getPostion() const
{
    return m_postion;
}

void CElem::initRef()
{
    m_ref = CRef::getInstance();
}

void CElem::release()
{
    if (m_student != nullptr)
    {
        delete m_student;
        m_student = nullptr;
    }
    if (m_postion != nullptr)
    {
        delete m_postion;
        m_postion = nullptr;
    }
    if (m_ref != nullptr)
    {
        delete m_ref;
        m_ref = nullptr;
    }
}
