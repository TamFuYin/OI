#include"graph.h"
#include<bits/stdc++.h>

namespace my_space
{
	const int n=100;
	int e[105][105],exist[105][105],Q;
	char s[105];
}

int query(int a,int b,int c)
{
	using namespace my_space;
	if(++Q>161700)
	{
		puts("Too many queries!");
		exit(0);
	}
	if(a<1||a>n||b<1||b>n||c<1||c>n)
	{
		puts("Illegal operation!");
		exit(0);
	}
	if(a==b||b==c||a==c)
	{
		puts("Illegal operation!");
		exit(0);
	}
	return e[a][b]+e[a][c]+e[b][c];
}

void report(int a,int b)
{
	using namespace my_space;
	if(a<b)std::swap(a,b);
	if(!exist[a][b])
	{
		puts("Wrong graph!");
		exit(0);
	}
	exist[a][b]=0;
}

double score()
{
	using namespace my_space;
	if(Q>161700)return 0;
	if(Q>=9900)return 30.0*(161700-Q)/(161700-9900);
	if(Q>=4950)return 30+30.0*(9900-Q)/(9900-4950);
	if(Q>=3400)return 60+30.0*(4950-Q)/(4950-3400);
	return 100;    
}

main()
{
	using namespace my_space;
	for(int i=1,j;i<=n;++i)
	{
		scanf("%s",s+1);
		for(j=1;j<=n;++j)e[i][j]=exist[i][j]=s[j]=='1';
	}
	get_graph();
	for(int i=1,j;i<=n;++i)for(j=1;j<=i;++j)if(exist[i][j])
	{
		puts("Wrong graph!");
		exit(0);
	}
	puts("Correct!");
	printf("Score = %.10lf.\n",score());
}
