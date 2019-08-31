#include "Manger.h"
#include "ViewUI.h"
#include "Config.h"
#include "Util.h"
#include <ctime>

CManger::CManger() :m_HashByName(CConfig::NameTableSize),
        m_HashByDelete(CConfig::DelTableSize),
        m_store(CMyString(CConfig::FilePath))
{
    srand(time(NULL)); //ֻ��һ��
}


CManger::~CManger()
{
}

void CManger::start()
{
    if (!m_store.getFileSize())
    { //��ʼ������
        initData();
    }
    loadData();
    menuControl();
}

void CManger::loadData()
{
    CViewUI::clearScreen();
    CViewUI::show("��ʼ��������,���Ժ�...\r\n");
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
        if (id <= 0) //ɾ��������
        {
            m_HashByDelete.insert(*pPos);
        }
        else
        {
            CMyString name(data + CStudent::BASE_SIZE); //��ȡ����
            CStudent *pStu = new CStudent(name);
            CUtil::read(pStu, data, CStudent::BASE_SIZE); //������������
            CElem elem(pStu,pPos);
            m_TreeById.insert_unique(elem); //id���в���
            m_HashByName.insert(elem); //�������в���
        }
        pos += 1 + size;
        data += size;
    }
    CViewUI::show("���ݼ��سɹ�\r\n");
    delete[] srcData;
    CViewUI::pause();
}

void CManger::initData()
{
    CViewUI::clearScreen();
    CViewUI::show("��ʼ��������,���Ժ�...\r\n");
    int maxStore = CUtil::calcRandomMaxStore();
    char * data = new char[maxStore];
    char * srcData = data;
    for (int i = 1; i <= CConfig::InitDataNum; ++i)
    {
        CMyString name = CUtil::randomName();
        char size = CStudent::calcTotalSize(name.length());
        CUtil::write(data, size);
        if(i == 3)
            CUtil::write(data, 0); //ģ��һ��ɾ��
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
    CViewUI::show("�����������\r\n");
    delete[] srcData; //�ͷſռ�
    CViewUI::pause();
}

void CManger::menuControl()
{
    while (true)
    {
        CViewUI::clearScreen();
        CViewUI::show("  ѧ������ϵͳ  \r\n");
        CViewUI::show("1.���ӹ���\r\n");
        CViewUI::show("2.ɾ������\r\n");
        CViewUI::show("3.�޸Ĺ���\r\n");
        CViewUI::show("4.ID��ѯ\r\n");
        CViewUI::show("5.������ѯ\r\n");
        CViewUI::show("6.�˳�\r\n");
        CViewUI::show("��ѡ��:");
        int choose = CViewUI::input<int>();
        switch (choose)
        {
        default:
            return;
        }
    }
}
