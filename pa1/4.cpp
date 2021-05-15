#include <cstdio>

#define L(I) (I<<1)
#define R(I) ((I<<1)|1)
#define P(I) (I>>1)

#define MAXN 1000006

struct Node{
	unsigned day, m;
}nodes[MAXN];
unsigned node_count;
unsigned n, t, p, q, x[MAXN], m[MAXN], k[MAXN];

void swapI(unsigned* i, unsigned* j){
	unsigned tmp = *i;
	*i = *j;
	*j = tmp;
}

void swapN(unsigned i, unsigned j){
	swapI(&nodes[i].day, &nodes[j].day);
	swapI(&nodes[i].m, &nodes[j].m);
}

void down(unsigned i){
	unsigned l = L(i), r = R(i);
	if(nodes[i].m >= nodes[l].m && nodes[i].m >= nodes[r].m) return;
	if(nodes[i].m <= nodes[l].m && nodes[i].m <= nodes[r].m){
		if(nodes[l].m >= nodes[r].m) swapN(i, l), down(l);
		else swapN(i, r), down(r);
	}else{
		if(nodes[i].m <= nodes[l].m) swapN(i, l), down(l);
		else swapN(i, r), down(r);
	}
}

void up(unsigned i){
	if(i == 1) return;
	unsigned p = P(i);
	if(nodes[i].m > nodes[p].m){
		swapN(i, p);
		up(p);
	}
}

void pop(){
	nodes[1].day = nodes[node_count].day;
	nodes[1].m = nodes[node_count].m;
	nodes[node_count].day = 0;
	nodes[node_count].m = 0;
	--node_count;
	down(1);
}

void push(unsigned day, unsigned m){
	++node_count;
	nodes[node_count].day = day;
	nodes[node_count].m = m;
	up(node_count);
}

unsigned partition(unsigned* arr, unsigned l, unsigned r){
	unsigned s = l, p = arr[l];
	for(unsigned h = l+1; h<=r; h++){
		if(arr[h] <= p){
			++s;
			swapI(arr+s, arr+h);
		}
	}
	swapI(arr+l, arr+s);
	return s;
}

void sort(unsigned *arr, unsigned l, unsigned r){
	if(l >= r) return;
	unsigned m = partition(arr, l, r);
	sort(arr, l, m-1);
	sort(arr, m+1, r);
}

unsigned bisearch(unsigned *arr, unsigned l, unsigned r, unsigned X){
	while(l <= r){
		unsigned m = l + ((r - l) >> 1);
		if(arr[m] < X) l = m+1;
		else if(arr[m] > X) r = m-1;
		else return m - 1;
	}
	return l - 1;
}

int main(){
	scanf("%d", &n);
	for(unsigned i = 1;i<=n;i++) scanf("%d", x+i);
	for(unsigned i = 1;i<=n;i++) scanf("%d", m+i);

	for(unsigned i = 1;i<=n;i++){
		unsigned min_day = i - m[i];
		if(node_count > 0 && nodes[1].day < min_day)
			pop();
		k[i] = nodes[1].m;
		push(i, x[i]);
	}

	sort(k, 1, n);

	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &p, &q);
		unsigned i1 = bisearch(k, 1, n, p);
		unsigned i2 = bisearch(k, 1, n, q) - i1;
		printf("%d %d\n", i1, i2);
	}
}
