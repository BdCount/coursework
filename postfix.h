#pragma once
// Operator supported: +,-,*,/,%,^,(,)
// перевод в префексную форму

#include<string>
int infix_to_postfix(std::string&, std::string&);

int precedence(char, char);

bool check_exprassion(std::string&);