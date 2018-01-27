#include <iostream>
#define MAX 201
int num[MAX][MAX];//最多有200个 
int m,n;
short direction[4][2]={
						{0,1},{1,0},
						{0,-1},{-1,0}
					};
short nowDirection=0;
bool DirectionChanged=false;
void init(){
	scanf("%d %d",&m,&n);	
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&num[i][j]);
}
void output(int x,int y){
	x+=direction[nowDirection][0];
	y+=direction[nowDirection][1];

	if(x<0||x>=n||y<0||y>=m||num[y][x]==-1){
		if(DirectionChanged)return;//如果已经变更过一次方向仍然不能动，则结束了 
		x-=direction[nowDirection][0];
		y-=direction[nowDirection][1];
		nowDirection++;
		if(nowDirection>3)nowDirection=0;
		DirectionChanged=true;
		
	}else{
		DirectionChanged=false; 
		printf("%d ",num[y][x]);
		num[y][x]=-1;
	}
	output(x,y); 
}
int main(int argc, char** argv) {
	init();
	output(0,-1);
	return 0;
}
