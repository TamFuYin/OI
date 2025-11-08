#include"message.h"
#include<bits/stdc++.h>
void send_message(std::vector<bool> M,std::vector<bool> C){
	const unsigned int MASK=3051994266;
	std::vector<char> col[31];
	std::vector<bool> row;
	for(int i=0;i<31;i++) col[i].clear();
	M.push_back(1);
	while(M.size()<1025) M.push_back(0);
	int c=0;while(C[c]) ++c;
	for(int i=0;i<31;i++) col[c].push_back(C[i]);
	col[c].push_back(0);
	for(int i=0;i<31;i++) printf("%d",col[c][i]),col[c][i]^=MASK>>i&1;
	puts("");puts("----------------");
	assert(!C[c]);
	int cur=0;
	for(int i=0;i<31;i++) if(!C[i])
		while(col[i].size()<66) col[i].push_back(M[cur++]);
	assert(cur==1025);
	for(int i=0;i<31;i++) assert(col[i].size()==(C[i]?0:66));
//	for(int i=0;i<31;i++) printf("%d",(int)C[i]);puts("");
	for(int i=0;i<66;i++){
		row.clear();
		for(int j=0;j<31;j++){
			if(C[j]) row.push_back(0);
			else row.push_back(col[j][i]);
		}
		send_packet(row);
	}
}
std::vector<bool> receive_message(std::vector<std::vector<bool> > R){
	const unsigned int MASK=3051994266;
	std::vector<char> C(31);
	int c=-1;
	for(int i=0;i<31;i++){
		for(int j=0;j<31;j++)
			C[j]=R[j][i]^(MASK>>j&1),
			printf("%d",C[j]);
		puts("");
		if(C[30]||C[i]) continue;
		int cnt=0;
		for(int j=0;j<30;j++){
			cnt+=C[j];
			if(!C[j]&&j<i) goto Continue;
		}
		printf("%d\n",cnt);
		if(cnt!=15) continue;
		c=i;break;
		Continue:;
	}
	assert(c!=-1);
//	printf("%d\n",(int)C[31]);
//	for(int i=0;i<32;i++) printf("%d",(int)C[i]);puts("");
	C.insert(C.begin()+c,0);
//	for(int i=0;i<31;i++) printf("%d",(int)C[i]);puts("");
	std::vector<bool> ans;
	for(int i=0;i<31;i++)if(!C[i]){
		for(int j=(i==c?31:0);j<66;j++)
			ans.push_back(R[j][i]);
	}
	while(ans.back()!=1) ans.pop_back();
	ans.pop_back();
	return ans;
}
