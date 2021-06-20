#include <cstdio>
#include <cstring>
#define MAXN 20000007

char str[MAXN];
int nxt[MAXN], cnt[MAXN], len;
long long ans;

int main()
{
	scanf( "%s", str );
	len = strlen( str );
	for ( int i = 1; i < len; i++ )
	{
		int j = nxt[i - 1];
		while ( j > 0 && str[i] != str[j] )
			j = nxt[j - 1];
		if ( str[i] == str[j] )
			j++;
		nxt[i] = j;
	}
	for ( int i = 0; i < len; i++ )
		cnt[nxt[i]]++;
	for ( int i = len - 1; i > 0; i-- )
		cnt[nxt[i - 1]] += cnt[i];
	for ( int i = 0; i < len; i++ )
	{
		ans += cnt[i];
	}
	printf( "%lld\n", ans );
}