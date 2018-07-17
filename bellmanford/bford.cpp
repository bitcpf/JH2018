#include<stdio.h>
#define M 10//边数
#define N 5//顶点数
#define MAX 10000
 
int BellmanFord(int dist[N][N],int d[N],int i);
 
int flag1=0;
int flag2=0;
 
typedef struct
{
	int startvex;
	int endvex;
	int length;
}edge;
edge T[M];
int main()
{
	int dist[N][N]={{0,6,MAX,7,MAX},
					{MAX,0,5,8,-4},
					{MAX,-2,0,MAX,MAX},
					{MAX,MAX,-3,0,9},
					{2,MAX,7,MAX,0}};//图的邻接矩阵
	int d[N];
	int num=0;
    num=BellmanFord(dist,d, 0);//计算下标为0的顶点到其它顶点的距离，num用于统计边数
	for(int i=0;i<N;i++)//打印到各个顶点之间的距离
		printf("%d ",d[i]);
	printf("\n");
	for(int j=0;j<num;j++)//打印考虑过的边
		printf("start=%d,end=%d,lenth=%d\n",T[j].startvex,T[j].endvex,T[j].length);


    return 0;
}
 
int BellmanFord(int dist[N][N],int d[N],int i)
{
	for(int j=0;j<N;j++)//初始化
		d[j]=MAX;
	d[i]=0;
	int num=0;
 
	for(int k=0;k<N-1;k++)
	{
		for(int ii=0;ii<N;ii++)
			for(int jj=0;jj<N;jj++)
			{
				if(dist[ii][jj]!=MAX)
				{
					if(d[jj]>(d[ii]+dist[ii][jj]))//不断更新距离
					{
						d[jj]=d[ii]+dist[ii][jj];//当原节点到jj节点的距离大于
						                         //原节点到ii节点的距离与从ii节点到jj节点的距离和时更新
						T[num].startvex=ii;
						T[num].endvex=jj;
						T[num].length=dist[ii][jj];
						num++;
					}
				}
			}
	}
	for(int ii=0;ii<N;ii++)
	for(int jj=0;jj<N;jj++)//有权值为负的回路的情况
	{
		if(d[jj]>(d[ii]+dist[ii][jj]))
			return 0;
	}
return num;
 
}

