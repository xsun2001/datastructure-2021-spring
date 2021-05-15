#include <cstdio>

int bufRing[100000];
int begin, end, n, m, x, res;

int main(){
	scanf("%d%d", &n, &m);
	while(m--){
		scanf("%d", &x);
		int found = 0;
		for(int i = begin; i<end; i++){
			if(x == bufRing[i]){
				found = 1;
				break;
			}
		}
		if(found == 0){
			++res;
			bufRing[end] = x;
			++end;
		}
		if(end-begin > n){
			++begin;
		}
	}
	printf("%d\n", res);
}
