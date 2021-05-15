#include <cstdlib>
#include <cstdio>
#include <cstring>

const int MAXN = 600;
int a[MAXN], b[MAXN], r[MAXN*MAXN];
char buf[5001];

bool isNumber(char c){
	return c >= '0' && c <= '9';
}
void readBigInteger(int *bi){
	while(!isNumber(buf[0]=getchar()));
	int i = 1;
	for(; isNumber(buf[i]=getchar()); i++);
	--i;
	while(i>=0){
		*bi = 0;
		int factor = 1;
		for(int j = 0; j < 9 && j <= i;j++){
			*bi += factor * (buf[i-j] - '0'); 
			factor *= 10;
		}
		++bi;
		i -= 9;
	}
	*bi = -1;
}
void writeBigInteger(int *bi){
	int len = 0;
	for(; bi[len] >= 0; len++);
	printf("%d", bi[--len]);
	for(--len; len >= 0; len--) printf("%09d", bi[len]);
	printf("\n");
}
void multiply(){
	memset(r,0, MAXN*MAXN*sizeof(int));
	int rl = 0;
	long long tmp = 0;
	for(int i = 0; a[i] >= 0; i++){
		for(int j = 0; b[j] >= 0; j++){
			tmp = r[i+j] + (long long)(a[i]) * b[j];
			r[i+j] = tmp % 1000000000;
			r[i+j+1] += tmp / 1000000000;
			if(r[i+j] && i+j>rl) rl = i+j;
			if(r[i+j+1] && i+j+1>rl) rl = i+j+1;
		}
	}
	r[rl+1]=-1;
}
int n;
int main(){
	scanf("%d", &n);
	while(n--){
		readBigInteger(a);
		readBigInteger(b);
		// writeBigInteger(a);
		// writeBigInteger(b);
		multiply();
		writeBigInteger(r);
	}
	
}
