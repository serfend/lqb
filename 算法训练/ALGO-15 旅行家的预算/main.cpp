

/*
��������
����һ�����м����ʻ���������ٵķ��ô�һ�����е���һ�����У��������ʱ�����ǿյģ���
	������������֮��ľ���D1���������������C������Ϊ��λ����ÿ����������ʻ�ľ���D2��������ÿ�����ͼ۸�P����;��վ��N��N����Ϊ�㣩����վi�������ľ���Di��ÿ�����ͼ۸�Pi��i=1��2������N����
	����������������С�������λ������޷�����Ŀ�ĵأ��������No Solution����
�����ʽ
������һ��Ϊ4��ʵ��D1��C��D2��P��һ���Ǹ�����N��
����������N�У�ÿ������ʵ��Di��Pi��
�����ʽ
����������Ե���Ŀ�ĵأ����һ��ʵ��������������С�������λ������ʾ��С���ã����������No Solution�����������ţ���
��������
275.6 11.9 27.4 2.8 2
102.0 2.9
220.0 2.2
�������
26.95
*/ 
	 
/*
	�й��оص�̰���㷨��
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
				printf("�Ѿ��������һ������վ\n");
			#endif
			return;
		} 
		if(maxLen<s[pos+1].pos-s[pos].pos)return;//�޷�������һվ 
		double minPrice=s[pos+1].price;
		int nextBest=pos+1;
		for(int i=pos+2;i<=n&&maxLen>s[i].pos-s[pos].pos;i++){
			#ifdef showDebug
				printf("�������ȥ%dվ\n",i);
			#endif
			if(s[i].price<minPrice){
				#ifdef showDebug  
					printf("�����վ(%d)�ļ۸�(%lf)����С�۸�(%lf)С\n",i,s[i].price,s[pos].price);
				#endif
				minPrice=s[i].price;
				nextBest=i;
				break;//�к��ʵ������뿪 
			} 
		}
		if(minPrice>s[pos].price){
			#ifdef showDebug
				printf("����վ����ͼ۱ȱ�վ�� ���ڱ�վ��%d��������\n",pos);
			#endif
			fullGas();
		}
		this->move(nextBest);
		go();//�������� 
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
