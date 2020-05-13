
#include "config.h"
#include "agent_proto.h"
#include "qdy_interface.h"
#include "all.h"
#include "stdio.h"
#include "cJSON.h"

#define SERVER_PORT		8000
#define SERVER_IP		"106.13.62.194"

void *recv_server_data(void *pdata);
void qdy_upload(void);
void rf433_upload(void);

char *device_id = "lancy";

#define sleep(x)	Delay_nS(x)

//
//

//#define __AT_APP __attribute__((used, section("APPCODE")))
#define __AT_APP

int my_send(unsigned char *buf, int ret)
{
	//sendto(sockfd, buf, ret, 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in));
	//dump_data((unsigned char *)buf, ret);
	network_send(buf, ret);
	//4G_SEND()
	return 0;
}

int login(void);
unsigned char recvline[1024];


u8 MotorFlg = 0;

__AT_APP int client_main(void)
{
	
	set_name(device_id, strlen(device_id) + 1);
	set_customer("test", strlen("test") + 1);

	set_net_send(my_send);

	login();

	aaa_test();
	
	while(1)
	{
		

		int ret;
		//��������
		//ret = recvfrom(sockfd, recvline, 1024, 0, (struct sockaddr*)&addrRecv,(socklen_t*)&sizeRecvAddr);
		
		
		ret = network_recv(recvline, sizeof(recvline));
		if(ret != 0)
		{
			qdy_recv_data(recvline, ret);
		}

		if(MotorFlg == 1)
		{
			Motorcw();
		}

		qdy_process();
	}

    //close(sockfd);
    //return 1;
}


int login(void)
{
	int ret;
	struct check_head *recv_head;

	struct proto_s_login_ack *ack;
	struct check_head head;
	__compages_head(&head, _aff_client_login_, device_id, 1234, "test");
	//��ʱ���� crc ����� ʱ���

	//��¼
	dump_data((unsigned char *)&head, sizeof(struct check_head));
	printf("%s %d %d \r\n", __FILE__, __LINE__, sizeof(struct check_head));
	//sendto(sockfd, &head, sizeof(struct check_head), 0, (struct sockaddr *)addr, sizeof(struct sockaddr_in));
	network_send( (unsigned char *)&head, sizeof(struct check_head));

	

	//�ȴ�������Ӧ��
	while(1)
	{

		
		//��������
		//ret = recvfrom(sockfd, recvline, 1024, 0, (struct sockaddr*)&addrRecv,(socklen_t*)&sizeRecvAddr);
		ret = network_recv(recvline, sizeof(recvline));
		if(ret != 0)
		{
			recv_head = (struct check_head *)recvline;
			printf("recv data! \r\n");
			dump_data(recvline, ret);

			if((recv_head->affairs == _aff_server_login_ack_))
				   goto login_ack;
			
			sleep(5);
			continue;
		}

		


		sleep(5);
	}
	
login_ack:
	
	ack = (struct proto_s_login_ack *)(recvline + sizeof(struct check_head));

	if(ack->ack == 0)
	{
		printf("connet is ok!\r\n");
	}else{
		printf("connet is err!\r\n");
	}
	return ack->ack;		//���ص�½���

}


double get_temperature(void)
{
	static int flg = 0;
	float ret = flg?21.4:21.9;
	flg = !flg;
	return ret;
}

double get_humidity(void)
{
	static int flg = 0;
	float ret = flg?31.7:31.1;
	flg = !flg;
	return ret;
}

//extern u8 lora_recv_data[100];

void qdy_upload(void)
{
#if 0
	cJSON *root;
	char *result;
	
	root=cJSON_CreateObject();//����һ��������״̬��JSON����

	//cJSON_AddNumberToObject(root,"temperature", get_temperature());
	//cJSON_AddNumberToObject(root,"humidity", get_humidity());
	cJSON_AddStringToObject(root, "HP", (const char *)get_lora_data());
	result=cJSON_PrintUnformatted(root);

	qdy_send_json_data("__server__", result, strlen(result) + 1);

	cJSON_Delete(root);//���root���ڵ�ɾ��
	free(result);//�ͷ�result�Ŀռ䣬����Ҫ�У�Ҫ��Ȼ�ڴ����ʧȥһ�οռ䣬���ϵͳ����

	clear_lora_data();
#endif
}


void rf433_upload(void)
{
	/*
	u8 rf_buf[6], ret;
	ret = recv_rf433_data(rf_buf, sizeof(rf_buf));
	if(ret != 0)
	{
		qdy_send_json_data("A", "rfdata", 7);
	}
	*/
}






