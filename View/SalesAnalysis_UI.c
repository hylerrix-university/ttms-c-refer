/*
 * SalesAnalysis_UI.c
 *	专业水印测试！！！ 
 *  Created on: 2015年6月20日
 *      Author: 王力 
 */
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;
extern char message[100];
int saleflag=1;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_BoxOffice() {
	salesanalysis_list_t  list;
	salesanalysis_node_t  *pos;
	/*定义一个分页器*/
	Pagination_t pageing;
	/*初始化销售链表*/ 
	List_Init(list,salesanalysis_node_t);
	//设置分页大小
	pageing.totalRecords=Salesanalysis_Srv_StaticSale(list); 
	/*设置分页显示页面大小*/
	pageing.pageSize =SALESANALYSIS_PAGE_SIZE;  
	Salesanalysis_Srv_StaticSale(list);//统计销售数据，并构建销售分析链表
	printf("\n\t\t\t请选择相应操作\n");
	char choice;
	do{
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t[P] 显示上一页剧目票房排行信息\n");
		printf("\t\t\t[N] 显示下一页剧目票房排行信息\n");
		printf("\t\t\t[R] 退出\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择："); 
		fflush(stdin);
		choice=getchar();
		switch(choice){
			case 'P':
			case 'p':
			    break;
			case 'n':
			case 'N':
			    break;
			case 'r':
			case 'R':{
				choice='E';
				break;
			}
		}  
	}while(choice!='E');	
}

//显示售票员在给定日期区间的售票情况
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	float sale;
	account_t user;
	user.id=usrID;
	sale=Salesanalysis_Srv_CompSaleVal(usrID,stDate,endDate);
	Account_Srv_FetchByID(user.id,&user);
	printf("从%d-%d-%d到%d-%d-%d期间销售额为%d:\n",stDate.year,stDate.month,stDate.day,endDate.year,endDate.month,endDate.day,sale);
}
//销售分析入口函数，显示菜单，菜单包含"降序显示截止目前剧院电影票房排行榜"，“显示或查询当日售票员售票情况”，
//“查询给定日期区间某售票员售票情况”
void SalesAanalysis_UI_MgtEntry() {
	
	user_date_t stDate,endDate;
	account_t user; 
	char choice;
	do{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ  销售数据分析 ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		if(saleflag==1)
		{
			strcpy(message,"\n\t\t\t请选择。"); 
			puts(message);
			saleflag++;
		}
		else
		    puts(message);
		printf("\n\t\t\t[B] 剧目票房排行榜\n");
		printf("\t\t\t[D] 查询员工在给定日期区间销售额情况\n");
		printf("\t\t\t[S] 查询员工在给定日期区间售票情况\n");
		printf("\t\t\t[R] 返回\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		/*刷新输入缓冲区*/
		fflush(stdin);
		scanf("%c",&choice);
		switch(choice)
		{
			case 'B': 
			case 'b':
				SalesAnalysis_UI_BoxOffice();
				break;
			case 'D':
			case 'd':
				if(gl_CurUser.type==USR_CLERK)
					SalesAnalysis_UI_StatSale(gl_CurUser.id,stDate,endDate);//参数 
				else
 					{
 						printf("\t\t\t请输入售票员姓名：");
 						fflush(stdin);
 						char UsrName[100];
						scanf("%s",UsrName);		
						if(!Account_Srv_FetchByName(UsrName,&user))
							strcpy(message,"\n\t\t\t该售票员不存在。\n");
						else
							SalesAnalysis_UI_StatSale(user.id,stDate,endDate);//参数
					}
				break;
			case 'S':
			case 's':
				if(gl_CurUser.type==USR_MANG)
				{
					char UsrName[100];
					printf("请输入售票员姓名：\n");
					scanf("%s",UsrName);
						/*刷新输入缓冲区*/ 
						fflush(stdin);
					if(!Account_Srv_FetchByName(UsrName,&user))
						printf("用户名不存在!!\n");
					else
					{
						printf("\t\t\t请输入剧目上映时间(格式为:年-月-日):");
						fflush(stdin);
						scanf("%d-%d-%d",&stDate.year,&stDate.month,&stDate.day);
						printf("\t\t\t请输入剧目上映时间(格式为:年-月-日):");
						fflush(stdin);
						while(scanf("%d-%d-%d",&endDate.year,&endDate.month,&endDate.day))
						{
							printf("\t\t\t您输入的格式有错误，请按照 年-月-日 来填写。");
							printf("\t\t\t请重新输入上映时间：");
						}
						SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					}
				}
				else
				{
					printf("\n\t\t\t您需要更高的权限才能进行此操作!\n"); 
					break;
				}
			default:
				strcpy(message,"\n\t\t\t您的输入有误，请重新选择。");
				break; 
		 } 
	}while(choice!='R' && choice!='r' );
}



