#include <iostream>
#include "LISP.h"

using std::cin;
using std::cout;
using std::endl;

int main(void)
{
    char input[255];
    cin.getline(input, 255, '\n');
    Node lispExpr(input);
    cout<<lispExpr.toString()<<endl;
    return 0;
}