#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr
long int p,q,n,t,flag,e[100],d[100],temp[100],j,m1[100],i;
int publickey,privatekey;
int prime(long int);
void ce();
long int cd(long int);
void decrypt(int* en,int* temp) 
{ 
	long int pt,ct,k,m[MAX];
 
	int i=0,j,key;
	
	key=d[0]; //Private key
 
	while(en[i]!=-1&&temp[i]!=-1) {
 
		ct=temp[i];
 
		k=1;
 
		for (j=0;j<key;j++) {
 
			k=k*ct;
 
			k=k%n;
 
		}
 
		pt=k+96;
 
		m[i]=pt;
 
		i++;
 
	}
 
	m[i]=-1;
 
	printf("\nTHE DECRYPTED MESSAGE IS: ");
 
	for (i=0;m[i]!=-1;i++)
 
	printf("%c",m[i]);

	printf("\n");
 
}
 
void func(int sockfd)
{
int buff1[MAX],buff2[MAX],buff3=0,buff4=0,buff5=0,count,tlen=0,n1,pk,d=0,k=0,x,x1;
printf("\nENTER FIRST PRIME NUMBER\n");
 
	scanf("%d",&p);
 
	flag=prime(p);
 
	if(flag==0) {
 
		printf("\nWRONG INPUT\n");
 
		exit(1);
 
	}
 
	printf("\nENTER ANOTHER PRIME NUMBER\n");
 
	scanf("%d",&q);
 
	flag=prime(q);
 
	if(flag==0||p==q) {
 
		printf("\nWRONG INPUT\n");
 
		exit(1);
 
	}
	n=p*q;  //Modulus for private and public key
 
	t=(p-1)*(q-1);  //Totient
	ce();
	publickey=e[0];  //Public key
	n1=htonl(n);
	pk=htonl(publickey);
	send(sockfd,&n1,sizeof(n1),0);   //Sending n and public key to client for encryption
	send(sockfd,&pk,sizeof(pk),0);
	//printf("%d\t%d\t",n,publickey);
while(1)
{

	recv(sockfd,&d,sizeof(d),0);
	count=ntohl(d);
	bzero(buff1,sizeof(buff1));
		while(k<count)
		{
			recv(sockfd,&x1,sizeof(int),0);
			buff1[k]=ntohl(x1);
			k++;
		}	
	buff1[count]=-1;
	/*for(i=0;buff1[i]!=-1;i++)
	printf("%d\t",buff1[i]);*/
	recv(sockfd,buff2,sizeof(buff2),0);
	printf("\nThe ENCRYPTED MESSAGE RECEIVED IS: ");
	for(i=0;buff2[i]!=-1;i++)
	printf("%c",buff2[i]);
	break;
}
decrypt(buff2,buff1);
}
int prime(long int pr) {
 
	int i;
 
	j=sqrt(pr);
 
	for (i=2;i<=j;i++) {
 
		if(pr%i==0)
 
		    return 0;
 
	}
 
	return 1;
 
}
 
void ce() // Calculates public key
 {
 
	int k;
 
	k=0;
 
	for (i=2;i<t;i++) {
 
		if(t%i==0)
 
		    continue;
 
		flag=prime(i);
 
		if(flag==1&&i!=p&&i!=q) {
 
			e[k]=i;
 
			flag=cd(e[k]);
 
			if(flag>0) {
 
				d[k]=flag;
 
				k++;
 
			}
 
			if(k==99)
 
			        break;
 
		}
 
	}
	d[k]=-1;
 
}
 
long int cd(long int x)  //Calculates private key
{
 
	long int k=1;
 
	while(1) {
 
		k=k+t;
 
		if(k%x==0)
 
		    return(k/x);
 
	}
 
}
int main()
{
int sockfd,connfd,len;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);
if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
{
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");
if((listen(sockfd,5))!=0)
{
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");
len=sizeof(cli);
connfd=accept(sockfd,(SA *)&cli,&len);
if(connfd<0)
{
printf("server acccept failed...\n");
exit(0);
}
else
printf("server acccept the client...\n");
func(connfd);
close(sockfd);
}
