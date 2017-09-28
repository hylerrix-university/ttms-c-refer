/*
 * salesanalysisPersist.c
 *	专业打水印！！！！ 
 *  Created on: 2015年6月21日
 *      Author: 王力 
 */

#include "../Persistence/EntityKey_Persist.h"
#include "../Service/play.h"
#include "../Service/Sale.h"
#include "../Service/salesanalysis.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//static const char PLAY_DATA_FILE[] = "play.dat";
static const char SALE_DATA_FILE[] = "sale.dat";
static const char SALESANALYSIS_DATA_FILE[] = "salesanalysis.dat";

//将一条salesanalysis记录（*data）写入salesanalysis.dat文件；成功return 1，否则return 0
int Salesanalysis_Perst_Insert(const salesanalysis_t *data) {
//	salesanalysis_t *temp = NULL;
	FILE *output;
	if(0==data->play_id)
	{
		printf("无记录数据!\n");
		return 0;
	}
	if((output=fopen("salesanalysis.dat","ab"))==NULL) 
	{
		printf("打开文件失败！！\n");
		return 0;
	}
	else
	{
//		fprintf(output,"%d %s %s %d %ld %ld %d %d-%d-%d %d-%d-%d \n",data->play_id,data->name,data->area,data->duration,data->totaltickets,data->sales,data->price,data->start_date.year,data->start_date.month,data->start_date.day,data->end_date.year,data->end_date.month,data->end_date.day);
		fwrite(data,sizeof(salesanalysis_t),1,output);
		printf("\n写入成功！\n");
		return 1;
	}

}

//遍历读salesanalysis.dat文件建立销售分析（salesanalysis）链表
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list) {
	FILE *input;
	salesanalysis_t *temp;
	if((input=fopen("salesanalysis.dat","rb"))==NULL)
	{
		printf("打开文件失败！");
		return 0; 
	}
	else
	{
		/*录入学生信息*/
		
		
		return 1;
	}

}

//遍历读Sale.dat文件建立list（sale_list_t） 链表，返回链表list长度
int Sale_Perst_SelectAll(sale_list_t list) {
	FILE *input;
	if((input=fopen("Sale.dat","rb"))==NULL)
	{
		printf("文件不存在!\n");
		return 0;
	}
	return 1;
}

