#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

string TrimBrackets(const string& input)
{
    string result = input;
    const int length = result.length();
    while(result[0] == '(' && result[result.length() -1] == ')')
    {
        int bracketCount = 1;
        for (int i = 1; i < result.length(); i++)
        {
            if(result[i] == '(')
            {
                bracketCount++;
            }
            if(result[i] == ')')
            {
                bracketCount--;
            }
            if(bracketCount==0 && i != length - 1)
            {
                return  result;
            }
        }
        result = result.substr(1, result.length() - 2);
    }

    return result;
}

int GetIndexSkipBracketed(const string& input, const char c, const char c1)
{
    const char StartBracket = '(';
    const char EndBracket = ')';
    int BracketCount = 0;
    int len = input.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (input[i] == StartBracket)
        {
            BracketCount++;
        }

        if (input[i] == EndBracket)
        {
            BracketCount--;
        }

        if ((input[i] == c || input[i] == c1) && BracketCount == 0)
            return i;
    }
    return -1;
}

int GetOperatorIndex(const string& equation)
{
    int index = GetIndexSkipBracketed(equation, '-', '+');
    if (index == -1)
    {
        index = GetIndexSkipBracketed(equation, '*', '/');
    }

    return index; 
}


char GetOperation(const string& input)
{
    const string equation = TrimBrackets(input);
    const int OperatorIndex = GetOperatorIndex(equation);
    return equation[OperatorIndex];
}

bool ContainsOperand(const string& input)
{
    if(input.find('(') != std::string::npos)
    {
        return true;
    }
    if(input.find(')') != std::string::npos)
    {
        return true;
    }
    if(input.find('+') != std::string::npos)
    {
        return true;
    }
    if(input.find('-') != std::string::npos)
    {
        return true;
    }
    if(input.find('*') != std::string::npos)
    {
        return true;
    }
    if(input.find('/') != std::string::npos)
    {
        return true;
    }
    return false;
}

bool TryGetNumber(float* number, const string& input)
{
    if(ContainsOperand(input))
        return false;
    *number = stof(input);
    return true;
}

string GetLeftOperation(const string& input)
{
    string equation = TrimBrackets(input);
    int operatorIndex = GetOperatorIndex(equation);
    string result = equation.substr(0, operatorIndex);
    return result;
}

string GetRightOperation(const string& input)
{
    string equation = TrimBrackets(input);
    int operatorIndex = GetOperatorIndex(equation);
    string result = equation.substr(operatorIndex + 1, equation.length() - operatorIndex - 1);
    return result;
}

float Calculate(const string& input)
{
   if(input.empty())
       return 0;
    
    float number = 0;
    if(TryGetNumber(&number, input))
        return number;

    char operation = GetOperation(input);

    switch (operation)
    {
    case '-': return Calculate(GetLeftOperation(input)) - Calculate(GetRightOperation(input));
    case '+': return Calculate(GetLeftOperation(input)) + Calculate(GetRightOperation(input));
    case '*': return Calculate(GetLeftOperation(input)) * Calculate(GetRightOperation(input));
    case '/': return Calculate(GetLeftOperation(input)) / Calculate(GetRightOperation(input));
    default: return 0;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string input;
    cout << "Введите выражение: ";
    cin >> input;
    const float res = Calculate(input);
    cout << "Результат: " << res << endl;
}