#include "Manger.h"
#include "ViewUI.h"
#include "Config.h"
#include "Util.h"
#include <ctime>

CManger::CManger() :m_HashByName(CConfig::NameTableSize),
        m_HashByDelete(CConfig::DelTableSize),
        m_store(CMyString(CConfig::FilePath))
{
    srand(time(NULL)); //只能一次
}


CManger::~CManger()
{
}

void CManger::start()
{
    if (!m_store.getFileSize())
    { //初始化数据
        initData();
    }
    loadData();
    menuControl();
}

void CManger::loadData()
{
    CViewUI::clearScreen();
    CViewUI::show("开始加载数据,请稍后...\r\n");
    int maxStore = m_store.getFileSize();
    char * data = new char[maxStore];
    m_store.open(CStore::READ_MODE);
    m_store.read(data,maxStore);
    m_store.close();
    char * srcData = data;
    int pos = 0;
    while (pos < maxStore)
    {
        char size = CUtil::read<char>(data);
        data++;
        int id = CUtil::read<int>(data);
        CPostion *pPos = new CPostion(pos, size);
        if (id <= 0) //删除的数据
        {
            m_HashByDelete.insert(*pPos);
        }
        else
        {
            CMyString name(data + CStudent::BASE_SIZE); //读取姓名
            CStudent *pStu = new CStudent(name);
            CUtil::read(pStu, data, CStudent::BASE_SIZE); //拷贝基本数据
            CElem elem(pStu,pPos);
            m_TreeById.insert_unique(elem); //id树中插入
            m_HashByName.insert(elem); //姓名表中插入
        }
        pos += 1 + size;
        data += size;
    }
    CViewUI::show("数据加载成功\r\n");
    delete[] srcData;
    CViewUI::pause();
}

void CManger::initData()
{
    CViewUI::clearScreen();
    CViewUI::show("开始生成数据,请稍后...\r\n");
    int maxStore = CUtil::calcRandomMaxStore();
    char * data = new char[maxStore];
    char * srcData = data;
    for (int i = 1; i <= CConfig::InitDataNum; ++i)
    {
        CMyString name = CUtil::randomName();
        char size = CStudent::calcTotalSize(name.length());
        CUtil::write(data, size);
        if(i == 3)
            CUtil::write(data, 0); //模拟一条删除
        else
            CUtil::write(data, i);
        CUtil::write(data, CUtil::randomYear());
        CUtil::write(data, CUtil::randomMonth());
        CUtil::write(data, CUtil::randomSex());
        CUtil::write(data, name.c_str());
        //CViewUI::show(name,true);
    }
    int totalSize = data - srcData;
    m_store.open(CStore::WRITE_MODE);
    m_store.write(srcData, totalSize);
    m_store.close();
    CViewUI::show("数据生成完毕\r\n");
    delete[] srcData; //释放空间
    CViewUI::pause();
}

void CManger::menuControl()
{
    while (true)
    {
        CViewUI::clearScreen();
        CViewUI::show("  学生管理系统  \r\n");
        CViewUI::show("1.增加功能\r\n");
        CViewUI::show("2.删除功能\r\n");
        CViewUI::show("3.修改功能\r\n");
        CViewUI::show("4.ID查询\r\n");
        CViewUI::show("5.姓名查询\r\n");
        CViewUI::show("6.退出\r\n");
        CViewUI::show("请选择:");
        int choose = CViewUI::input<int>();
        switch (choose)
        {
        default:
            return;
        }
    }
}
