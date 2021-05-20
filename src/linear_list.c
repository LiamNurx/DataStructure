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
	if(NULL != *ppList)
	{
		printf("Current Pointer is not NULL!\n\r");
	}
	else
	{
		*ppList = (LINEAR_LIST_STR *)malloc(sizeof(LINEAR_LIST_STR));
	}

	if(NULL == *ppList)
	{
		printf("Memory Allocation Failed for *ppList!\n\r");
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
 *	Description:
 *	函数返回形参线性表的长度;
 */
UINT32 GetListLength(LINEAR_LIST_STR *pList)
{
	return pList->listLength;
}

/*
 *	Param:
 *	pList:		线性表指针;
 *	n:			待取值元素位序;
 *	pElement:	待赋值元素指针;(用于传回所需元素值)
 *	
 *	Description:
 *	1.函数将形参线性表中指定位序的元素值赋值给 pelement;
 *
 *	Return:
 *	-1:	访问位序值不合理;
 *	0:	元素按位序取值成功;
 */
UINT32 GetListElement(LINEAR_LIST_STR *pList, UINT32 n, UINT8 *pElement)
{
	if((1 > n) && (n > pList->listLength))
	{
		printf("Error, Current List Length is: %d; \'n\'=%d is out of value!\n\r", pList->listLength, n);
		return -1;
	}

	*pElement = pList->listElement[--n];
	return 0;
}


/*
 *	Param:
 *	pList:		线性表指针;
 *	element:	待查询元素;
 *	
 *	Description:
 *	1.返回线性表中第一个与 element 值相同的元素的位序;
 *	2.若线性表中不存在这样的元素，则返回值为0;
 *
 *	Return:
 *	0:	形参线性表中无待查元素值;
 *	!0:	形参线性表中与待查元素值相同的元素位序;
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
 *	Param:
 *	pListA:		形参线性表指针;(数据合并到此线性表中)
 *	pListB:		形参线性表指针;
 *	
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
UINT32 LinearListUnion(LINEAR_LIST_STR *pListA, LINEAR_LIST_STR *pListB)
{
	UINT8 tempElement;
	UINT32 listLength;

	while(!IsListEmpty(pListB))
	{
		listLength = GetListLength(pListA);
		ElementDelete(pListB, 1, &tempElement);

		if(!ElementLocate(pListA, tempElement))
		{
			ElementInsert(pListA, listLength+1, tempElement);
		}
	}

	return pListB->listLength;
}

/*
 *	Param:
 *	pListA:		形参线性表指针;(保存处理结果)	
 *	pListB:		形参线性表指针;(提供原始数据)
 *	
 *	Description:
 *	1.每次从 pListB 中取出一个元素;
 *	2.根据取出的元素在 pListA 中进行查询;
 *	3.若 pListA 中不存在与其值相同的元素，则将该元素插入 pListA 尾部;
 *	4.重复上述操作至 pListB 中所有元素查询完毕;
 *	
 *	Return:
 *	0:	数据线性表内容为空;
 *	!0:	函数返回处理后的线性表长度;
 */
UINT32 LinearListPurge(LINEAR_LIST_STR *pListA, LINEAR_LIST_STR *pListB)
{
	UINT32  i;

	if(0 == pListB->listLength)
	{
		return 0;
	}

	for(i=0; i<pListB->listLength; i++)
	{
		if(!ElementLocate(pListA, pListB->listElement[i]))
		{
			ElementInsert(pListA, pListA->listLength+1, pListB->listElement[i]);
		}
	}

	return pListA->listLength;
}


/*
 *	Param:
 *	pListA:	形参线性表指针;
 *	pListB:	形参线性表指针;
 *
 *	Description:
 *	1.依次对比两个线性表内同一位序的元素值
 *
 *	Return:
 *	-1:		pListA < pListB;
 *	0:		pListA == pListB;
 *	1:		pListA > pListB;
 */
int LinearCompare(LINEAR_LIST_STR *pListA, LINEAR_LIST_STR *pListB)
{
	int i = 0;
	
	if((0 == pListA->listLength) || (0 == pListB->listLength))
	{
		if(0 != pListB->listLength)
			return -1;
		else if(0 != pListA->listLength)
			return 1;
		else
			return 0;
	}

	while((i < pListA->listLength) && (i < pListB->listLength))
	{
		if(pListA->listElement[i] < pListB->listElement[i])
			return -1;
		else if(pListA->listElement[i] > pListB->listElement[i])
			return 1;

		i++;
	}

	if(pListA->listLength == pListB->listLength)
		return 0;
	else if(pListA->listLength < pListB->listLength)
		return -1;
	else
		return 1;
}


int LinearTest(void)
{
	int i;

	LINEAR_LIST_STR *pLa = NULL;
	LINEAR_LIST_STR **ppLa = &pLa;
	LINEAR_LIST_STR *pLb = NULL;
	LINEAR_LIST_STR **ppLb = &pLb;

	//	若内存动态分配失败，则函数退出;
	if(InitList(ppLa) || InitList(ppLb))
	{
		printf("Memory Location Failed!\n\r");
		return -1;
	}

	for(i=0; i<26; i++)
	{
		pLa->listElement[pLa->listLength++] = 'a'+i;		
		pLb->listElement[pLb->listLength++] = 'a'+i;
	}

	pLa->listElement[pLa->listLength++] = 'Q';
	//pLb->listElement[pLb->listLength++] = 'Q';

	printf("pListA(%d): ", pLa->listLength);
	for(i=0; i<pLa->listLength; i++)
	{
		printf("%c", pLa->listElement[i]);
	}
	printf("\n\r");

	printf("pListA(%d): ", pLb->listLength);
	for(i=0; i<pLb->listLength; i++)
	{
		printf("%c", pLb->listElement[i]);
	}
	printf("\n\r");

	switch(LinearCompare(pLa, pLb))
	{
		case -1:
			printf("ListA < ListB\n\r");
			break;
		case 0:
			printf("ListA == ListB\n\r");
			break;
		case 1:
			printf("ListA > ListB\n\r");
			break;
		default:
			break;
	}

	//	释放动态分配的内存并将原指向动态分配内存的指针赋值为空指针;
	DestroyList(ppLa);
	DestroyList(ppLb);

	return 0;
}











