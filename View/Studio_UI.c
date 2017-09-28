/*
 * Studio_UI.c
 *
 *  Created on: 2015年4月24日
 *      Author: Administrator
 */
#include "Studio_UI.h"

#include "../Common/list.h"
#include "../Service/studio.h"
#include "../Service/seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.h"

static const int STUDIO_PAGE_SIZE = 5;

int studioflag=1;
extern char message[100];

#include <stdio.h>
#include <string.h>

void Studio_UI_MgtEntry(void) {
	int i, id, r;
	char choice;
	char ch; 

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   演出厅信息  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		if(studioflag==1)
		{
			strcpy(message,"\n\t\t\t演出厅信息如下。");
			puts(message);
			studioflag++;
		}
		else
		    puts(message);
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\tID   演出厅名                座位行数     座位列数     座位总数\n"); 
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//显示数据
		for (i = 0, pos = (studio_node_t *) (paging.curPos);
				pos != head && i < paging.pageSize; i++) {
			printf("\t\t\t%-5d%-24s%-13d%-13d%-8d\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
			pos = pos->next;
		}
		printf("\n\t\t\t------- 总共%2d条记录 ------------- 页数： %2d/%2d ---------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[P]上一页|[N]下一页|[A]添加|[D]删除|[U]更新|[S]座位信息|[R]返回\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'a':	
		case 'A':
			if (r=Studio_UI_Add()) //新，跳到最后一页显示
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
				sprintf(message,"\n\t\t\t成功添加了%2d个演出厅。",r);
			}
			break;
		case 'd':
		case 'D':
			printf("\t\t\t请输入演出厅ID：");
			while(scanf("%d",&id)!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			if(Studio_UI_Delete(id))
			{	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
				sprintf(message,"\n\t\t\t成功删除第%2d号演出厅。",id);
			}
			else
			{
				strcpy(message,"\n\t\t\t该演出厅并不存在。");
			}
			break;
		case 'u':
		case 'U':
			printf("\t\t\t请输入演出厅ID：");
			while(scanf("%d",&id)!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			if (Studio_UI_Modify(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
				strcpy(message,"\n\t\t\t修改演出厅成功。");
			}
			else
			    strcpy(message,"\n\t\t\t该演出厅并不存在。");
			break;
		case 's':
		case 'S':
			printf("\t\t\t请输入演出厅ID：");
			while(scanf("%d",&id)!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void) {
	studio_t rec;
	int i=1;
	int newRecCount = 0;
	char choice;
	char ch;

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	    printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   新增演出厅  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
	    printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\n\t\t\t请输入第%d个演出厅。\n\n",i++);
		printf("\t\t\t演出厅名：");
		fflush(stdin);
		gets(rec.name);
		printf("\t\t\t演出厅座位行数：");
		while(scanf("%d",&(rec.rowsCount))!=1)
		{
			printf("\t\t\t您输入的不是数字\n");
			printf("\t\t\t请重新输入：");
			while((ch=getchar())!='\n')
			    continue; 
		}
		printf("\t\t\t演出厅座位列数：");
		while(scanf("%d",&(rec.colsCount))!=1)
		{
			printf("\t\t\t您输入的不是数字\n");
			printf("\t\t\t请重新输入：");
			while((ch=getchar())!='\n')
			    continue; 
		}
		rec.seatsCount = rec.rowsCount * rec.colsCount;
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		//获取主键
		rec.id = EntKey_Srv_CompNewKey("Studio");
		if (Studio_Srv_Add(&rec))
		{
			newRecCount += 1;
			printf("\t\t\t演出厅添加成功！\n");
		}
		else
			printf("\t\t\t演出厅添加失败！\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]添加更多|[R]返回\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		fflush(stdin);
		printf("\n\t\t\t请输入您的选择："); 
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;
	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		return 0;
	}
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   更新演出厅  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	printf("\n\t\t\t演出厅ID--%d\n", rec.id);
	printf("\n\t\t\t演出厅名--[%s]:", rec.name);
	fflush(stdin);
	gets(rec.name);
	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if(seatcount){
		do{			//如果座位文件中已有座位信息，则更新的行列必须比以前大，否则不允许更改
			printf("\n\t\t\t座位行数必须 >= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("\n\t\t\t座位列数必须 >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		}while(	newrow<rec.rowsCount||newcolumn<rec.colsCount);
		rec.rowsCount=newrow;
		rec.colsCount=newcolumn;
		rec.seatsCount=seatcount;
	}
	else{
		printf("\t\t\t座位行数：");
		scanf("%d", &rec.rowsCount);
		printf("\t\t\t座位列数：");
		scanf("%d", &rec.colsCount);
		rec.seatsCount=0;
	}

	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");

	if (Studio_Srv_Modify(&rec))
	{
		rtn = 1;
	}
	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {
	int rtn = 0;
	if (Studio_Srv_DeleteByID(id))
	{
		//在删除放映厅时，同时根据放映厅id删除座位文件中的座位
		Seat_Srv_DeleteAllByRoomID(id); 
		rtn = 1;
	}
	getchar();
	return rtn;
}

