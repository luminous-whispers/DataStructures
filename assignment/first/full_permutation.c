￼￼include<iostream>
using namespace std;
int n,a[10],visited[10]={0};//初始化定义数字数组和访问数组
void DFS(int k)
{
	int i,j;
	if(k>n)//大于n
	{
		for(j=1;j<=n;j++)//输出数组里面的元素
		{
			printf("%5d",a[j]);
		}
		cout<<"\n";
	}
	else
	{
		for(i=1;i<=n;i++)//循环判断
		{
			if(!visited[i])//是否访问过
			{
				visited[i]=1;//置为1
				a[k]=i;//赋值当前i给到k
				DFS(k+1);//下一步i
				visited[i]=0;//回溯
			}
		}
	}
}
int main()
{
	
	cin>>n;//输入n
	DFS(1);//从1开始深搜
	return 0;
}


