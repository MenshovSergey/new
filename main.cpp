#include "lint.h"
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main(){
	lint a(2);
	lint b  = lint::my_pow(a,3);

	int n;
	cout << b;
	cin >> n;
	return 0;
}