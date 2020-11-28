#include <stdio.h>
#include <string.h>

typedef struct tagNode{
	int x,y;
	int dir;
}Node;

const int M=105;

int A,B;
int n,m;

int map[M][M];
Node node[M];

int get_dir(char c)
{
	switch(c){
	case 'N':
		return 1;
	case 'E':
		return 2;
	case 'S':
		return 3;
	case 'W':
		return 0;
	}
	return -1;
}

int main()
{
	int N;
	for(scanf("%d",&N);N--;){
		memset(map,0,sizeof(map));
		scanf("%d%d%d%d",&A,&B,&n,&m);
		int x,y;
		char c[10];
		for(int i=0;i<n;i++){
			scanf("%d%d%s",&x,&y,c);
			map[x][y]=i+1;
			node[i+1].x=x;
			node[i+1].y=y;
			node[i+1].dir=get_dir(c[0]);
		}
		bool f=false;
		int I=0,num=0;
		for(int L=0;L<m;L++){
			scanf("%d%s%d",&I,c,&num);
			if(f)
				continue;
			Node tmp=node[I];
			map[node[I].x][node[I].y]=0;
			if(c[0]=='F'){
				if(tmp.dir==0)
					//tmp.x-=num;
					for(int i=0;i<num;i++){
						--tmp.x;
						if(tmp.x<1||tmp.x>A||tmp.y<1||tmp.y>B){
							f=true;
							printf("Robot %d crashes into the wall\n",I);
							break;
						}else if(map[tmp.x][tmp.y]){
							f=true;
							printf("Robot %d crashes into robot %d\n",I,map[tmp.x][tmp.y]);
							break;
						}
					}
				if(tmp.dir==1)
					//tmp.y+=num;
					for(int i=0;i<num;i++){
						++tmp.y;
						if(tmp.x<1||tmp.x>A||tmp.y<1||tmp.y>B){
							f=true;
							printf("Robot %d crashes into the wall\n",I);
							break;
						}else if(map[tmp.x][tmp.y]){
							f=true;
							printf("Robot %d crashes into robot %d\n",I,map[tmp.x][tmp.y]);
							break;
						}
					}
				if(tmp.dir==2)
					//tmp.x+=num;
					for(int i=0;i<num;i++){
						++tmp.x;
						if(tmp.x<1||tmp.x>A||tmp.y<1||tmp.y>B){
							f=true;
							printf("Robot %d crashes into the wall\n",I);
							break;
						}else if(map[tmp.x][tmp.y]){
							f=true;
							printf("Robot %d crashes into robot %d\n",I,map[tmp.x][tmp.y]);
							break;
						}
					}
				if(tmp.dir==3)
					//tmp.y-=num;
					for(int i=0;i<num;i++){
						--tmp.y;
						if(tmp.x<1||tmp.x>A||tmp.y<1||tmp.y>B){
							f=true;
							printf("Robot %d crashes into the wall\n",I);
							break;
						}else if(map[tmp.x][tmp.y]){
							f=true;
							printf("Robot %d crashes into robot %d\n",I,map[tmp.x][tmp.y]);
							break;
						}
					}
			}
			if(c[0]=='L')
				tmp.dir=(tmp.dir-num+num*4)%4;
			if(c[0]=='R')
				tmp.dir=(tmp.dir+num)%4;
			node[I]=tmp;
			map[tmp.x][tmp.y]=I;
		}
		if(!f)
			puts("OK");
	}
	return 0;
}
