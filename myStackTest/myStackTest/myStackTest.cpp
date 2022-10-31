// myStackTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
//////////////////////////////////////////
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

typedef struct _mydata
{
    uint8_t xData;
} MY_DATA_t;

#define STACK_IS_EMPTY 1
#define STACK_NOT_EMPTY 0

#define STACK_SIZE 5

#define STACK_IS_FULL 255
#define STACK_NOT_FULL 254

typedef struct _mystackNode
{
    struct _mystackNode *pNext;
    MY_DATA_t mNodeData;
} MYSTACKNODE_t, *pMYSTACKNODE_t;

//    定义栈结构体
typedef struct Stack
{
    pMYSTACKNODE_t pTOP;    //    定义栈顶节点
    pMYSTACKNODE_t pBOTTOM; //    定义栈底节点
    uint8_t mStkSize;
} STACK_t, *PSTACK_t;

STACK_t gMyStack;

void fnInitStack(PSTACK_t pStk)
{
    /*
    pMYSTACKNODE_t pNode = (pMYSTACKNODE_t)malloc(sizeof(MYSTACKNODE_t));

    if (pNode == (pMYSTACKNODE_t)0)
    {
        return;
    }

    pNode->pNext = (pMYSTACKNODE_t)0;
    pNode->mNodeData.xData = 0;

    pStk->pTOP = pNode;
    pStk->pBOTTOM = pNode;
    pStk->mStkSize = 1;
    */
    pStk->mStkSize = 0;
    pStk->pTOP = (pMYSTACKNODE_t)0;
    pStk->pBOTTOM = (pMYSTACKNODE_t)0;
}

uint8_t fnCheckStackIsEmpty(PSTACK_t pStk)
{
    // Stack is Empty
    if (pStk->pTOP == pStk->pBOTTOM)
    {
        return STACK_IS_EMPTY;
    }

    return STACK_NOT_EMPTY;
}

uint8_t fnCheckStackIsFull(PSTACK_t pStk)
{
    if (pStk->mStkSize < STACK_SIZE)
        return STACK_NOT_FULL;

    return STACK_IS_FULL;
}

void fnPushStack(PSTACK_t pStk, uint8_t mEle)
{
    if (fnCheckStackIsFull(pStk) == STACK_NOT_FULL)
    {
        pMYSTACKNODE_t pNode = (pMYSTACKNODE_t)malloc(sizeof(MYSTACKNODE_t));

        pNode->mNodeData.xData = mEle;
        pNode->pNext = pStk->pTOP;
        pStk->pTOP = pNode;
        pStk->mStkSize += 1;
    }
    else
    {
        printf("The stack was full, push fail.\r\n");
    }
}

void fnPopStack(PSTACK_t pStk, uint8_t *mEle)
{
    if (STACK_IS_EMPTY == fnCheckStackIsEmpty(pStk))
    {
        return;
    }

    pMYSTACKNODE_t pNode = pStk->pTOP;
    *mEle = pNode->mNodeData.xData;

    pStk->pTOP = pNode->pNext;

    free(pNode);
    pNode = (pMYSTACKNODE_t)0; //防止产生野指针
    /* this mean pNode still point to a address, but memory was freed. */
    pStk->mStkSize -= 1;
}

void fnTraverseStack(PSTACK_t pStk)
{
    if (STACK_IS_EMPTY == fnCheckStackIsEmpty(pStk))
    {
        return;
    }

    pMYSTACKNODE_t pNode = pStk->pTOP;

    while (pNode != pStk->pBOTTOM)
    {
        printf("%d	", pNode->mNodeData.xData);
        pNode = pNode->pNext;
    }

    printf("\r\n");
}

void fnDeleteStack(PSTACK_t pStk)
{
    if (STACK_IS_EMPTY == fnCheckStackIsEmpty(pStk))
    {
        return;
    }

    pMYSTACKNODE_t pNode = pStk->pTOP;

    while (pNode != pStk->pBOTTOM)
    {
        printf("\r\nTopAddr before delete: 0x%x	,Ele is: %d\r\n", pStk->pTOP, pStk->pTOP->mNodeData.xData);
        pStk->pTOP = pNode->pNext;
        free(pNode);
        pNode = pStk->pTOP;
        if (pStk->pTOP != pStk->pBOTTOM)
            printf("TopAddr after delete: 0x%x	,Ele is: %d\r\n", pStk->pTOP, pStk->pTOP->mNodeData.xData);
    }

    pStk->pTOP = pStk->pBOTTOM;
}

int _tmain(int argc, _TCHAR *argv[])
{
    uint8_t mStkEle;
    int mInputEle;

    printf("Welcome to my Stack world!!\r\n");

    fnInitStack(&gMyStack);
    printf("top: %d, bottom: %d\r\n", gMyStack.pTOP, gMyStack.pBOTTOM);

    while (STACK_NOT_FULL == fnCheckStackIsFull(&gMyStack))
    {
        printf("\r\npls input the Ele need to push into stack: ");
        scanf_s("%d", &mInputEle);
        printf("top addr before PUSH: 0x%x	\r\n", gMyStack.pTOP);
        fnPushStack(&gMyStack, (uint8_t)mInputEle);
        printf("Top addr: after PUSH: 0x%x, Top Ele is: %d\r\n", gMyStack.pTOP, gMyStack.pTOP->mNodeData.xData);
    }

    printf("\r\nTraverse all Ele in this stack: \r\n");
    fnTraverseStack(&gMyStack);
    printf("\r\n");
    /*
        while (fnCheckStackIsEmpty(&gMyStack) != STACK_IS_EMPTY)
        {
            printf("top addr before POP: 0x%x	\r\n", gMyStack.pTOP);
            fnPopStack(&gMyStack, &mStkEle);
            printf("#%d	\r\n", mStkEle);
            printf("top addr after POP: 0x%x	\r\n", gMyStack.pTOP);
        }
    */
    fnDeleteStack(&gMyStack);

    system("pause");
    return 0;
}
