// Operator supported: +,-,*,/,%,^,(,)
// Operands supported: all single character operands

// перевод в префексную форму

/*
6*(-65)


*/
#pragma once

#include<stack>
#include"postfix.h"
#include "stroka_dec.h"
int infix_to_postfix(std::string& infix, std::string& posfix)
{
#ifdef DEBUG
    int count = 0;
#endif // DEBUG

    std::stack<char> oper;
    std::stack<Stroka_Dec*> res;
    int errors = false;    // флаг на ошибки // 1 - деление на 0; 2 - степень; 3- корень; 4 - факториал;
    char x, token;
    int i, j, size;    //i-index of infix,j-index of postfix
    j = 0;
    size = infix.size();
    Stroka_Dec* x1, * x2;
    for (i = 0; i < size && !errors; i++)
    {
        token = infix[i];
        
        if (token == '-') {
            if (i == 0) {
                token = 'f';
            }
            else
            if( !(infix[i - 1] == ')' || isalnum(infix[i - 1]) || infix[i - 1] == '!') )
                token = 'f';
        }
        if (token == '+') {
            if (i == 0) {
                continue;
            }
            if ( !(infix[i - 1] == ')' || isalnum(infix[i - 1]) || infix[i - 1] == '!') )
                continue;
        }
        
        
        if ((token >= '0' && token <= '9') || token == '.') // извлекаем переменные
        {
            int g = i;
            std::string str;
            for (; isalnum(token) || token == '.'; g++)
                token = infix[g];
            str.resize(g - i - 1);

            for (g = 0; g < str.size(); g++, i++)
                str[g] = infix[i];
          
            Stroka_Dec* f = new Stroka_Dec;
            *f = str;
/*
            if (i - g - 1 <= 0) { // унарный - в начале
                    
                if(i - g - 1 == 0)
                if (infix[0] == '-') {
                    oper.pop();
                    *f = f->operator-();
                }
                else
                if(infix[0] == '+')
                oper.pop(); // унарный + в начале
            }
            else
            if ((infix[i - g - 1] == '+' || infix[i - g - 1] == '-') && infix[i - g - 2] == '(') // унарный минус для числа
            if(infix[i - g - 1] == '+')
                oper.pop();
            else {
                oper.pop();
                *f = f->operator-();
            }/**/
            res.push(f);
            i--;
        }
        else
            if (token == '(')
                oper.push('(');
            else
                if (token == ')')
                {
                    Stroka_Dec*x1 = NULL, *x2 = NULL;
                    while ((x = oper.top()) != '(' && (!res.empty())) { // извлекаем выражение в скобках
                        x2 = res.top(); res.pop();
                        switch (x)
                        {
                        case '+':
                            x1 = res.top(); res.pop();
                            *x1 = (*x1 + *x2); res.push(x1); break;
                        case '-':
                            x1 = res.top(); res.pop();
                            *x1 = (*x1 - *x2); res.push(x1); break;
                        case '*':
                            x1 = res.top(); res.pop();
                            *x1 = (*x1 * *x2); res.push(x1); break;
                        case '/': {
                            if (*x2 == 0) {
                                errors = 1;
                                break;
                            }
                            else {
                                x1 = res.top(); res.pop();
                                *x1 = (*x1 / *x2); res.push(x1); break;
                            }
                        }
                            
                        case '^': {
                                if (*x2 < 0) {
                                    errors = 2;
                                    break;
                                }
                                x1 = res.top(); res.pop();
                                *x1 = (x1->pow(*x2)); res.push(x1); break;
                        }

                        case 'f': {
                            *x2 = x2->operator-();
                            res.push(x2);  x2 = NULL;
                            break;
                        }

                           case '&':
                            if (*x2 < 0) {
                                errors = 3;
                                break;
                            }
                            *x2 = x2->sqrt();
                            res.push(x2);  x2 = NULL;
                            break;
                        case '!':
                            if (*x2 < 0) {
                                errors = 5;
                                break;
                            }
                            *x2 = x2->factorial();
                            res.push(x2);  x2 = NULL;
                            break;
                        }
                        delete x2;
                        oper.pop();
                    }
                    oper.pop();
                }
                else
                {
                    Stroka_Dec*x1, *x2;
                    while ((!oper.empty()) && (!res.empty()) && precedence(token, oper.top()) <= precedence(oper.top(), -1)) { //если приoритет предыдущей операции выше, то выполняем ее
                        x = oper.top();
                        x2 = res.top(); res.pop();
                        switch (x)
                        {
                        case '+':
                            x1 = res.top(); res.pop();
                            *x1 = (*x1 + *x2); res.push(x1); break;
                        case '-':
                            x1 = res.top(); res.pop();
                            *x1 = (*x1 - *x2); res.push(x1); break;
                        case '*':
                            x1 = res.top(); res.pop();
                            *x1 = (*x1 * *x2); res.push(x1); break;
                        case '/':
                            if (*x2 == 0) {
                                errors = 1;
                                break;
                            }
                            else {
                                x1 = res.top(); res.pop();
                                *x1 = (*x1 / *x2); res.push(x1); break;
                            }
                        case '^':
                            if (*x2 < 0) {
                                errors = 2;
                                break;
                            }
                            x1 = res.top(); res.pop();
                            *x1 = (x1->pow(*x2)); res.push(x1); break;

                        case 'f': {
                            *x2 = x2->operator-();
                            res.push(x2);  x2 = NULL;
                            break;
                        }

                        case '&':
                            if (*x2 < 0) {
                                errors = 3;
                                break;
                            }
                            *x2 = x2->sqrt();
                            res.push(x2);  x2 = NULL;
                            break;
                        case '!':
                            if (*x2 < 0) {
                                errors = 5;
                                break;
                            }
                            *x2 = x2->factorial();
                            res.push(x2);  x2 = NULL;
                            break;
                        }
                        delete x2;
                        oper.pop();
                    }

                    oper.push(token); // добавляем операцию в стек
                }
    }

    if (!errors) {
        while (!oper.empty() && (!res.empty()) && !errors){
            x = oper.top();
            oper.pop();
            x2 = res.top(); res.pop();
            switch (x)
            {
            case '+':
                x1 = res.top(); res.pop();
                *x1 = (*x1 + *x2); res.push(x1); break;
            case '-':
                x1 = res.top(); res.pop();
                *x1 = (*x1 - *x2); res.push(x1); break;
            case '*':
                x1 = res.top(); res.pop();
                *x1 = (*x1 * *x2); res.push(x1); break;
            case '/':
                if (*x2 == 0) {
                    errors = 1;
                    break;
                }
                else {
                    x1 = res.top(); res.pop();
                    *x1 = (*x1 / *x2); res.push(x1); break;
                }
            case '^':
                if (*x2 < 0) {
                    errors = 2;
                    break;
                }
                x1 = res.top(); res.pop();
                *x1 = (x1->pow(*x2)); res.push(x1); break;
            case 'f': {
                *x2 = x2->operator-();
                res.push(x2);  x2 = NULL;
                break;
            }
            case '&':

                if (*x2 < 0) {
                    errors = 3;
                    break;
                }
                *x2 = x2->sqrt();
                res.push(x2);  x2 = NULL;
                break;
            case '!':
                if (*x2 < 0) {
                    errors = 5;
                    break;
                }
                *x2 = x2->factorial();
                res.push(x2);  x2 = NULL;
                break;
            }
            delete x2;
        }
    }

    if (errors)
    while (!res.empty()) {
        delete res.top();
        res.pop();
    }
    else {
        res.top()->long_to_string(posfix);
    }
    return errors;
}

int precedence(char x, char y)
{
    if (x == '(')
        return 0;    
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    if (x == '&' && y != x)
        return 4;
    if (x == '!')
        return 5;
    if (x == 'f' && y != x)
        return 6;
    return 7;
}


#define IN 1 /* внутри слова */
#define OUT 0 /* вне слова */

bool check_exprassion(std::string& str) {

    bool error = false;
    int i = 0;
    int state = OUT;
    int dot = 0;
    int barcket_in = 0;
    bool flag = false;  // в строке есть операнды

#ifdef DEBUG
    int count = 0;
#endif // DEBUG



    if (str[0] == '!' || str[0] == ')' || str[0] == '*' || str[0] == '/' || str[0] == '.' || str[0] == '^')
        return true;
    if ( (str[0] == '+' || str[0] == '-' || str[0] == '&' || str[0] == '(' ) && str.size() == 1)
        return true;
    if ( (str[str.size() - 1] > '9' || str[str.size() - 1] < '0') && str[str.size() - 1] != ')' && str[str.size() - 1] != '!')
        return true;

    while (i < str.size()) {
        if (str[i] == '!' || str[i] == '&' || str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-'
            || str[i] == '*' || str[i] == '/' || str[i] == '^')
            state = OUT;
        else if (state == OUT && str[i] != '.') {
            state = IN;
            dot = 0;
        }

        //chek_numbers
        if (str[i] <= '9' && str[i] >= '0')
            flag = true;

/*        // chek_dots
        {
            if (state == IN && str[i] == '.')
                dot++;
            if (state == OUT && str[i] == '.')
                return true;
            if (dot > 1)
                return true;
            if ((i + 1 < str.size() && str[i] == '.') && state == IN && (str[i + 1] > '9' || str[i + 1] < '0'))
                return true;
        }
        /**/
        // chek_factorial
        if (str[i] == '!'){
            if ((str[i - 1] == '(') || str[i - 1] == '&' || str[i - 1] == '*' || str[i - 1] == '/'
                || str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '^')
                return true;
            if (i + 1 < str.length())
                if (str[i + 1] == '&' || str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9'))
                    return true;
        }

        // chek_sqrt
        if (str[i] == '&')
        {
            if (i + 1 < str.size()) {
                if (str[i + 1] == ')' || str[i + 1] == '!' || str[i + 1] == '^' || str[i + 1] == '/' || str[i + 1] == '*')
                    return true;
            }
            else
                return true;
            if (i > 0)
                if ((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i - 1] == '!' || str[i - 1] == ')')
                    return true;
        }

        // chek_operators_+_-
        if (str[i] == '+' || str[i] == '-')
        {

            if (i > 0 && i + 1 < str.size()) {
                if ((str[i - 1] == '+' || str[i - 1] == '-') && (str[i + 1] == '+' || str[i + 1] == '-'))
                    return true;
            }
            if (i > 0)
                if (str[i] == '+' || str[i] == '-') {
                    if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' || str[i + 1] == '!' || str[i + 1] == ')')
                        return true;
                }
            if(i + 1 < str.size())
                if (str[i] == '+' || str[i] == '-') {
                    if ((str[i + 1] > '9' || str[i + 1] < '0') && str[i + 1] != ')' && str[i + 1] != '(' && str[i + 1] != '&' && str[i + 1] != '+' && str[i + 1] != '-')
                        return true;
            }
        }

        // chek_operators_/_*
        if (str[i] == '/' || str[i] == '*') {
            if(i + 1 < str.size())
                if (str[i + 1] == ')' || str[i + 1] == '!' || str[i + 1] == '^' || str[i + 1] == '/' || str[i + 1] == '*')
                    return true;
            if(i > 0)
                if ( str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^' || str[i - 1] == '(' || str[i - 1] == '&'
                    || str[i - 1] == '+' || str[i - 1] == '-')
                    return true;
        }
        // chek_pow
        if (str[i] == '^') {
            if (i + 1 < str.size())
                if(str[i + 1] == '^' || str[i + 1] == '!' || str[i + 1] == ')' || str[i + 1] == '*'
                   || str[i + 1] == '/')
                    return true;
            if (i > 0)
                if (str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '&'
                    || str[i - 1] == '^' || str[i - 1] == '(')
                    return true;
        }


        // chek_barcket
        {
            if (str[i] == '(') {
                barcket_in++;
                if (i > 0)
                    if (str[i - 1] == ')' || str[i - 1] == '!' || (str[i - 1] > '9' && str[i - 1] < '0'))
                        return true;
            }


            if (i + 1 < str.size())
                if (str[i] == '(' && str[i + 1] == ')')
                    return true;

            if (str[i] == ')')
                if (barcket_in == 0)
                    return true;
                else {
                    barcket_in--;
                    if (i + 1 < str.size())
                        if (str[i - 1] == '(' || str[i - 1] == '&' || (str[i - 1] > '9' && str[i - 1] < '0'))
                            return true;
                }
         }
        i++;

#ifdef DEBUG
        std::cout << "postfix_count = " << count++ << std::endl;
#endif // DEBUG
    }

    if (barcket_in)
        return true;

    return !flag;
}

#undef IN
#undef OUT
    