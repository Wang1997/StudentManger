#include "Manger.h"
#include "ViewUI.h"
#include "Config.h"
#include "Util.h"
#include <ctime>

CManger::CManger() :m_HashByName(CConfig::NameTableSize),
        m_HashByPos(CConfig::DelTableSize),
        m_store(CMyString(CConfig::FilePath))
{
    srand(time(NULL)); //srand只能一次
}


CManger::~CManger()
{
    CViewUI::clearScreen();
    CViewUI::show("正在退出,请稍后...\r\n");
}

void CManger::start()
{
    char *data = nullptr;
    int maxStore = 0;
    if (!m_store.getFileSize())
    { //初始化数据
        data = initData(maxStore);
    }
    loadData(data,maxStore);
    menuControl();
}

void CManger::loadData(char * data, int maxStore)
{
    CViewUI::clearScreen();
    CViewUI::show("开始加载数据,请稍后...\r\n");

    if (data == nullptr) //为空时从文件加载数据
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
        if (id == CConfig::IDDelFlag) //删除的数据
        {
            m_HashByPos.insert(CPostion(pos, size));
        }
        else
        {
            CPostion *pPos = new CPostion(pos, size); //创建位置对象
            CMyString name(data + CStudent::BASE_SIZE); //先读取姓名
            CStudent *pStu = new CStudent(name);
            CUtil::read(pStu, data, CStudent::BASE_SIZE); //拷贝基本数据
            CElem elem(pStu,pPos);
            m_TreeById.insert_equal(elem); //id树中插入
            m_HashByName.insert(elem); //姓名表中插入
        }
        maxId = MAX(maxId,id);
        pos += 1 + size;
        data += size;
    }
    CViewUI::show("数据加载成功\r\n");
    CStudent::initMaxId(maxId+1);
    delete[] srcData;
    CViewUI::pause();
}

char* CManger::initData(int& maxStore)
{
    CViewUI::clearScreen();
    CViewUI::show("开始生成数据,请稍后...\r\n");
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
    maxStore = data - srcData; //修正真正占用值
    m_store.open(CStore::WRITE_MODE);
    m_store.write(srcData, maxStore);
    m_store.close();
    CViewUI::show("数据生成完毕\r\n");
    CViewUI::pause();
    return srcData;
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
                CViewUI::show("对不起,输入有误\r\n");
                CViewUI::pause();
                break;
            }   
        }
    }
}

void CManger::addControl()
{
    CViewUI::show("请输入对应需添加的信息\r\n");
    CMyString name = inputNameView();
    char sex = inputSexView();
    short year = inputYearView();
    char month = inputMonthView();
    CStudent *pStu = new CStudent(name,sex,year,month);
    if (addStudent(pStu))
    {
        CViewUI::show("添加成功\r\n");
    }
    else
    {
        CViewUI::show("添加失败\r\n");
    }
}

void CManger::deleteControl()
{
    int id = inputIdView();
    AVLTree<CElem, TreeCompare<CElem>>::Iterator it;
    try
    {
        it = queryById(id);
        CViewUI::show("学生信息如下:\r\n");
        showStudent((*it).getStudent());
    }
    catch (CMyNotFindException e)
    {
        CViewUI::show("对不起,查找不到该ID信息\r\n");
        return;
    }

    if (!inputConfirmView()) //确认信息为n
    {
        CViewUI::show("确认信息失败\r\n");
        return;
    }

    if (deleteStudent(it))
    {
        CViewUI::show("删除成功\r\n");
    }
    else
    {
        CViewUI::show("删除失败\r\n");
    }
}

void CManger::updateControl()
{
    int id = inputIdView();
    AVLTree<CElem, TreeCompare<CElem>>::Iterator it;
    try
    {
        it = queryById(id);
        CViewUI::show("学生信息如下:\r\n");
        showStudent((*it).getStudent());
    }
    catch (CMyNotFindException e)
    {
        CViewUI::show("对不起,查找不到该ID信息\r\n");
        return;
    }

    CViewUI::show("---------------------------\r\n");
    CViewUI::show("默认回车表示不更新该数据信息\r\n");
    CViewUI::show("---------------------------\r\n");
    CElem elem = *it;
    bool needUpdate = false;
    //修改姓名
    try
    {
        CMyString name = inputNameView(true);
        if(updateName(elem,name))
            needUpdate = true;
    }
    catch (CMyInputException e)
    {
        CViewUI::show("姓名不更新\r\n");
    }
    //修改性别
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
        CViewUI::show("性别不更新\r\n");
    }
    //修改年份
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
        CViewUI::show("年份不更新\r\n");
    }
    //修改月份
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
        CViewUI::show("月份不更新\r\n");
    }

    CViewUI::show("---------------------------\r\n");

    if (needUpdate)
    {
        addInStore(elem);
        CViewUI::show("数据更新成功\r\n");
    }
    else
    {
        CViewUI::show("木有数据需更新\r\n");
    }
}

void CManger::queryIdControl()
{
    int id = inputIdView();
    try
    {
        AVLTree<CElem, TreeCompare<CElem>>::Iterator it = 
                                                queryById(id);
        CViewUI::show("学生信息如下:\r\n");
        showStudent((*it).getStudent());
    }
    catch (CMyNotFindException e)
    {
        CViewUI::show("对不起,查找不到该ID信息\r\n");
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
        CViewUI::show("请输入ID:");
        choose = CViewUI::input<int>();
        if (choose <= 0)
        {
            CViewUI::show("对不起,请输入合理的ID\r\n");
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
        CViewUI::show("请输入姓名(范围[4,9]):");
        CViewUI::input(name, CConfig::MaxNameLen);

        int len = strlen(name);
        if (ignore && !len) //可忽略
        {
            delete[] name; //释放内存
            throw CMyInputException("姓名输入被忽略");
        }
            
        if (len < 4)
        {
            CViewUI::show("对不起,姓名最少输入4字节\r\n");
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
        CViewUI::show("请输入性别([0:男],[1:女],[2:未知]):");
        CViewUI::input(sex, sexLimit);

        int len = strlen(sex);
        if (ignore && !len) //可忽略
        {
            throw CMyInputException("性别输入被忽略");
        }

        if (sex[0] >= '0' && sex[0] <= '2')
        {
            break;
        }
        CViewUI::show("对不起,请输入 0 或者 1 或者 2\r\n");
    }
    return (sex[0]-'0');
}

short CManger::inputYearView(bool ignore)
{
    const int yearLimit = 5;
    char year[yearLimit];
    while (true)
    {
        CViewUI::show("请输入年份(范围[1970,2019]):");
        CViewUI::input(year, yearLimit);

        int len = strlen(year);
        if (ignore && !len) //可忽略
        {
            throw CMyInputException("年份输入被忽略");
        }

        int nYear = CUtil::strToInt(year);
        if (nYear >= CConfig::MinYear && nYear <= CConfig::MaxYear)
        {
            return (short)nYear;
        }
        CViewUI::show("对不起,请输入的范围在1970-2019之间\r\n");
    }
}

char CManger::inputMonthView(bool ignore)
{
    const int monthLimit = 3;
    char month[monthLimit];
    while (true)
    {
        CViewUI::show("请输入月份(范围[1,12]):");
        CViewUI::input(month, monthLimit);

        int len = strlen(month);
        if (ignore && !len) //可忽略
        {
            throw CMyInputException("月份输入被忽略");
        }

        int nMonth = CUtil::strToInt(month);
        if (nMonth >= CConfig::MinMonth && nMonth <= CConfig::MaxMonth)
        {
            return (char)nMonth;
        }
        CViewUI::show("对不起,请输入的范围在1-12之间\r\n");
    }
}

bool CManger::inputConfirmView()
{
    char info = 0;
    while (true)
    {
        CViewUI::show("请确认信息:(y or n):");
        info = CViewUI::input<char>();
        if (info == 'y' || info == 'n')
        {
            break;
        }
        CViewUI::show("对不起,请输入y或者n\r\n");
    }
    return ((info == 'y') ? true : false);
}

bool CManger::addStudent(CStudent * pStu)
{
    int size = pStu->getTotalSize(); //获取占用的空间
    CPostion *pPos = new CPostion;
    try
    {
        *pPos = getStuPostion(size);
    }
    catch (CMyNotFindException e)
    { //说明没找到,需要添加到文件末尾
        int dataEndPos = m_store.getFileSize();
        *pPos = CPostion(dataEndPos,size);
    }
    CElem elem(pStu, pPos);
    //更新到文件
    addInStore(elem);
    //插入内存数据
    m_TreeById.insert_equal(elem); //id树中插入
    m_HashByName.insert(elem); //姓名表中插入
    return true;
}

bool CManger::addInStore(const CElem & elem)
{
    CPostion *pPos = elem.getPostion();
    CStudent *pStu = elem.getStudent();

    //设置数据,准备写入文件
    int totalSize = pPos->getSize() + 1;
    char *data = new char[totalSize];
    char *srcData = data;
    CUtil::write(data, (char)(totalSize - 1));
    CUtil::write(data, pStu, CStudent::BASE_SIZE);
    CUtil::write(data, pStu->getName().c_str());
    //写入文件
    m_store.open(CStore::READ_WRITE_MODE);
    m_store.seek(pPos->getPos()); //设置位置
    m_store.write(srcData, totalSize);
    m_store.close();

    return true;
}

CPostion CManger::getStuPostion(int size)
{
    CPostion pos(size);
    int times = 1;
    while (times <= CConfig::PosFindTimes) //往后找n次
    {
        HashTable<CPostion, Hash<CPostion>>::Iterator it = 
            m_HashByPos[pos];
        if (!it.isEnd())
        { //找到数据，拿第一个即可
            pos = *it;
            m_HashByPos.remove(it); //从位置表中移除
            return pos;
        }
        ++pos; //找不到,找下一个
        if(pos.getSize() >= CConfig::DelTableSize)
            break;
        ++times;
    }
    //未找到,抛出异常
    throw CMyNotFindException("未找到合适位置");
}

bool CManger::deleteStudent(AVLTree<CElem, TreeCompare<CElem>>::Iterator treeIt)
{
    if(treeIt.isEnd()) //迭代器无效
        return false;

    CElem elem = *treeIt;
    m_TreeById.remove(treeIt); //Id树中删除
    deleteInHashName(elem); //姓名表中删除
    //添加到位置表中
    m_HashByPos.insert(*elem.getPostion());
    //更新文件信息
    deleteInStore(elem.getPostion()->getPos());

    return true;
}

bool CManger::deleteInHashName(const CElem & elem)
{
    //查找姓名表
    HashTable<CElem, Hash<CElem>>::Iterator hashIt =
        m_HashByName[elem];
    while (!hashIt.isEnd())
    {
        // 比较ID是否一样
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
    m_store.seek(pos + 1); //偏移到Id位置
    m_store.write(&CConfig::IDDelFlag, sizeof(CConfig::IDDelFlag)); //修改ID标志
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
    { //原先位置不够大,需要更换位置
        CPostion pPos;
        try
        {
            pPos = getStuPostion(size);
        }
        catch (CMyNotFindException e)
        { //说明没找到,需要添加到文件末尾
            int dataEndPos = m_store.getFileSize();
            pPos = CPostion(dataEndPos, size);
        }
        //将文件中的信息标记删除
        deleteInStore(elem.getPostion()->getPos());
        //将自己这块数据添加到位置表中
        m_HashByPos.insert(*elem.getPostion());
        //更新自己的内存位置信息
        CUtil::write(elem.getPostion(), &pPos, sizeof(CPostion));
    }

    //先删除姓名表中的信息
    deleteInHashName(elem);
    //更新姓名
    elem.getStudent()->setName(name);
    //重新添加进姓名表
    m_HashByName.insert(elem);
    return true;
}

AVLTree<CElem, TreeCompare<CElem>>::Iterator CManger::queryById(int id)
{
    AVLTree<CElem, TreeCompare<CElem>>::Iterator it =
        m_TreeById.find(CElem(id));

    while (!it.isEnd())
    {
        // 比较ID是否一样
        if ((*it).getStudent()->getId() == id)
        {
            return it; //返回结果
        }
        ++it;
    }

    throw CMyNotFindException("查找无结果");
}

void CManger::queryByName(CMyString & name)
{
    CElem elem(name);
    HashTable<CElem, Hash<CElem>>::Iterator it = 
        m_HashByName[elem];
    bool findFlag = false; //查找结果
    while (!it.isEnd())
    {
        // 比较姓名是否一样
        if ((*it).getStudent()->getName() == name)
        {
            if (!findFlag)
            {
                CViewUI::show("学生信息如下:\r\n");
            }
            showStudent((*it).getStudent());
            findFlag = true;
            CViewUI::show("------------------\r\n");
        }
        ++it;
    }
    if (!findFlag)
    {
        CViewUI::show("对不起,暂无该姓名的学生\r\n");
    }
}

void CManger::showStudent(CStudent * pStu)
{
    CViewUI::show("ID:%d\r\n",pStu->getId());
    CViewUI::show("姓名:");
    CViewUI::show(pStu->getName());
    CViewUI::newLine();
    CViewUI::show("性别:");
    switch (pStu->getSex())
    {
        case 0:
        {
            CViewUI::show("男\r\n");
            break;
        }
        case 1:
        {
            CViewUI::show("女\r\n");
            break;
        }
        default:
        {
            CViewUI::show("未知\r\n");
            break;
        }
    }
    CViewUI::show("出生年月:%d年%d月\r\n",pStu->getYear(),pStu->getMonth());
}
