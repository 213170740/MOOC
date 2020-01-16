#include <stdio.h>
#include <stdlib.h>

/*
题目内容：

我们认为2是第一个素数，3是第二个素数，5是第三个素数，依次类推。

现在，给定两个整数n和m，0<n<=m<=200，你的程序要计算第n个素数到第m个素数之间所有的素数的和，包括第n个素数和第m个素数。



输入格式:

两个整数，第一个表示n，第二个表示m。



输出格式：

一个整数，表示第n个素数到第m个素数之间所有的素数的和，包括第n个素数和第m个素数。



输入样例：

2 4



输出样例：

15
*/
int main(int argc, char *argv[]) {
	int	isprime=1;
	int n,m;
	int num=0;
	int sum=0;
	scanf("%d %d",&n,&m);
	int i=1,j=1;
	for(i=2;num <m;i++)
	{
		isprime=1;
		for(j=2;j<i;j++)
		{
		//	printf("i=%d j=%d\nnum=%d\n",i,j,num);
			if(i%j==0)
			{
				isprime = 0;
				break;
			}
		}
		if(isprime)
		{
			num++;
			if(num>=n)
			{
				sum += i;
			//	printf("%d\n",sum);
			}
			//printf("%d %d %d\n",i,sum,num);
		}	
	}
	printf("%d\n",sum);
	system("pause");
	return 0;
}
