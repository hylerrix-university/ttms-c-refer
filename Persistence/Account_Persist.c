// Persistence

#include "Account_Persist.h"
#include "../Service/account.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

extern account_t gl_CurUser;
extern account_t gl_Admin;
extern message;

//------------------------------------------------------------------------------------------------------
// Persistence
static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

//判断账号文件是否存在，返回1存在，返回0不存在
int Account_Perst_CheckAccFile() {
	FILE *fp;
	if((fp=fopen("Account.dat","rb"))==NULL)
	    return 0;
	return 1;
}
//根据用户名载入账号,载入成功 return 1；否则 return 0
int Account_Perst_SelByName(char usrName[], account_t *buf) {
	return 1;
}
//新账号写入账号文件中，返回实际写入的数据块数目
int Account_Perst_Insert(const account_t *data) {
	FILE *fp;
	fp=fopen("Account.dat","ab");
	fwrite(data,sizeof(data),1,fp);
//	strcpy(message,"...");
	return 1;
}
//在账号文件中查找与参数账号匹配的账号，找到 return 1；否则 return 0；并进行覆盖重写
int Account_Perst_Update(const account_t * data) {
	return 1;
}
//在账号文件中删除与参数id匹配的账号，删除成功 return 1；否则 return 0；
int Account_Perst_DeleteByID(int id) {
	return 1;
}
//在账号文件中查找与参数id匹配的账号，并通过指针buf传出；匹配成功 return 1；否则 return 0；
int Account_Perst_SelectByID(int id, account_t *buf) {
	return 1;
}
//遍历读ACCOUNT_DATA_FILE文件，动态构建用户账号list链表,list 为链表头指针，返回list长度
int Account_Perst_SelectAll(account_list_t list) {
	return 1;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/*
Consumer* read_list()
{
    FILE *fp;
    if ((fp = fopen("CONSUMER.dat", "rb")) == NULL)
    {
        printf("无法读取 CONSUMER.dat\n");
        return NULL;
    }
    int sign;
    Consumer *s,*p,*head;
     
    head= (Consumer*)malloc(SIZE_C);
    if (head == NULL)
    {
        printf("读取失败！内存空间申请不足！\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        return NULL;
    }
    p = head;
    p->next = NULL;
    while (feof(fp))
    {
        s = (Consumer*)malloc(SIZE_C);
        //fread(s, SIZE_C, 1, fp);
                fread(s, sizeof(char), SIZE_C, fp);
        p->next = s;
        p = s;
        p->next = NULL;
    }
    fclose(fp);
    return head;
}//读取文件到链表
int save_consumer(Consumer *p)
{
    FILE *fp;
    Consumer *head;
    head = p;//p为已经构建好的链表
    //if ((fp = fopen("CONSUMER.dat", "ab+")) == NULL)
        if ((fp = fopen("CONSUMER.dat", "wb")) == NULL)
    {
        printf("无法打开 CONSUMER.dat!\n");
        return -1;
    }
    while (p != NULL)
    {
        //fwrite(p, SIZE_C, 1, fp);
                fwrite(p, sizeof(char), SIZE_C, fp);
        p = p->next;
    }
    fclose(fp);
    return 1;
}//储存链表到文件
*/
