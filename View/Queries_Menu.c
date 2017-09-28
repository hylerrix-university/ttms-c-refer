#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "Account_UI.h"
#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"

extern char message[100];
extern account_t gl_CurUser; 

int queriesflag=1;

void Queries_Menu(void){
	char choice;
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷぷ   信息查询  ぷぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		if(queriesflag==1)
		{
			switch(gl_CurUser.type)
			{
				case 0:
					strcpy(message,"\n\t\t\t匿名用户,您好。");
					break;
				case 1:
				    strcpy(message,"\n\t\t\t销售员,您好。");
				    break;
				case 2:
					strcpy(message,"\n\t\t\t经理,您好。");
					break;
				case 9:
					strcpy(message,"\n\t\t\t系统管理员,您好。");
					break;
				default:
				    strcpy(message,"\n\t\t\t您好。");
				    break;
			}
		    strcat(message,"欢迎使用用户账号管理模块。");
		    puts(message);
		    queriesflag++;
		}
		else
	    	puts(message);
		printf("\t\t\t[S]查询演出厅\n");
		printf("\t\t\t[P]查询剧目\n");
		printf("\t\t\t[T]查询票\n");
		printf("\t\t\t[C]查询演出计划\n");
		printf("\t\t\t[R]返回上一层\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's'://Studio_query;
		    Studio_UI_MgtEntry();
		    queriesflag--;
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			queriesflag--;
			break;
		case 'T':
		case 't': //Ticket_query;
		    strcpy(message,"\n\t\t\t查询票模块尚未开通");
		    Queries_Menu();
			break;
		case 'C':
		case 'c':
			Schedule_UI_ListAll();
			strcpy(message,"\n\t\t\t查询演出计划尚未开通");
		    Queries_Menu();
			break;
		}
	} while ('R' != choice && 'r' != choice);
	}
