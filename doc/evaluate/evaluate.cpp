#include <iostream>
#include <cstdlib>
#include <set>
#include <cstring>
using namespace std;

typedef unsigned long long ULL;
typedef set<ULL>::iterator SIT;

const int m = (1 << 11);
const int D = 32;
const int MAXD = 14;
const int TRIES = 10000;

ULL n;
set<ULL> C[MAXD+1];
ULL E[MAXD+1][m];
int cnt[MAXD+1];

ULL genRand(){
	ULL res = rand();
	res = (res << D/2) ^ rand();
	return res%n;
}

void simulate()
{
	C[0].clear();
	C[0].insert(0);
	for(int i=0; i<MAXD; i++){
		for(int j=0; j<m; j++){
			E[i][j] = genRand();
			if (C[i].find(E[i][j]) != C[i].end())
				return;
		}
		C[i+1].clear();
		for(SIT it=C[i].begin(); it != C[i].end(); ++it){
			ULL v = *it;
			if (C[i+1].find(v) != C[i+1].end())
				return;
			ULL sv = genRand();
			while (sv == v || C[i+1].find(sv) != C[i+1].end())
				sv = genRand();
			C[i+1].insert(v);
			C[i+1].insert(sv);
		}

		for(int j=0; j<=i; j++)
			for(int k=0; k<m; k++)
				if (C[i+1].find(E[j][k]) != C[i+1].end())
					return;
		cnt[i+1]++;
	}
}

int main()
{
	n = 1;
	for(int i=0; i<D; i++)
		n *= 2;
	memset(cnt, 0, sizeof(cnt));

	for(int i=0; i<10; i++){
		cout << "test rand " << i << " = " << genRand() << endl;
	}

	for(int i=0; i<TRIES; i++){
		simulate();
		cout << "Simulate " << i << " completed." << endl;
	}

	for(int i=1; i<=MAXD; i++)
		cout << "cnt[" << i << "]" << cnt[i] << endl;
}

