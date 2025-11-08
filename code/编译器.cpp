#include<bits/stdc++.h>
enum{
	VAR,RUN,MOV,ADD,MLP,DIV,MOD,
};
namespace compiler{
	void precompile(std::vector<std::string>& file){
		for(auto line:file){
			for(int i=0;i<line.size()-1;i++){
				if(line.substr(i,2)=="//"){
					line=line.substr(0,i);
					break;
				}
			}
		}
		for(auto line:file){
			if(line[0]=='#'){
				//暂不支持 define 功能
				line.clear();
			}
			if(line=="using namespace std;"){
				line.clear();
			}
		}
		for(auto )
	}
	std::vector<ASM> compile(std::vector<std::string> file){
	}
}
const int N=1e5;
std::vector<int> in;
std::string line;
std::vector<std::string> cpp;
int main(){
	int n;std::cin>>n;in.resize(n);
	for(int i=1;i<=n;i++) std::cin>>in[i];
	while(std::getline(std::cin,line)) cpp.push_back(line);
	compiler::compile(cpp);
}
