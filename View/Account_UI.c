#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <conio.h>

#include "Account_UI.h"
#include "../Service/Account.h"
//#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include "Account_UI.h"
#define WRONGTIMES 3

account_node_t *pMain=NULL;

extern account_t gl_CurUser;
//extern account_t gl_Admin;
extern char message[100];

int menuflag=1;
int iCount;
int loginWrongTimes=0;

int SysLogin() {
	account_node_t *p;
    
	char username[20];
	char password[20];
	char ch;
	int i=0;
	Account_Srv_InitSys();
	fflush(stdin);
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷ  X·影院票务管理系统  ぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	if(loginWrongTimes==0)
	{
    	strcpy(message,"\n\t\t\t您有三次登陆机会，请先登录：");
	    puts(message);
	}
	else
	{
		puts(message);
	}
    printf("\n\t\t\t\t%-35s","请输入用户名：");
    scanf("%s",username);
	printf("\t\t\t\t%-35s","密码：");
    while((ch=getch())!='\r')
    {
        if(ch!=8)//不是回撤就录入
        {
            password[i]=ch;
            putchar('*');//并且输出*号
            i++;
        }
        else
        {
            putchar('\b');//这里是删除一个，我们通过输出回撤符 /b，回撤一格，
            putchar(' ');//再显示空格符把刚才的*给盖住，
            putchar('\b');//然后再 回撤一格等待录入。
            i--;
        }
    }
    password[i]='\0';
    printf("\n\n");
    printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
    if((!Account_Srv_Verify(username,password)))
//    while(!Account_Srv_Verify(username,password))
    {
    	loginWrongTimes++;
    	if(loginWrongTimes==WRONGTIMES)
    	{
    		printf("\n\t\t\t对不起您输错3次了,所以您无权登录本系统\n");
			printf("\n\t\t\t如有任何问题请联系管理员,按回车键退出......\n");
			getchar();
			return 0;
		}
		sprintf(message,"\n\t\t\t您的登录信息有误，请重新输入！您还有%d次机会。",WRONGTIMES-loginWrongTimes);
	    if(SysLogin()==0)
		    return 0;
	}
	loginWrongTimes=0;
	return 1;
}

//管理系统用户功能入口函数，显示用户账号管理菜单
void Account_UI_MgtEntry() {
	char ch;
	int choice;
	char username[20];
	char password[20];
	int i=4;
	system("cls");
	fflush(stdin);
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   用户账号管理  ぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	if(menuflag==1)
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
	    menuflag++;
	}
	else
	    puts(message);
    printf("\n");
    printf("\t\t\t[0] 重录所有账号\n");
    printf("\t\t\t[1] 添加一个账号\n");
    printf("\t\t\t[2] 修改一个账号\n");
    printf("\t\t\t[3] 删除一个账号\n");
    printf("\t\t\t[4] 添加一个账号\n");
    printf("\t\t\t[5] 查找指定账号\n");
    printf("\t\t\t[6] 显示所有账号\n");
    printf("\t\t\t[7] 账号录入文件\n");
    printf("\t\t\t[8] 修改当前账号密码\n");
    printf("\t\t\t[9] 返回\n");
	printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
    printf("\n\t\t\t请输入您的选择：");
    if(scanf("%d",&choice)!=1)
    {
    	while((ch=getchar())!='\n')
    	    continue;
    	strcpy(message,"\n\t\t\t您输入的不是数字。");
    	Account_UI_MgtEntry();
	}
    switch(choice)
    {
    	case 0:
    		printf("\t\t\t重录账号有风险，确定重录？(y/其它)");
    		fflush(stdin);
    		if((ch=getchar()!='y'))
    		{
    			menuflag--;
    			break;
			}
    		fflush(stdin);
    		pMain=Creat_Node();
    		strcpy(message,"\n\t\t\t录制账号成功。");
    		break;
    	case 1:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\t没有添加的账号。");
            else
    		    Account_UI_Add(pMain);
    		break;
    	case 2:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\t没有可以修改的账号。");
            else
            {
                printf("\n\t\t\t请输入你要修改的账号名：");
				scanf("%s",username);
				if(Account_UI_Modify(pMain,username))
				    printf("\n\t\t\t修改成功。");
				else
				    printf("\n\t\t\t修改失败。"); 
			}
    		break;
    	case 3:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\t没有可以删除的账号。");
            else
            {
            	printf("\n\t\t\t删除帐号请承担风险！");
                printf("\n\t\t\t请输入你要删除的账号名：");
				scanf("%s",username);
				Account_UI_Delete(pMain,username);
			}
    		break;
    	case 4:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\t链表还没有生成。");
    		else
    		    Account_UI_Add(pMain);
		    break;
		case 5:
			if(pMain==NULL)
			    strcpy(message,"\n\t\t\t链表还没有生成。");
    		else
    		{
				printf("\n\t\t\t请输入你要查询的账号名：");
				scanf("%s",username); 
				if(Account_UI_Query(pMain,username))
				    strcpy(message,"\n\t\t\t该账号已经注册。");
				else
				    strcpy(message,"\n\t\t\t该账号尚未注册。");
			}
			break;
		case 6:
//    		if(pMain==NULL)
//    		    strcpy(message,"\n\t\t\t没有已录入的账户。"); 
//            else
//			    Print_Node(pMain);
    		strcpy(message,"\n\t\t\t浏览所有注册账号功能尚未开通。"); 
    		break;
    	case 7:
    		Account_Perst_CheckAccFile();
    		strcpy(message,"\n\t\t\t账号录入文件功能尚未开通。"); 
    		break;
    	case 8:
    		strcpy(message,"\n\t\t\t修改当前账号密码尚未开通。");
    		break;
    	case 9:
    		Main_Menu();
		    break;
    	default:
    		strcpy(message,"\n\t\t\t请输入 0-9的整数"); 
    		while(ch!='\n')
    		    ch=getchar();
			break;
	}
	Account_UI_MgtEntry();
}

account_node_t *Creat_Node()
{
	int n,i;
	char ch;
    account_node_t *p,*h,*s;
    iCount=0;
    system("cls");
    if((h=(account_node_t *)malloc(sizeof(account_node_t)))==NULL)
    {
    	strcpy(message,"\n\t\t\t\t\t\t对不起，程序无法分配内存空间");
        return NULL;        
    }
    h->data.username[0]='\0';
    h->prev=NULL;
    h->next=NULL;
    p=h;
    printf("\n\n\n");
    printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   重录所有帐号  ぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
    printf("\n\t\t\t准备录入的账号密码信息数量：");
    if(scanf("%d",&n)!=1)
    {
    	while((ch=getchar())!='\n')
    	    continue;
    	strcpy(message,"\n\t\t\t您输入的不是数字。");
    	Account_UI_MgtEntry();
	}
    for(i=0;i<n;i++)
    {
        if((s=(account_node_t *)malloc(sizeof(account_node_t)))==NULL)
        {
	        strcpy(message,"\n\t\t\t\t\t\t对不起，程序无法分配内存空间");
            return NULL;
        }
        p->next=s;
        printf("\n\t\t\t正在录入第 %d 个：\n",i+1);
        printf("\t\t\t\t%-35s","账号：");
        scanf("%s",s->data.username);
        printf("\t\t\t\t%-35s","密码：");
        scanf("%s",s->data.password);
        printf("\t\t\t\t%-35s","[1]售票\\[2]经理\\[其它]管理：");
		while(scanf("%d",&s->data.type)!=1)
	    {
	    	while((ch=getchar())!='\n')
	    	    continue;
	    	printf("\n\t\t\t%-35s\n","您的输入有误，请重新输入");
	    	printf("\t\t\t\t%-35s","[1]售票\\[2]经理\\[其它]管理：");
		}
		if(s->data.type!=0 && s->data.type!=1 && s->data.type!=2)
		    s->data.type=9;
//		Account_Srv_Add(&s);
		s->prev=p;
	    s->next=NULL;
	    p=s;
	    iCount++;
    }
    h->prev=NULL;
    return(h);
}

int Account_UI_Add(account_list_t list ) {
	account_node_t *pNew,*pTemp=list;
	int choice;
	char ch; 
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   添加一个帐号  ぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	do
	{
		pNew=(account_node_t *)malloc(sizeof(account_node_t));
		printf("\n\t\t\t录入您要添加的新账号密码信息：\n");
		printf("\t\t\t\t%-35s","账号：");
		scanf("%s",pNew->data.username);
		printf("\t\t\t\t%-35s","密码：");
		scanf("%s",pNew->data.password);
		printf("\t\t\t\t%-35s","级别(\\1售票\\2经理\\9管理)：");
		scanf("%d",&pNew->data.type);
		while(pTemp->next)
			pTemp=pTemp->next;
		pTemp->next=pNew;
		pNew->prev=pTemp;
		pNew->next=NULL;
		printf("\n\t\t\t是否继续添加([1]继续/[其它]退出)：");
		while(scanf("%d",&choice)!=1)
	    {
	    	while((ch=getchar())!='\n')
	    	    continue;
	    	printf("\n\t\t\t%-35s\n","您输入的不是数字，请重新输入");
	    	printf("\t\t\t\t%-35s","级别(\\1售票\\2经理\\9管理)：");
		}
	}while(choice==1);
	strcpy(message,"\n\t\t\t添加成功。");
	iCount++;
	return 1;
}
// 2
int Account_UI_Modify(account_list_t list ,char usrName[]) {
	account_node_t *pTemp=list;
	char temppsw[20];
	char confirmpsw[20];
	char ch;
	int i=0;
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   修改一个帐号  ぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	do
	{
		if(!strcmp(pTemp->data.username,usrName))
		    break;
		pTemp=pTemp->next;
	}while(pTemp);
    printf("\n\t\t\t该账户信息为：\n");
    printf("\t\t\t\t账号：%30s \n",pTemp->data.username);
    printf("\t\t\t\t密码：%30s \n",pTemp->data.password);
    printf("\t\t\t\t级别：%30d \n",pTemp->data.type);
	printf("\n\t\t\t%-30s","请输入新的密码：");
	while((ch=getch())!='\r')
    {
        if(ch!=8)//不是回撤就录入
        {
            temppsw[i]=ch;
            putchar('*');//并且输出*号
            i++;
        }
        else
        {
            putchar('\b');//这里是删除一个，我们通过输出回撤符 /b，回撤一格，
            putchar(' ');//再显示空格符把刚才的*给盖住，
            putchar('\b');//然后再 回撤一格等待录入。
            i--;
        }
    }
    temppsw[i]='\0';
	printf("\n\t\t\t%-30s","请确定您的密码：");
	while((ch=getch())!='\r')
    {
        if(ch!=8)//不是回撤就录入
        {
            confirmpsw[i]=ch;
            putchar('*');//并且输出*号
            i++;
        }
        else
        {
            putchar('\b');//这里是删除一个，我们通过输出回撤符 /b，回撤一格，
            putchar(' ');//再显示空格符把刚才的*给盖住，
            putchar('\b');//然后再 回撤一格等待录入。
            i--;
        }
    }
    confirmpsw[i]='\0';
	if(strcmp(temppsw,confirmpsw))
	{ 
	    strcpy(message,"\n\t\t\t两次密码不一致。");
	    return 0;
	}
	strcpy(pTemp->data.password,temppsw);
	strcpy(message,"\n\t\t\t修改成功。");
	return 1;
}

// 3 根据用户账号名删除一个已经存在的用户账号信息，如果不存在这个用户账号名，提示出错信息
int Account_UI_Delete(account_list_t list ,char usrName[]) {
	account_node_t *pTemp,*pFree;
	int flag=0;
	system("cls");
	getchar();
	printf("\t\t\t你要删除的账号是：%s\n",usrName);
	pTemp=list;
	do
	{
		if(!strcmp(pTemp->data.username,usrName))
		{
		    flag=1;    
			break;
		}
		pTemp=pTemp->next;
	}while(pTemp);
	if(flag!=1)
	{
	    strcpy(message,"\n\t\t\t该账户不存在");
	    return 0;
	}
    else
    {
    	pFree=pTemp;
    	if(pTemp->prev->prev==NULL && pTemp->next==NULL)
    	{
    	    pMain=NULL;
		}
    	else if(pTemp->prev==NULL && pTemp->next!=NULL)
    	{
    		pTemp=pTemp->next;
    		pTemp->prev=NULL;
		}
    	else if(pTemp->prev!=NULL && pTemp->next!=NULL)
    	{
    		pTemp->prev->next=pTemp->next;
		    pTemp->next->prev=pTemp->prev;
		}
	    else if(pTemp->prev!=NULL && pTemp->next==NULL)
	    {
	    	pTemp=pTemp->prev;
	    	pTemp->next=NULL;
		}
		free(pFree);
	    strcpy(message,"\n\t\t\t删除成功。");
	    iCount--;
		return 1;
	}
}
// 5 根据用户账号名查找该用户账号是否存在，存在返回1，否则返回0，并提示错误信息
int Account_UI_Query(account_list_t  list ,char usrName[]) {
	account_node_t *pTemp=list;
	system("cls");
	printf("\n\n\n"); 
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   查询一个帐号  ぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	while(pTemp)
	{
		if(strcmp(pTemp->data.username,usrName))
		    break; 
		pTemp=pTemp->next;
	}
	return 1;
}

account_node_t Print_Node(const account_node_t *userinfo)
{
	int pageSize,i;
	Pagination_t paging;
	account_node_t *p;
	char choice,ch;
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   显示所有帐号  ぷぷぷぷぷぷぷぷぷぷ╬\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
	printf("\t\t\t请输入每页显示的个数：");
	while(scanf("%d",&pageSize)!=1)
	{
	    while((ch=getchar())!='\n')
	        continue;
	    printf("\t\t\t您输入的不是数字，请重新输入。\n");
	    printf("\t\t\t输入每页显示的个数：");
	}
	//初始化分页器参数
	paging.offset = 0;
	paging.pageSize = pageSize;
	paging.totalRecords = iCount;
	//定位到第一页
	Paging_Locate_FirstPage(userinfo, paging);
	system("cls");
	do {
		printf("\n\n\n");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷぷぷ   显示所有帐号  ぷぷぷぷぷぷぷぷぷぷ╬\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==╝\n");
		printf("\t\t\t每页显示的个数是：%d\n",pageSize);
		printf("\n\t\t\t%s\t\t%s\t\t%s\n", "账号", "密码","账号类型");
		Paging_ViewPage_ForEach(userinfo, paging, account_node_t, p, i);
		{
			printf("\t\t\t%s\t\t%s", p->data.username, p->data.password);
		}
	    switch(userinfo->data.type)
		{
			case USR_ANOMY:
				printf("\t\t%s\n","匿名用户");
			    break; 
			case USR_CLERK: 
			    printf("\t\t%s\n","销售员");
				break;
			case USR_MANG:
			    printf("\t\t%s\n","经理");
			    break;
			case USR_ADMIN:
			    printf("\t\t%s\n","系统管理员");
				break;
			default:
				printf("\t\t\terror！");
		}
		printf("\t\t\t--总共 %2d 条记录 --------- 当前： %2d/%2d --\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t[F]第一页|[P]上一页|[N]下一页|[L]最后一页|[E]退出\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t请输入您的选择:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'f':
		case 'F':
			Paging_Locate_FirstPage(userinfo, paging)
			;
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(userinfo, paging, -1, account_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(userinfo, paging, 1, account_node_t);
			}
			break;
		case 'l':
		case 'L':
			Paging_Locate_LastPage(userinfo, paging, account_node_t)
			;
			break;
		}
		system("cls");
	} while (choice != 'e' && choice != 'E');
	menuflag--;
} 
