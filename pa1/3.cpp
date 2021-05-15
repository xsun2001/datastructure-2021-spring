#include <cstdio>
#include <cstdlib>
#define MAXN 501000
inline int min(int x, int y){
	return x <= y ? x : y;
}
char *str1, *str2;
char *dp;
int n, m, k;
#define DP(I, J) dp[I * m + J]
int main(){
	scanf("%d%d%d", &n, &m, &k);
	str1 = (char*) malloc(n * sizeof(char));
	str2 = (char*) malloc(m * sizeof(char));
	scanf(" %s", str1);
	scanf(" %s", str2);
	for(int i = 0; i<=m; i++) dp[0][i] = min(i, k+1);
	for(int i = 0; i<=n; i++) dp[i][0] = min(i, k+1);
	for(int i = 1; i<=n; i++){
		for(int j = 1; j<=m; j++){
			dp[i][j] = min(1 + min(dp[i-1][j], dp[i][j-1]), k+1);
			if(str1[i-1] == str2[j-1]) dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
			else dp[i][j] = min(min(dp[i][j], dp[i-1][j-1] + 2), k+1);
		}
	}
	printf("%d\n", dp[n][m] > k ? -1 : dp[n][m]);
}
