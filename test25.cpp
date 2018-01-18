#include <iostream>    
#include <string.h>  
#include <algorithm>   
using namespace std;  
const int inf = 0x3f3f3f3f; 
// 0xffffffff = -1; 0x3f3f3f3f=(0011 1111 ...)2 :������  
int N, M, S, D;  
//������ ��·��  �����صĳ��б�ţ�Ŀ�ĵصĳ��б�š� 
int map[550][550];
// ��ͼ��Ϣ  
int val[550], dis[550], vis[550], cnt[550], sum[550], pre[550];  
//ÿ��Ȩֵ   ��S����   ���    ·����ʽ���� ����Ԯ��  ǰ��   
void path(int d) {  
//�� �ݹ� ��ʽ ��� ·�� 
    if(pre[d] != -1) {  // ������S�Լ�����һ�εݹ鲻������κ����� 
        path(pre[d]);  
        printf("%d ", pre[d]); //������ڵ� 
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
    for(i = 0; i < N; i++) {  //��ʼ��   
        dis[i] = inf;  
        vis[i] = 0;  
        cnt[i] = 0;  
        sum[i] = 0;  
        pre[i] = -1;  
    }  
    dis[S] = 0;  //��ʼ����ʼ��   
    vis[S] = 1;  
    cnt[S] = 1; //��㵽�䱾��ʽΪ1   
    sum[S] = val[S];  
    for(i = 0; i < N; i++) {  
        int minn = inf, mini = S;  
        for(j = 0; j < N; j++) {  
            if(vis[j] == 0 && minn > dis[j]) {  
			// Ѱ��   �� ������ ���� ��i�� ���� ���뵽δ�����ĳ��� 
			// ����   �γɵ� ����·�� �� ��̵�һ��  
                minn = dis[j];  
                mini = j;  
            }  
        }  
        vis[mini] = 1; 
		// ˢ��   �� ������ ���� ��(i+1)�� ���� ���뵽δ�����ĳ��� 
		// ����   �γɵ� ����·�� �� ��
		// ��S����(dis),����Ԯ��(sum),·����ʽ����(cnt),ǰ��(pre)
		// ��Щ���� 
        for(j = 0; j < N; j++) {  
            if(vis[j] == 0) {  
                if(dis[j] > dis[mini] + map[mini][j]) {  
                    dis[j] = dis[mini] + map[mini][j];  
                    sum[j] = sum[mini] + val[j];  
                    cnt[j] = cnt[mini];  //��ʽ���ڵ���ǰ���ķ�ʽ   
                    pre[j] = mini;  
                }  
                else if(dis[j] == dis[mini] + map[mini][j]) {  
                    cnt[j] = cnt[mini] + cnt[j]; //���ַ�ʽ������ȣ���ʽ�����   
                    if(sum[j] < sum[mini] + val[j]) {  //�ܻ�ø���ľ�Ԯ�������   
                        sum[j] = sum[mini] + val[j];  
                        pre[j] = mini;  
                    }  
                }  
            }  
        }  
    }  
    printf("%d %d\n", cnt[D], sum[D]);
	//��D��·����ʽ��  ��Ԯ����Ŀ 
    path(D);  
    //�� �ݹ� ��ʽ ��� ·�� 
    printf("%d\n", D);  
    //����δ��������յ� 
    return 0;  
}  
