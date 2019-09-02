#include "Manger.h"
#include "ViewUI.h"
#include "Config.h"
#include "Util.h"
#include <ctime>

CManger::CManger() :m_HashByName(CConfig::NameTableSize),
        m_HashByPos(CConfig::DelTableSize),
        m_store(CMyString(CConfig::FilePath))
{
    srand(time(NULL)); //srandֻ��һ��
}


CManger::~CManger()
{
    CViewUI::clearScreen();
    CViewUI::show("�����˳�,���Ժ�...\r\n");
}

void CManger::start()
{
    char *data = nullptr;
    int maxStore = 0;
    if (!m_store.getFileSize())
    { //��ʼ������
        data = initData(maxStore);
    }
    loadData(data,maxStore);
    menuControl();
}

void CManger::loadData(char * data, int maxStore)
{
    CViewUI::clearScreen();
    CViewUI::show("��ʼ��������,���Ժ�...\r\n");

    if (data == nullptr) //Ϊ��ʱ���ļ���������
    {
        maxStore = m_store.getFileSize();
        data = new char[maxStore];
        m_store.open(CStore::READ_MODE);
        m_store.read(data, maxStore);
        m_store.close();
    }
    
    char *srcData = data;
    int pos = 0;
    int maxId = 0;
    while (pos < maxStore)
    {
        char size = CUtil::read<char>(data);
        data++;
        int id = CUtil::read<int>(data);
        if (id == CConfig::IDDelFlag) //ɾ��������
        {
            m_HashByPos.insert(CPostion(pos, size));
        }
        else
        {
            CPostion *pPos = new CPostion(pos, size); //����λ�ö���
            CMyString name(data + CStudent::BASE_SIZE); //�ȶ�ȡ����
            CStudent *pStu = new CStudent(name);
            CUtil::read(pStu, data, CStudent::BASE_SIZE); //������������
            CElem elem(pStu,pPos);
            m_TreeById.insert_equal(elem); //id���в���
            m_HashByName.insert(elem); //�������в���
        }
        maxId = MAX(maxId,id);
        pos += 1 + size;
        data += size;
    }
    CViewUI::show("���ݼ��سɹ�\r\n");
    CStudent::initMaxId(maxId+1);
    delete[] srcData;
    CViewUI::pause();
}

char* CManger::initData(int& maxStore)
{
    CViewUI::clearScreen();
    CViewUI::show("��ʼ��������,���Ժ�...\r\n");
    maxStore = CUtil::calcRandomMaxStore();
    char * data = new char[maxStore];
    char * srcData = data;
    for (int i = 1; i <= CConfig::InitDataNum; ++i)
    {
        CMyString name = CUtil::randomName();
        char size = CStudent::calcTotalSize(name.length());
        CUtil::write(data, size);
        CUtil::write(data, i);
        CUtil::write(data, CUtil::randomYear());
        CUtil::write(data, CUtil::randomMonth());
        CUtil::write(data, CUtil::randomSex());
        CUtil::write(data, name.c_str());
        //CViewUI::show(name);
    }
    maxStore = data - srcData; //��������ռ��ֵ
    m_store.open(CStore::WRITE_MODE);
    m_store.write(srcData, maxStore);
    m_store.close();
    CViewUI::show("�����������\r\n");
    CViewUI::pause();
    return srcData;
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
            case 1:
            {
                addControl();
                CViewUI::pause();
                break;
            }
            case 2:
            {
                deleteControl();
                CViewUI::pause();
                break;
            }
            case 3:
            {
                updateControl();
                CViewUI::pause();
                break;
            }
            case 4:
            {
                queryIdControl();
                CViewUI::pause();
                break;
            }
            case 5:
            {
                queryNameControl();
                CViewUI::pause();
                break;
            }
            case 6:
            {
                return;
            }
            default:
            {
                CViewUI::show("�Բ���,��������\r\n");
                CViewUI::pause();
                break;
            }   
        }
    }
}

void CManger::addControl()
{
    CViewUI::show("�������Ӧ����ӵ���Ϣ\r\n");
    CMyString name = inputNameView();
    char sex = inputSexView();
    short year = inputYearView();
    char month = inputMonthView();
    CStudent *pStu = new CStudent(name,sex,year,month);
    if (addStudent(pStu))
    {
        CViewUI::show("��ӳɹ�\r\n");
    }
    else
    {
        CViewUI::show("���ʧ��\r\n");
    }
}

void CManger::deleteControl()
{
    int id = inputIdView();
    AVLTree<CElem, TreeCompare<CElem>>::Iterator it;
    try
    {
        it = queryById(id);
        CViewUI::show("ѧ����Ϣ����:\r\n");
        showStudent((*it).getStudent());
    }
    catch (CMyNotFindException e)
    {
        CViewUI::show("�Բ���,���Ҳ�����ID��Ϣ\r\n");
        return;
    }

    if (!inputConfirmView()) //ȷ����ϢΪn
    {
        CViewUI::show("ȷ����Ϣʧ��\r\n");
        return;
    }

    if (deleteStudent(it))
    {
        CViewUI::show("ɾ���ɹ�\r\n");
    }
    else
    {
        CViewUI::show("ɾ��ʧ��\r\n");
    }
}

void CManger::updateControl()
{
    int id = inputIdView();
    AVLTree<CElem, TreeCompare<CElem>>::Iterator it;
    try
    {
        it = queryById(id);
        CViewUI::show("ѧ����Ϣ����:\r\n");
        showStudent((*it).getStudent());
    }
    catch (CMyNotFindException e)
    {
        CViewUI::show("�Բ���,���Ҳ�����ID��Ϣ\r\n");
        return;
    }

    CViewUI::show("---------------------------\r\n");
    CViewUI::show("Ĭ�ϻس���ʾ�����¸�������Ϣ\r\n");
    CViewUI::show("---------------------------\r\n");
    CElem elem = *it;
    bool needUpdate = false;
    //�޸�����
    try
    {
        CMyString name = inputNameView(true);
        if(updateName(elem,name))
            needUpdate = true;
    }
    catch (CMyInputException e)
    {
        CViewUI::show("����������\r\n");
    }
    //�޸��Ա�
    try
    {
        char sex = inputSexView(true);
        if (elem.getStudent()->getSex() != sex)
        {
            elem.getStudent()->setSex(sex);
            needUpdate = true;
        }
    }
    catch (CMyInputException e)
    {
        CViewUI::show("�Ա𲻸���\r\n");
    }
    //�޸����
    try
    {
        short year = inputYearView(true);
        if (elem.getStudent()->getYear() != year)
        {
            elem.getStudent()->setYear(year);
            needUpdate = true;
        }
    }
    catch (CMyInputException e)
    {
        CViewUI::show("��ݲ�����\r\n");
    }
    //�޸��·�
    try
    {
        char month = inputMonthView(true);
        if (elem.getStudent()->getMonth() != month)
        {
            elem.getStudent()->setMonth(month);
            needUpdate = true;
        }
    }
    catch (CMyInputException e)
    {
        CViewUI::show("�·ݲ�����\r\n");
    }

    CViewUI::show("---------------------------\r\n");

    if (needUpdate)
    {
        addInStore(elem);
        CViewUI::show("���ݸ��³ɹ�\r\n");
    }
    else
    {
        CViewUI::show("ľ�����������\r\n");
    }
}

void CManger::queryIdControl()
{
    int id = inputIdView();
    try
    {
        AVLTree<CElem, TreeCompare<CElem>>::Iterator it = 
                                                queryById(id);
        CViewUI::show("ѧ����Ϣ����:\r\n");
        showStudent((*it).getStudent());
    }
    catch (CMyNotFindException e)
    {
        CViewUI::show("�Բ���,���Ҳ�����ID��Ϣ\r\n");
    }
    
}

void CManger::queryNameControl()
{
    CMyString name = inputNameView();
    queryByName(name);
}

int CManger::inputIdView()
{
    int choose = 0;
    do
    {
        CViewUI::show("������ID:");
        choose = CViewUI::input<int>();
        if (choose <= 0)
        {
            CViewUI::show("�Բ���,����������ID\r\n");
            choose = 0;
        }
    }while(!choose);
    
    return choose;
}

CMyString CManger::inputNameView(bool ignore)
{
    char *name = new char[CConfig::MaxNameLen];
    while (true)
    {
        CViewUI::show("����������(��Χ[4,9]):");
        CViewUI::input(name, CConfig::MaxNameLen);

        int len = strlen(name);
        if (ignore && !len) //�ɺ���
        {
            delete[] name; //�ͷ��ڴ�
            throw CMyInputException("�������뱻����");
        }
            
        if (len < 4)
        {
            CViewUI::show("�Բ���,������������4�ֽ�\r\n");
            continue;
        }
        break;
    }

    CMyString ret(name);
    delete[] name;
    return ret;
}

char CManger::inputSexView(bool ignore)
{
    const int sexLimit = 2;
    char sex[sexLimit];
    while (true)
    {
        CViewUI::show("�������Ա�([0:��],[1:Ů],[2:δ֪]):");
        CViewUI::input(sex, sexLimit);

        int len = strlen(sex);
        if (ignore && !len) //�ɺ���
        {
            throw CMyInputException("�Ա����뱻����");
        }

        if (sex[0] >= '0' && sex[0] <= '2')
        {
            break;
        }
        CViewUI::show("�Բ���,������ 0 ���� 1 ���� 2\r\n");
    }
    return (sex[0]-'0');
}

short CManger::inputYearView(bool ignore)
{
    const int yearLimit = 5;
    char year[yearLimit];
    while (true)
    {
        CViewUI::show("���������(��Χ[1970,2019]):");
        CViewUI::input(year, yearLimit);

        int len = strlen(year);
        if (ignore && !len) //�ɺ���
        {
            throw CMyInputException("������뱻����");
        }

        int nYear = CUtil::strToInt(year);
        if (nYear >= CConfig::MinYear && nYear <= CConfig::MaxYear)
        {
            return (short)nYear;
        }
        CViewUI::show("�Բ���,������ķ�Χ��1970-2019֮��\r\n");
    }
}

char CManger::inputMonthView(bool ignore)
{
    const int monthLimit = 3;
    char month[monthLimit];
    while (true)
    {
        CViewUI::show("�������·�(��Χ[1,12]):");
        CViewUI::input(month, monthLimit);

        int len = strlen(month);
        if (ignore && !len) //�ɺ���
        {
            throw CMyInputException("�·����뱻����");
        }

        int nMonth = CUtil::strToInt(month);
        if (nMonth >= CConfig::MinMonth && nMonth <= CConfig::MaxMonth)
        {
            return (char)nMonth;
        }
        CViewUI::show("�Բ���,������ķ�Χ��1-12֮��\r\n");
    }
}

bool CManger::inputConfirmView()
{
    char info = 0;
    while (true)
    {
        CViewUI::show("��ȷ����Ϣ:(y or n):");
        info = CViewUI::input<char>();
        if (info == 'y' || info == 'n')
        {
            break;
        }
        CViewUI::show("�Բ���,������y����n\r\n");
    }
    return ((info == 'y') ? true : false);
}

bool CManger::addStudent(CStudent * pStu)
{
    int size = pStu->getTotalSize(); //��ȡռ�õĿռ�
    CPostion *pPos = new CPostion;
    try
    {
        *pPos = getStuPostion(size);
    }
    catch (CMyNotFindException e)
    { //˵��û�ҵ�,��Ҫ��ӵ��ļ�ĩβ
        int dataEndPos = m_store.getFileSize();
        *pPos = CPostion(dataEndPos,size);
    }
    CElem elem(pStu, pPos);
    //���µ��ļ�
    addInStore(elem);
    //�����ڴ�����
    m_TreeById.insert_equal(elem); //id���в���
    m_HashByName.insert(elem); //�������в���
    return true;
}

bool CManger::addInStore(const CElem & elem)
{
    CPostion *pPos = elem.getPostion();
    CStudent *pStu = elem.getStudent();

    //��������,׼��д���ļ�
    int totalSize = pPos->getSize() + 1;
    char *data = new char[totalSize];
    char *srcData = data;
    CUtil::write(data, (char)(totalSize - 1));
    CUtil::write(data, pStu, CStudent::BASE_SIZE);
    CUtil::write(data, pStu->getName().c_str());
    //д���ļ�
    m_store.open(CStore::READ_WRITE_MODE);
    m_store.seek(pPos->getPos()); //����λ��
    m_store.write(srcData, totalSize);
    m_store.close();

    return true;
}

CPostion CManger::getStuPostion(int size)
{
    CPostion pos(size);
    int times = 1;
    while (times <= CConfig::PosFindTimes) //������n��
    {
        HashTable<CPostion, Hash<CPostion>>::Iterator it = 
            m_HashByPos[pos];
        if (!it.isEnd())
        { //�ҵ����ݣ��õ�һ������
            pos = *it;
            m_HashByPos.remove(it); //��λ�ñ����Ƴ�
            return pos;
        }
        ++pos; //�Ҳ���,����һ��
        if(pos.getSize() >= CConfig::DelTableSize)
            break;
        ++times;
    }
    //δ�ҵ�,�׳��쳣
    throw CMyNotFindException("δ�ҵ�����λ��");
}

bool CManger::deleteStudent(AVLTree<CElem, TreeCompare<CElem>>::Iterator treeIt)
{
    if(treeIt.isEnd()) //��������Ч
        return false;

    CElem elem = *treeIt;
    m_TreeById.remove(treeIt); //Id����ɾ��
    deleteInHashName(elem); //��������ɾ��
    //��ӵ�λ�ñ���
    m_HashByPos.insert(*elem.getPostion());
    //�����ļ���Ϣ
    deleteInStore(elem.getPostion()->getPos());

    return true;
}

bool CManger::deleteInHashName(const CElem & elem)
{
    //����������
    HashTable<CElem, Hash<CElem>>::Iterator hashIt =
        m_HashByName[elem];
    while (!hashIt.isEnd())
    {
        // �Ƚ�ID�Ƿ�һ��
        if ((*hashIt).getStudent()->getId() == 
                            elem.getStudent()->getId())
        {
            m_HashByName.remove(hashIt);
            break;
        }
        ++hashIt;
    }
    return true;
}

bool CManger::deleteInStore(int pos)
{
    m_store.open(CStore::READ_WRITE_MODE);
    m_store.seek(pos + 1); //ƫ�Ƶ�Idλ��
    m_store.write(&CConfig::IDDelFlag, sizeof(CConfig::IDDelFlag)); //�޸�ID��־
    m_store.close();
    return true;
}

bool CManger::updateName(const CElem & elem, const CMyString & name)
{
    if (name == elem.getStudent()->getName())
    {
        return false;
    }

    int size = CStudent::calcTotalSize(name.length());

    if (size > elem.getPostion()->getSize())
    { //ԭ��λ�ò�����,��Ҫ����λ��
        CPostion pPos;
        try
        {
            pPos = getStuPostion(size);
        }
        catch (CMyNotFindException e)
        { //˵��û�ҵ�,��Ҫ��ӵ��ļ�ĩβ
            int dataEndPos = m_store.getFileSize();
            pPos = CPostion(dataEndPos, size);
        }
        //���ļ��е���Ϣ���ɾ��
        deleteInStore(elem.getPostion()->getPos());
        //���Լ����������ӵ�λ�ñ���
        m_HashByPos.insert(*elem.getPostion());
        //�����Լ����ڴ�λ����Ϣ
        CUtil::write(elem.getPostion(), &pPos, sizeof(CPostion));
    }

    //��ɾ���������е���Ϣ
    deleteInHashName(elem);
    //��������
    elem.getStudent()->setName(name);
    //������ӽ�������
    m_HashByName.insert(elem);
    return true;
}

AVLTree<CElem, TreeCompare<CElem>>::Iterator CManger::queryById(int id)
{
    AVLTree<CElem, TreeCompare<CElem>>::Iterator it =
        m_TreeById.find(CElem(id));

    while (!it.isEnd())
    {
        // �Ƚ�ID�Ƿ�һ��
        if ((*it).getStudent()->getId() == id)
        {
            return it; //���ؽ��
        }
        ++it;
    }

    throw CMyNotFindException("�����޽��");
}

void CManger::queryByName(CMyString & name)
{
    CElem elem(name);
    HashTable<CElem, Hash<CElem>>::Iterator it = 
        m_HashByName[elem];
    bool findFlag = false; //���ҽ��
    while (!it.isEnd())
    {
        // �Ƚ������Ƿ�һ��
        if ((*it).getStudent()->getName() == name)
        {
            if (!findFlag)
            {
                CViewUI::show("ѧ����Ϣ����:\r\n");
            }
            showStudent((*it).getStudent());
            findFlag = true;
            CViewUI::show("------------------\r\n");
        }
        ++it;
    }
    if (!findFlag)
    {
        CViewUI::show("�Բ���,���޸�������ѧ��\r\n");
    }
}

void CManger::showStudent(CStudent * pStu)
{
    CViewUI::show("ID:%d\r\n",pStu->getId());
    CViewUI::show("����:");
    CViewUI::show(pStu->getName());
    CViewUI::newLine();
    CViewUI::show("�Ա�:");
    switch (pStu->getSex())
    {
        case 0:
        {
            CViewUI::show("��\r\n");
            break;
        }
        case 1:
        {
            CViewUI::show("Ů\r\n");
            break;
        }
        default:
        {
            CViewUI::show("δ֪\r\n");
            break;
        }
    }
    CViewUI::show("��������:%d��%d��\r\n",pStu->getYear(),pStu->getMonth());
}
