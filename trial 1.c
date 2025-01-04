#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct LNode {  
    int num;       // 系数  
    int exp;       // 指数  
    struct LNode *Next; // next 指针  
} LNode, *LinkList;  
  
// 链表初始化  
void Init_List(LinkList *L) {  
    *L = (LNode *)malloc(sizeof(LNode));  
    (*L)->Next = NULL;  
}  
  
// 利用求导法则生成结点  
LNode *Derivation(int a, int b)   {  
    LNode *node = (LNode * )malloc(sizeof(LNode));  
    node->num = a * b;  
    node->exp = b - 1;  
    return node;  
}  
  
// 尾插法  
void TailInsert(LinkList L, LNode *node) {  
    LNode *p = L;  
    while (p->Next != NULL) {  
        p = p->Next;  
    }  
    node->Next = NULL;  
    p->Next = node;  
}  
  
// 输出链表，f==0 为常数多项式输出 0 0  
void PrintList(LinkList L, int f) {  
    if (f) {  
        LNode *m = L->Next; // 从链表的第一个实际元素开始  
        int first = 1; // 标志位，用于控制是否打印空格  
        while (m != NULL) {  
            if (!first) {  
                printf(" ");  
            }  
            printf("%d %d", m->num, m->exp);  
            m = m->Next;  
            first = 0;  
        }  
    } else {  
        printf("0 0");  
    }  
}  
  
int main() {  
    LinkList L;  
    LNode *N;  
    int a, b;  
    int flag = 0; // 标志位，判断该多项式是否为常数多项式  
  
    Init_List(&L);  
    while (scanf("%d %d", &a, &b) == 2) { // 使用 == 2 来确保正确读取了两个整数  
        if (b != 0) { // b == 0 为常数，不参与链表的插入  
            flag = 1;  
            N = Derivation(a, b);  
            TailInsert(L, N);  
        }  
    }  
    PrintList(L, flag);  
    printf("\n"); // 添加换行符以符合输出习惯  
  
    // 释放链表内存（在实际应用中应该添加）  
    // 注意：这里的释放逻辑略去了，因为需要递归释放所有节点，并且原题没有要求  
  
    return 0;  
}
