/*
 * salesanalysis.c
 *	水印测试 
 *  Created on: 2015年6月21日
 *      Author: 王力 
 */
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/SalesAnalysis_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/list.h"

//计算员工usrID在给定时间区间的销售额，返回销售额
inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){
	int amount=0;
	/*定义sale_list_t类型链表saleList*/
	sale_list_t saleList;
	/*定义sale_node_t指针变量pSale*/
	sale_node_t *pSale;
	/*对saleList链表进行初始化*/
	List_Init(saleList,sale_node_t);
	/*根据id载入匹配的销售信息，构建saleList链表*/
	Sale_Perst_SelectByUsrID(saleList, usrID,stDate,endDate); 
	List_ForEach(saleList,pSale)
	{
		/*累加销售额*/ 
		amount+=pSale->data.value;
	}
	/*删除链表释放内存*/
	List_Destroy(saleList,sale_node_t); 
	return amount; 
}

//结合剧目Play.dat,统计销售数据，构建销售分析salesanalysis_list_t list链表，返回list链表长度
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list)
{
	int count = 0;
	assert(NULL!=list);
	play_list_t playList,pos;
	salesanalysis_node_t *newNode;
	int sold,total;
	//载入剧目列表
	List_Free(list,salesanalysis_node_t);
	/*链表初始化*/ 
	List_Init(playList,play_node_t);
	/*构建链表获得所有信息*/ 
	Play_Srv_FetchAll(playList);
	/*循环遍历*/ 
	List_ForEach(playList,pos)
	{
		printf("\t\t\t剧目 ID:%s\n",pos->data.name);
		newNode = (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
		if(!newNode)
		{
			printf("\t\t\t内存分配失败!!\n");
			break;
		}
		newNode->data.play_id = pos->data.id;
		strcpy(newNode->data.name,pos->data.name);
		strcpy(newNode->data.area,pos->data.area);
		newNode->data.duration = pos->data.duration;
		newNode->data.start_date = pos->data.start_date;
		newNode->data.end_date	= pos->data.end_date;
		newNode->data.price = pos->data.price;
		newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold,&total);
		newNode->data.totaltickets = sold;
		List_AddTail(list,newNode);
		count++;
	}
	/*删除链表，释放内存*/ 
	List_Destroy(playList,play_node_t);
	printf("\t\t\t操作已完成！\n");
	/*返回结点个数*/ 
	return count;
}

//对剧院电影票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){
}


