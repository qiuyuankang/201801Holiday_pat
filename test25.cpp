#include <iostream>    
#include <string.h>  
#include <algorithm>   
using namespace std;  
const int inf = 0x3f3f3f3f; 
// 0xffffffff = -1; 0x3f3f3f3f=(0011 1111 ...)2 :是正数  
int N, M, S, D;  
//城市数 道路数  出发地的城市编号；目的地的城市编号。 
int map[550][550];
// 地图信息  
int val[550], dis[550], vis[550], cnt[550], sum[550], pre[550];  
//每点权值   距S距离   标记    路径方式数量 最大救援队  前驱   
void path(int d) {  
//用 递归 方式 输出 路径 
    if(pre[d] != -1) {  // 出发点S自己的那一次递归不会输出任何数据 
        path(pre[d]);  
        printf("%d ", pre[d]); //输出父节点 
    }  
}  
int main() {  
    scanf("%d %d %d %d", &N, &M, &S, &D);  
    int i, j;  
    for(i = 0; i < N; i++) {  
        scanf("%d", val + i);  
    }  
    for(i = 0; i < N; i++) {  
        for(j = 0; j < N; j++) {  
            if(i == j) map[i][j] = 0;  
            else map[i][j] = inf;  
        }  
    }  
    int x, y, z;  
    for(i = 0; i < M; i++) {  
        scanf("%d %d %d", &x, &y, &z);  
        map[x][y] = z;  
        map[y][x] = z;  
    }  
    for(i = 0; i < N; i++) {  //初始化   
        dis[i] = inf;  
        vis[i] = 0;  
        cnt[i] = 0;  
        sum[i] = 0;  
        pre[i] = -1;  
    }  
    dis[S] = 0;  //初始化起始点   
    vis[S] = 1;  
    cnt[S] = 1; //起点到其本身方式为1   
    sum[S] = val[S];  
    for(i = 0; i < N; i++) {  
        int minn = inf, mini = S;  
        for(j = 0; j < N; j++) {  
            if(vis[j] == 0 && minn > dis[j]) {  
			// 寻找   从 出发地 出发 走i步 而且 必须到未到过的城市 
			// 这样   形成的 所有路径 中 最短的一条  
                minn = dis[j];  
                mini = j;  
            }  
        }  
        vis[mini] = 1; 
		// 刷新   从 出发地 出发 走(i+1)步 而且 必须到未到过的城市 
		// 这样   形成的 所有路径 的 ：
		// 距S距离(dis),最大救援队(sum),路径方式数量(cnt),前驱(pre)
		// 这些数据 
        for(j = 0; j < N; j++) {  
            if(vis[j] == 0) {  
                if(dis[j] > dis[mini] + map[mini][j]) {  
                    dis[j] = dis[mini] + map[mini][j];  
                    sum[j] = sum[mini] + val[j];  
                    cnt[j] = cnt[mini];  //方式等于到达前驱的方式   
                    pre[j] = mini;  
                }  
                else if(dis[j] == dis[mini] + map[mini][j]) {  
                    cnt[j] = cnt[mini] + cnt[j]; //两种方式距离相等，则方式数相加   
                    if(sum[j] < sum[mini] + val[j]) {  //能获得更大的救援，则更新   
                        sum[j] = sum[mini] + val[j];  
                        pre[j] = mini;  
                    }  
                }  
            }  
        }  
    }  
    printf("%d %d\n", cnt[D], sum[D]);
	//到D的路径方式数  救援队数目 
    path(D);  
    //用 递归 方式 输出 路径 
    printf("%d\n", D);  
    //补充未被输出的终点 
    return 0;  
}  
