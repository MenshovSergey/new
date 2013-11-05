

// lint.h


#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
using namespace std;



struct lint
{
private:

	lint multdigit(int) const;
	lint mult10(int) const;
	void initialize(const char*);

public:

	char *vlstr;
	int  vlen;
	int  vlsign;
	lint(const char* = NULL);
	lint(string);
	lint(int);
	lint(const lint &);	
	~lint();

	const lint& operator=(const lint&) ;

	lint operator- () const;

	friend lint operator+ (const lint &, const lint &);
	friend lint operator- (const lint &, const lint &);
	friend lint operator* (const lint &, const lint &);
	friend lint operator/ (const lint &, const lint &);
	friend lint operator% (const lint &, const lint &);

	friend int operator == (const lint &, const lint &);
	friend int operator != (const lint &, const lint &);
	friend int operator < (const lint &, const lint &);
	friend int operator <= (const lint &, const lint &);
	friend int operator > (const lint &, const lint &);
	friend int operator >= (const lint &, const lint &);

	operator bool() const;

	friend ostream & operator << (ostream &, const lint &);
	friend istream &  operator >> (istream &,lint&);
	friend lint abs(const lint &);

	char *strrev(char *s) const;
	string to_String() const;

	lint operator += (const lint &) ;
	lint operator -= (const lint &) ;
	friend lint& operator ++ (lint &);
	friend lint operator ++ (lint&, int);
	friend lint& operator -- (lint &);
	friend lint operator -- (lint&, int);
	static lint& my_pow(const lint&, int);
	
	
};

static lint zero = lint("0");
static lint one = lint("1");
static lint two = lint("2");




