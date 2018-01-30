

/*
问题描述
　　一个旅行家想驾驶汽车以最少的费用从一个城市到另一个城市（假设出发时油箱是空的）。
	给定两个城市之间的距离D1、汽车油箱的容量C（以升为单位）、每升汽油能行驶的距离D2、出发点每升汽油价格P和沿途油站数N（N可以为零），油站i离出发点的距离Di、每升汽油价格Pi（i=1，2，……N）。
	计算结果四舍五入至小数点后两位。如果无法到达目的地，则输出“No Solution”。
输入格式
　　第一行为4个实数D1、C、D2、P与一个非负整数N；
　　接下来N行，每行两个实数Di、Pi。
输出格式
　　如果可以到达目的地，输出一个实数（四舍五入至小数点后两位），表示最小费用；否则输出“No Solution”（不含引号）。
样例输入
275.6 11.9 27.4 2.8 2
102.0 2.9
220.0 2.2
样例输出
26.95
*/ 
	 
/*
	中规中矩的贪心算法题
*/
//#define showDebug true 
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXStation 1000 
struct station{
	double pos;
	double price;

}s[MAXStation];
int n;
double len;
struct car{
	double gas;
	int pos;
	double maxGas;
	double GasPerLen;
	
	double LenPerGas;
	double maxLen;
	double cost; 
	void init(){
		maxLen=maxGas*GasPerLen;
		LenPerGas=1/GasPerLen;
		gas=0;
		pos=0;
		cost=0; 
	}
	void addGas(double num){
		cost+=num*s[pos].price;
		gas+=num;
	}
	void fullGas(){
		cost+=(maxGas-gas)*s[pos].price;
		gas=maxGas;
	}
	void move(int newPos){
		double gasConsume=(s[newPos].pos-s[pos].pos)*LenPerGas;
		if(gas<gasConsume){
			cost+=(gasConsume-gas)*s[pos].price;
			gas=0;
		}else{
			gas-=gasConsume;
		}
		pos=newPos;
	}
	void go(){
		if(pos==n){
			#ifdef showDebug 
				printf("已经到达最后一个加油站\n");
			#endif
			return;
		} 
		if(maxLen<s[pos+1].pos-s[pos].pos)return;//无法到达下一站 
		double minPrice=s[pos+1].price;
		int nextBest=pos+1;
		for(int i=pos+2;i<=n&&maxLen>s[i].pos-s[pos].pos;i++){
			#ifdef showDebug
				printf("如果可以去%d站\n",i);
			#endif
			if(s[i].price<minPrice){
				#ifdef showDebug  
					printf("如果这站(%d)的价格(%lf)比最小价格(%lf)小\n",i,s[i].price,s[pos].price);
				#endif
				minPrice=s[i].price;
				nextBest=i;
				break;//有合适的立即离开 
			} 
		}
		if(minPrice>s[pos].price){
			#ifdef showDebug
				printf("后面站的最低价比本站高 则在本站（%d）加满油\n",pos);
			#endif
			fullGas();
		}
		this->move(nextBest);
		go();//继续出发 
	}
}c; 

	bool cmpPos(station tar,station cmp){
		return cmp.pos-tar.pos>0;
	}

int main(int argc, char** argv) {
	scanf("%lf %lf %lf %lf %d",&len,&c.maxGas,&c.GasPerLen,&s[0].price,&n);
	for(int i=1;i<=n;i++){
		scanf("%lf %lf",&s[i].pos,&s[i].price);
	}
	s[++n].pos=len;
	s[n].price=0;
	c.init();
	sort(s,s+n+1,cmpPos);
	#ifdef showDebug
	for(int i=0;i<=n;i++){
		printf("%.2lf %.2lf\n",s[i].pos,s[i].price);
	} 
	#endif
	c.go();
	if(c.pos==n)
		printf("%.2lf",c.cost);
	else
		printf("No Solution");
	return 0;
}
