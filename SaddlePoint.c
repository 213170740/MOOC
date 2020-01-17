#include <stdio.h>
#include <stdlib.h>

/*
题目内容：

给定一个n*n矩阵A。
矩阵A的鞍点是一个位置（i，j），
在该位置上的元素是第i行上的最大数，第j列上的最小数。
一个矩阵A也可能没有鞍点。

你的任务是找出A的鞍点。


输入格式:

输入的第1行是一个正整数n, （1<=n<=100），
然后有n行，每一行有n个整数，同一行上两个整数之间有一个或多个空格。



输出格式：

对输入的矩阵，如果找到鞍点，就输出其下标。
下标为两个数字，第一个数字是行号，第二个数字是列号，均从0开始计数。

如果找不到，就输出
NO
题目所给的数据保证了不会出现多个鞍点。



输入样例：

4
1 7 4 1
4 8 3 6
1 6 1 2
0 7 8 9



输出样例：
2 1
*/
int main(int argc, char *argv[]) {
//读n
	int n = 0;
	scanf("%d",&n);
//读矩阵
	int matrix[n][n];
	int i=0,j=0;
	for(; i<n; i++) {
		scanf("%d",&matrix[i][0]);
		for(j=1; j<n; j++) {
			scanf("%d",&matrix[i][j]);
		}
	}
	int IsSaddle = 1;
	int index_j = 0;
	int index_i = 0; 
//找第i行最大值
	for(i=0; i<n; i++) {
		index_j = 0;//最大值下标
		IsSaddle = 1;
		for(j=0; j<n; j++) {
			if(matrix[i][j]>matrix[i][index_j]) {
				index_j=j;
			}
		}
//判断第i行的最大值是不是第j行的最小值
		int k=0;
		for(k=0; k<n; k++) {
			if(matrix[k][index_j]<matrix[i][index_j]) {
				IsSaddle=0;
				break;
			}
		}
		if(IsSaddle==1) {
			break;
		}
	}
//输出结果
	if(IsSaddle==1) {
		printf("%d %d\n",i,index_j);
	} else {
		printf("NO\n");
	}
	system("pause");
	return 0;
}
