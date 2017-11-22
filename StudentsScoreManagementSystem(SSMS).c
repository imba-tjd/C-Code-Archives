/* 假设某班有不超过40人（具体人数在程序运行时由键盘录入）参加本学期的期末考试，考试科目为语文（CN），数学（MT），英语（EN），科学（SC）。
要求编写一个学生成绩管理系统，实现对班级学生成绩的录入、修改、查找、删除、显示、排序、统计、保存等操作的管理。
*/

/* TODO
in StringToMiddleString：一个汉字的长度也算1（sizeof(WCHAR) == 2）
LoadDB：fwscanf第一次不为7？
Data.db用utf8保存
Compare：wcscmp无法做到按照姓名字典顺序排序，strcmp可以.
修改和删除的默认值也许应该为N
scanf %s 读到EOF不返回EOF
每次保存数据库时前进行备份
链表的耦合性太高（不过懒得改了）
*/

#include <conio.h>  // getch()
#include <io.h>     // access函数判断文件是否存在
#include <locale.h> // utf8转gbk输出
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // 显示日期
#include <wchar.h>   // 宽字符结构体及函数
#include <windows.h> // cls清屏

// 数据结构声明
typedef struct
{
    int studentNumber; // 学号
    wchar_t name[9];   // 名字
    int sex;           // 性别，0为男，1为女

    int CN; // 语文
    int MT; // 数学
    int EN; // 英语
    int SC; // 科学
} Student;  // 学生

typedef struct SNode
{
    Student data;
    struct SNode *next;
} SNode;

typedef struct
{
    int year;
    int month;
    int day;
    wchar_t *week;
} Date; // 日期

static Date Today;  // 今天的日期
static int Count;   // 学生数量，save时重新计算
static SNode *Head; // 头结点

// 函数声明
int MainMenu(void);         // 显示主菜单
void ShowAuthor(void);      // 显示作者信息
void ShowMenuHead(void);    // 显示菜单头
void EditMenu(void);        // 编辑学生信息的菜单
void QueryMenu(void);       // 排序、输出学生信息的菜单
void PrintSingleMenu(void); // 输出单个学生信息的菜单
void PrintMultiMenu(void);  // 输出多个学生信息的菜单
void PrintCourseMenu(void); // 输出各科学生分数段的菜单

void SaveDB(void);                               // 保存数据库
void LoadDB(void);                               // 加载数据库
Date SetToday(void);                             // 设定日期和星期
void ClearInput(void);                           // 清除用户输入的多余信息
SNode *CreateStudentList(void);                  // 创建链表头结点
bool InsertList(SNode *const head, Student stu); // 将结点插入链表
void ErrorAndExit(void);                         // 发生错误，程序退出
void PressToContinue(void);                      // 提示用户按任意键返回

void Add(void);    // 添加学生的信息
void Delete(void); // 删除学生的信息
void Change(void); // 修改学生成绩

void PrintSingle(int cases); // 输出单个学生信息
void PrintMulti(int cases);  // 输出多个学生信息
void PrintCourse(void);      // 输出各学科分数段信息

wchar_t *StudentToString(Student *stu);                           // 返回学生信息字符串
void PrintStudents(Student **stu);                                // 真·输出学生信息（受PrintSingle和PrintMulti调用）
int AllScore(Student *s);                                         // 返回课程总分
int AverageScore(Student *s);                                     // 返回课程平均分
wchar_t *StringToMiddleString(wchar_t originString[], int width); // 返回居中的字符串
wchar_t *IntToMiddleString(int num, int width);                   // 返回居中的数字字符串
int Compare(Student *s1, Student *s2, int cases);                 // 根据指定条目对两个学生进行比较
int JudgeSegment(int score);                                      // 判断成绩处于哪个分数段

int GetStudentNumber(void);                             // 从用户获取学号
bool CreateStudent(Student *stu);                       // 从用户获取学生信息
Student *GetSutdentByStudentNumber(int stuNum);         // 根据学号寻找学生
Student **GetSutdentByStudentName(const wchar_t *name); // 根据姓名寻找学生

int main(void)
{
    setlocale(LC_ALL, "chs");
    Today = SetToday();
    LoadDB();
    return MainMenu();
}

void ShowMenuHead(void)
{
    system("cls");
    wprintf(L"****************************************************\n");
    wprintf(L"    学生成绩管理系统\n");
    wprintf(L"    今天的日期是： %d 年 %d 月 %d 日，星期%s。\n", Today.year, Today.month, Today.day, Today.week);
    wprintf(L"    数据库中共有 %d 人\n", Count);
    putchar('\n');
}

void ShowAuthor(void)
{
    ShowMenuHead();

    wprintf(L"    作者：Imba-TJD：\n");
    wprintf(L"    创建时间：2017/9/22：\n");
    wprintf(L"    完成时间：2017/11/27：\n");
    PressToContinue();
}

int MainMenu(void)
{
    while (true)
    {
        ShowMenuHead();

        wprintf(L"    请选择你要的功能：\n");
        wprintf(L"    1 ： 添加、修改或删除学生成绩信息\n"
                "    2 ： 查询学生信息\n"
                "    3 ： 显示作者信息\n"
                "    4 ： 退出程序\n");

        switch (getch())
        {
        case '1':
            EditMenu();
            continue;
        case '2':
            QueryMenu();
            continue;
        case '3':
            ShowAuthor();
            continue;
        case '4':
            return 0;
        }
    }
}

void EditMenu(void)
{
    while (true)
    {
        ShowMenuHead();

        wprintf(L"    请选择你要的功能：\n");
        wprintf(L"    1 ： 添加学生信息\n"
                "    2 ： 修改学生信息\n"
                "    3 ： 删除学生信息\n"
                "    4 ： 返回主菜单\n");

        switch (getch())
        {
        case '1':
            Add();
            SaveDB();
            continue;
        case '2':
            Change();
            SaveDB();
            continue;
        case '3':
            Delete();
            SaveDB();
            continue;
        case '4':
            return;
        }
    }
}

void QueryMenu(void)
{
    while (true)
    {
        ShowMenuHead();

        wprintf(L"    请选择你要的功能：\n");
        wprintf(L"    1 ： 输出单个学生信息\n"
                "    2 ： 输出所有学生的信息\n"
                "    3 ： 输出各科分数段信息\n"
                "    4 ： 返回主菜单\n");

        switch (getch())
        {
        case '1':
            PrintSingleMenu();
            continue;
        case '2':
            PrintMultiMenu();
            continue;
        case '3':
            PrintCourseMenu();
            continue;
        case '4':
            return;
        }
    }
}

void PrintSingleMenu(void)
{
    while (true)
    {
        ShowMenuHead();

        wprintf(L"    请选择你要的功能：\n");
        wprintf(L"    1 ： 按学号输出学生信息\n"
                "    2 ： 按姓名输出学生信息\n"
                "    3 ： 返回上一级\n");

        switch (getch())
        {
        case '1':
            PrintSingle(1);
            continue;
        case '2':
            PrintSingle(2);
            continue;
        case '3':
            return;
        }
    }
}

void PrintMultiMenu(void)
{
    while (true)
    {
        ShowMenuHead();

        wprintf(L"    请选择你要的功能：\n");
        wprintf(L"    1 ： 按学号输出学生信息\n"
                "    2 ： 按姓名字典顺序序输出学生信息\n"
                "    3 ： 按总分/平均分输出学生信息\n"
                "    4 ： 按语文成绩输出学生信息\n"
                "    5 ： 按数学成绩输出学生信息\n"
                "    6 ： 按英语成绩输出学生信息\n"
                "    7 ： 按科学成绩输出学生信息\n"
                "    8 ： 返回上一级\n");

        switch (getch())
        {
        case '1':
            PrintMulti(1);
            continue;
        case '2':
            PrintMulti(2);
            continue;
        case '3':
            PrintMulti(3);
            continue;
        case '4':
            PrintMulti(4);
            continue;
        case '5':
            PrintMulti(5);
            continue;
        case '6':
            PrintMulti(6);
            continue;
        case '7':
            PrintMulti(7);
            continue;
        case '8':
            return;
        }
    }
}

void PrintCourseMenu(void)
{
    PrintCourse();

    // while (true)
    // {
    // ShowMenuHead();

    // wprintf(L"    请选择你要的功能：\n");
    // wprintf(L"    1 ： 输出语文分数段信息\n"
    //         "    2 ： 输出数学分数段信息\n"
    //         "    3 ： 输出英语分数段信息\n"
    //         "    4 ： 输出科学分数段信息\n"
    //         "    5 ： 返回上一级\n");

    // switch (getch())
    // {
    // case '1':
    //     PrintCourse(1);
    //     continue;
    // case '2':
    //     PrintCourse(2);
    //     continue;
    // case '3':
    //     PrintCourse(3);
    //     continue;
    // case '4':
    //     PrintCourse(4);
    //     continue;
    // case '5':
    //     return;
    // }
}

// 数据功能性函数

void Add(void)
{
    Student stu;
    while (true)
    {
        if (CreateStudent(&stu) == false)
            return;

        if (InsertList(Head, stu) == false)
        {
            wprintf(L"    学号为%d的学生已经存在！\n", stu.studentNumber);
            PressToContinue();
            return;
        }

        while (true)
        {
            // ClearInput();
            wprintf(L"    还要输入下一个学生的信息吗？（Y/N）Y\b");
            switch (getchar())
            {
            case '\n':
                break;
            case 'Y':
                break;
            case 'y':
                break;
            case 'N':
                return;
            case 'n':
                return;
            default:
                wprintf(L"    不接受的选项。\n");
                ClearInput();
                continue;
            }
            break;
        }
    }
}

void Change(void)
{
    int stuNum;
    Student *originStu;
    Student stu;

    putchar('\n');
    if ((stuNum = GetStudentNumber()) == EOF)
        return;

    if ((originStu = GetSutdentByStudentNumber(stuNum)) == NULL)
        return;

    if (CreateStudent(&stu) == false)
        return;

    while (true)
    {
        // ClearInput();
        wprintf(L"    真的要修改原学号为%d的学生的信息吗？（Y/N）Y\b", stuNum);
        switch (getchar())
        {
        case '\n':
            *originStu = stu;
            break;
        case 'Y':
            *originStu = stu;
            break;
        case 'y':
            *originStu = stu;
            break;
        case 'N':
            break;
        case 'n':
            break;
        default:
            wprintf(L"    不接受的选项。\n");
            ClearInput();
            continue;
        }

        return;
    }

    *originStu = stu;
}

void Delete(void)
{
    int stuNum;
    SNode *p = Head;

    putchar('\n');
    if ((stuNum = GetStudentNumber()) == EOF)
        return;

    while (true)
    {
        if (p->next == NULL)
        {
            wprintf(L"    找不到指定学号的学生！\n");
            PressToContinue();
            return;
        }

        if (p->next->data.studentNumber == stuNum)
            break;

        p = p->next;
    }

    while (true)
    {
        // ClearInput();
        wprintf(L"    真的要删除学号为%d的学生的信息吗？（Y/N）Y\b", stuNum);
        switch (getchar())
        {
        case '\n':
            break;
        case 'Y':
            break;
        case 'y':
            break;
        case 'N':
            return;
        case 'n':
            return;
        default:
            wprintf(L"    不接受的选项。\n");
            ClearInput();
            continue;
        }

        // free(&p->next->data);
        p->next = p->next->next;
        return;
    }
}

bool CreateStudent(Student *stu)
{
    putchar('\n');
    wprintf(L"    取得学生信息，输入ctrl+Z退出：\n");

    if ((stu->studentNumber = GetStudentNumber()) == EOF)
        return false;

    while (true)
    {
        wprintf(L"    请输入学生姓名：");
        switch (wscanf(L"%s", stu->name))
        {
        case EOF: // 这个貌似不起作用
            return false;
        case 1:
            break;
        default:
            wprintf(L"    读取失败，请重新输入姓名！\n");
            ClearInput();
            continue;
        }

        break;
    }

    while (true)
    {
        wprintf(L"    请输入学生性别（男：0，女：1）：");
        switch (scanf("%d", &stu->sex))
        {
        case EOF:
            return false;
        case 1:
            break;
        default:
            wprintf(L"    请输入数字！\n");
            ClearInput();
            continue;
        }

        if (stu->sex != 0 && stu->sex != 1)
        {
            wprintf(L"    性别只能是男或女！\n");
            ClearInput();
            continue;
        }

        break;
    }

    while (true)
    {
        wprintf(L"    请输入语文成绩：");
        switch (scanf("%d", &stu->CN))
        {
        case EOF:
            return false;
        case 1:
            break;
        default:
            wprintf(L"    请输入数字！\n");
            ClearInput();
            continue;
        }

        if (stu->CN < 0 || stu->CN > 100)
        {
            wprintf(L"    分数不能小于0或超过100！\n");
            ClearInput();
            continue;
        }

        break;
    }

    while (true)
    {
        wprintf(L"    请输入数学成绩：");
        switch (scanf("%d", &stu->MT))
        {
        case EOF:
            return false;
        case 1:
            break;
        default:
            wprintf(L"    请输入数字！\n");
            ClearInput();
            continue;
        }

        if (stu->MT < 0 || stu->MT > 100)
        {
            wprintf(L"    分数不能小于0或超过100！\n");
            ClearInput();
            continue;
        }

        break;
    }

    while (true)
    {
        wprintf(L"    请输入英语成绩：");
        switch (scanf("%d", &stu->EN))
        {
        case EOF:
            return false;
        case 1:
            break;
        default:
            wprintf(L"    请输入数字！\n");
            ClearInput();
            continue;
        }

        if (stu->EN < 0 || stu->EN > 100)
        {
            wprintf(L"    分数不能小于0或超过100！\n");
            ClearInput();
            continue;
        }

        break;
    }

    while (true)
    {
        wprintf(L"    请输入科学成绩：");
        switch (scanf("%d", &stu->SC))
        {
        case EOF:
            return false;
        case 1:
            break;
        default:
            wprintf(L"    请输入数字！\n");
            ClearInput();
            continue;
        }

        if (stu->SC < 0 || stu->SC > 100)
        {
            wprintf(L"    分数不能小于0或超过100！\n");
            ClearInput();
            continue;
        }

        break;
    }

    ClearInput();
    return true;
}

int GetStudentNumber(void)
{
    int stuNum;

    while (true)
    {
        wprintf(L"    请输入学生学号：");
        switch (scanf("%d", &stuNum))
        {
        case EOF:
            return EOF;
        case 1:
            break;
        default:
            wprintf(L"    请输入数字！\n");
            ClearInput();
            continue;
        }

        if (stuNum < 0)
        {
            wprintf(L"    学号不能为负！\n");
            ClearInput();
            continue;
        }

        ClearInput();
        return stuNum;
    }
}

Student *GetSutdentByStudentNumber(int stuNum)
{
    Student *stu = NULL;
    SNode *p = Head;

    while ((p = p->next) != NULL)
    {
        if (p->data.studentNumber == stuNum)
        {
            stu = &p->data;
            break;
        }
    }
    if (stu == NULL)
    {
        wprintf(L"    找不到指定学号的学生！\n");
        PressToContinue();
        return NULL;
    }
    return stu;
}

Student **GetSutdentByStudentName(const wchar_t *name)
{
    Student **stus = calloc(Count + 1, sizeof(Student *));
    SNode *p = Head;
    int position = 0;

    while ((p = p->next) != NULL)
    {
        if (wcscmp(p->data.name, name) == 0)
            stus[position++] = &p->data;
    }
    stus[position] = NULL;

    if (stus[0] == NULL)
    {
        // putchar('\n');
        wprintf(L"    找不到指定姓名的学生！\n");
        PressToContinue();
        return NULL;
    }

    return stus;
}

wchar_t *StudentToString(Student *stu)
{
    wchar_t *sstring = calloc(80, sizeof(wchar_t));

    wcscat(sstring, IntToMiddleString(stu->studentNumber, 8));
    wcscat(sstring, L"|");
    wcscat(sstring, StringToMiddleString(stu->name, 6));
    wcscat(sstring, L"|");
    wcscat(sstring, StringToMiddleString(stu->sex == 0 ? L"男" : L"女", 7));
    wcscat(sstring, L"|");
    wcscat(sstring, IntToMiddleString(stu->CN, 8));
    wcscat(sstring, L"|");
    wcscat(sstring, IntToMiddleString(stu->MT, 8));
    wcscat(sstring, L"|");
    wcscat(sstring, IntToMiddleString(stu->EN, 8));
    wcscat(sstring, L"|");
    wcscat(sstring, IntToMiddleString(stu->SC, 8));
    wcscat(sstring, L"|");
    wcscat(sstring, IntToMiddleString(AllScore(stu), 8));
    wcscat(sstring, L"|");
    wcscat(sstring, IntToMiddleString(AverageScore(stu), 10));

    return sstring;
}

inline int AllScore(Student *s)
{
    return s->CN + s->MT + s->EN + s->SC;
}

inline int AverageScore(Student *s)
{
    return (AllScore(s) / 4);
}

wchar_t *StringToMiddleString(wchar_t originString[], int width)
{
    wchar_t *mstring = calloc(width + 1, sizeof(wchar_t));
    int length = wcslen(originString);

    for (int i = 0; i < (width - length) / 2; i++)
        wcscat(mstring, L" ");
    wcscat(mstring, originString);
    for (int i = (width + length) / 2; i < width; i++)
        wcscat(mstring, L" ");

    return mstring;
}

wchar_t *IntToMiddleString(int num, int width)
{
    // int i;
    wchar_t tstring[4];

    wsprintfW(tstring, L"%d", num);
    // for (i = 0; num != 0; i++, num /= 10)
    // tstring[i] = num % 10 + '0'; // 这样会倒序
    // tstring[i] = '\0';

    return StringToMiddleString(tstring, width);
}

int Compare(Student *s1, Student *s2, int cases)
{
    switch (cases)
    {
    case 1:
        if (s1->studentNumber > s2->studentNumber)
            return 1;
        if (s1->studentNumber == s2->studentNumber)
            return 0;
        if (s1->studentNumber < s2->studentNumber)
            return -1;
    case 2:
        //return wcscmp(s1->name, s2->name);
        wprintf(L"此功能尚未实现！\n");
        ErrorAndExit();
    case 3:
        if (AllScore(s1) > AllScore(s2))
            return 1;
        if (AllScore(s1) == AllScore(s2))
            return 0;
        if (AllScore(s1) < AllScore(s2))
            return -1;
    case 4:
        if (s1->CN > s2->CN)
            return 1;
        if (s1->CN == s2->CN)
            return 0;
        if (s1->CN < s2->CN)
            return -1;
    case 5:
        if (s1->MT > s2->MT)
            return 1;
        if (s1->MT == s2->MT)
            return 0;
        if (s1->MT < s2->MT)
            return -1;
    case 6:
        if (s1->EN > s2->EN)
            return 1;
        if (s1->EN == s2->EN)
            return 0;
        if (s1->EN < s2->EN)
            return -1;
    case 7:
        if (s1->SC > s2->SC)
            return 1;
        if (s1->SC == s2->SC)
            return 0;
        if (s1->SC < s2->SC)
            return -1;
    }

    return 0; // control may reach end of non-void function
}

int JudgeSegment(int score)
{
    if (score > 100 || score < 0)
        return -1;
    else if (score >= 90)
        return 0; // 优秀
    else if (score >= 80)
        return 1; // 良
    else if (score >= 70)
        return 2; // 中
    else if (score >= 60)
        return 3; // 及格
    else
        return 4; // 不及格
}

// 输出函数

void PrintSingle(int cases)
{
    Student **stus = calloc(Count + 1, sizeof(Student *));
    int stuNum;
    wchar_t name[9];

    putchar('\n');
    switch (cases)
    {
    case 1:
        if ((stuNum = GetStudentNumber()) == EOF)
            return;
        if ((stus[0] = GetSutdentByStudentNumber(stuNum)) == NULL)
            return;

        stus[1] = NULL;
        break;
    case 2:
        wprintf(L"    请输入学生姓名：");
        wscanf(L"%s", name);
        ClearInput();

        if ((stus = GetSutdentByStudentName(name)) == NULL)
            return;
        break;
    }

    PrintStudents(stus);
}

void PrintMulti(int cases)
{
    Student **stus = calloc(Count + 1, sizeof(Student *)); // 指向所有学生的指针数组
    SNode *p = Head->next;

    for (int i = 0; i < Count; i++) // 把指向学生的指针赋值到指针数组里
    {
        stus[i] = &p->data;
        p = p->next;
    }

    if (cases != 1)
        for (int i = 0; i < Count - 1; i++)
            for (int j = i + 1; j < Count; j++)
                if (Compare(stus[i], stus[j], cases) < 0)
                {
                    Student *t = stus[i];
                    stus[i] = stus[j];
                    stus[j] = t;
                }
    stus[Count] = NULL;

    PrintStudents(stus);
}

void PrintCourse(void)
{
    int ALL[4] = {0}; // 分别表示四科的平均分
    int CNS[5] = {0}; // 分别表示语文的优秀、良、中、及格、不及格
    int MTS[5] = {0};
    int ENS[5] = {0};
    int SCS[5] = {0};

    for (SNode *p = Head->next; p != NULL; p = p->next)
    {
        ALL[0] += p->data.CN;
        ALL[1] += p->data.MT;
        ALL[2] += p->data.EN;
        ALL[3] += p->data.SC;

        CNS[JudgeSegment(p->data.CN)] += 1;
        MTS[JudgeSegment(p->data.MT)] += 1;
        ENS[JudgeSegment(p->data.EN)] += 1;
        SCS[JudgeSegment(p->data.SC)] += 1;
    }

    putchar('\n');
    wprintf(L"      学科  |  优秀  |   良   |   中   |  及格  | 不及格 |  平均分  \n");
    wprintf(L"      语文  | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) |  %3.0f  \n",
            CNS[0], 100.0 * CNS[0] / Count, CNS[1], 100.0 * CNS[1] / Count, CNS[2], 100.0 * CNS[2] / Count, CNS[3], 100.0 * CNS[3] / Count, CNS[4], 100.0 * CNS[4] / Count, 1.0 * ALL[0] / Count);
    wprintf(L"      数学  | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) |  %3.0f  \n",
            MTS[0], 100.0 * MTS[0] / Count, MTS[1], 100.0 * MTS[1] / Count, MTS[2], 100.0 * MTS[2] / Count, MTS[3], 100.0 * MTS[3] / Count, MTS[4], 100.0 * MTS[4] / Count, 1.0 * ALL[1] / Count);
    wprintf(L"      英语  | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) |  %3.0f  \n",
            ENS[0], 100.0 * ENS[0] / Count, ENS[1], 100.0 * ENS[1] / Count, ENS[2], 100.0 * ENS[2] / Count, ENS[3], 100.0 * ENS[3] / Count, ENS[4], 100.0 * ENS[4] / Count, 1.0 * ALL[2] / Count);
    wprintf(L"      科学  | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) | %d(%2.0f%%) |  %3.0f  \n",
            SCS[0], 100.0 * SCS[0] / Count, SCS[1], 100.0 * SCS[1] / Count, SCS[2], 100.0 * SCS[2] / Count, SCS[3], 100.0 * SCS[3] / Count, SCS[4], 100.0 * SCS[4] / Count, 1.0 * ALL[3] / Count);

    putchar('\n');
    PressToContinue();
}

void PrintStudents(Student **stus)
{
    putchar('\n');
    wprintf(L"      学号  |  姓名  |  性别  |  语文  |  数学  |  英语  |  科学  |  总分  |  平均分  \n");

    while (*stus != NULL)
        wprintf(L"    %s\n", StudentToString(*stus++));

    putchar('\n');
    PressToContinue();
}

// 程序功能性函数

void ClearInput(void)
{
    while (getchar() != '\n')
        ;
}

void SaveDB(void)
{
    FILE *file;
    SNode *p = Head;
    Count = 0;

    if ((file = fopen("Data.db", "w")) == NULL)
        ErrorAndExit();

    while ((p = p->next) != NULL)
    {
        Count++;
        fwprintf(file, L"%d %s %d %d %d %d %d\n",
                 p->data.studentNumber, p->data.name, p->data.sex, p->data.CN, p->data.MT, p->data.EN, p->data.SC);
    }
    fclose(file);
}

void LoadDB(void)
{
    Head = CreateStudentList();
    FILE *file;
    Student stu;

    if (access("Data.db", 0)) // 存在返回0，不存在返回-1
        return;

    if ((file = fopen("Data.db", "r")) == NULL)
        ErrorAndExit();

    // fseek(file, 0, 0);

    while (!feof(file))
    {
        if (fwscanf(file, L"%d %s %d %d %d %d %d",
                    &stu.studentNumber, stu.name, &stu.sex, &stu.CN, &stu.MT, &stu.EN, &stu.SC))
        {
            if (InsertList(Head, stu) == false)
                ErrorAndExit();

            Count++;
        }
    }
    fclose(file);
}

Date SetToday(void) // 设定今天的日期
{
    const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const wchar_t *CNWeeks[] = {L"天", L"一", L"二", L"三", L"四", L"五", L"六"};

    Date today;

    struct tm *lt;
    time_t tt;
    time(&tt);
    lt = localtime(&tt);

    today.year = lt->tm_year + 1900;
    today.month = lt->tm_mon + 1;
    today.day = lt->tm_mday;

    int baseWeek = 5; // 以2017年9月22日为基准
    int days = 0;

    for (int i = 9; i < today.month; i++)
        days += daysPerMonth[i];
    days += today.day - 22;

    days %= 7;
    baseWeek += days;
    if (baseWeek >= 7)
        baseWeek -= 7;

    today.week = (wchar_t *)CNWeeks[baseWeek];
    return today;
}

SNode *CreateStudentList(void)
{
    SNode *head = calloc(1, sizeof(SNode));
    head->next = NULL;
    return head;
}

bool InsertList(SNode *const head, Student stu)
{
    SNode *p = head;
    SNode *q = calloc(1, sizeof(SNode));

    q->data = stu;
    q->next = NULL;

    while (p->next != NULL)
    {
        if (p->next->data.studentNumber == stu.studentNumber)
            return false;
        else if (p->next->data.studentNumber >= stu.studentNumber) // 学号从小到大递增
        {
            q->next = p->next;
            p->next = q;
            return true;
        }
        p = p->next;
    }

    p->next = q;
    return true;
}

void ErrorAndExit(void)
{
    wprintf(L"    发生严重错误!程序即将退出...");
    // ClearInput();
    getchar();
    exit(0xff);
}

void PressToContinue(void)
{
    wprintf(L"    按任意键返回……\n");
    getch();
}
