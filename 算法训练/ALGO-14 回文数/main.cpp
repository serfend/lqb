/*
	进制的转换
	大数的加法运算
	
	在计算左半边和右半边时可能还能再优化 
*/
#include <iostream>
#include <string.h>
#define MAXLENGTH 31
int radix;
struct BN{
	int value[MAXLENGTH];
	int len;
	BN(char info[]){
		memset(value,0,sizeof(value));
		len=strlen(info);
		for(int i=0;i<len;i++){
			int tmp=info[len-i-1];
			if(tmp>='A')tmp=tmp-'A'+10;
			else if(tmp>='0')tmp-='0';
			value[i]=tmp;
		}
	}
	BN Add(){
		int tmp[MAXLENGTH]={0};
		int length=len/2+1;
		int carry=0;
		for(int i=0;i<length;i++){
			tmp[i]=value[i]+value[len-i-1];
		}
		for(int i=0;i<length;i++){
			value[i]=tmp[i]+carry;
			if(value[i]>=radix){
				value[i]-=radix;
				carry=1;
			}else{
				carry=0;
			}
		}
		for(int i=length;i<len-1;i++){
			value[i]=tmp[len-i-1]+carry;
			if(value[i]>=radix){
				value[i]-=radix;
				carry=1;
			}else{
				carry=0;
			}
		}
		value[len-1]=tmp[0]+carry;
		if(tmp[0]>=radix){
			value[len-1]-=radix;
			value[len++]=1;
		}
	}
	void Show(){
		for(int i=0;i<len;i++){
			int tmp=value[len-i-1];
			printf("%x",tmp);
		}
		printf("\n");
	}
	bool check(){
		int length=len/2+1;
		for(int i=0;i<length;i++){
			if(value[i]!=value[len-i-1])return false;
		}
		return true;
	}
}; 
int main(int argc, char** argv) {
//	freopen("input2.txt","r",stdin);
	scanf("%d",&radix);
	char info[1024];
	scanf("%s",info);
	BN rel=info;
	int ans;
//	rel.Show();
	for(ans=0;ans<=MAXLENGTH;ans++){
		rel.Add();
//		rel.Show();
		if(rel.check())break;
	};
	if(ans>MAXLENGTH){
		printf("Impossible!");
	}else{
		printf("STEP=%d",ans+1);
	}
		
	return 0;
}
