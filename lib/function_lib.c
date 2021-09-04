/*
********************************************************************************************
*	FileName:	function_lib.c
*	Author:		Liam.Nurx
*	Update:		2021.05
*	
*	Description:
*	
********************************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "function_lib.h"

/*
 *	Description:
 *	1.难易程度:				简单;	
 *	2.算法复杂度为:			O(n^2);
 *	3.改进:
 *						哈希表;
 */
int* TwoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int i;
	int j;

	for(i=0; i<numsSize; i++)
	{		
		for(j=i+1; j<numsSize; j++)					//	同一元素不再重复比较;
		{
			if(target == *(nums + i) + *(nums +j))
			{
				*(returnSize + 0) = i;
				*(returnSize + 1) = j;

				return returnSize;					//	找到第一组答案时函数返回;
			}
		}
	}

	return returnSize;								//	无结果时的返回;
}

void TwoSumTest(void)
{
	int numArr[4] = {11, 4, 2, 5};
	int *pRetn = NULL;

	pRetn = (int *)malloc(sizeof(int)*2);			//	动态分配结果下标数组内存;
	memset(pRetn, 0, sizeof(int)*2);				//	清零新开辟内存;

	TwoSum(numArr, 4, 9, pRetn);
	printf("Result is:\n\r%d    %d\n\r", pRetn[0], pRetn[1]);
	free(pRetn);									//	释放动态内存;
}











