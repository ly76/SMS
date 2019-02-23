#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//简介00： 前端时间作死之后王冉老师让梁学长交给我的去年数据结构的课设...要求本学期之前把这里的课程设计尽可能完成、虽然一度十分后悔，但已经来不及只能硬着头皮上了...
   //这里因为技术与智力问题果然还是先挑几个单链表做着

//所需分析：  1.学生信息录入 Input_information()  --创建以及插入链表
//            2.学生信息浏览 Browse_information() --输出链表
//            3.学生信息查询 Query_information()  --查询特定结点并加入其它操作
//            4.信息排序 Osrt_information()       --1.使用冒泡法或者快排（冒泡的指针实现...） 2.怎么按照姓名排序没看懂
//            5.信息删除 Delete_information()     --删除特定结点
//            6.信息修改 Revise_information()     --修改特定的结点
//            0.退出 exit()


//--------结构体的创建--------//   ----------------------------------------------
typedef struct student   //数据域结构体：学号、姓名、语、数、外
{
    char num[20];  //学号
    char name[20]; //姓名
    int score[4];  //语文、数学、外语、总分

}student;
typedef struct Node
{
    student data;  //存到数据域
    struct Node * next;
}node;

//-----------创建链表------------//  -----------------------------------------------
node * CreatList()  //Input_information()之一部分，当然这个课设说的不是很明白
{
    node *L,*p1,*p2;  //用p1指向新结点、p2指向最后一个结点
    int i,n;
    printf("请输入学生人数：\n");
    scanf("%d",&n);
    printf("请输入学生各项成绩 包括：学号，姓名，语文成绩，数学成绩，英语成绩\n");
    L=(node*)malloc(sizeof(node)); //创建头节点L
    p2=L;
    for(i=0;i<n;i++)
    {
        p1=(node*)malloc(sizeof(node));  //创建新的结点
        scanf("%s%s%d%d%d",p1->data.num,p1->data.name,&p1->data.score[0],&p1->data.score[1],&p1->data.score[2]);
        p2->next=p1;
        p2=p1;   //不断将p1指向的结点传给p2 ...emm说这个似乎没什么意义，凑个注释字数
    }
    p2->next=NULL;
    printf("学生信息创建成功");
return L;  //最普通的一个带头节点链表创建完成啦
}


//------------输出链表------------//  ------------------------------------------------------
void Print(node *L)
{
    node *p=L->next; //p仅指向头指针之后的有值链表
    while(p!=NULL)
    {
        printf("%s%s%d%d%d",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
        p=p->next; //每循环一次向前指一个
    }
}  //最水的一个输出函数就完成啦


//-----------查询链表------------//  --------------------------------------------------------
void Search_num(node *L) //按学号进行的学生信息查询
{
    node *p=L->next;
    char n[20];
    printf("请输入查找的学号\n");
        scanf("%s",n); //这里比较的学号并不一定是整形...比如我的实验室ID A0617M86
    while(p!=NULL)
    {
        if(strcmp(p->data.num,n)==0) //字符串比较函数
        {
            printf("%s%s%d%d%d",p->data.num,p->data.name,p->data.score[0],p->data.score[1],p->data.score[2]);
            break;
        }
        else p=p->next;
    }

}
//最开始定式思维想的是冒泡法排完序...但好像会搅乱内存..最后果然还是选择了“打擂台”的方法，总的来说节省了空间
void Search_c(node *L) //语文成绩最高
{
    node *p1=L->next;
    node *p2=p1->next;
    while(p2!=NULL)
    {
        if(p2->data.score[0] > p1->data.score[0]) //如果p2指向的值大于了p1
        {
            p1=p2;   //把最大值赋给P1(让p1指向p2) ，此过程p1永远大于p2
            p2=p2->next;   //p2往后找
        }
        else
        {
            p2=p2->next;  //p2继续往后找
        }
    }
    Print(p1);   //输出（语文）最大值p1的整个结点

}
// 同上 时间复杂度 o=2n
void Search_M(node *L)  //数学成绩最高
{
    node *p1=L->next;
    node *p2=p1->next;
    while(p2) //p2!=NULL 的简略写法，尝试一下
    {
        if(p2->data.score[1] > p1->data.score[1])
        {
            p1=p2;
            p2=p2->next;
        }
        else
        {
            p2=p2->next;
        }
    }
    Print(p1); //注意这里是函数调的函数，得前面有和我一样的函数才能这么搞
}
//同上上
void Search_E(node *L)  //英语成绩最高
{
    node *p1=L->next;
    node *p2=p1->next;
    while(p2)
    {
        if(p2->data.score[2] > p1->data.score[2])
        {
            p1=p2;
            p2=p2->next;
        }
        else
        {
            p2=p2->next;
        }
    }
    Print(p1);
}


//------------链表排序-------------//  --------------------------------------------
void Sort(node *L)  //真正的“sort”（STL里）内部用的是快排，但限于水平，这里的“Sort”函数实现用冒泡法代替
{
    node *p1 = L->next;
    node *p2 = L->next;
    student temp;
    for(;p1->next!=NULL;p1=p1->next)   //...忽然发现值交换法的冒泡排序比顺序（数组）实现还要简单
    {
        for(p2=L->next;p2->next!=NULL;p2=p2->next)
        {
            if(p2->data.score[3] > p2->next->data.score[3])
            {
                temp = p2->data;         //这里使用的是结点数据的交换，而不是结点交换法
                p2->data = p2->next->data;  //至于原因...emm 还是那句话 水平不足啊.....
                p2->next->data=temp;   //后面会尝试着找到教程把结点交换法补上
            }
        }
    }

}


//-------------链表删除--------------//-------------------------------------
void Delete(node * L) //普通的删除操作...具体思想是遗落特定结点
{
    node *p=L->next;
    node *pre=L; //前驱结点
    printf("请输入要删除的学生学号： \n");
    char num1[20];
    scanf("%s",&num1[20]);
    while((pre!=NULL)&&(pre->next->data.num!=num1)) //查找所查元素的前驱
    {
        pre=pre->next;
    }
    p=pre->next;
    if(p!=NULL)
        {
            pre->next = p->next; //让前驱结点直接连接到所查询结点后面的结点
            free(p); //释放已删除的结点的内存
            printf("删除成功\n");
        }
        else
        {
            printf("未查找到此同学\n");
        }
}

// --------------修改特定的结点----------------// -----------------------
void Modifaaction(node *L)
{
    node *p = L->next;
    char num2[20];
    printf("请输入需要修改的学生学号：\n");
    scanf("%s",num2);   //同样是指向字符串数组的首位 与&num2[20]等价，试一下
    while(p!=NULL)
    {
        if(strcmp(p->data.num,num2)==0)  //修改p现在所指的结点数据
        {
            printf("请重新学生考试信息：\n");
            scanf("%s%s%d%d%d",p->data.num,p->data.name,&p->data.score[0],&p->data.score[1],&p->data.score[2]);
            printf("修改成功\n");
            break;
        }
        p=p->next;
    }
    if(p==NULL)
    {
        printf("没有此考生\n");
    }
}


//********------主函数 ===========================================---
int main()
{
    //事实上之前虽然做了这么多看起来很高大上的函数名但是因为敲起来太麻烦了结果一个也没用...
    //还是借的之前直译的最简单命名方式
    int n;
    node *L=NULL;
    printf("-----------//--欢迎使用学生管理系统--//-------------\n");
    printf("----*           1.学生信息录入                         *\n");
    printf("----*           2.学生信息浏览                         *\n");
    printf("----*           3.学生信息查询(按学号)                 *\n");
    printf("----*           4.学生信息查询(按语文最高)             *\n");
    printf("----*           5.学生信息查询(按数学最高)             *\n");
    printf("----*           6.学生信息查询(按英语最高)             *\n");
    printf("----*           7.信息排序(按照总分)                   *\n");
    printf("----*           8.信息删除                             *\n");
    printf("----*           9.信息修改                             *\n");
    printf("----*              0.退出                              *\n");
    printf("//-------------------------------------------------//\n");
    printf("请输入要使用的功能编号:\n");
    while(scanf("%d",&n)!=EOF)
    {
        switch(n)
        {
            case 1:
                L=CreatList();
                break;
            case 2:
                Print(L);
                break;
            case 3:
                Search_num(L);
                break;
            case 4:
                Search_c(L);
                break;
            case 5:
                Search_M(L);
                break;
            case 6:
                Search_E(L);
                break;
            case 7:
                Sort(L);
                break;
            case 8:
                Delete(L);
                break;
            case 9:
                Modifaaction(L);
                break;
            case 0:
                exit(0);
            default:
                printf("输入有误，请重新输入：\n");
        }
    }
    return 0;
}



//本文件已从原来的CPP修改至可用C99直接编译
   //确认了不会报错
