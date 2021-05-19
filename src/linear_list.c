/*
********************************************************************************************
*	FileName:	linear_list.c
*	Author:		Liam.Nurx
*	Update:		2021.05
*	
*	Description:
*	
********************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "linear_list.h"

/*
 *	Description:
 *	1.动态分配线性表内存空间;
 *	2.若内存分配成功，则将分配到的内存初始化为0;
 *
 *	Return:
 *	0:	内存分配成功;
 *	-1:	内存分配失败;
 */
int InitList(LINEAR_LIST_STR **ppList)
{
	*ppList = (LINEAR_LIST_STR *)malloc(sizeof(LINEAR_LIST_STR));

	if(NULL == *ppList)
	{
		printf("Memory Allocation Failed for *pLa!\n\r");
		return -1;
	}

	memset(*ppList, 0, sizeof(LINEAR_LIST_STR));

	return 0;
}

/*
 *	Description:
 *	1.销毁线性表，释放线性表内存;
 *	2.将形参指针赋值为空指针;
 */
void DestroyList(LINEAR_LIST_STR **ppList)
{
	free(*ppList);

	*ppList = NULL;
}

/*
 *	Description:
 *	1.判断形参线性表是否为空;
 *
 *	Return:
 *	0:	线性表非空;
 *	1:	线性表为空;
 */
int IsListEmpty(LINEAR_LIST_STR *pList)
{
	return (0 == pList->listLength)?1:0;
}

/*
 *
 */
UINT32 GetListLength(LINEAR_LIST_STR *pList)
{
	return pList->listLength;
}

/*
 *	Description:
 *	1.返回线性表中第一个与 element 值相同的元素的位序;
 *	2.若线性表中不存在这样的元素，则返回值为0;
 *
 *	Note:
 *	起始元素的位序为1;
 */
UINT32 ElementLocate(LINEAR_LIST_STR *pList, UINT8 element)
{
	int i;
	
	for(i=0; i<pList->listLength; i++)
	{
		if(element == pList->listElement[i])
		{
			return ++i;
		}
	}

	return 0;
}


/*
 *	Param:
 *	pList:		线性表指针;
 *	n:			待删除元素位序;			//	起始元素的位序为 1;
 *	pElement:	待删除元素;
 *	
 *	Description:
 *	1.删除线性表 pList 中的第 i 个元素;
 *	2.被删除的元素值赋值给形参 pElement;
 *	3.被删除元素之后的元素全部前移一个单元;
 *	4.线性表长度减一;
 *
 *	Return:
 *	函数返回线性表长度;
 */
UINT32 ElementDelete(LINEAR_LIST_STR *pList, UINT32 n, UINT8 *pElement)
{
	int j;

	if((1 <= n) && (n <= pList->listLength))
	{
		*pElement = pList->listElement[--n];
		
		for(;n<pList->listLength-1; n++)
		{
			pList->listElement[n] = pList->listElement[n+1];
		}

		--pList->listLength;
	}
	else
	{
		printf("Error value of param \"n\";\n\r");
	}

	return pList->listLength;
}



/*
 *	Param:
 *	pList:		线性表指针;
 *	n:			待插入元素的位序;			//	起始元素的位序为 1;
 *	element:	待插入元素;
 *
 *	Description:
 *	1.将位序范围在 [i--pList->length] 之间的元素全部后移一个单位;
 *	2.将元素 element 插入位序为 i 的位置;
 *	3.线性表长度加一;
 *
 *	Return:
 *	函数返回当前线性表长度;
 */
UINT32 ElementInsert(LINEAR_LIST_STR *pList, UINT32 n, UINT8 element)
{
	int i;

	if((1 <= n) && (n <= pList->listLength+1) && (pList->listLength+1 <= LINEAR_LIST_ELEMENT_MAX))
	{
		for(i=pList->listLength; i>=n; i--)
		{
			pList->listElement[i] = pList->listElement[i-1];
		}

		pList->listElement[i] = element;
		++pList->listLength;
	}
	else
	{
		if(LINEAR_LIST_ELEMENT_MAX <= pList->listLength+1)
		{
			printf("Error, Element Overflow!\n\r");
		}
		else
		{
			printf("Error value of param \"n\";\n\r");
		}
	}
	
	return pList->listLength;
}

/*
 *	Description:
 *	1.根据形参的线性表: pLa, pLb 合并得到新的线性表 pLa = pLa U pLb;
 *	2.从 pLb 中取一个数据元素;
 *	3.依该数据元素的值在线性表 pLa 中查询;
 *	4.若线性表 pLa 中不存在与该值相同的数据元素，则将该元素插入到 pLa 并从 pLb 中删除;
 *	5.重复以上操作直至 pLb 为空;
 *
 *	Return:
 *	函数返回合并后的线性表的长度;
 */
UINT32 LinearListUnion(LINEAR_LIST_STR *pLa, LINEAR_LIST_STR *pLb)
{
	UINT8 tempElement;
	UINT32 listLength;

	while(!IsListEmpty(pLb))
	{
		listLength = GetListLength(pLa);
		ElementDelete(pLb, 1, &tempElement);

		if(!ElementLocate(pLa, tempElement))
		{
			ElementInsert(pLa, listLength+1, tempElement);
		}
	}

	return pLa->listLength;
}


int LinearTest(void)
{
	int i;
	UINT8 element;

	LINEAR_LIST_STR *pLa = NULL;
	LINEAR_LIST_STR **ppLa = &pLa;
	LINEAR_LIST_STR *pLb = NULL;
	LINEAR_LIST_STR **ppLb = &pLb;

	InitList(ppLa);
	InitList(ppLb);

	//printf("Address of pLa: 0x%X\n\r", (UINT32)pLa);
	//printf("Address of pLb: 0x%X\n\r", (UINT32)pLb);

	for(i=0; i<26; i++)
	{
		pLa->listElement[i] = 'a'+i;
		pLb->listElement[i] = 'A'+i;
		pLa->listLength = i+1;
		pLb->listLength = i+1;
	}

	//	判断线性表是否为空;
	if(IsListEmpty(pLa))
	{
		printf("pLa is Empty!\n\r");
	}
	if(IsListEmpty(pLa))
	{
		printf("pLb is Empty!\n\r");
	}

	//	线性表长度查询;
	printf("Length of listA: %d\n\rLength of listB: %d\n\r", \
		   GetListLength(pLa), \
		   GetListLength(pLb));

	//	线性表元素位序查询;
	printf("Serial Number of \'q\' in listA is: %d\n\rSerial Number of \'Q\' in listB is: %d\n\r", \
		   ElementLocate(pLa, 'q'), \
		   ElementLocate(pLb, 'Q'));

	//	线性表元素删除;
	printf("Before ElementDelete ListA:\n\r");
	for(i=0; i<pLa->listLength; i++)
	{
		printf("%c", pLa->listElement[i]);
	}
	printf("\n\r");
	ElementDelete(pLa, 17, &element);
	printf("Deleted Element: %c\n\r", element);
	printf("After ElementDelete ListA:\n\r");
	for(i=0; i<pLa->listLength; i++)
	{
		printf("%c", pLa->listElement[i]);
	}
	printf("\n\r");

	//	线性表元素插入;
	printf("After ElementInsert ListA:\n\r");
	ElementInsert(pLa, 17, element);
	for(i=0; i<pLa->listLength; i++)
	{
		printf("%c", pLa->listElement[i]);
	}
	printf("\n\r");

	//	线性表合并;
	printf("Before LinearListUnion listA(%d): ", GetListLength(pLa));
	for(i=0; i<pLa->listLength; i++)
	{
		printf("%c", pLa->listElement[i]);
	}
	printf("\n\r");

	printf("Before LinearListUnion listB(%d): ", GetListLength(pLb));
	for(i=0; i<pLb->listLength; i++)
	{
		printf("%c", pLb->listElement[i]);
	}
	printf("\n\r");

#if 1
	printf("After LinearListUnion:\n\rlistB(%d)\n\rlistA(%d): ", \
		   GetListLength(pLb), \
		   LinearListUnion(pLa, pLb));
	for(i=0; i<pLa->listLength; i++)
	{
		printf("%c", pLa->listElement[i]);
	}
	printf("\n\r");
#else
	printf("After LinearListUnion:\n\rlistA(%d)\n\rlistB(%d): ", \
		   GetListLength(pLa), \
		   LinearListUnion(pLb, pLa));
	for(i=0; i<pLb->listLength; i++)
	{
		printf("%c", pLb->listElement[i]);
	}
	printf("\n\r");
#endif

	//	释放动态分配的内存并将原指向动态分配内存的指针赋值为空指针;
	DestroyList(ppLa);
	DestroyList(ppLb);

#if 0
	printf("Address of pLa: 0x%X\n\r", (UINT32)pLa);
	printf("Address of pLb: 0x%X\n\r", (UINT32)pLb);

	pLa->listLength = 100;
	pLb->listLength = 100;
	printf("Length A: %d\n\rLength B: %d\n\r", \
		   pLa->listLength, \
		   pLb->listLength);
#endif
}











