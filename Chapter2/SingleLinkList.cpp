/**
 * @file SingleLinkList.cpp
 * @author AaronLi
 * @date 2023-01-06-下午3:56
 * @description
 * <p> 单链表实现 </p>
 * <p></p>
 * <p>
 * 通过2.3 线性表的类型定义章节中线性表的抽象数据类型定义<br>
 * 使用单链表的方式实现
 * </p>
 * @link 
 */

#include <iostream>
using namespace std;

/**
 * @date 23-1-6 下午4:02
 * @description 函数结果状态代码、元素类型及函数返回值类型
 */

#define OK (1)
#define ERROR (0)
#define  OVERFLOW (-2)

/* 元素类型 */
#define ElemType int
/* 函数返回值类型 */
typedef int Status;

/**
 * @date 23-1-6 下午5:17
 * @description 单链表的存储结构
 */

typedef struct LNode {
    ElemType data;       /* 节点的数据域 */
    struct LNode *next;      /* 节点的指针域 */
} LNode, *LinkList;       /* LinkList为指向结构体LNode的指针类型 */

/**
 * @date 23-1-6 下午5:17
 * @description 单链表的初始化
 * @return 构造一个空的线性表L
 */

Status InitList(LinkList &L) {
    L = new LNode;        /* 生成新节点作为头节点、用头指针L指向头节点 */
    L->next = nullptr;       /* 头节点的指针域置空 */
    return OK;
}

/**
 * @date 23-1-6 下午6:07
 * @description 单链表的取值
 * @return 在带头节点的单链表L中根据序号i获取元素的值，用e返回L中第i个数据元素的值
 */

Status GetElem(LinkList L, int i, ElemType &e) {
    int j = 1;        /* 计数器j初值赋为1 */
    LNode *p;
    p = L->next;        /* 初始化，p指向首元节点 */
    while (p && j < i) {     /* 顺链域向后查找，之道p为空或者p指向第i个元素 */
        p = p->next;
        ++j;
    }
    if (!p || j > i)return ERROR;        /* i值不合法i>0或i<=0 */
    e = p->data;      /* 取第i个节点的数据域 */
    return OK;
}

/**
 * @date 23-1-6 下午7:39
 * @description 单链表的查找
 * @return 在带头节点的单链表L中查找值为e的元素
 */

LNode *LocateElem(LinkList L, ElemType e) {
    LNode *p;
    p = L->next;      /* 初始化，p指向首元节点 */
    while (p && p->data != e) {       /* 顺链域向后查找，直到p为空或p所指向的数据域等于e */
        p = p->next;      /* p指向下一个节点 */
    }
    return p;       /* 查找成功返回值为e的节点地址p，查找失败p为NULL */
}

/**
 * @date 23-1-6 下午8:03
 * @description 单链表的插入
 * @return 在带头节点的单链表L中第i个位置插入值为e的新节点
 */

Status ListInsert(LinkList &L, int i, ElemType e) {
    LNode *p = L, *s;
    int j = 0;
    while (p && (j < i - 1)) {
        p = p->next;        /* 查找第i-1个节点，p指向该节点 */
        ++j;
    }
    if (!p || j > i - 1)return ERROR;       /* i>n+1或i<1报错 */
    s = new LNode;      /* 生成新节点*s */
    s->data = e;        /* 将节点*s的数据域置为e */
    s->next = p->next;      /* 将节点*s的指针域指向插入节点 */
    p->next = s;        /* 将节点*p的指针域指向节点*s */
    return OK;
}

/**
 * @date 23-1-6 下午8:05
 * @description 单链表的删除
 * @return 在带头节点的单链表L中，删除第i个元素
 */

Status ListDelete(LinkList &L, int i) {
    LNode *p = L, *q;
    int j = 0;
    while ((p->next) && (j < i - 1)) {
        p = p->next;        /* 查找第i-1个节点，p指向该节点 */
        ++j;
    }
    if (!(p->next) || (j > i - 1))return ERROR;     /* 当i>n或i<1时，删除位置不合理 */
    q = p->next;        /* 临时保存被删节点的地址以备释放 */
    p->next = q->next;      /* 改变删除节点前驱节点的指针域 */
    delete q;       /* 释放删除节点的空间 */
    return OK;
}

/**
 * @date 23-1-6 下午9:35
 * @description 前插法创建单链表
 * @return 逆位序输入n个元素的值，建立带表头节点的单链表L
 */

void CreateList_H(LinkList &L,const int Data[], int n) {
    LNode *p;
    L = new LNode;
    L->next = nullptr;       /* 建立一个带头节点的空链表 */
    for (int i = 0; i < n; ++i) {
        p = new LNode;     /* 生成新节点*p */
        p->data=Data[i];        /* 输入元素值赋给新节点*p的数据域 */
        p->next = L->next;     /* 将新节点*p插入到头节点之后 */
        L->next = p;
    }
}

/**
 * @date 23-1-6 下午9:42
 * @description 后插法创建单链表
 * @return 正位序输入n个元素的值，建立带表头节点的单链表L
 */

void CreateList_R(LinkList &L, const int Data[], int n) {
    LNode *r , *p ;
    L = new LNode;
    L->next = nullptr;       /* 先建立一个带空头节点的空链表 */
    r = L;        /* 尾指针r指向头节点 */
    for (int i = 0; i < n; ++i) {
        p = new LNode;       /* 生成新节点 */
        p->data = Data[i];       /* 输入元素值赋给新节点*p的数据域 */
        p->next = nullptr;
        r->next = p;      /* 将新节点*p插入尾节点*r之后 */
        r = p;        /* r指向新的尾节点*p */
    }
}

/**
 * @date 23-1-6 下午10:07
 * @description 输出单链路L
 * @return 以字符串形式输出单链路L
 */

void PrintList(LinkList L) {
    LNode *p = L;
    cout << "None";
    p = p->next;
    while (p) {
        cout << "-->" << p->data;
        p = p->next;
    }
    cout << endl;
}

int main() {
    int i = 0, result = 0, target = 0;
    int laData[] = {2, 6, 8, 9, 11, 15, 20};
    LinkList la;
    LinkList lb;

    /**
     * @date 23-1-6 下午10:19
     * @description 查看链表具体值
     */

    InitList(la);
    CreateList_R(la, laData, sizeof(laData) / sizeof(laData[0]));
    cout << "链表为：";
    PrintList(la);
    cout << endl;

    /**
     * @date 23-1-6 下午10:19
     * @description 查看具体序号对应值
     */

    cout << "输入查找值：";
    cin >> i;
    GetElem(la, i, result);
    cout << "序号为" << i
         << ",其值为：" << result;
    cout << endl;

    /**
     * @date 23-1-6 下午10:20
     * @description 插入具体值
     */
    cout << "输入具体插入位置序号：";
    cin >> i;
    cout << "输入插入位置的值：";
    cin >> target;
    ListInsert(la, i, target);
    cout << "链表为：";
    PrintList(la);
    cout << endl;

    /**
     * @date 23-1-6 下午10:20
     * @description 删除具体值
     */

    cout << "输入具体删除位置序号：";
    cin >> i;
    ListDelete(la, i);
    cout << "链表为：";
    PrintList(la);
    cout << endl;

    /**
     * @date 23-1-6 下午10:35
     * @description 使用前插入法创建链表
     */

    cout <<"前插入法创建的链表：";
    CreateList_H(lb,laData,sizeof(laData)/sizeof(laData[0]));
    PrintList(lb);
    cout << endl;

    return OK;
}