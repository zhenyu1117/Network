#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int read()
{
	int x=0,w=1;char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*w;
}
const int N=100010;
int n,m,x,y,cnt,ans;
int head[N],deep[N],f[N][20],a[N];
struct node{
	int to,next;
}edge[2*N];
void add(int x,int y)
{
	cnt++;
	edge[cnt].to=y;
	edge[cnt].next=head[x];
	head[x]=cnt;
}
void init()
{
	for(int i=1;i<=19;i++)
		for(int j=1;j<=n;j++)
			f[j][i]=f[f[j][i-1]][i-1];
}
void dfs(int k,int fa)
{
	for(int i=head[k];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa) continue;
		deep[v]=deep[k]+1;f[v][0]=k;
		dfs(v,k);
	}
}
int LCA(int x,int y)
{
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=19;i>=0;i--)
	{
		if(deep[f[x][i]]>=deep[y]) x=f[x][i];
	}
	if(x==y) return x;
	for(int i=19;i>=0;i--)
	{
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
void get(int k,int fa)
{
	for(int i=head[k];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa) continue;
		get(v,k);
		a[k]+=a[v];
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<n;i++)
	{
		x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);init();
	for(int i=1;i<=m;i++)
	{
		x=read();y=read();
		int lca=LCA(x,y);
		a[x]++;a[y]++;a[lca]-=2;
	}
	get(1,0);
	for(int i=2;i<=n;i++)
	{
		if(a[i]==0) ans+=m;
		else if(a[i]==1) ans++;
	}
	cout<<ans;
}
