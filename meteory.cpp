#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define F first
#define S second
#define pii pair<int,int>
#define vi vector<int>
#define vpii vector<pii>

#define loop(i,n) sloop(0,i,n)
#define sloop(s, i, n) for(int i=(s);i<(n);i++)

#define all(v) (v).begin(),(v).end()

#define int long long

class Fenwick{
int n;
vi fen;
int lsb(int x){return x&-x;}

void up_pref(int id,int val){
	while(id<=n){
		fen[id]+=val;
		id+=lsb(id);
	}
}

public:
	void update(const tuple<int,int,int>&a){
		int l = get<0>(a);
		int r = get<1>(a);
		int val = get<2>(a);
		//cout<<l<<' '<<r<<' '<<val<<endl;
		if(l<=r){up_pref(r+1,-val);up_pref(l,val);}
		else{
			up_pref(n+1, -val);
			up_pref(l, val);
			up_pref(r+1, -val);
			up_pref(1,val);
		}
	}

	void reset(){
		fill(all(fen),0);
	}

	int get_val(int id){
		int res=0;
		while(id){
			res+=fen[id];
			id-=lsb(id);
		}
		return res;
	}

	Fenwick(int _n):n(_n),fen(n+1){}

};


void solve()
{
	int n,m;
	cin>>n>>m;
	vector<vi>wlasn(n+1);
	loop(i,m){
		int x;
		cin>>x;
		wlasn[x].pb(i+1);
	}

	/*
	loop(i,n+1){
		cout<<i<<": ";
		for(int j:wlasn[i])cout<<j<<' ';
		cout<<endl;
	}*/

	vi pot(n+1);
	loop(i,n)cin>>pot[i+1];

	int q;
	cin>>q;

	Fenwick fen(m+1);

	vector<tuple<int,int,int>> queries(q);
	for(auto &[l,r,v]:queries){
		cin>>l>>r>>v;
	}
	queries.pb({1,m,2*1e9});
	++q;

	vpii prz(n+1);
	loop(i,n+1)prz[i]={1,q};

	vpii v;
	v.reserve(n);
	

	while(1){

		sloop(1,i,n+1){
			if(prz[i].F<prz[i].S){
				int mi = (prz[i].F+prz[i].S)/2;
				v.pb({mi,i});
			}
		}

		if(!v.size())break;
		sort(v.rbegin(),v.rend());

		fen.reset();

		sloop(1,t,q+1){
			fen.update(queries[t-1]);
			//if(!v.size())break;
			while(v.size()&&v.back().F==t){
				int s=0;
				for(int i:wlasn[v.back().S]){
					s+=fen.get_val(i);
					//cout<<s<<' '<<i<<endl;
				}
				//cout<<t<<' '<<v.back().S<<' '<<s<<' '<<pot[v.back().S]<<endl;
				if(s>=pot[v.back().S])prz[v.back().S].S=t;
				else prz[v.back().S].F=t+1;
				v.pop_back();
			}
		}

		}

	//cout<<endl;
	//sloop(1,i,n+1)cout<<prz[i].F<<' '<<prz[i].S<<'\n';
	sloop(1,i,n+1){
		if(prz[i].F==q)cout<<"NIE\n";
		else cout<<prz[i].F<<'\n';
	}
}

signed main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	solve();

	cout << '\n';
	return 0;
}
