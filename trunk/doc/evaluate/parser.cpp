#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main()
{
	string line;
	cout << "x, y" << endl;
	while (getline(cin, line)){
		if (line[0] == 'c'){
			int i, t;
			sscanf(line.c_str(), "cnt[%d]%d", &i, &t);
			printf("%lf, %lf\n", (double)i, t/10000.0);
		}
	}
}

