#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024];
   char  		str_r[1024];
   WSADATA 		wsadata;

   int n,i,j,t=0,recv;
   long long int total=0;
   double time;
   clock_t start,end;
   for(i=0;i<1023;i++)
   {
   		str[i]='0';
   }

   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用



   sd=socket(AF_INET, SOCK_DGRAM, 0); //開啟一個 TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server

	start=clock(); //傳送
	sleep(1);
	total=0;
	for(j=0;j<1024*1024;j++)
	{
		n = sendto(sd, str, strlen(str)+1, 0,(LPSOCKADDR)&serv,sizeof(serv));  //傳送
	   total = total + n;
	   printf( "client send:%d bytes, total:%d\n",n,total);
	   end=clock();
	   time=total/(end-start)/1000;
		printf("傳輸速率：%f MBytes\n",time);

	}

    serv.sin_family       = AF_INET;
    serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
    serv.sin_port         = htons(5678);

	total=0;
	start=clock();
	sleep(1);

	for(j=0;j<1024*1024;j++)
	{
		recv=sizeof(serv);
	   n = recvfrom(sd, str_r, MAXLINE, 0,(LPSOCKADDR)&serv,&recv); //接收
		if(n==0)//未收到
			break;
		total = total + n;
	   printf( "client recv:%d bytes, total:%d\n",n,total);
	   //sleep(3);
	   end=clock();
	   time=total/(end-start)/1000;
    	printf("接收速率：%f MBytes\n",time);

	}


   WSACleanup();  // 結束 WinSock DLL 的使用
   system("pause");

   return 0;
}
