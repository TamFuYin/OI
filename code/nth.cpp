#include "nth.h"
namespace Alice{
	int a;
	void initA(std::bitset<M> A,unsigned S,unsigned c){
		a=A.count();
		for(int i=20;i>=0;i--) sendA(a>>i&1);
	}
	void receiveA(bool x){
	}
}
namespace Bob{
	int a,b,cur=20,c;
	std::bitset<M> B;
	void initB(std::bitset<M> _B,unsigned S,unsigned _c){
		b=B.count();c=_c;B=_B;
	}
	void receiveB(bool x){
		a|=int(x)<<(cur--);
		if(cur==-1){
			if(a<b){
				if()
			}
		}
	}
}
