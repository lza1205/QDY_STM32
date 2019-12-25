
#include <string.h>
#include <stdio.h>


#include "config.h"
#include "agent_proto.h"

int (*net_send)(unsigned char *buf, int len);

static char my_name[USER_NAME_LEN];
static unsigned int passwd = 1234;
static char my_customer[USER_NAME_LEN];


void set_name(char *name, int len)
{
	memcpy(my_name, name, __min(USER_NAME_LEN, len));
}

void set_passwd(unsigned int pw)
{
	passwd = pw;
}

void set_customer(char *customer, int len)
{
	memcpy(my_customer, customer, __min(USER_NAME_LEN, len));
}


void set_net_send(int (*send)(unsigned char *buf, int len))
{
	net_send = send;
}

int __crc(char *buf, int len)
{
/*
	int i;
	int crc = 0x55;
	
	for(i = 0; i < len; i++)
	{
		crc = crc ^ buf[i];
	}
	return crc;
*/
	return 0;
}

/* ��ͷ����������У�� */
int check_head_crc(struct check_head *head)
{
#if 0
	int crc = 0;
	crc = __crc((char *)head, sizeof(struct check_head) - sizeof(int));

//	printf("recv crc is %d \r\n", head->crc);

//	printf("crc is %d \r\n", crc);
	
	if(crc == head->crc)
		return 0;
	return -1;
#endif
	return 0;
}


/* �޸�ͷ���������ʶ��ͬʱ������дУ�� */
void update_head(struct check_head *head, unsigned int air)
{
	head->affairs = air;
	head->crc = __crc((char *)head, sizeof(struct check_head) - sizeof(int));
}


/*
char *qdy_get_data(char *buf)
{
	return (char *)(buf + sizeof(struct check_head) + sizeof(struct proto_c_send_data));
}


char *qdy_get_src_name(char *buf)
{
	struct proto_c_send_data *recv_proto = (struct proto_c_send_data *)(buf + sizeof(struct check_head));
	return recv_proto->src_name;
}

char *qdy_get_dest_name(char *buf)
{
	struct proto_c_send_data *recv_proto = (struct proto_c_send_data *)(buf + sizeof(struct check_head));
	return recv_proto->dest_name;
}
*/

int qdy_get_len(int len)
{
	return (len - sizeof(struct check_head) - sizeof(struct proto_c_send_data));
}

/* ��ӡ���� */
void hexdump(  
                FILE *f,  
                char *title,  
                char *s,  
                int l)  
{  
#if 1
    int n = 0;  
  
    printf("%s", title);  
    for (; n < l; ++n) {  
        if ((n % 16) == 0) {  
                printf("\n%04x", n);  
        }  
        printf(" %d", s[n]);  
    }  
  
    printf("\n");
#endif
}

void dump_data(unsigned char *buf, int len)
{

	hexdump(stdout, "== data ==",  
                (char *)buf,  
                len);

}


/***************************************
������: __compages_head
����: ����ͷ��
***************************************/
volatile unsigned int key_cnt = 0;

void __compages_head(struct check_head *head, unsigned int air, char *name, unsigned int passwd, char *customer)
{
	memset(head, 0, sizeof(struct check_head));

	head->affairs = air;

	memset(head->name, 0, USER_NAME_LEN);
	strcpy(head->name, name);	
	head->passwd = passwd;
	memset(head->customer, 0, USER_NAME_LEN);
	strcpy(head->customer, customer);
	
	key_cnt ++;

	head->key = key_cnt;

	/* �Ӹ���У�� */
	head->crc = __crc((char *)head, sizeof(struct check_head) - sizeof(int));
}

void qdy_resolve_recv_data(unsigned char *buf, int len);
void __qdy_recv_data(unsigned char *buf, int len)
{
	/* ����Ӧ������ */	
	struct proto_c_send_data proto, *recv_proto;
	struct check_head *head, ack_head;

	int ret;
	char sendbuf[1204];
	int send_len;

	/* ��Ҫ���¹����ͷ */
	head = (struct check_head *)buf;
	memcpy(&ack_head, head, sizeof(struct check_head));	//��¼�����ͷ���Ȼ�Ҫ����֤
//	ack_head.affairs = _aff_client_send_data_ack_;
	update_head(&ack_head, _aff_client_send_data_ack_);

	recv_proto = (struct proto_c_send_data*)(buf + sizeof(struct check_head));
	
	memcpy(proto.dest_name, recv_proto->src_name, USER_NAME_LEN);
	memcpy(proto.src_name, my_name, USER_NAME_LEN);

	memcpy(sendbuf, &ack_head, sizeof(struct check_head));
	memcpy(sendbuf + sizeof(struct check_head), &proto, sizeof(proto));
	send_len = sizeof(struct check_head) + sizeof(proto);

	//ack
	ret = net_send(sendbuf, send_len);


	/* �������յ����ݰ� */
	qdy_resolve_recv_data(buf, len);

}


/*
������:qdy_recv_data
����
*/
void qdy_recv_data(unsigned char *recvbuf, int len)
{
	struct check_head *head;
	if (len < 0)
	{
		perror("my_recvfrom_handle");
		return;
	}
	else
	{
		head = (struct check_head *)recvbuf;

		/* ��鳤�� */
		if(len < sizeof(struct check_head))
			return;

		/* �����ݰ�ͷ������У�� */
		if(check_head_crc(head) != 0)
			return;			

		switch(head->affairs)
		{
			case _aff_client_send_data_:
				__qdy_recv_data(recvbuf, len);
				break;

			case _aff_client_send_data_ack_:
				//��ʱ�����κδ���
				break;
		}
	}
}



int qdy_send_data(unsigned char *name, char *data, int len)
{
	int ret;

	struct proto_c_send_data proto;
	struct check_head head;

	char sendbuf[1024];
	int send_len;

	/* �����ͷ */
	__compages_head(&head, _aff_client_send_data_, my_name, passwd, my_customer);

	memset(proto.dest_name, 0, USER_NAME_LEN);
	strcpy((proto.dest_name), name);

	memset(proto.src_name, 0, USER_NAME_LEN);
	strcpy((proto.src_name), my_name);
	proto.c_proto = _proto_c_msg_;		/* Э�� */

	memcpy(sendbuf, &head, sizeof(head));
	memcpy(sendbuf + sizeof(head), &proto, sizeof(proto));
	send_len = sizeof(head) + sizeof(proto);
	memcpy(sendbuf + send_len, data, len);
	send_len += len;

	//set_net_send(my_send);
	ret = net_send((char *)sendbuf, send_len);

}




int qdy_sync_server(void)
{
	int ret;

	struct check_head head;

	/* �����ͷ */
	__compages_head(&head, _aff_client_sync_, my_name, passwd, my_customer);

	//set_net_send(my_send);
	ret = net_send((char *)&head, sizeof(struct check_head));

}


