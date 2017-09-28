#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Query_Persist.h"

//根据票的信息插入到订单的信息
inline int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);
}

//删除订单的信息
inline int Sale_Srv_DeleteByID(int saleID) {
	return Sale_Perst_DeleteByID(saleID);
}

/*
//通过uid查询订单
inline int Sale_Srv_SelectByUid(char *queryuid, Sale_list_t head) {
	return Sale_Infor_By_Uid(queryuid, head);
}

//根据时间查询订单
inline int Sale_Srv_selectByTime(char querytime[][30], Sale_list_t head) {
	return Sale_Infor_By_Time(querytime, head);
}
*/




//#include "../Persistence/Sale_Persist.h"
//#include "../Persistence/Query_Persist.h"
//
////根据票的信息插入到订单的信息
//inline int Sale_Srv_Add(const sale_t *data) {
//	sale_list_t head;
//	sale_node_t *pos;
//	
//	
//	int newcount=0;
//	while(*date!=NULL){
//		printf("请输入: 售票记录ID、售票员ID、票ID、处理日期、处理时间、票价、票类型")；
//		scanf("%5ld    %5d    %5d      %d%d%d         %d%d%d      %5d      %10s\n",
//					"pos->user_id", "pos->ticket_id",
//				"pos->user_date_t date.year","pos->user_date_t date.month","pos->user_date_t date.day", "pos->user_time_t time.hour","pos->user_time_t time.minute",
//				"pos->user_time_t time.second","pos->value","sale_type_t.type") ; 
//		entkey_srv_ComNewKey(char entName[]);
//
//		sale_srv_Add(const sale_t *date) ;
//		count++;		
//	}
//	return Sale_Perst_Insert(data);
//}
//
////删除订单的信息
//inline int Sale_Srv_DeleteByID(int saleID) {
//	int saleID,rtn=0;
//	printf("请输入ID");
//	scanf("%d",&saleID);
//	while(saleID！=0){
//		Sale_Perst_DeleteByID(int saleID);
//		}
//}
//
///*
////通过uid查询订单
//inline int Sale_Srv_SelectByUid(char *queryuid, Sale_list_t head) {
//	return Sale_Infor_By_Uid(queryuid, head);
//}
//
////根据时间查询订单
//inline int Sale_Srv_selectByTime(char querytime[][30], Sale_list_t head) {
//	return Sale_Infor_By_Time(querytime, head);
//}
//*/
