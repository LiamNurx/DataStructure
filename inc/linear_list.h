/*
********************************************************************************************
*	FileName:	linear_list.h
*	Author:		Liam.Nurx
*	Update:		2021.05
*	
*	Description:
*	
********************************************************************************************
*/

#ifndef			LINEAR_LIST_H
#define			LINEAR_LIST_H

#include "basetype.h"

#define			LINEAR_LIST_ELEMENT_MAX				1024

//	线性表结构体类型;
typedef	struct
{
	UINT32		listLength;									//	4 Bytes;
	UINT8		listElement[LINEAR_LIST_ELEMENT_MAX];		//	1024 Bytes;
}LINEAR_LIST_STR;											//	==> 1028 Bytes;


int InitList(LINEAR_LIST_STR **ppList);
void DestroyList(LINEAR_LIST_STR **ppList);
int IsListEmpty(LINEAR_LIST_STR *pList);
UINT32 GetListLength(LINEAR_LIST_STR *pList);
UINT32 ElementDelete(LINEAR_LIST_STR *pList, UINT32 n, UINT8 *pElement);
UINT32 ElementLocate(LINEAR_LIST_STR *pList, UINT8 element);
UINT32 ElementInsert(LINEAR_LIST_STR *pList, UINT32 n, UINT8 element);
UINT32 LinearListUnion(LINEAR_LIST_STR *pLa, LINEAR_LIST_STR *pLb);
int LinearCompare(LINEAR_LIST_STR *pListA, LINEAR_LIST_STR *pListB);
int LinearTest(void);

#endif			//	End of LINEAR_LIST_H


















