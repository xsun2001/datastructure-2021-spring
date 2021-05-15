#include <cstdlib>
#include <cstdio>
using ll = long long;
using namespace std;

ll n, m, px, py;
ll x[200000], y[200000];

inline bool isNumber(char c){
	return c >= '0' && c <= '9';
}
inline ll readInt(){
	char c;
	ll res = 0;
	while(!isNumber(c = getchar()));
	do{
		res = res*10+c-'0';
	}while(isNumber(c = getchar()));
	return res;
}
inline void swap(ll *a, ll  *b){
	ll t = *a;
	*a = *b;
	*b = t;
}
inline int partition(ll *a, int l, int r){
	int s = l;
	ll p = a[l];
	for(int h = l+1; h<r; h++){
		if(a[h] <= p){
			s++;
			swap(a+s, a+h);
		}
	} 
	swap(a+l, a+s);
	return s;
}
void quicksort(ll *a, int l, int r){
	if(l >= r) return;
	int m = partition(a, l, r);
	quicksort(a, l, m);
	quicksort(a, m+1, r);
}
inline ll toLeft(int k){
	return -x[k]*py - y[k]*(px-x[k]);
}
inline int search(int l, int r){
	while(l<=r){
		int m = l+((r-l)>>1);
		ll left = toLeft(m);
		if(left > 0) r = m-1;
		else if(left < 0) l = m+1;
		else return m+1;
	}
	return l;
}
int main(){
	n = readInt();
	for(ll i = 0;i<n;i++) x[i] = readInt();
	for(ll i = 0;i<n;i++) y[i] = readInt();
	quicksort(x, 0, n);
	quicksort(y, 0, n);
	
	m = readInt();
	while(m--){
		px = readInt(), py = readInt();
		printf("%d\n", search(0, n-1));
	}
}
