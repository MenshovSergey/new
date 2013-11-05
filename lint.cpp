
#include "lint.h"
// lint.h


#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <string>
using namespace std;


lint::lint(const char *value)
{
	initialize(value);
	
}

lint::operator bool() const{
	return (*this != zero);
}

void lint::initialize(const char* value){
	if (value)
	{
		vlsign = (*value == '-') ? 1 : 0;

		if (ispunct(*value))
		{
			vlen = strlen(value) - 1;
			vlstr = new char[vlen + 1]; 
			assert(vlstr != NULL);
			strcpy(vlstr, (value + 1));
		}
		else
		{
			vlen = strlen(value);
			vlstr = new char[vlen + 1]; 
			assert(vlstr != NULL);
			strcpy(vlstr, value);
		}
		strrev(vlstr);
	}
	else
	{
		vlstr = new char[2]; 
		assert(vlstr != NULL);
		*vlstr = '0'; 
		*(vlstr + 1) = '\0';
		vlen = 1; 
		vlsign = 0;
	}
}

lint::lint(string s) 
{
	 initialize(s.c_str());
}


lint::lint(int n)
{


	int i;
	if (n < 0) 
	{ 
		vlsign = 1; 
		n = (-n); 
	}
	else 
   {
			vlsign = 0;
	}

	if (n)
	{
		i = (int) log10((double)n) + 2;
		vlstr = new char[i]; 
		assert(vlstr != NULL);
		vlen = i - 1;
		i = 0;
		while (n >= 1)
		{
			vlstr[i] = n % 10 + '0';
			n /= 10;
			i++;
		}
		vlstr[i] = '\0';
	}
	else
	{
		vlstr = new char[2]; assert(vlstr != NULL);
		*vlstr = '0'; *(vlstr + 1) = '\0';
		vlen = 1;
	}
}

lint::lint(const lint& x) : vlen(x.vlen), vlsign(x.vlsign)
{
	vlstr = new char[x.vlen + 1]; 
	assert(vlstr != NULL);
	strcpy(vlstr, x.vlstr);
}



lint::~lint() 
{ 
	delete [] vlstr; 
}

string lint::to_String() const
{
	char* my_temp = this->vlstr;
	return strrev(my_temp);
}


int operator== (const lint &u, const lint &v)
{
	return (u.vlsign == v.vlsign && !strcmp(u.vlstr, v.vlstr));
}

int operator!= (const lint &u, const lint &v)
{
	return !(u == v);
}

int operator < (const lint &u, const lint &v)
{
	if (u.vlsign < v.vlsign) 
	{
		return 0;
	}
	else 
		if (u.vlsign > v.vlsign) 
		{
			return 1;
		}
	if (u.vlen < v.vlen) 
	{
		return (1 ^ u.vlsign);
	}
	else 
		if (u.vlen > v.vlen) 
		{
			return (0 ^ u.vlsign);
		}

	int temp;
	char *temp1 = new char[u.vlen + 1], 
	*temp2 = new char[v.vlen + 1];
	assert(temp1 != NULL);
	assert(temp2 != NULL);

	strcpy(temp1, u.vlstr);
	strcpy(temp2, v.vlstr);
	u.strrev(temp1);
	u.strrev(temp2);

	temp = strcmp(temp1, temp2);
	delete [] temp1; 
	delete [] temp2;

	if (temp < 0)
	{
		return (1 ^ u.vlsign);
	}
	else 
	  if (temp > 0)
	  {
		  return (0 ^ u.vlsign);
	  }
	else
	{
		return 0;
	}
}

int operator<= (const lint &u, const lint &v)
{
	return (u < v || u == v);
}

int operator > (const lint &u, const lint &v)
{
	return (!(u < v) && u != v);
}

int operator>= (const lint &u, const lint &v)
{
	return (u > v || u == v);
}

lint abs(const lint &v)
{
	lint u(v);
	if (u.vlsign) 
	{
		u.vlsign = 0;
	}
	return u;
}


lint lint::operator-() const
{
	lint temp(*this);
	if (temp != zero) 
	{
	   temp.vlsign = !vlsign;
	}
	return temp;
}

lint lint::operator+= (const lint& v)
{
	return *this = *this + v;
}

lint lint::operator-= (const lint& v)
{
	return *this = *this - v;
}


const lint & lint::operator= (const lint &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	delete [] vlstr;
	vlstr = new char[rhs.vlen + 1]; 
	assert(vlstr != NULL);
	strcpy(vlstr, rhs.vlstr);
	vlen = rhs.vlen;
	vlsign = rhs.vlsign;
	return *this;
}


lint operator+ (const lint &u, const lint &v)
{
	if (u.vlsign ^ v.vlsign)
	{
		if (u.vlsign == 0) 
		{ 
			lint t1 = u - abs(v); 
			return t1; 
		}
		else
		{ 
			lint t2 = v - abs(u); return t2; 
		}
	}

	int j, d1, d2, digitsum, carry = 0,
		maxlen = (u.vlen > v.vlen) ? u.vlen : v.vlen;
	char *temp = new char[maxlen + 2]; 
	assert(temp != NULL);

	for (j = 0; j < maxlen; j++)
	{
		d1 = (j > u.vlen - 1) ? 0 : u.vlstr[j] - '0';
		d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0';
		digitsum = d1 + d2 + carry;
		if (digitsum >= 10)
		{
			digitsum -= 10;
			carry = 1;
		}
		else
			carry = 0;
		temp[j] = digitsum + '0';
	}

	if (carry)
		temp[j++] = '1';

	if (u.vlsign) temp[j++] = '-';

	temp[j] = '\0';
	u.strrev(temp);
	lint result(temp);
	delete [] temp;
	return result;
}

lint operator- (const lint &u, const lint &v)
{
	if (u.vlsign ^ v.vlsign)
	{
		if (u.vlsign == 0) 
		{ 
			lint t1 = u + abs(v); 
			return t1; 
		}
		else
		{ 
			lint t2 = -(v + abs(u)); 
			return t2; 
		}
	}

	int maxlen = (u.vlen > v.vlen) ? u.vlen : v.vlen,
		d, d1, d2, i, negative, borrow = 0;
	char *temp = new char[maxlen + 1]; 
	assert(temp != NULL);

	lint w, y;

	if (u.vlsign == 0)
		if (u < v)	
		{
			w = v; 
			y = u; 
			negative = 1; 
		}
		else		
		{ 
			w = u; 
			y = v; 
			negative = 0; 
		}
	else
		if (u < v)  
		{ 
			w = u; 
			y = v; 
			negative = 1; 
		}
		else        
		{ 
			w = v; 
			y = u; 
			negative = 0; 
		}

		for (i = 0; i < maxlen; i++)
		{
			d1 = (i > w.vlen - 1) ? 0 : w.vlstr[i] - '0';
			d2 = (i > y.vlen - 1) ? 0 : y.vlstr[i] - '0';
			d = d1 - d2 - borrow;
			if (d < 0)
			{
				d += 10;
				borrow = 1;
			}
			else
				borrow = 0;
			temp[i] = d + '0';
		}

		while (i - 1 > 0 && temp[i - 1] == '0')
			--i;

		if (negative)	
		{
			temp[i++] = '-';
		}
		temp[i] = '\0';
		u.strrev(temp);

		lint result(temp);
		delete [] temp;
		return result;
}

lint operator* (const lint &u, const lint &v)
{
	lint pprod("1"), tempsum("0");

	for (int j = 0; j < v.vlen; j++)
	{
		int digit = v.vlstr[j] - '0';
		pprod = u.multdigit(digit);
		pprod = pprod.mult10(j);
		tempsum += pprod;
	}

	tempsum.vlsign = u.vlsign ^ v.vlsign;
	return tempsum;
}

lint operator/ (const lint &u, const lint &v)
{
	lint w, y, b, c, d, quotient = lint("0");
	int len = u.vlen - v.vlen;
	if (v == lint("0"))
	{
		cerr << "Error: divide by zero" << endl;
		return lint("0");
	}
	w = abs(u); y = abs(v);
	if (w < y) return lint("0");

	char *temp = new char[w.vlen + 1]; assert(temp != NULL);
	strcpy(temp, w.vlstr + len);
	b.strrev(temp);
	c = lint(temp);
	delete [] temp;
	for (int i = 0; i <= len; i++)
	{
		quotient = quotient.mult10(1);
		b = d = lint("0");
		while (b < c)
		{
			b = b + y; d = d + lint("1");
		}
		if (c < b)
		{
			b = b - y;
			d = d - lint("1");
		}

		quotient = quotient + d;

		if (i < len)
		{
			c = (c - b).mult10(1);
			c = c + lint(w.vlstr[len - i - 1] - '0');
		}
	}

	quotient.vlsign = u.vlsign^v.vlsign;
	return quotient;
}

lint operator% (const lint &u, const lint &v)
{
	return (u - v * (u / v));
}
lint& operator ++ (lint & t){
	t = t + one;
	return t;
}
lint operator ++ (lint & t, int r){
	t = t + one;
	return t - one;
}
lint& operator -- (lint & t){
	t = t - one;
	return t;
}
lint operator -- (lint & t, int r){
	t = t - one;
	return t + one;
}

char * lint::strrev(char *s) const
{
	int len = strlen(s), len1 = len - 1, index,
		limit = len >> 1;
	char t;

	for (int i = 0; i < limit; i++)
	{
		index = len1 - i;
		t = s[index];
		s[index] = s[i];
		s[i] = t;
	}
	return s;
}


ostream & operator<< (ostream &s, const lint &v)
{
	char *temp = new char[v.vlen + 1]; 
	assert(temp != NULL);
	if (v.vlen > 0)
	{
		strcpy(temp, v.vlstr);
		if (v.vlsign) 
		{
			s << "-";
		}
		s << v.strrev(temp);
	}
	else
	{
			s << "0";
	}
	delete [] temp;
	return s;
}

istream&  operator >> (istream & is,lint& r)
{
	string my;
	is >> my;
	lint e(my.c_str());
	r = e;
	return is;
}


lint lint::multdigit(int num) const
{
	int j, carry = 0;
	if (num)
	{
		char *temp = new char[vlen + 2]; assert(temp != NULL);
		for (j = 0; j < vlen; j++)
		{
			int d1 = vlstr[j] - '0', digitprod = d1*num + carry;

			if (digitprod >= 10)
			{
				carry = digitprod / 10;
				digitprod -= carry * 10;
			}
			else carry = 0;
			temp[j] = digitprod + '0';
		}

		if (carry)
			temp[j++] = carry + '0';
		temp[j] = '\0';

		strrev(temp);
		lint result(temp);
		delete [] temp;
		return result;
	}
	else return zero;
}

lint lint::mult10(int num) const
{
	if (*this != zero)
	{
		int j, dd = vlen + num, bb = vlen - 1;
		char *temp = new char[dd + 1]; assert(temp != NULL);

		for (j = 0; j < vlen; j++)	
		{
			temp[j] = vlstr[bb - j];
		}
		for (j = vlen; j < dd; j++)
		{
			temp[j] = '0';
		}

		temp[dd] = '\0';
		lint result(temp);
		delete [] temp;
		return result;
	}
	else return zero;
}

static lint& my_pow( const lint& my, int t)
{
	if (t == 0)
	{
		return one;
	}
	if (t % 2 == 1){
		return my_pow(my, t - 1) * my;
	} else
	{
		lint r = my_pow(my, t / 2);
		return r * r;
	}
	
}



