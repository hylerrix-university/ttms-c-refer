#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "View/Account_UI.h"

account_t gl_CurUser={9, USR_ANOMY, "admin","admin"};

char message[100];

int main()
{
	if(!SysLogin())
	{
		getchar();
		exit(0);
	}
	printf("\t\t\t%30c","");
	printf("Õý");Sleep(200);
	printf("ÔÚ");Sleep(200);
	printf("µÇ");Sleep(200);
	printf("Â¼");Sleep(200);
	printf("Çë");Sleep(200);
	printf("ÉÔ");Sleep(300);
	printf("ºó");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	Main_Menu();
	return EXIT_SUCCESS;
}
