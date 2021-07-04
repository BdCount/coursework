#ifndef STROKA_H
#define STROKA_H

#include <iostream>
int char_array_fix(char** parray, std::istream& in);

class Stroka
{
protected:
    char* p_mass; // ��������� �� ������ 
    unsigned int length;  // ������ ������
public:
    Stroka();
    Stroka(const char* point);
    Stroka(const char a);
    Stroka(Stroka& str);
    virtual ~Stroka();
    unsigned int get_length(void);
    Stroka& operator= (const Stroka& str);


    friend std::istream& operator>> (std::istream& in, Stroka& str);
    friend std::ostream& operator<< (std::ostream& out, const Stroka& str);

};


#endif