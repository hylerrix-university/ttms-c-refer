#include "Sale_Persist.h"
#include "../Common/list.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

int Sale_Perst_Insert(const sale_t *data) {
	
	return 0;
}


int Sale_Perst_DeleteByID(int saleID) {
	

	return 0;
}

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate,
		user_date_t endDate) {

	
	return 0;
}


//根据给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate,
		user_date_t endDate) {

	
	return 0;
}

/*

//queryUid = null,query all the uid Sale information return the all uid Sale information number
//queryUid =  uid, query the uid Sale information return the uid Sale  number
 *
int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head)
{

	return 0;
}

int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
{

	
	return 0;
}

//根据票的id获得票的基本信息 
int Select_Price_By_Playid(int id, ticket_t *buf)
{
	
		return 0;
}
*/



//#include "Sale_Persist.h"
//#include "../Common/list.h"
//#include "../Service/Sale.h"
//#include <stdio.h>
//#include<unistd.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//static const char SALE_DATA_FILE[] = "Sale.dat";
//static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";
//
//int Sale_Perst_Insert(const sale_t *data) {
//	FILE *fp;
//	int found=0;  
//	assert(NULL!=data);
//	fp = fopen(SALE_DATA_FILE, "ab");
//	int rtn = 0;
//	if (fp == NULL) {
//		printf("Cannot open file %s!\n", SALE_DATA_FILE);
//		return 0;
//	}
//
//	rtn = fwrite(data, sizeof(sale_t), 1, fp);
//
//	fclose(fp);
//	return rtn;
//}
//
//
//int Sale_Perst_DeleteByID(int saleID) {
//	FILE *fp,*fp1;
//	sale_t buf;
//	if(rename(SALE_DATA_FILE, SALE_DATA_TEMP_FILE)<0){
//		printf("Cannot open file %s!\n", SALE_DATA_FILE);
//		return 0;	
//	}
//	else{
//		fp=fopen(SALE_DATE_FILE,"wb");
//		fp1=fopen(SALE_DATE_FILE,"rb");
//		if(fp==NULL){
//			printf("Cannot open file %s!\n", SALE_DATA_FILE);
//			getchar();
//			return 0;
//		}
//		if(fp1==NULL){
//			printf("Cannot open file %s!\n", SALE_DATA_FILE);
//			getchar();
//			return 0;
//		}
//		while (!feof(fp)) {
//		if (fread(&buf, sizeof(studio_t), 1, fp1)) {
//			if (buf.id == ID) {
//				found = 1;
//				continue; 
//			}
//			else  {
//				fwrite(&buf, sizeof(sale_t), 1, fp);
//			} 
//		}		
//	}
//		fclose(fpTarg);
//		fclose(fpSour);
//			//删除临时文件
//	remove(SALE_DATA_TEMP_FILE);
//	return found;		
//	}
//}
//
////根据用户ID载入给定时间区间内的销售记录
//int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate,
//		user_date_t endDate) {
//		FILE *fp;
//		fp=fopen(SALE_DATE_FILE,"rb");
//		if(fp==NULL){
//			printf("Cannot open file %s!\n", SALE_DATA_FILE);
//			getchar();
//			return 0;
//		}
//		sale_t saleRec;
//		int recCount=0;
//		sale_node_t *newNode; 
//		
//		while (!feof(fp)) {
//		if (fread(&saleRec, sizeof(sale_t), 1, fp)) {
//			if (  saleRec.date>=user_date_t stDate  && saleRec.date<=user_date_t endDate) {
//				newNode = (studio_node_t*) malloc(sizeof(studio_node_t));
//				newNode=saleRec;
//				list_ADDTail(newNode);
//				recCount++;
//			}
//		}
//	}
//	fclose(fp);
//	return recCount;
//}
//
//
////根据给定时间区间内的销售记录
//int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate,
//		user_date_t endDate) {
//		FILE *fp;
//		fp=fopen(SALE_DATE_FILE,"rb");
//		if(fp==NULL){
//			printf("Cannot open file %s!\n", SALE_DATA_FILE);
//			getchar();
//			return 0;
//		}
//		sale_t saleRec;
//		int recCount=0;
//		sale_node_t *newNode; 
//		
//		while (!feof(fp)) {
//		if (fread(&saleRec, sizeof(sale_t), 1, fp)) {
//			if (usrID == saleRec.user_id &&  saleRec.date>=user_date_t stDate  
//						&& saleRec.date<=user_date_t endDate) {
//				newNode = (studio_node_t*) malloc(sizeof(studio_node_t));
//				newNode=saleRec;
//				list_ADDTail(newNode);
//				recCount++;
//			}
//		}
//	}
//	fclose(fp);
//	return recCount;	
//
//	
//	return 0;
//}
//
///*
//
////queryUid = null,query all the uid Sale information return the all uid Sale information number
////queryUid =  uid, query the uid Sale information return the uid Sale  number
// *
//int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head)
//{
//
//	return 0;
//}
//
//int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
//{
//
//	
//	return 0;
//}
//
////根据票的id获得票的基本信息 
//int Select_Price_By_Playid(int id, ticket_t *buf)
//{
//	
//		return 0;
//}
//*/

