//------------------------------------------------------------------------------------------------------
//View
//创建系统初始化账号admin

#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_

#include "../Service/account.h"

//------------------------------------------------------------------------------------------------------
// UI
static const int ACCOUNT_PAGE_SIZE = 3;

int SysLogin();
void Account_UI_MgtEntry();
int Account_UI_Add(account_list_t list);
int Account_UI_Modify(account_list_t list,char usrName[]);
int Account_UI_Delete(account_list_t list,char usrName[]);
int Account_UI_Query(account_list_t list,char usrName[]);
void Change_Passwd(); 
int SysLogout();
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
account_node_t *Creat_Node();
account_node_t Print_Node(const account_node_t *);
//------------------------------------------------------------------------------------------------------


static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

#endif /* ACCOUNT_UI_H_ */	
