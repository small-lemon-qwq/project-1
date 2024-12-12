#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int l,r;
	long double c,m,Lazy;
}t[2000005];
pair<int,int>a[1000005];
node merge(node x,node y){
	if(x.l==-1)return y;
	if(y.l==-1)return x;
	return{x.l,y.r,(x.c*x.m+y.c*y.m)/(x.m+y.m),x.m+y.m};
}
void build(int l,int r,int p){
	t[p].l=l;
	t[p].r=r;
	t[p].Lazy=0;
	int m=(l+r)>>1;
	if(l==r){
		t[p].c=a[m].first;
		t[p].m=a[m].second;
		return;
	}
	build(l,m,p*2);
	build(m+1,r,p*2+1);
	t[p]=merge(t[p*2],t[p*2+1]);
}
node getsum(int l,int r,int p){
	int L=t[p].l,R=t[p].r;
	if(L>=l&&R<=r)return t[p];
	if(R<l||L>r)return{-1};
	int m=(L+R)>>1;
	if(t[p].Lazy&&L!=R){
		t[p*2].c+=t[p].Lazy;
		t[p*2+1].c+=t[p].Lazy;
		t[p*2].Lazy+=t[p].Lazy;
		t[p*2+1].Lazy+=t[p].Lazy;
		t[p].Lazy=0;
	}
	return merge(getsum(l,r,p*2),getsum(l,r,p*2+1));
}
void update(int l,int r,int p,int c){
	int L=t[p].l,R=t[p].r;
	if(L>=l&&R<=r){t[p].c+=c;t[p].Lazy+=c;return;}
	if(R<l||L>r)return;
	int m=(L+R)>>1;
	if(t[p].Lazy&&L!=R){
		t[p*2].c+=t[p].Lazy;
		t[p*2+1].c+=t[p].Lazy;
		t[p*2].Lazy+=t[p].Lazy;
		t[p*2+1].Lazy+=t[p].Lazy;
		t[p].Lazy=0;
	}
	update(l,r,p*2,c);
	update(l,r,p*2+1,c);
	t[p]=merge(t[p*2],t[p*2+1]);
}
int n;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].first>>a[i].second;
	}
	build(1,n,1);
	int op;
	while(cin>>op){
		if(op==1){
			int l,r;
			cin>>l>>r;
			cout<<getsum(l,r,1).c<<"\n";
		}else{
			int l,r,x;
			cin>>l>>r>>x;
			update(l,r,1,x);
		}
	}
	return 0;
}
/*
3
50 3
100 1
90 1
*/