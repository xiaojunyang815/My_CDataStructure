// myStringTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

char tCh1[] = {'c', '+', '+'};
char tCh2[] = {'c', '+', '+', '\0'};
char tCh3[] = "myCSt";
char tCh4[] = "good idea";

int fnStrlen(const char *pStrSrc);
char *fnStrcat(char *pStrDest, const char *pStrSrc);
char *fnStrcpy(char *pStrDest, char *pStrSrc);
int fnStrcmp(const char *pStr1, const char *pStr2);
void *fnMemcpy(void *pDest, void *pSrc, size_t n);
void *fnMemmove(void *pDest, void *pSrc, size_t n);

void *fnMemmove(void *pDest, void *pSrc, size_t n)
{
	char *pStrDest = (char *)pDest;
	char *pStrSrc = (char *)pSrc;

	assert(pSrc != NULL && pDest != NULL && n > 0);

	if ((pStrSrc > pStrDest) || ((pStrSrc + n) < pStrDest))
	{
		while (n--)
		{
			*(pStrDest++) = *(pStrSrc++);
		}
		*pStrDest = '\0';
	}
	else if (pStrSrc < pStrDest)
	{
		pStrDest += n;
		pStrSrc += n;
		*pStrDest = '\0';

		while (n--)
		{
			*(--pStrDest) = *(--pStrSrc);
		}
	}

	return pDest;
}

void *fnMemcpy(void *pDest, void *pSrc, size_t n)
{
	char *pStrDest = (char *)pDest;
	char *pStrSrc = (char *)pSrc;

	assert(pSrc != NULL && pDest != NULL && n > 0);

	while (n--)
	{
		*pStrDest++ = *pStrSrc++;
	}
	*pStrDest = '\0';

	return pDest;
}

char *fnStrcat(char *pStrDest, const char *pStrSrc)
{
	char *pAdd = pStrDest;

	assert(pStrDest != NULL && pStrSrc != NULL);

	while (*pStrDest != '\0')
		pStrDest++;

	while (*pStrSrc != '\0')
	{
		*pStrDest++ = *pStrSrc++;
	}
	*pStrDest = '\0';

	return pAdd;
}

char *fnStrcpy(char *pStrDest, char *pStrSrc)
{
	char *pAdd = pStrDest;

	assert(pStrDest != NULL && pStrSrc != NULL);

	while (*pStrSrc != '\0')
	{
		*pStrDest++ = *pStrSrc++;
	}
	*pStrDest = '\0';

	return pAdd;
}

int fnStrcmp(const char *pStr1, const char *pStr2)
{
	assert(pStr1 != NULL && pStr2 != NULL);

	while ((*pStr1 != '\0') && (*pStr2 != '\0') && (*pStr1 == *pStr2))
	{
		pStr1++;
		pStr2++;
	}

	return *pStr1 - *pStr2;
}

int fnStrlen(const char *pStrSrc)
{
	int count = 0;
	assert(pStrSrc != NULL);

	while (*pStrSrc++ != '\0')
	{
		count += 1;
	}
	return count;
}

int _tmain(int argc, _TCHAR *argv[])
{
	char *mv_src = "the src test memmove"; // length=20
	// char mv_dest[40];
	char *pMvDest = (char *)malloc(42);

	printf("Welcome to my String World.\r\n");

	printf("tCh1 length is: %d\r\n", fnStrlen(tCh1));
	printf("tCh2 length is: %d\r\n", fnStrlen(tCh2));
	printf("tCh3 length is: %d\r\n", fnStrlen(tCh3));
	printf("tCh4 length is: %d\r\n", fnStrlen(tCh4));

	printf("tChx length is: %d\r\n", fnStrlen("welcome to my world."));

	printf("mvSrc length is: %d\r\n", fnStrlen(mv_src));

	printf("Test MemMove ret is: %s\r\n", fnMemmove(pMvDest, mv_src, fnStrlen(mv_src)));
	printf("pMvDest length is: %d\r\n", fnStrlen(pMvDest));

	printf("Test MemCopy ret is: %s\r\n", fnMemcpy(pMvDest, mv_src, fnStrlen(mv_src)));
	printf("pMvDest length is: %d\r\n", fnStrlen(pMvDest));

	printf("Test Strcat ret is: %s\r\n", fnStrcat(pMvDest, mv_src));
	printf("pMvDest length is: %d\r\n", fnStrlen(pMvDest));

	printf("Test StrCopy ret is: %s\r\n", fnStrcpy(pMvDest, mv_src));
	printf("pMvDest length is: %d\r\n", fnStrlen(pMvDest));

	free(pMvDest);
	pMvDest = NULL; //��ֹ����Ұָ��

	system("pause");
	return 0;
}
