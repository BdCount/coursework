#ifndef STROKA_DEC_H
#define STROKA_DEC_H

#include "Stroka.h"
#include <iostream>
#include <math.h>

class Stroka_Dec : public Stroka
{
protected:
	const char base = 10;

public:
	Stroka_Dec();
	Stroka_Dec(const char* point);
	Stroka_Dec(const char a);
	Stroka_Dec(const Stroka_Dec& str);
	Stroka_Dec(int n);


	bool utoi(void);
//	~Stroka_Dec();
	~Stroka_Dec();

	Stroka_Dec& operator= (const Stroka_Dec& str);
	Stroka_Dec& operator= (const std::string& str);
	Stroka_Dec& operator= (int n);

	Stroka_Dec operator+ (const Stroka_Dec& str);
	Stroka_Dec operator- (const Stroka_Dec& str);
	Stroka_Dec operator* (const Stroka_Dec& str);

	Stroka_Dec operator+ (int n);
	Stroka_Dec operator- (int n);
	Stroka_Dec operator- ();
	Stroka_Dec operator* (int n);
	Stroka_Dec operator/ (const Stroka_Dec& str);

	bool operator== (const Stroka_Dec& num2);
	bool operator== (int n);

	bool operator> (const Stroka_Dec& num2);
	bool operator> (int n);

	bool operator< (const Stroka_Dec& num2);
	bool operator< (int n);

	Stroka_Dec abs(Stroka_Dec );

	Stroka_Dec factorial();

	Stroka_Dec binpow(int n);

	Stroka_Dec pow(Stroka_Dec n);
	Stroka_Dec sqrt();

	void long_to_string(std::string& str);
	friend std::ostream& operator<< (std::ostream& out, const Stroka_Dec& str);
	friend std::istream& operator>> (std::istream& in, Stroka_Dec& str);

private:
	void viravnivanie(Stroka_Dec* max, Stroka_Dec* min);
	void normal(Stroka_Dec& res, char flag);

	int slojenie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res);
	int vichitanie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res);
	int ummojenie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res);
	int delenie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res);
	Stroka_Dec ProdTree(Stroka_Dec  l, Stroka_Dec  r);


};

#endif