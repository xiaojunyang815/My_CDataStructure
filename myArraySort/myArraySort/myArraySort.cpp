// myArraySort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"

#define ASCENDING_ORDOR 1

#define SORT_ARRAY_SIZE 21
int gOriginalArray[] =
    {
        128, 65, 97, 200, 78, 54, 156, 198, 15, 27,
        275, 34, 8, 234, 13, 26, 278, 39, 376, 1,
        147};

int gTestArray[5] =
    {
        5, 4, 3, 2, 1};

void fnPrintArray(int *pDispArray, int mCounter)
{
  int i;
  printf("Array Context as:	\r\n");
  for (i = 0; i < mCounter; i++)
  {
    printf("%d	,", pDispArray[i]);
  }
  printf("\r\n");
}
/////////////////////////////////////////////////////
//冒泡排序
/*
Index Orignal    i=0,j=0-6  i=1, j=0-5  i=2, j=0-4  i=3, j=0-3  i=3, j=0-2  i=4, j=0-1
0     5          3          3           3           3           2           1
1     3          5          4           4           2           1           2
2     8          4          5           2           1           3           3
3     4          6          2           1           4           4           4
4     6          2          1           5           5           5           5
5     2          1          6           6           6           6           6
6     1          8          8           8           8           8           8
*/
void fnBubbleSort(int *pSourceArray)
{
  int i, j;

  for (i = 0; i < SORT_ARRAY_SIZE - 1; i++)
  {
    for (j = 0; j < SORT_ARRAY_SIZE - i - 1; j++)
    {
#ifdef ASCENDING_ORDOR
      if (pSourceArray[j] > pSourceArray[j + 1])
#else
      if (pSourceArray[j] < pSourceArray[j + 1])
#endif
      {
        int temp = pSourceArray[j];
        pSourceArray[j] = pSourceArray[j + 1];
        pSourceArray[j + 1] = temp;
      }
    }
  }
}
/*
  传统冒泡排序中每一趟排序操作只能找到一个最大值或最小值,
  我们考虑利用在每趟排序中进行正向和反向两遍冒泡的方法,
  一次可以得到两个最终值(最大者和最小者) ,
  从而使排序趟数几乎减少了一半。
*/
void fnBubbleSort1(int *pSourceArray)
{
  int left = 0;
  int right = SORT_ARRAY_SIZE - 1;

  while (left < right)
  {
    for (int i = left; i < right; i++)
    {
      if (pSourceArray[i] > pSourceArray[i + 1])
      {
        int temp = pSourceArray[i];
        pSourceArray[i] = pSourceArray[i + 1];
        pSourceArray[i + 1] = temp;
      }
    }
    right--;

    for (int j = right; j >= left; j--)
    {
      if (pSourceArray[j + 1] < pSourceArray[j])
      {
        int tempx = pSourceArray[j];
        pSourceArray[j] = pSourceArray[j + 1];
        pSourceArray[j + 1] = tempx;
      }
    }
    left++;
  }
}
/////////////////////////////////////////////////////////////
//快速排序
/*
快速排序的基本思想：
通过一趟排序将待排记录分隔成独立的两部分，
其中一部分记录的关键字均比另一部分的关键字小，
则可分别对这两部分记录继续进行排序，以达到整个序列有序。
*/
void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int partion(int *pSourceArray, int left, int right)
{
  int j = left;
  int i = j - 1;
  int key = pSourceArray[right];

  for (; j < right; ++j)
  {
    if (pSourceArray[j] <= key)
      swap(&pSourceArray[j], &pSourceArray[++i]);
  }

  swap(&pSourceArray[right], &pSourceArray[++i]);

  return i;
}

void quickSort(int *pSourceArray, int left, int right)
{
  if (left >= right)
    return;

  int mid = partion(pSourceArray, left, right);

  quickSort(pSourceArray, left, mid - 1);
  quickSort(pSourceArray, mid + 1, right);
}
//////////////////////////////////////////////////////
//插入排序
/*
插入排序（Insertion-Sort）的算法描述是一种简单直观的排序算法。
它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，
找到相应位置并插入。
插入排序在实现上，通常采用in-place排序（即只需用到O(1)的额外空间的排序），
因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。
*/
/*
Index Orignal    i=1,j=0    i=2, j=1    i=3, j=2    i=4, j=3    i=5, j=4    i=6, j=5
                 tmp=[1]=3  NA          tmp=[3]=4   tmp=[4]=6   tmp=[5]=2   tmp=[6]=1
0     5          3          3           3           3           2           1
1     3          5          5           4           4           3           2
2     8          8          8           5           5           4           3
3     4          4          4           8           6           5           4
4     6          6          6           6           8           6           5
5     2          2          2           2           2           8           6
6     1          1          1           1           1           1           8
*/
void insertSort(int *pSourceArray, int mArrayLength)
{
  int tmp = 0;
  int i;
  int j;

  for (i = 1; i < mArrayLength; i++)
  {
    j = i - 1;
    if (pSourceArray[i] < pSourceArray[j])
    {
      tmp = pSourceArray[i];
      pSourceArray[i] = pSourceArray[j];
      while ((j > 0) && (tmp < pSourceArray[j - 1]))
      {
        pSourceArray[j] = pSourceArray[j - 1];
        j--;
      }
      pSourceArray[j] = tmp;
    }
  }
}
// Shell Sort
void shellInsertSort(int *pSourceArray, int dk)
{
  int i, j;

  for (i = dk; i < SORT_ARRAY_SIZE; i++)
  {
    j = i - dk;
    if (pSourceArray[i] < pSourceArray[j])
    {
      int tmp = pSourceArray[i];
      pSourceArray[i] = pSourceArray[j];

      while ((j > 0) && (pSourceArray[j] > tmp))
      {
        pSourceArray[j + dk] = pSourceArray[j];
        j -= dk;
      }
      pSourceArray[j + dk] = tmp;
    }
  }
}
void shellSort(int *pSourceArray, int n)
{
  int dk = n / 2;
  while (dk >= 1)
  {
    shellInsertSort(pSourceArray, dk);
    dk = dk / 2;
  }
}
//////////////////////////////////////////////////////
//选择排序
/*
选择排序(Selection-sort)是一种简单直观的排序算法。
它的工作原理：首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，
然后，再从剩余未排序元素中继续寻找最小（大）元素，
然后放到已排序序列的末尾。
以此类推，直到所有元素均排序完毕。
*/
/*
Index Orignal    i=0,j=1-7  i=1, j=2-7  i=2, j=3-7  i=3, j=4-7  i=4, j=5-7  i=5, j=6-1
                 key=0->6   key=1->5    key=2->6    key=3       key=4->6    key=5->6
0     5          1          1           1           1           1           1
1     3          3          2           2           2           2           2
2     8          8          8           3           3           3           3
3     4          4          4           4           4           4           4
4     6          6          6           6           6           5           5
5     2          2          3           8           8           8           6
6     1          5          5           5           5           6           8
*/
void selectSort(int *pSourceArray, int mArrayLength)
{
  int i;
  int tmp, key;

  for (i = 0; i < mArrayLength; i++)
  {
    key = i;
    for (int j = i + 1; j < mArrayLength; j++)
    {
      if (pSourceArray[j] < pSourceArray[key])
      {
        key = j;
      }
    }

    if (key != i)
    {
      tmp = pSourceArray[key];
      pSourceArray[key] = pSourceArray[i];
      pSourceArray[i] = tmp;
    }
  }
}
//////////////////////////////////////////////////////
//堆(Heap)排序
void createHeap(int *pSourceArray, int i, int n)
{
  for (; i >= 0; --i)
  {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int j = 0;
    if (right < n)
    {
      pSourceArray[left] > pSourceArray[right] ? j = left : j = right;
    }
    else
    {
      j = left;
    }
    if (pSourceArray[j] > pSourceArray[i])
    {
      int tmp = pSourceArray[i];
      pSourceArray[i] = pSourceArray[j];
      pSourceArray[j] = tmp;
    }
  }
}

void heapSort(int *pSourceArray, int n)
{
  createHeap(pSourceArray, n / 2 - 1, n);

  for (int j = n - 1; j >= 0; j--)
  {
    int tmp = pSourceArray[0];
    pSourceArray[0] = pSourceArray[j];
    pSourceArray[j] = tmp;

    int i = j / 2 - 1;
    createHeap(pSourceArray, i, j);
  }
}

//////////////////////////////////////////////////////
//归并排序
void mergeArray(int *pSourceArray, int left, int mid, int right)
{
  int len = right - left + 1;
  int *pTempArray = new int[len];

  int k = 0;
  int i = left;
  int j = mid + 1;
}

int _tmain(int argc, _TCHAR *argv[])
{
  printf("Welcome to my ArraySort world.\r\n");

  fnPrintArray(gOriginalArray, SORT_ARRAY_SIZE);
  // fnBubbleSort1(gOriginalArray);
  // quickSort(gOriginalArray, 0, SORT_ARRAY_SIZE-1);

  // insertSort(gTestArray, 5);
  // insertSort(gOriginalArray, SORT_ARRAY_SIZE);

  // shellSort(gOriginalArray, SORT_ARRAY_SIZE);

  // selectSort(gOriginalArray, SORT_ARRAY_SIZE);

  heapSort(gOriginalArray, SORT_ARRAY_SIZE);
  fnPrintArray(gOriginalArray, SORT_ARRAY_SIZE);

  system("pause");
  return 0;
}
