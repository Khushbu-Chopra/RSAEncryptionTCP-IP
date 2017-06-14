#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr
long int n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
int tmp,tmp1;
char msg[100];
void encrypt();
void func(int sockfd)
{
	int key,pk=0,x,count=0,k=0,x1,n1=0,c;
	read(sockfd,&n1,sizeof(n1),0);
	n=ntohl(n1);
	read(sockfd,&pk,sizeof(pk),0);
	key=ntohl(pk);
	//printf("%d\t%ld\t",n,key);	
	printf("\nENTER MESSAGE\n");
 
	fflush(stdin);
 
	scanf("%s",msg);
 
	for (i=0;msg[i]!=NULL;i++)
 
	m[i]=msg[i];
 	
	encrypt(n,key);
	for(i=0;temp[i]!=-1;i++)
	{
		count++;
		
	}
	//printf("%d",count);
	/*
	for(i=0;temp[i]!=-1;i++)
	{	
		printf("%d\t",temp[i]);
		
	}
	*/
	while(1)
	{

		c=htonl(count);//passing count
		send(sockfd, &c, sizeof(c), 0);
		while(k<count)//passing temp
		{
		  x1=htonl(temp[k]);
		  send(sockfd,&x1,sizeof(int),0);
		  k++;
		}
		send(sockfd,en,sizeof(en),0); 
		break;	
	}

}
void encrypt(int n, int key) {
 
	long int pt,ct,k,len;
 
	i=0;
 
	len=strlen(msg);
 
	while(i!=len) {
 
		pt=m[i];
 
		pt=pt-96;
 
		k=1;
 
		for (j=0;j<key;j++) {
 
			k=k*pt;
 
			k=k%n;
 
		}
 
		temp[i]=k;
 
		ct=k+96;
 
		en[i]=ct;
 
		i++;
 
	}
 
 	en[i]=-1;
	
	temp[i]=-1;
 
	printf("\nTHE ENCRYPTED MESSAGE IS: ");
 
	for (i=0;en[i]!=-1;i++)
 
	printf("%c",en[i]);

	printf("\n");
 
}


int main()
{
int sockfd,connfd;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
