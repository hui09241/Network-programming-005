#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n,i,j;
  	char  	str[MAXLINE]="1234",str_r[MAXLINE];
	clock_t start,end;
	long long int total=0;
	double time;
  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	for(i=0;i<1023;i++)
   {
   		str[i]='0';
   }

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

  	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));


   	int r=0;
   	while(1) {

	   	cli_len = sizeof(cli);
		printf("server waits for client\n");
		if (r==0)
		{
		total=0;
		start=clock();
		sleep(1);
		for(j=0;j<1024*1024;j++)
		{
			n=recvfrom(serv_sd, str_r, MAXLINE, 0,(LPSOCKADDR)&cli,&cli_len); //��server����
			if(n==0)//������
			break;
			total = total + n;
		   	printf("server recv: %d bytes, total:%d \n",n,total);
		   // sleep(3);
		   	end=clock();
		     time=total/(end-start)/1000;
		   	printf("�����t�v�G%f MBytes\n",time);



		}


		}

		if(r==1)
		{
			total=0;
			start=clock();
			sleep(1);
		for(j=0;j<1024;j++)
		{
			for(i=0;i<1024;i++)
   			{

	  		 n=sendto(serv_sd, str, strlen(str)+1, 0,(LPSOCKADDR)&cli,cli_len);//�ǰe
	 	 	 total = total + n;
	  		 printf( "server send:%d bytes, total:%d\n",n,total);
	  		 //sleep(3);
	  		 end=clock();
	  		  time=total/(end-start)/1000;
    		printf("�ǰe�t�v�G%f MBytes\n",time);
   			}
		}
		}
		r++;//�אּ����
		if (r==2)//��������
		   break;
	}

   	WSACleanup();
   	system("pause");
}
