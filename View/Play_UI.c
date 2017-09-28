/*
* File name:  Play_UI.c
* File ID:	  TTMS_SSF_Play_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Play_UI.h"
#include "Schedule_UI.h"

#include "../Common/list.h"
#include "../Service/play.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Play_UI_ShowList(play_list_t list, Pagination_t paging);
void Play_UI_MgtEntry(int flag);
int Play_UI_Add(void);
int Play_UI_Modify(int id);
int Play_UI_Delete(int id);
int Play_UI_Query(int id);
 
	/*
	 * Function:    Play_UI_ShowList
	 * Function ID:	TTMS_SCU_Play_UI_Show
	 * Description: 以列表模式显示剧目信息
	 * Input:       list剧目信息链表的头指针，paging分页设置参数
	 * Output:      所有剧目的信息
	 * Return:      返回查找到的记录数目
	 */

static void ShowListByPage(play_node_t *list,int listSize)
{
	int pageSize=5,i;
	Pagination_t paging;
	play_node_t *p;
	char choice;
	paging.pageSize=pageSize;
	paging.totalRecords=listSize;
	Paging_Locate_FirstPage(list,paging);
	do{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   剧目信息  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\n\n\n");
		printf("\t\t\t%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n","剧目ID号","剧目名称","剧目类型","剧目来源地","剧目级别","演出时间(分钟)","上映日期","结束日期","票价");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("%5d%32s%8s%10s%3s%7s%13s%13s%5s\n",p->data.id,p->data.name,p->data.type,p->data.area,p->data.rating,p->data.duration,p->data.start_date,p->data.end_date,p->data.price);
		printf("--Total Records:%2d---------Page%2d/%2d--\n\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[F]第一页|[p]上一页|[N]下一页|[L]最后一页|[e]退出\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("请输入选项：");
		fflush(stdin);
		scanf("%c",&choice);
		switch(choice)
		{
			case 'f':
			case 'F':
				Paging_Locate_FirstPage(list,paging);
				break;
			case 'p':
			case 'P':
	            if(1<Pageing_CurPage(paging))
				{
		    		Paging_Locate_OffsetPage(list,paging,-1,play_node_t);
		    	}
	    		break;	
			case 'n':   
			case 'N':
				if(Pageing_TotalPages(paging)>Pageing_CurPage(paging))
				{
					Paging_Locate_OffsetPage(list,paging,-1,play_node_t);
				}
				break;
			case 'l':
			case 'L':
				Paging_Locate_LastPage(list,paging,play_node_t);
				break;
		}
	}while(choice!='e'&&choice!='E'); 
}
int CreateList_Head(play_list_t list){
		int i=0;
		play_node_t*p;
		for(i =0;i<100;i++)
		{
			p = (play_node_t*)malloc(sizeof(play_node_t));
			if(!p)
				break;
			List_AddHead(list,p);
		} 
		return i;
	}
void Play_UI_ShowList(play_list_t list,Pagination_t paging){
	int size;
	ShowListByPage(list,size);
}

/*
 * Function:    Play_UI_MgtEntry
 * Function ID:	TTMS_SCU_Play_UI_MgtEnt
 * Description: 剧目信息管理界面
 * Input:       flag为0，进入管理页面，flag为1进入查询界面
 * Output:      剧目管理界面
 * Return:      无
 */
void Play_UI_MgtEntry(int flag)
{
	int i,j,fg;
	play_list_t list;
	Pagination_t paging;
	char ch;
	switch(flag)
	{
		case 0:
			system("cls");
			printf("\n\n\n");
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   管理剧目  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
			printf("\n\n\n");
			printf("\t\t\t[A] 添加剧目\n");
			printf("\t\t\t[U] 修改剧目\n");
			printf("\t\t\t[D] 删除剧目\n");
			printf("\t\t\t[M] 演出计划管理\n");
			printf("\t\t\t[其他] 返回\n");
			printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			printf("\n\t\t\t请输入选项：");
			fflush(stdin);
			scanf("%c",&ch);
			toupper(ch);
			switch(ch)
			{
				case 'A':
				case 'a':
					Play_UI_Add();
					break;
				case 'U':
				case 'u':
					printf("\t\t\t请输入要修改的剧目编号:");
					while(scanf("%d",&j)!=1)
					{
						printf("\t\t\t您输入的不是数字\n");
						printf("\t\t\t请重新输入：");
						while((ch=getchar())!='\n')
						    continue; 
					}
					Play_UI_Modify(j);
					break;
				case 'D':
				case 'd':
					printf("\t\t\t请输入要删除的剧目编号:");
					while(scanf("%d",&j)!=1)
					{
						printf("\t\t\t您输入的不是数字\n");
						printf("\t\t\t请重新输入：");
						while((ch=getchar())!='\n')
						    continue; 
					}
					Play_UI_Delete(j);
					break;
				case 'M':
				case 'm':
					printf("\t\t\t请输入要查询的演出计划ID：");
					while(scanf("%d",&j)!=1)
					{
						printf("\t\t\t您输入的不是数字\n");
						printf("\t\t\t请重新输入：");
						while((ch=getchar())!='\n')
						    continue; 
					}
					Schedule_UI_MgtEntry(j);
					break;
				default:
					Main_Menu();
					break;
			}
			Play_UI_MgtEntry(0);
			break;
		case 1:
			system("cls");
			printf("\n\n\n");
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   查询剧目  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
			printf("\n\n\n");
			printf("\t\t\t该功能尚未实现\n");
			printf("\t\t\t请输入要查询的剧目编号:");
			while(scanf("%d",&j)!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue;
			}
			Main_Menu();
//			Play_UI_Query(j);
	        break;
	    default:
	        break;
	}
	Main_Menu();
}


/*
 * Function:    Play_UI_Add
 * Function ID:	TTMS_SCU_Play_UI_Add
 * Description: 添加一条剧目信息
 * Input:       无
 * Output:      输入信息时的各种提示
 * Return:      添加的记录数
 */
int Play_UI_Add(void)
{
	play_t rec;
	int i= 0,temp;
	char ch,choice;
    system("cls");
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   添加剧目  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\n\t\t\t正在添加第%d个剧目\n\n",i+1);
		printf("\t\t\t信息ID号:");
		fflush(stdin);
		while(scanf("%d", &(rec.id))!=1)
		{
			printf("\t\t\t您输入的不是数字\n");
			printf("\t\t\t请重新输入：");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t剧目名称:");
		scanf("%s",rec.name);
		printf("\t\t\t剧目类型:");
		scanf("%s",&temp);
		rec.type=(play_type_t)(temp);
		printf("\t\t\t剧目来源地:");
		scanf("%s",rec.area);
		printf("\t\t\t剧目级别:");
		scanf("%s",&temp);
		rec.rating=(play_rating_t)(temp);
		printf("\t\t\t演出时间(分钟):");
		while(scanf("%d",&rec.duration)!=1)
		{
			printf("\t\t\t您输入的不是数字\n");
			printf("\t\t\t请重新输入：");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t上映日期:");
		scanf("%s",rec.start_date);
		printf("\t\t\t结束日期:");
		scanf("%s",rec.end_date);
		printf("\t\t\t票价:");
		scanf("%s",&rec.price);
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");

		//获取主键
		rec.id = EntKey_Srv_CompNewKey("play");

		if (Play_Srv_Add(&rec)!=0)
		{
			i += 1;
			printf("\t\t\t添加成功!");
		}
		else
		printf("\t\t\t添加失败!");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]添加更多|[其它]返回\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		scanf("%c",&choice);
	} while ('A' == choice || 'a' == choice);
	return i;
}

	
/*
 * Function:    Play_UI_Modify
 * Function ID:	TTMS_SCU_Play_UI_Mod
 * Description: 更新剧目信息
 * Input:       待更新的剧目ID号
 * Output:      输入信息时的各种提示
 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
 */
int Play_UI_Modify(int id){
	play_t rec;
	int rtn = 0,i,temp;
	play_list_t list;
	int seatcount;
	play_t *re;
    system("cls");
	/*Load record*/
	if (Play_Srv_FetchByID(id, &rec)!=1) {
		printf("剧目不存在!\n");
		return 0;
	}
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   剧目信息  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	printf("\n\n\n");
	printf("%-5s%-32s%-8s%-10s%-3s%-7s%-13s%-13s%-5s\n","1","2","3","4","5","6","7","8","9");
	printf("\t\t\t%10s%10s%10s%10s%10s%10s%10s%10s%10s\n","信息ID号","剧目名称","剧目类型","剧目来源地","剧目级别","演出时间(分钟)","上映日期","结束日期","票价");
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("%5d%32s%8s%10s%3s%7s%13s%13s%5s\n",rec.id,rec.name,rec.type,rec.area,rec.rating,rec.duration,rec.start_date,rec.end_date,rec.price);
	fflush(stdin);
	scanf("请输入需要修改的选项(输入0退出)：%d",&i);
	do{
		switch(i)
		{
			case 1:printf("信息ID号:");
				scanf("%d", &(rec.id));
				break;
			case 2:	printf("剧目名称:");
				scanf("%s",rec.name);
				break;	
			case 3:printf("剧目类型:");
				scanf("%s",&temp);
				rec.type=(play_type_t)(temp);
				break;
			case 4:	printf("剧目来源地:");
				scanf("%s",rec.area);
				break;
			case 5:printf("剧目级别:");
				scanf("%s",&temp);
				rec.rating=(play_rating_t)(temp);
				break;	
			case 6:printf("演出时间(分钟):");
				scanf("%s",&rec.duration);
				break;	
			case 7:	printf("上映日期:");
				scanf("%s",rec.start_date);
				break;
			case 8:printf("结束日期:");
				scanf("%s",rec.end_date);
				break;
			case 9:	printf("票价:");
				scanf("%s",&rec.price);
				break;
		}
	}while((scanf("请输入需要修改的选项(输入0退出)：%d",&i))!=0);
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	if (Play_Srv_Modify(&rec)) 
	{
		rtn = 1;
		printf("添加失败\n");
	}
	else
		printf("添加成功\n");
	return rtn;
}


/*
 * Function:    Play_UI_Delete
 * Function ID:	TTMS_SCU_Play_UI_Del
 * Description: 按照ID号删除剧目信息
 * Input:       待删除的剧目ID号
 * Output:      提示删除是否成功
 * Return:      0表示删除失败，1表示删除成功
 */
int Play_UI_Delete(int id){
	int rtn = 0;
    system("cls");
	if(Play_Srv_DeleteByID(id)==1){
		printf("删除成功，按任意键返回!\n");
		rtn = 1;
	}
	 else {
		printf("该剧目不存在，按任意键返回!\n");
	}

	getchar();
	return rtn;

}

/*
 * Function:    Play_UI_Query
 * Function ID:	TTMS_SCU_Play_UI_Qry
 * Description: 按照ID号查询剧目信息
 * Input:       待查找的剧目ID号
 * Output:      查找到的剧目信息
 * Return:      0表示未找到，1表示找到了
 */
int Play_UI_Query(int id){
	
	return 0;
}
