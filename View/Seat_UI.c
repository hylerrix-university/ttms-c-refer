/*
 *  Seat_UI.c
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */
#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include <stdio.h>
#include <string.h>

extern char message[100];

//根据状态返回对应表示状态符号
inline char Seat_UI_Status2Char(seat_status_t status) {

	char statusChar;
	switch (status) {
		case SEAT_GOOD:		//有座位
			statusChar = '#';
			break;
		case SEAT_BROKEN:	//损坏的座位
			statusChar = '~';
			break;
		case SEAT_NONE:
		default:
			statusChar = ' ';
			break;
	}
	return statusChar;
}

//根据状态符号返回桌位状态
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t status;
	switch (statusChar) {
	case '#':		//有座位
		status = SEAT_GOOD;
		break;
	case '~':	//损坏的座位
		status = SEAT_BROKEN;
		break;
	default:
		status = SEAT_NONE;
		break;
	}
	return status;
}

void Seat_UI_MgtEntry(int roomID) {
	int i, j;
	char choice;
	int seatCount;
	int enterflag; 
	int changedCount = 0;
	studio_t studioRec;
	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {  //获得对应id放映厅的信息
	    strcpy(message,"\n\t\t\t该演出厅并不存在！");
		getchar();
		return;
	}
	seat_list_t list;
	seat_node_t *p;
	List_Init(list, seat_node_t);
	//选择放映厅的所有座位
	seatCount = Seat_Srv_FetchByRoomID(list, roomID);
	if (!seatCount) {		//若放映厅还没有设置座位，则自动生成座位
		seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,
				studioRec.colsCount);
		//修改演出厅里的座位数量
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);
	}
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   演出厅 ID: %2d ぷぷぷぷぷぷぷぷぷぷ╬\n",roomID);
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\t\t\t===============================================================\n");
		printf("\n\t\t\t总共有%d行。\n",studioRec.rowsCount);
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//显示数据
		for (i = 1; i <= studioRec.rowsCount; i++) {
			j = 1;
		    enterflag=1;
			printf("\t\t\t行%2d:%c", i, ' ');
			List_ForEach(list,p)
			{
				if (p->data.row == i) {
					while (p->data.column != j) {
						printf("%3c", ' ');
						j++;
					}
					printf("%-2c", Seat_UI_Status2Char(p->data.status));
					if(enterflag%29==0)
					    printf("\n\t\t\t      ");
					enterflag++;
					j++;
				}
			}
			printf("\n");
		}
		printf("\n\t\t\t[A]增加座位|[D]删除座位|[U]更新座位|[R]返回");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'a':
		case 'A':
			changedCount = Seat_UI_Add(list, roomID, studioRec.rowsCount,
					studioRec.colsCount);
			if (changedCount > 0) {
				seatCount += changedCount;
				//修改演出厅里的座位数量
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'd':
		case 'D':
			changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
					studioRec.colsCount);
			if (changedCount > 0) {
				seatCount -= changedCount;
				//修改演出厅里的座位数量
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'u':
		case 'U':
			Seat_UI_Modify(list, studioRec.rowsCount, studioRec.colsCount);
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(list, seat_node_t);
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //输入一个座位
	seat_t rec;
	seat_node_t *p;
	int newRecCount = 0;
	char choice;
	char ch;
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ  添加新座位 ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\n\n"); 
		do {
			printf("\n\t\t\t座位行数不应该超过 %2d 并且 座位列数不应该超过 %2d。\n",row, column);
			printf("\n\t\t\t座位行数：");
			while(scanf("%d", &(rec.row))!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			printf("\t\t\t座位列数：");
			while(scanf("%d", &(rec.column))!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			fflush(stdin);
		} while (rec.row > row || rec.column > column);
		p = Seat_Srv_FindByRowCol(list, rec.row, rec.column);
		if (p) {						//若输入的行列号所对应的座位已存在，则不能插入
			strcpy(message,"\t\t\t该座位已经存在！\n");
			break;
		}
		rec.id = EntKey_Srv_CompNewKey("Seat");		//设置座位id
		rec.roomID = roomID;
		rec.status = SEAT_GOOD;    //插入的新座位的状态默认为好座位
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		if (Seat_Srv_Add(&rec)) {
			newRecCount++;
			printf("\t\t\t新座位增添成功！\n");
			p = (seat_node_t*) malloc(sizeof(seat_node_t));
			p->data = rec;
			Seat_Srv_AddToSoftedList(list, p); //若增加了新座位，需更新list
		} else
			printf("\t\t\t新座位增添失败！\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]增添更多座位|[R]返回\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Seat_UI_Modify(seat_list_t list, int row, int column) {
	int rtn = 0;
	int newrow, newcolumn;
	char choice;
	char ch;
	seat_node_t *p;
    system("cls");
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   更新座位  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	printf("\n\n\n"); 
	do {
		do {				//更新的座位行列信息不能超出放映厅的行列数
			printf("\n"); 
			printf("\t\t\t座位行数不应该超过 %2d 并且 座位列数不应该超过 %2d！\n",row, column);
			printf("\t\t\t座位行数：");
			scanf("%d", &newrow);
			printf("\t\t\t座位列数：");
			scanf("%d", &newcolumn);
		} while (newrow > row || newcolumn > column);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			printf("\t\t\t座位[%d,%d]状态为：[%c]。\n", newrow, newcolumn,Seat_UI_Status2Char(p->data.status));
			printf("\t\t\t请输入新的状态(#/~/ )："); 
			fflush(stdin);
			p->data.status = Seat_UI_Char2Status(getchar());
			fflush(stdin);
			printf("\n\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			if (Seat_Srv_Modify(&(p->data))) {
				rtn = 1;
				printf("\n\t\t\t座位更新成功！\n");
			} else
				printf("\n\t\t\t座位更新失败！!\n");
		} else
			printf("\n\t\t\t该座位并不存在！\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[U]更新更多座位|[R]返回\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
	} while ('u' == choice || 'U' == choice);
	return rtn;
}

int Seat_UI_Delete(seat_list_t list, int row, int column) {

	int delSeatCount = 0;
	int newrow, newcolumn;
	seat_node_t *p;
	char choice;
	char ch;
	int i=1;

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   删除座位  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t正在删除第%-2d个座位\n",i); 
		do {
			fflush(stdin);
			printf("\n\t\t\t座位行数不应该超过 %2d 并且 座位列数不应该超过 %2d。\n",row, column);
			printf("\t\t\t座位行数：");
			while(scanf("%d", &(newrow))!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			printf("\t\t\t座位列数：");
			while(scanf("%d", &(newcolumn))!=1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while((ch=getchar())!='\n')
				    continue; 
			}
			fflush(stdin);
		} while (newrow > row || newcolumn > column);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p)
		{
			printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			if (Seat_Srv_DeleteByID(p->data.id))
			{
				printf("\n\t\t\t座位删除成功！\n");
				delSeatCount++;
				List_FreeNode(p);	//释放结点座位结点p
			}
		}
		else
		{
			printf("\t\t\t该座位并不存在！\n");
		}
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[D]删除更多座位|[R]返回\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		i++	;
	} while ('d' == choice || 'D' == choice);
	return delSeatCount;
}

