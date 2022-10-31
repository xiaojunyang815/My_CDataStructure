// myListTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
///////////////////List Operate//////////////////
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

typedef struct _mydata
{
    uint8_t xData;
} MY_DATA_t, *pMY_DATA_t;

#define ELEMENTTYPE MY_DATA_t
#define pELEMENTTYPE MY_DATA_t *

#define LIST_IS_EMPTY 1
#define LIST_NOT_EMPTY 0

#define ELE_DEL_SUCCESS 1
#define ELE_FOUND 2
#define ELE_NOT_FOUND 255

/////////////////////////////////////////////////
typedef struct _mylistNode
{
    struct _mylistNode *pPrev;
    struct _mylistNode *pNext;
    ELEMENTTYPE pNodeData;
} MYLISTNODE_T, *pMYLISTNODE_T;
/////////////////////////////////////////////////
pMYLISTNODE_T pMyListHead;

#define DEMO_ELEMENT_SIZE 20
uint8_t gDemoArray[DEMO_ELEMENT_SIZE] =
    {
        56, 24, 10, 38, 25, 48, 99, 120, 5, 76,
        57, 29, 11, 37, 23, 50, 97, 118, 7, 75};

uint8_t gDemoAddArray[5] =
    {
        31, 41, 51, 61, 71};

/////////////////////////////////////////////////
void fnInitMyList(void)
{
    pMyListHead = (pMYLISTNODE_T)0;
}

// Insert at head
MYLISTNODE_T *fnInsertNEleToListHead(uint8_t *pEleData, uint8_t nEleCounter)
{
    MYLISTNODE_T *pNode;

    if (nEleCounter == 0)
    {
        return 0;
    }

    while (nEleCounter--)
    {
        pNode = (MYLISTNODE_T *)malloc(sizeof(MYLISTNODE_T));

        if (pNode != (MYLISTNODE_T *)0)
        {
            /*Init Node*/
            pNode->pNext = (MYLISTNODE_T *)0;
            pNode->pPrev = (MYLISTNODE_T *)0;
            pNode->pNodeData.xData = *pEleData++;

            if (pMyListHead != (MYLISTNODE_T *)0)
            {
                pNode->pNext = pMyListHead;
                pMyListHead->pPrev = pNode;
            }

            pMyListHead = pNode;
        }
        else
        {
            return 0;
        }

    } // while(nEleCounter--)

    return pMyListHead;
}

// Insert at Tail
MYLISTNODE_T *fnInsertNEleToListTail(uint8_t *pEleData, uint8_t nEleCounter)
{
    MYLISTNODE_T *pNode;
    if (nEleCounter == 0)
    {
        return NULL;
    }

    while (nEleCounter--)
    {
        pNode = (MYLISTNODE_T *)malloc(sizeof(MYLISTNODE_T));

        if (pNode != (MYLISTNODE_T *)0)
        {
            /*Init Node*/
            pNode->pNext = (MYLISTNODE_T *)0;
            pNode->pPrev = (MYLISTNODE_T *)0;
            pNode->pNodeData.xData = *pEleData++;

            if (pMyListHead == (MYLISTNODE_T *)0)
            {
                pMyListHead = pNode;
            }
            else
            {
                pMyListHead->pNext = pNode;
                pNode->pPrev = pMyListHead;
                pMyListHead = pNode;
            }
        } // if(pNode != (MYLISTNODE_T*)0)
        else
        {
            return 0;
        }
    } // while(nListLength--)

    // return the head of List
    while (pMyListHead->pPrev != (MYLISTNODE_T *)0)
    {
        pMyListHead = pMyListHead->pPrev;
    }

    return pMyListHead;
}

// Delete specified element
uint8_t fnDeleteSpecifiedEle(const uint8_t mEleData)
{
    MYLISTNODE_T *pNode = (MYLISTNODE_T *)0;
    uint8_t mReturnResult;

    mReturnResult = ELE_NOT_FOUND;

    while (pMyListHead->pNext != (MYLISTNODE_T *)0)
    {
        if (pMyListHead->pNodeData.xData == mEleData)
        {
            pNode = pMyListHead;

            if (pNode->pPrev == (MYLISTNODE_T *)0) /* at head */
            {
                pMyListHead = pMyListHead->pNext;
                pMyListHead->pPrev = (MYLISTNODE_T *)0;
            }
            else /* at center */
            {
                pMyListHead = pMyListHead->pNext;
                pMyListHead->pPrev = pNode->pPrev;
                pNode->pPrev->pNext = pMyListHead;
            }
            free(pNode);               // free the Node
            pNode = (MYLISTNODE_T *)0; //��ֹ����Ұָ��
            mReturnResult = ELE_DEL_SUCCESS;
            break;
        }
        else
        {
            pMyListHead = pMyListHead->pNext;
        }
    }
    /* pMyListHead point to tail here */
    if (pMyListHead->pNodeData.xData == mEleData)
    {
        pNode = pMyListHead;
        if (pMyListHead->pPrev != (MYLISTNODE_T *)0)
        {
            pMyListHead = pMyListHead->pPrev;
            pMyListHead->pNext = (MYLISTNODE_T *)0;
        }
        else // pMyListHead->pPrve==NULL && pMyListHead->pNext==NULL
        {
            pMyListHead = (MYLISTNODE_T *)0;
        }
        free(pNode);
        pNode = (MYLISTNODE_T *)0; //��ֹ����Ұָ��
        mReturnResult = ELE_DEL_SUCCESS;
    }

    if (pMyListHead != (MYLISTNODE_T *)0)
    {
        while (pMyListHead->pPrev != (MYLISTNODE_T *)0)
        {
            pMyListHead = pMyListHead->pPrev;
        }
    }
    return mReturnResult;
}

// Insert and Sort
MYLISTNODE_T *fnInsertAndSortNEleIntoList(uint8_t *pEleData, uint8_t nListLength)
{
    MYLISTNODE_T *pNode;
    if (nListLength == 0)
    {
        return NULL;
    }

    while (nListLength--)
    {
        MYLISTNODE_T *pTempNode;

        pNode = (MYLISTNODE_T *)malloc(sizeof(MYLISTNODE_T));

        if (pNode != (MYLISTNODE_T *)0)
        {
            pNode->pPrev = (MYLISTNODE_T *)0;
            pNode->pNext = (MYLISTNODE_T *)0;
            pNode->pNodeData.xData = *pEleData++;

            if (pMyListHead == (MYLISTNODE_T *)0)
            {
                pMyListHead = pNode;
            }
            else
            {
                if (pNode->pNodeData.xData >= pMyListHead->pNodeData.xData) // right directoin
                {
                    /* right node was NULL, just insert it */
                    if (pMyListHead->pNext == (MYLISTNODE_T *)0)
                    {
                        pMyListHead->pNext = pNode;
                        pNode->pPrev = pMyListHead;
                        pMyListHead = pNode;
                    }
                    else
                    {
                        while (pMyListHead->pNext != (MYLISTNODE_T *)0)
                        {
                            pTempNode = pMyListHead->pNext;
                            /* we found the right position, insert it */
                            /* pMyListHead<pNode<pTempNode */
                            if (pNode->pNodeData.xData <= pTempNode->pNodeData.xData)
                            {
                                pMyListHead->pNext = pNode;
                                pTempNode->pPrev = pNode;

                                pNode->pPrev = pMyListHead;
                                pNode->pNext = pTempNode;

                                pTempNode = (MYLISTNODE_T *)0;
                                break;
                            }
                            else
                            {
                                pMyListHead = pTempNode;
                            }
                        } // while(pMyListHead->pNext != (MYLISTNODE_T*)0)
                        /* run to here, break OR means pNode should be on the tail */
                        if (pMyListHead->pNext == (MYLISTNODE_T *)0)
                        {
                            pMyListHead->pNext = pNode;
                            pNode->pPrev = pMyListHead;
                            pMyListHead = pNode;
                        }
                    }
                }    // if(pNode->pNodeData->xData >= pMyListHead->pNodeData->xData)
                else // left direction
                {
                    // left node was NULL, just insert it
                    if (pMyListHead->pPrev == (MYLISTNODE_T *)0)
                    {
                        pMyListHead->pPrev = pNode;
                        pNode->pNext = pMyListHead;

                        pMyListHead = pNode;
                    }
                    else
                    {
                        while (pMyListHead->pPrev != (MYLISTNODE_T *)0)
                        {
                            pTempNode = pMyListHead->pPrev;
                            /* we found the right position, insert it */
                            /* pTempNode<pNode<pMyListHead */
                            if (pNode->pNodeData.xData >= pTempNode->pNodeData.xData)
                            {
                                pNode->pNext = pMyListHead;
                                pNode->pPrev = pTempNode;

                                pTempNode->pNext = pNode;
                                pMyListHead->pPrev = pNode;

                                pTempNode = (MYLISTNODE_T *)0;
                                break;
                            }
                            else
                            {
                                pMyListHead = pTempNode;
                            }
                            if (pMyListHead->pPrev == (MYLISTNODE_T *)0)
                            {
                                pMyListHead->pPrev = pNode;
                                pNode->pNext = pMyListHead;
                                pMyListHead = pNode;
                            }
                        }
                    }
                } // else if(pNode->pNodeData->xData >= pMyListHead->pNodeData->xData)
            }     // else if(pMyListHead == (MYLISTNODE_T*)0)
        }         // if(pNode != (MYLISTNODE_T*)0)
        else
        {
            return 0;
        }
    } // while(nListLength--)

    // return the head of List
    while (pMyListHead->pPrev != (MYLISTNODE_T *)0)
    {
        pMyListHead = pMyListHead->pPrev;
    }

    return pMyListHead;
}

uint8_t fnSearchSpecifyElement(MYLISTNODE_T *pListHead, uint8_t Ele, uint8_t *pEleIdx)
{
    MYLISTNODE_T *pHead;

    if (pListHead == (MYLISTNODE_T *)0)
    {
        return LIST_IS_EMPTY;
    }

    pHead = pListHead;
    *pEleIdx = 0;

    while (pHead != (MYLISTNODE_T *)0)
    {
        if (Ele == pHead->pNodeData.xData)
        {
            return ELE_FOUND;
        }
        else
        {
            pHead = pHead->pNext;
            *pEleIdx += 1;
        }
    }

    return ELE_NOT_FOUND;
}

void fnOutputListElements(MYLISTNODE_T *pListToDisp)
{
    uint8_t mEleCounter = 0;
    MYLISTNODE_T *pDispList;

    pDispList = pListToDisp;

    while (pDispList != (MYLISTNODE_T *)0)
    {
        mEleCounter += 1;
        printf("	%d", pDispList->pNodeData.xData);
        pDispList = pDispList->pNext;
    }

    printf("\r\n Total %d Elements were displayed. \r\n", mEleCounter);
}

uint8_t fnGetCounterOfListEle(MYLISTNODE_T *pListHead)
{
    uint8_t mCounter = 0;
    MYLISTNODE_T *pHead = pListHead;

    while (pHead != (MYLISTNODE_T *)0)
    {
        pHead = pHead->pNext;
        mCounter += 1;
    }

    return mCounter;
}

uint8_t fnCheckListIsEmpty(MYLISTNODE_T *pListHead)
{
    if (pListHead == (MYLISTNODE_T *)0)
        return 1;

    return 0;
}

int _tmain(int argc, _TCHAR *argv[])
{
    int mInputData;
    uint8_t mEleIndex;

    printf("hello, Welcome to MY LIST world!\r\n");

    fnInitMyList();
    printf("Counter: %d\r\n", fnGetCounterOfListEle(pMyListHead));

    printf("\r\nNow, we insert and sort the List.\r\n");
    fnInsertAndSortNEleIntoList(gDemoArray, DEMO_ELEMENT_SIZE);
    fnOutputListElements(pMyListHead);
    printf("Counter: %d\r\n", fnGetCounterOfListEle(pMyListHead));

    // fnInsertNEleToListTail(gDemoArray, DEMO_ELEMENT_SIZE);

    fnInsertNEleToListHead(gDemoAddArray, 5);
    fnOutputListElements(pMyListHead);
    printf("Counter: %d\r\n", fnGetCounterOfListEle(pMyListHead));

    if (ELE_FOUND == fnSearchSpecifyElement(pMyListHead, 200, &mEleIndex))
    {
        printf("\r\nEle Found, index is %d\r\n", mEleIndex);
    }
    else
    {
        printf("\r\nEle not found.\r\n");
    }

    /*
    printf("\r\nAdd and sort other some elements.\r\n");
    fnInsertAndSortNEleIntoList(gDemoAddArray, 5);
    fnOutputListElements(pMyListHead);
    printf("Counter: %d\r\n", fnGetCounterOfListEle(pMyListHead));
    */
    printf("\r\nNow, let us delete specified element.\r\n");
    while (LIST_NOT_EMPTY == fnCheckListIsEmpty(pMyListHead))
    {
        printf("Please input the data you want to delete: ");

        scanf_s("%d", &mInputData);

        if (ELE_DEL_SUCCESS == fnDeleteSpecifiedEle((uint8_t)mInputData))
        {
            printf("\r\nOK, deleted successfully.\r\n");
            fnOutputListElements(pMyListHead);
            printf("Counter: %d\r\n", fnGetCounterOfListEle(pMyListHead));
        }
        else
        {
            printf("\r\nNo element was found.\r\n");
            fnOutputListElements(pMyListHead);
        }
    }

    system("pause");

    return 0;
}
