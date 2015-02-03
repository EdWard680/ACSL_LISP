#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Problems.h"

using std::cout;
using std::cin;
using std::istream;
using std::ifstream;
using std::endl;
using std::invalid_argument;

typedef const string (*LISP_FUNCTION_t)(const string &);
LISP_FUNCTION_t problems[] = {reverse, compress, compressDuplicatesOnly, shrink, split};


int main(int argc, char **argv)
{
    istream *in = NULL;
    char buf[255];
    
    if(argc > 1)
        in = new ifstream(argv[1]);
    else
        in = &cin;
    
    for(int i = 0; i < 5 && in->good(); i++)
    {
        in->getline(buf, 255, '\n');
        try
        {
            cout<<problems[i](buf)<<endl;
        }
        catch(const invalid_argument &ia)
        {
            cout<<"Invalid input: "<<ia.what()<<endl;
        }
    }
    
    return 0;
}