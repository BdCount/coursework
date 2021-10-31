#include <cstring>
#include "Stroka.h"

int char_array_fix(char** parray, std::istream& in)
{
    int er, count, N = 4;
    int c;
    char* ar;
    ar = new char[N];
    if (ar == NULL)  /* проверка выделения памяти */
    {
        printf("ошибка выделения памяти \n");
        return 0;
    }

    for (int i = 0; i < N; i++)
        ar[i] = 0;

    c = 0;
    count = 0;
    while (1)
    {
        if (count < N)
            *(ar + count) = getchar();
        //     in >> *(ar + count);

        else
        {
            char* tmp;
            tmp = ar;
            N *= 2;

            {
                ar = new char[N];
                if (ar == NULL)  /* проверка перевыделения памяти */
                {
                    printf("ошибка выделения памяти \n");
                    delete(tmp);
                    return 0;
                }

                for (int i = 0, k = N / 2; i < k; i++)
                    ar[i] = tmp[i];
            }
            count--;
        }
        if (*(ar + count) == '\n')
            break;
        count++;
    }




    *(ar + count) = '\0';
    *parray = ar;
    return count;
}
    Stroka::Stroka(){
#ifdef stroka_constructor
        std::cout << "stroka_constructor" << std::endl;
#endif
        p_mass = new char[2];
        length = 0;
        p_mass[0] = '\0';
    }
    Stroka::Stroka(const char* point) // конструктор-строка
    {
#ifdef stroka_constructor_argument
        std::cout << "stroka_constructor_argument" << std::endl;
#endif
        if (point == nullptr)
        {
            p_mass = new char[1];
            length = 0;
            p_mass[0] = '\0';
        }
        else
        {
            length = strlen(point);
            p_mass = new char[length + 1];

            for (unsigned int i = 0; i <= length; i++)
                p_mass[i] = point[i];
        }

    }
    Stroka::Stroka(const char a) // конструктор - символ
    {
#ifdef stroka_constructor_argument_one

        std::cout << "stroka_constructor_argument_one" << std::endl;
#endif
        p_mass = new char[2];
        length = 1;
        p_mass[0] = a;
        p_mass[1] = '/0';
    }
    Stroka::Stroka(Stroka& str) : length{ str.length } // конструктор - копирования
    {
#ifdef stroka_constructor_copy
        std::cout << "stroka_constructor_copy: кол-во вызовов = " << count_cpy << std::endl;
#endif
        p_mass = new char[length + 1];
        for (unsigned int i = 0; i <= this->length; i++)
            this->p_mass[i] = str.p_mass[i];
    }
    Stroka::~Stroka() {
#ifdef Stroka_destructor
        std::cout << "Stroka_destructor" << std::endl;
#endif
        delete[] p_mass;
        p_mass = nullptr;
        length = 0;
    }
    unsigned int Stroka::get_length(void)
    {
#ifdef DEBAG
        std::cout << "Stroka_get_length" << std::endl;
#endif
        return length;
    }
    Stroka& Stroka::operator= (const Stroka& str)
    {
#ifdef stroka_operator_prisvaivanie
        std::cout << "stroka_operator_=" << std::endl;
#endif
        if (this == &str)
            return *this;
        delete[] this->p_mass;
        this->length = str.length;
        this->p_mass = new char[length + 1];
        for (unsigned int i = 0; i <= this->length; i++)
            this->p_mass[i] = str.p_mass[i];
        return *this;
    }

    std::istream& operator>> (std::istream& in, Stroka& str)
{
#ifdef DEBAG
    std::cout << std::endl << "< stroka_operator>> >" << std::endl;
#endif

    str.length = char_array_fix(&str.p_mass, in);
    if (str.length == 0)
    {
        str.p_mass = new char[2];
        str.p_mass[0] = '\0';
    }

    return in;
}
    std::ostream& operator<< (std::ostream& out, const Stroka& str)
{

#ifdef DEBAG
    std::cout << std::endl << "< stroka_operator<< >" << std::endl;
#endif
    out << str.p_mass;
    return out;
}

