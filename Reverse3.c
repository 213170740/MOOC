#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
逆序的三位数：
程序每次读入一个正三位数，然后输出逆序的数字。
注意，当输入的数字含有结尾的0时，输出不应带有前导的0。比如输入700，输出应该是7。
*/
int main(int argc, char *argv[]) {
	int digit;
	scanf("%d",&digit);
	int h,m,l;
	h=digit/100;
	l=digit%10;
	m=digit%100/10;
	int ret=l*100+m*10+h;
	printf("%d\n",ret);
	system("pause");
	return 0;
}
