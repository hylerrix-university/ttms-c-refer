#include <stdio.h>
#include <string.h>

#include "Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Queries_Menu.h"
#include "Account_UI.h"
#include "Sale_UI.h"
#include "SalesAnalysis_UI.h"

extern char message[100]; 
extern account_t gl_CurUser; 

int mainmenuflag=1;

void Main_Menu(void) {
	char choice;
	char ch;
	do {
		system("cls");
		printf("\n\n\n"); 
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷ   欢迎来到   X·票务管理系统  ぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		if(mainmenuflag==1)
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
		    mainmenuflag++;
		}
		else
	    	puts(message);
		printf("\n\t\t\t[S] 管理演出厅\n");
		printf("\t\t\t[P] 管理剧目\n");
		printf("\t\t\t[T] 售票\n");
		printf("\t\t\t[R] 退票\n");
		printf("\t\t\t[Q] 查询信息\n");
		printf("\t\t\t[N] 分析销售数据\n");
		printf("\t\t\t[A] 账号管理菜单\n"); 
		printf("\t\t\t[E] 注销\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t请输入您的选择：");
		fflush(stdin);
		choice = getchar();
		switch (choice)
		{
			case 'S':
			case 's':
				Studio_UI_MgtEntry();
				mainmenuflag--;
				break;
			case 'P':
			case 'p':
				Play_UI_MgtEntry(0);
				break;
			case 'Q':
			case 'q':
				Queries_Menu();
				mainmenuflag--;
				break;
			case 'T':
			case 't':
				Sale_UI_MgtEntry();
				strcpy(message,"\n\t\t\t售票功能尚未开通，尽情期待。");
				break;
			case 'R':
			case 'r':
				Sale_UI_ReturnTicket();
				strcpy(message,"\n\t\t\t退票功能尚未开通，尽情期待。");
				break;
			case 'N':
			case 'n':
				SalesAanalysis_UI_MgtEntry();
				break;
			case 'A':
			case 'a':
				Account_UI_MgtEntry();
				mainmenuflag--;
				break;
			case 'E':
			case 'e':
				printf("\n\t\t\t确定注销？[Y/y]确定[其它字母]取消：");
				fflush(stdin);
				scanf("%c",&ch);
				if(ch!='y')
				{
					strcpy(message,"\n\t\t\t注销失败"); 
					Main_Menu();
				    break;
				}
			    mainmenuflag--;
			    main();
			    break;
		}
	} while ('E' != choice && 'e' != choice);
}

