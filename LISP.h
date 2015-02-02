#ifndef _LISP_H_
#define _LISP_H_

#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

using std::string;
using std::vector;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::invlaid_argument;

class Node
{
public:
    typedef enum {CHAR, INT, LIST} TYPE;
    
private:
    bool expr;
    TYPE t;
    
    union Data
    {
        char c;
        unsigned short i;
        vector<const Node *> list;
    } data;
    
public:
    Node(const string& s);
    Node(const char c);
    Node(const unsigned short i);
    Node(const vector<const Node *> l);
    Node(const Node& other);
    virtual ~Node();
    
public:
    const bool isExpr() const {return expr;};
    const TYPE getType() const {return t;};
    const char * const getChar() const;
    const unsigned short * const getInt() const;
    const vector<const Node *> * const getList() const;   // I s2g if you even TRY to change the data in list
    
public:
    const string toString() const;
    operator const string() const {return toString();};
};


#endif _LISP_H_