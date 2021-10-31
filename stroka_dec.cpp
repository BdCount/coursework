#ifndef STROKA_DEC_CPP
#define STROKA_DEC_CPP
#include "stroka_dec.h"

	Stroka_Dec::Stroka_Dec()
	{
#ifdef stroka_dec_constructor
		std::cout << "stroka_DEC_constructor" << std::endl;
#endif
	};
	Stroka_Dec::Stroka_Dec(const char* point)
	{
#ifdef stroka_dec_constructor_argument
		std::cout << "stroka_DEC_constructor_argument" << std::endl;
#endif
		int flag = 0, i = 0;
		unsigned int len = strlen(point);
		this->length = len;
		/*if (point[0] == '+' || point[0] == '-') {
			i = 1;
			this->length = len - 1;
		}/**/
		unsigned int count = 0;
		for (; i < len; i++)
			if ((point[i] > '9' || point[i] < '0') && point[i] != '.' && point[i] != ',' && point[i] != '+' && point[i] != '-')
			{
				flag = 1;
				break;
			}


		if (flag || (point[0] != '+' && point[0] != '-' && point[0] != ',' && point[0] != '.' && (point[0] < '0' || point[0] > '9')))
			this->length = 0;
		else
		{
			delete[] this->p_mass;
			if (point[0] != '+' && point[0] != '-')
			{

				for (unsigned int i = 0; i < len; i++) // проверка на незначащие нули
				{
					if (point[i] == '0' && len != 1)
						count++;
					else
						break;
				}
				this->length += 1 - count;
				this->p_mass = new char[length + 1];
				this->p_mass[0] = '+';
				for (unsigned int i = count, j = 1; i <= len; i++, j++)
					this->p_mass[j] = point[i];
			}
			else
			{
				for (unsigned int i = 1; i < len; i++) // проверка на незначащие нули
					if (point[i] == '0')
						count++;
					else
						break;
				this->length -= count;
				this->p_mass = new char[length + 1];
				this->p_mass[0] = point[0];
				for (unsigned int i = count + 1, j = 1; i <= len; i++, j++)
					this->p_mass[j] = point[i];
			}
		}
	}
	Stroka_Dec::Stroka_Dec(const char a)
		:Stroka(a)
	{
#ifdef stroka_dec_constructor_argument_one
		std::cout << "\stroka_dec_constructor_argument_one" << std::endl;
#endif
		if (a < '0' || a > '9')
		{
			p_mass[0] = '\0';
			length = 0;
		}
		else
		{
			delete[] p_mass;
			p_mass = new char[3];
			p_mass[0] = '+';
			p_mass[1] = a;
			p_mass[2] = '/0';
		}
	}
	Stroka_Dec::Stroka_Dec(const Stroka_Dec& str)
	{
#ifdef stroka_dec_constructor_copy
		std::cout << "stroka_dec_constructor_copy" << std::endl;
#endif
		delete[] this->p_mass;
		this->length = str.length;
		this->p_mass = new char[this->length + 1];
		for (unsigned int i = 0; i <= this->length; i++)
			this->p_mass[i] = str.p_mass[i];
	}
	Stroka_Dec::Stroka_Dec(int n)
	{
#ifdef stroka_dec_constructor_copy
		std::cout << "stroka_dec_constructor_copy" << std::endl;
#endif
		int len = 0;

		if (n == 0)
			len = 1;

		for (int j = n; j != 0; len++)
			j /= base;


		delete[] this->p_mass;

		this->length = len + 1;
		this->p_mass = new char[this->length + 1];

		if (n >= 0) {
			this->p_mass[0] = '+';
		}
		else {
			n *= -1;
			this->p_mass[0] = '-';
		}

		for (int i = 1, j = n; i < this->length; i++) {
			this->p_mass[this->length - i] = j % base + 48;
			j /= base;
		}

		this->p_mass[this->length] = '\0';

	}


	bool Stroka_Dec::utoi(void)
	{
#ifdef DEBAG
		std::cout << "Stroka_Dec_Utoi" << std::endl;
#endif
		/*
		if (this->p_mass[0] == '-' || this->length > 11)
			return false;
		else
		if (this->length < 11)
			return true;
		else
		{

			if (this->p_mass[1] <= '4' && this->p_mass[2] <= '2' && this->p_mass[3] <= '9' && this->p_mass[4] <= '4' && this->p_mass[5] <= '9' &&
				this->p_mass[6] <= '6' && this->p_mass[7] <= '7' && this->p_mass[8] <= '2' && this->p_mass[9] <= '9' && this->p_mass[10] <= '6')
				return true;
			else
				return false;
		}


		/**/
		// другой вариант

		if (this->p_mass[0] == '-' || this->length > 11)
			return false;
		Stroka_Dec tmp = "4294967296";
		tmp = tmp - *this;
		if (tmp.p_mass[0] == '-')
			return false;
		else
			return true;

		/**/
	}
	Stroka_Dec::~Stroka_Dec()
	{
#ifdef stroka_dec_destructor
		std::cout << "stroka_dec_destructor" << std::endl;
#endif
	}

	Stroka_Dec& Stroka_Dec::operator= (const Stroka_Dec& str)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator=" << std::endl;
#endif
		if (this == &str)
			return *this;
		delete[] p_mass;
		length = str.length;
		p_mass = new char[length + 1];
		for (unsigned int i = 0; i <= this->length; i++)
			this->p_mass[i] = str.p_mass[i];
		return *this;
	}
	Stroka_Dec& Stroka_Dec::operator= (const std::string& str)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator=" << std::endl;
#endif

		delete[] this->p_mass;
		if (str[0] != '+' && str[0] != '-') {
			this->length = str.length() + 1;
			this->p_mass = new char[this->length + 1];
			this->p_mass[0] = '+';
			for (unsigned int i = 1, j = 0; i <= this->length; i++, j++)
				this->p_mass[i] = str[j];
		}
		else {
			this->length = str.length();
			this->p_mass = new char[this->length + 1];
			for (unsigned int i = 0; i <= this->length; i++)
				this->p_mass[i] = str[i];
		}
		return *this;
	}
	Stroka_Dec& Stroka_Dec::operator= (int n)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator=" << std::endl;
#endif
		Stroka_Dec str(n);
		if (this == &str)
			return *this;
		*this = str;
		return *this;
	}

	Stroka_Dec Stroka_Dec::operator+ (const Stroka_Dec& str)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator+" << std::endl;
#endif

		if (str.length == 0)
			return *this;
		if (this->length == 0)
			return str;
		Stroka_Dec res;
		Stroka_Dec max = *this;
		Stroka_Dec min = str;
		delete[] res.p_mass;

		viravnivanie(&max, &min); // приведем их к нормальному виду// |max| > |min|


		char flag = 0;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '+')
			flag = 1;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '-')
			flag = 2;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '+')
			flag = 3;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '-')
			flag = 4;



		switch (flag)
		{
		case 1: slojenie(&max, &min, &res); res.p_mass[0] = '+';  break;
		case 2: slojenie(&max, &min, &res);  res.p_mass[0] = '-'; break;
		case 3: vichitanie(&max, &min, &res); res.p_mass[0] = max.p_mass[0]; break;
		case 4: vichitanie(&max, &min, &res);  res.p_mass[0] = max.p_mass[0]; break;
		}

		normal(res, flag); // привидение к нормальному виду
		return res;
	}
	Stroka_Dec Stroka_Dec::operator- (const Stroka_Dec& str)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator-" << std::endl;
#endif
		Stroka_Dec tmp = str;
		tmp.p_mass[0] = tmp.p_mass[0] == '+' ? '-' : '+';
		return *this + tmp;
	}
	Stroka_Dec Stroka_Dec::operator* (const Stroka_Dec& str)
	{
		Stroka_Dec res;
		Stroka_Dec max = *this;
		Stroka_Dec min = str;
		delete[] res.p_mass;

		viravnivanie(&max, &min); // приведем их к нормальному виду// |max| > |min|

		char flag = 0;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '+')
			flag = 1;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '-')
			flag = 2;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '+')
			flag = 3;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '-')
			flag = 4;

		switch (flag)
		{
		case 1: ummojenie(&max, &min, &res); res.p_mass[0] = '+';  break;
		case 2: ummojenie(&max, &min, &res);  res.p_mass[0] = '+'; break;
		case 3: ummojenie(&max, &min, &res); res.p_mass[0] = '-'; break;
		case 4: ummojenie(&max, &min, &res);  res.p_mass[0] = '-'; break;
		}

		normal(res, flag); // привидение к нормальному виду
		return res;
	}

	Stroka_Dec Stroka_Dec::operator+ (int n)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator+" << std::endl;
#endif

		Stroka_Dec str(n);
		if (str.length == 0)
			return *this;
		if (this->length == 0)
			return str;
		Stroka_Dec res;
		Stroka_Dec max = *this;
		Stroka_Dec min = str;
		delete[] res.p_mass;

		viravnivanie(&max, &min); // приведем их к нормальному виду// |max| > |min|


		char flag = 0;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '+')
			flag = 1;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '-')
			flag = 2;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '+')
			flag = 3;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '-')
			flag = 4;



		switch (flag)
		{
		case 1: slojenie(&max, &min, &res); res.p_mass[0] = '+';  break;
		case 2: slojenie(&max, &min, &res);  res.p_mass[0] = '-'; break;
		case 3: vichitanie(&max, &min, &res); res.p_mass[0] = max.p_mass[0]; break;
		case 4: vichitanie(&max, &min, &res);  res.p_mass[0] = max.p_mass[0]; break;
		}

		normal(res, flag); // привидение к нормальному виду
		return res;
	}
	Stroka_Dec Stroka_Dec::operator- (int n)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_operator-" << std::endl;
#endif
		Stroka_Dec tmp(n);
		tmp.p_mass[0] = tmp.p_mass[0] == '+' ? '-' : '+';
		return *this + tmp;
	}
	Stroka_Dec Stroka_Dec::operator- () {

		this->p_mass[0] = this->p_mass[0] == '-' ? '+' : '-';
		return *this;
		/*
		if (this->p_mass[0] == '-')
			this->p_mass[0] == '+';
		else
			this->p_mass[0] == '+';
			/**/
	}
	Stroka_Dec Stroka_Dec::operator* (int n)
	{
		Stroka_Dec str(n);
		Stroka_Dec res;
		Stroka_Dec max = *this;
		Stroka_Dec min = str;
		delete[] res.p_mass;

		viravnivanie(&max, &min); // приведем их к нормальному виду// |max| > |min|

		char flag = 0;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '+')
			flag = 1;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '-')
			flag = 2;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '+')
			flag = 3;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '-')
			flag = 4;

		switch (flag)
		{
		case 1: ummojenie(&max, &min, &res); res.p_mass[0] = '+';  break;
		case 2: ummojenie(&max, &min, &res);  res.p_mass[0] = '+'; break;
		case 3: ummojenie(&max, &min, &res); res.p_mass[0] = '-'; break;
		case 4: ummojenie(&max, &min, &res);  res.p_mass[0] = '-'; break;
		}

		normal(res, flag); // привидение к нормальному виду
		return res;
	}
	Stroka_Dec Stroka_Dec::abs(Stroka_Dec str) {
		str.p_mass[0] = '+';
		return str;
	}
	Stroka_Dec Stroka_Dec::operator/ (const Stroka_Dec& str) {

		

		if (abs(*this) < abs(str)) {
			return 0;
		}

		Stroka_Dec res;
		Stroka_Dec max = *this;
		Stroka_Dec min = str;
		delete[] res.p_mass;

		//	viravnivanie(&max, &min); // приведем их к нормальному виду// |max| > |min|

		char flag = 0;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '+')
			flag = 1;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '-')
			flag = 2;
		if (str.p_mass[0] == '-' && this->p_mass[0] == '+')
			flag = 3;
		if (str.p_mass[0] == '+' && this->p_mass[0] == '-')
			flag = 4;

		switch (flag)
		{
		case 1: delenie(&max, &min, &res); res.p_mass[0] = '+';  break;
		case 2: delenie(&max, &min, &res);  res.p_mass[0] = '+'; break;
		case 3: delenie(&max, &min, &res); res.p_mass[0] = '-'; break;
		case 4: delenie(&max, &min, &res);  res.p_mass[0] = '-'; break;
		}

		return res;
	}

	bool Stroka_Dec::operator== (const Stroka_Dec& num2) {
		int i;
		Stroka_Dec TEMP;
		if (this->length == num2.length) {
			for (i = 0; i < num2.length; i++) {
				if (this->p_mass[i] != num2.p_mass[i]) {
					return false;
				}
			}
		}
		else {
			return false;
		}
		return true;
	}
	bool Stroka_Dec::operator== (int n) {
		int i;
		Stroka_Dec num2(n);
		if (this->length == num2.length) {
			for (i = 0; i < num2.length; i++) {
				if (this->p_mass[i] != num2.p_mass[i]) {
					return false;
				}
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool Stroka_Dec::operator> (const Stroka_Dec& num2) {
		int i;
		Stroka_Dec TEMP;

		if (this->p_mass[0] == '+' && num2.p_mass[0] == '-')
			return true;
		if (this->p_mass[0] == '-' && num2.p_mass[0] == '+')
			return false;
		if (this->p_mass[0] == '+' && this->length > num2.length)
			return true;
		else
			if (this->length != num2.length)
				return false;

		if (this->p_mass[0] == '-' && this->length > num2.length)
			return false;
		else
			if (this->length != num2.length)
				return true;

		if (this->p_mass[0] == '+') {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] > num2.p_mass[i]) {
					return true;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}

		}
		else {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] < num2.p_mass[i]) {
					return true;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}
		}
		return false;
	}
	bool Stroka_Dec::operator> (int n) {
		int i;
		Stroka_Dec num2(n);

		if (this->p_mass[0] == '+' && num2.p_mass[0] == '-')
			return true;
		if (this->p_mass[0] == '-' && num2.p_mass[0] == '+')
			return false;
		if (this->p_mass[0] == '+' && this->length > num2.length)
			return true;
		else
			if (this->length != num2.length)
				return false;

		if (this->p_mass[0] == '-' && this->length > num2.length)
			return false;
		else
			if (this->length != num2.length)
				return true;

		if (this->p_mass[0] == '+') {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] > num2.p_mass[i]) {
					return true;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}

		}
		else {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] < num2.p_mass[i]) {
					return true;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}
		}
		return false;
	}

	bool Stroka_Dec::operator< (const Stroka_Dec& num2) {
		int i;
		Stroka_Dec TEMP;

		if (this->p_mass[0] == '+' && num2.p_mass[0] == '-')
			return false;
		if (this->p_mass[0] == '-' && num2.p_mass[0] == '+')
			return true;
		if (this->p_mass[0] == '+' && this->length > num2.length)
			return false;
		else
			if (this->length != num2.length)
				return true;

		if (this->p_mass[0] == '-' && this->length > num2.length)
			return true;
		else
			if (this->length != num2.length)
				return false;

		if (this->p_mass[0] == '+') {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] > num2.p_mass[i]) {
					return false;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}

		}
		else {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] > num2.p_mass[i]) {
					return true;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}
		}
		return false;
	}
	bool Stroka_Dec::operator< (int n) {
		int i;
		Stroka_Dec num2(n);

		if (this->p_mass[0] == '+' && num2.p_mass[0] == '-')
			return false;
		if (this->p_mass[0] == '-' && num2.p_mass[0] == '+')
			return true;
		if (this->p_mass[0] == '+' && this->length > num2.length)
			return false;
		else
			if (this->length != num2.length)
				return true;

		if (this->p_mass[0] == '-' && this->length > num2.length)
			return true;
		else
			if (this->length != num2.length)
				return false;

		if (this->p_mass[0] == '+') {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] > num2.p_mass[i]) {
					return false;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}

		}
		else {
			for (i = 1; i < num2.length; i++) {
				if (this->p_mass[i] > num2.p_mass[i]) {
					return true;
				}
				else
					if (this->p_mass[i] != num2.p_mass[i]) {
						return false;
					}
			}
		}
		return false;
	}

	Stroka_Dec Stroka_Dec::factorial()
	{
		if (*this < 0)
			throw "отрицательный факториал";
		if (*this == 0)
			return 1;
		if (*this == 1 || *this == 2)
			return *this;
		return ProdTree(2, *this);
	}

	Stroka_Dec Stroka_Dec::binpow(int n) {

		if (n < 0)
			throw "отрицательная степень";
		Stroka_Dec res = 1;
		for (int i = 0; n > i; i++)
			res = res * res;

		return res;
	}

	Stroka_Dec Stroka_Dec::pow(Stroka_Dec n) {

		if (n < 0 || *this < 0)
			throw "отрицательная степень";

		if (n == 0)
			return 1;
		Stroka_Dec res = *this;
		for (int i = 1; n > i; i++)
			res = res * *this;

		return res;
	}

	Stroka_Dec Stroka_Dec::sqrt() {
		char ostatok = 0;
		Stroka_Dec* res;
		res = new Stroka_Dec;
		delete res->p_mass;
		res->length = (this->length - 1) / 2 + (this->length - 1) % 2 + 1; // временно
		res->p_mass = new char[res->length + 1];
		res->p_mass[0] = '+';
		res->p_mass[1] = '1';
		for (int i = 2; i < res->length; i++) {
			res->p_mass[i] = '0';
		}
		res->p_mass[res->length] = '\0';


		/*
				Stroka_Dec str;
				for (int i = 0; (*max - *min * temp) > 0; i++) {

					str = temp;
					temp = temp * 10 + 9;
				}
				temp = (temp - (str + 1) * 9);
				str = 0;

				for (int i = 0; (*max - *min * (temp + doptmp)) > 0; i++) {
					str = doptmp;
					doptmp = doptmp * 10;
				}
				if (doptmp == 1)
					doptmp = 0;
				else
					doptmp = (doptmp - str * 9);
					/**/
		for (int i = 1, j, len = res->length; i < len; i++) {
			for (j = 5; (*this - (*res * *res)) > 0 && j < 10; j++) {
				res->p_mass[i] = j + 48;
			}
			j -= 2;
			for (; (*this - (*res * *res)) < 0 && j > -1; j--) {
				res->p_mass[i] = j + 48;
			}
		}
		/**/
//		*res = temp + doptmp;
		return *res;
	}

	void Stroka_Dec::long_to_string(std::string& str) {

		if(this->p_mass[0] == '+')
			str = "";
		else
			str = "-";
		for (unsigned int i = 1; i <= this->length; i++)
			str += this->p_mass[i];
		return;
	}

	void Stroka_Dec::viravnivanie(Stroka_Dec* max, Stroka_Dec* min) // делаем max > min
	{
#ifdef DEBAG
		std::cout << "stroka_dec_viravnivanie" << std::endl;
#endif
		char* temp_ch_p = NULL;
		unsigned int temp_int = 0;
		bool flag_swap = false; // флаг на перемещение max и min местами
		int len_max;
		int dot_pos_max, dot_pos_min;
		int size_integer, size_rational;

		dot_pos_max = max->length;
		dot_pos_min = min->length;
		//len_max = max->length > min->length ? max->length : min->length;


		for (int i = 1; i < min->length; i++)  // узнаем размер целой части у min
		{
			if (min->p_mass[i] == ',' || min->p_mass[i] == '.')
			{
				dot_pos_min = i;
				min->p_mass[i] = ',';
			}
		}
		for (int i = 1; i < max->length; i++)	// узнаем размер целой части у max
		{
			if (max->p_mass[i] == ',' || max->p_mass[i] == '.')
			{
				dot_pos_max = i;
				max->p_mass[i] = ',';
			}
		}

		size_integer = dot_pos_max > dot_pos_min ? dot_pos_max : dot_pos_min;
		size_rational = max->length - dot_pos_max > min->length - dot_pos_min ? max->length - dot_pos_max : min->length - dot_pos_min;




		if (dot_pos_max < dot_pos_min) // если целая часть min > max по размеру
		{

			temp_int = min->length;        // меняем min и max местами
			min->length = max->length;
			max->length = temp_int;

			temp_ch_p = min->p_mass;
			min->p_mass = max->p_mass;
			max->p_mass = temp_ch_p;

			temp_int = dot_pos_max;
			dot_pos_max = dot_pos_min;
			dot_pos_min = temp_int;

			flag_swap = true;

		}
		else
			if (dot_pos_max > dot_pos_min)  // если целая часть min < max по размеру
				flag_swap = true;







		if (1/*dot_pos_max > dot_pos_min && dot_pos_max != dot_pos_min/**/) // выравнивание целой части
		{
			int N, i, j;
			N = size_integer + size_rational; // размер выравненой целой части
			len_max = N;
			temp_ch_p = min->p_mass;
			min->p_mass = new char[N + 1];
			min->p_mass[0] = temp_ch_p[0];
			for (i = 1, j = dot_pos_min; j < size_integer; i++, j++) // добавляем нули  
			{
				min->p_mass[i] = '0';
			}
			for (j = 1; i < size_integer; i++, j++) // копируем данные
			{
				min->p_mass[i] = temp_ch_p[j];
			}

			min->p_mass[i] = ',';

			// выравнивание дробной части
			for (i = size_integer + 1, j = dot_pos_min + 1; j < min->length; i++, j++) // добавляем нули  
			{
				min->p_mass[i] = temp_ch_p[j];
			}
			for (; i < N; i++) // копируем данные
			{
				min->p_mass[i] = '0';
			}
			min->p_mass[N] = '\0';
		}


		if (1/*dot_pos_max > dot_pos_min && dot_pos_max != dot_pos_min/**/) // выравнивание целой части
		{
			int N, i, j;
			N = size_integer + size_rational; // размер выравненой целой части
			temp_ch_p = max->p_mass;
			max->p_mass = new char[N + 1];
			max->p_mass[0] = temp_ch_p[0];
			for (i = 1, j = dot_pos_max; j < size_integer; i++, j++) // добавляем нули  
			{
				max->p_mass[i] = '0';
			}
			for (j = 1; i < size_integer; i++, j++) // копируем данные
			{
				max->p_mass[i] = temp_ch_p[j];
			}


			max->p_mass[i] = ',';

			// выравнивание дробной части
			for (i = size_integer + 1, j = dot_pos_max + 1; j < max->length; i++, j++)   // копируем данные
			{
				max->p_mass[i] = temp_ch_p[j];
			}
			for (; i < N; i++) // добавляем нули
			{
				max->p_mass[i] = '0';
			}
			max->p_mass[N] = '\0';
		}


		//		return ;


		if (!flag_swap) // если целые части равны по размеру
		{
			for (int i = 1; i < dot_pos_max; i++)  // сравниваем целые части
			{
				if ((min->p_mass[i] > max->p_mass[i]))  // min > max
				{
					temp_int = min->length;        // меняем min и max местами
					min->length = max->length;
					max->length = temp_int;
					temp_ch_p = min->p_mass;
					min->p_mass = max->p_mass;
					max->p_mass = temp_ch_p;
					flag_swap = true;
					break;
				}
				else
					if (min->p_mass[i] < max->p_mass[i])  // min < max
					{
						flag_swap = true;   // оставляем как есть
						break;
					}
			}
		}


		if (!flag_swap) /// если целые части равны
		{
			for (int i = dot_pos_max + 1; i < len_max; i++)
			{
				if ((min->p_mass[i] > max->p_mass[i]))  // min > max
				{
					temp_int = min->length;        // меняем min и max местами
					min->length = max->length;
					max->length = temp_int;
					temp_ch_p = min->p_mass;
					min->p_mass = max->p_mass;
					max->p_mass = temp_ch_p;
					flag_swap = true;
					break;
				}
				else
					if (min->p_mass[i] < max->p_mass[i])  // min < max
					{
						flag_swap = true;   // оставляем как есть
						break;
					}
			}
		}





		for (unsigned int i = 1, tmp, lens = (size_integer + size_rational) / 2; i <= lens; i++) // привидение к обратному виду
		{
			tmp = max->p_mass[i];
			max->p_mass[i] = max->p_mass[len_max - i];
			max->p_mass[len_max - i] = tmp;
		}
		for (unsigned int i = 1, tmp, lens = (size_integer + size_rational) / 2; i <= lens; i++) // привидение к обратному виду
		{
			tmp = min->p_mass[i];
			min->p_mass[i] = min->p_mass[len_max - i];
			min->p_mass[len_max - i] = tmp;
		}
	}
	void Stroka_Dec::normal(Stroka_Dec& res, char flag)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_normal" << std::endl;
#endif
		char* temp;



		/**/
		for (; res.p_mass[res.length - 1] == '0' && res.length != 2;)  // инициализация нового массива (при res == 0 выдает ошибку)
			res.length--;
		/**/

		temp = new char[res.length + 1];
		temp[0] = res.p_mass[0];


		for (unsigned int i = 1, tmp, lens = res.length; i < lens; i++) // привидение к нормальному виду
		{
			temp[i] = res.p_mass[res.length - i];
		}


		temp[res.length] = '\0';
		delete[] res.p_mass;
		res.p_mass = temp;
	}

	int Stroka_Dec::slojenie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_slojenie" << std::endl;
#endif
		char ostatok = 0;

		for (int i = 1; i < max->length; i++) {
			if (max->p_mass[i] != 0)
				max->p_mass[i] = max->p_mass[i] - 48;
			if (min->p_mass[i] != 0)
				min->p_mass[i] = min->p_mass[i] - 48;
		}



		res->p_mass = new char[max->length + 2];

		for (int i = 0; i < max->length + 1; i++)
			res->p_mass[i] = 0;

		for (unsigned int i = 1; i < max->length; i++) // сложение 2 чисел
		{
			res->p_mass[i] = max->p_mass[i] + min->p_mass[i];
		}

		res->p_mass[max->length + 1] = '\0';

		for (unsigned int i = 1; i < max->length; i++) // перенос остатков в другие десятки
		{
			res->p_mass[i] += ostatok;
			ostatok = res->p_mass[i] / base;
			res->p_mass[i] = res->p_mass[i] % base;
		}
		if (ostatok)
		{
			res->length = max->length + 1;
			res->p_mass[max->length] = ostatok;
			res->p_mass[max->length + 1] = '\0';
		}
		else
		{
			res->length = max->length;
			res->p_mass[max->length] = '\0';
		}

		for (int i = 1; i < res->length; i++) {
			res->p_mass[i] = res->p_mass[i] + 48;

		}
		return 0;
	}
	int Stroka_Dec::vichitanie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_vichitanie" << std::endl;
#endif
		unsigned int len = 1;
		char ostatok = 0;
		int dot_pos = -1;

		for (int i = 1; min->p_mass[i] != '\0'; i++, len++)  // узнаем размер целой части у min
		{
			if (min->p_mass[i] == ',')
				dot_pos = i;
		}

		dot_pos = dot_pos > 0 ? dot_pos : len;

		res->length = len; // временно
		res->p_mass = new char[len + 1];
		res->p_mass[len] = '\0';
		for (unsigned int i = 1; i < len; i++)
		{
			if (min->p_mass[i] == ',')
			{
				res->p_mass[i] = ',';
				i++;
			}
			res->p_mass[i] = (char)(max->p_mass[i] - min->p_mass[i]);
		}

		//	res->p_mass[len] = 0;

		for (unsigned int i = 1; i < len; i++)
		{
			if (res->p_mass[i] == ',')
				i++;
			if (res->p_mass[i] < 0)
			{
				res->p_mass[i] += 10;

				if (res->p_mass[i + 1] == ',')
					res->p_mass[i + 2] -= 1;
				else
					res->p_mass[i + 1] -= 1;
			}
			res->p_mass[i] += 48;
		}

		return 0;
	}
	int Stroka_Dec::ummojenie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res)
	{
#ifdef DEBAG
		std::cout << "stroka_dec_vichitanie" << std::endl;
#endif


		unsigned int len = 1;
		char ostatok = 0;
		int dot_pos = -1;


		for (int i = 1; i < max->length; i++) {
			if (max->p_mass[i] != 0)
				max->p_mass[i] = max->p_mass[i] - 48;
			if (min->p_mass[i] != 0)
				min->p_mass[i] = min->p_mass[i] - 48;
		}

		for (int i = 1; min->p_mass[i] != '\0'; i++, len++)  // узнаем размер целой части у min
		{
			if (min->p_mass[i] == ',')
				dot_pos = i;
		}

		dot_pos = dot_pos > 0 ? len : dot_pos;

		res->length = max->length + min->length - 1; // временно
		res->p_mass = new char[res->length + 1];
		for (int i = 0; i < res->length; i++)
			res->p_mass[i] = 0;



		for (int j = 1; j < min->length; j++) {

			for (unsigned int i = 1; i < max->length; i++) // умножение 2 чисел
			{
				res->p_mass[j + i - 1] += max->p_mass[i] * min->p_mass[j];
				ostatok = res->p_mass[j + i - 1] / base;
				res->p_mass[j + i] += ostatok;
				res->p_mass[j + i - 1] = res->p_mass[j + i - 1] % base;
			}
		}

		if (res->p_mass[res->length - 1] == 0)
			res->length--;

		for (int i = 1; i < res->length; i++)
			res->p_mass[i] += 48;

		int f;
		f = 500;
		res->p_mass[res->length] = '\0';

		return 0;
	}
	int Stroka_Dec::delenie(Stroka_Dec* const max, Stroka_Dec* const min, Stroka_Dec* const res) {
		char ostatok = 0;
		Stroka_Dec temp(9), doptmp(1);
		max->p_mass[0] = '+';
		min->p_mass[0] = '+';


		res->length = max->length - min->length + 2; // временно
		res->p_mass = new char[res->length + 1];
		//		delete[] temp.p_mass;
		//		temp.length = res->length - 1;
		//		temp.p_mass = new char[temp.length];
		temp.p_mass[0] = '+';

		Stroka_Dec str;
		for (int i = 0; (*max - *min * temp) > 0; i++) {

			str = temp;
			temp = temp * 10 + 9;
		}
		temp = (temp - (str + 1) * 9);

		//+100008
		//+999999

		// ищем число с которого начнется перебор
		/*
		for (int i = 0; i < res->length; i++)
			res->p_mass[i] = 0;
		for (int i = 1, len = temp.length; i < len; i++)
			temp.p_mass[i] = '9';
		temp.p_mass[temp.length] = '/0';
		/**/
		str = 0;
		for (int i = 0; (*max - *min * (temp + doptmp)) > 0; i++) {
			str = doptmp;
			doptmp = doptmp * 10;
		}
		if (doptmp == 1)
			doptmp = 0;
		else
			doptmp = (doptmp - str * 9);

		/**/


		for (int i = 1, j, len = doptmp.length; i < len; i++) {
			for (j = 5; (*max - (*min * (temp + doptmp))) > 0 && j < 10; j++) {

				str = doptmp;
				doptmp.p_mass[i] = j + 48;
			}
			j -= 2;
			for (; (*max - (*min * (temp + doptmp))) < 0 && j > -1; j--) {

				str = doptmp;
				doptmp.p_mass[i] = j + 48;
			}

			//			doptmp.p_mass[i] = j - 2 + 48;
			/**/;
		}

		*res = temp + doptmp;

		/*
		for (int j = 1; j < max->length; j++) {

			for (unsigned int i = 1; i < max->length; i++) // деление 2 чисел
			{
				res->p_mass[j + i - 1] += max->p_mass[i] * min->p_mass[j];
				ostatok = res->p_mass[j + i - 1] / base;
				res->p_mass[j + i] += ostatok;
				res->p_mass[j + i - 1] = res->p_mass[j + i - 1] % base;
			}
		}

		if (res->p_mass[res->length - 1] == 0)
			res->length--;

		for (int i = 1; i < res->length; i++)
			res->p_mass[i] += 48;

		int f;
		f = 500;
		res->p_mass[res->length] = '\0';
	/**/
		return 0;
	}
	Stroka_Dec Stroka_Dec::ProdTree(Stroka_Dec  l, Stroka_Dec  r)
	{
		if (l > r)
			return 1;
		if (l == r)
			return l;
		if (r - l == 1)
			return (Stroka_Dec)l * r;
		Stroka_Dec  m = (l + r) / 2;
		return ProdTree(l, m) * ProdTree(m + 1, r);
	}


std::istream& operator>> (std::istream& in, Stroka_Dec& str)
{

#ifdef DEBAG
	std::cout << std::endl << "< stroka_dec_operator_>> > " << std::endl;
#endif

	str.length = char_array_fix(&str.p_mass, in);
	Stroka_Dec tmp = str.p_mass;
	str = tmp;
	return in;

}
std::ostream& operator<< (std::ostream& out, const Stroka_Dec& str)
{

#ifdef DEBAG
	std::cout << std::endl << "< stroka_dec_operator<< > " << std::endl;
#endif
	if (str.length == 0)
		out << "-----------\n";
	out << str.p_mass;
	return out;
}
#endif
/**/
