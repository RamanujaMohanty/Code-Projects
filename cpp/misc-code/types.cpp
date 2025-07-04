#include <iostream>
#include <string>

bool isalpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isspace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

int main()
{
    std::string a = "A0B1C2 hello";
    if (isalpha(a[0])) std::cout << "The first character is a letter." << std:: endl;
    if (isspace(a[6])) std::cout << "This character is a space." << std::endl;
    return 0;
}
