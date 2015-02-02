#include "LISP.h"

Node::Node(const string& s): expr(false)  // Main conversion step
{
    istringstream ss(s);
    char indicator;    // The first character tells us what kind of data it is
    while((indicator = char(ss.peek())) == ' ') ss.ignore(1);  // ensure that we are starting on a non-space
    
    switch(indicator)
    {
    case '\'':  // expression
        ss.ignore(1);
        if(ss.peek() != '(')    // assumes the next character is a list begin
            throw invalid_argument(string("Node::Node(")+s+"s is an invalid lisp expression");
        expr = true;
        
    case '(':  // list
    {
        ss.ignore();
        t = LIST;
        string next;
        int depth = 0;
        char cur;
        while((ss.peek() != ')' || depth > 0) && ss.good())
        {
            next.push_back(cur = char(ss.get()));   // extracts next character
            
            if(cur == '(')
                depth++;
            else if(cur == ')')
                depth--;
            
            if(depth == 0 && (cur == ' ' || cur == ')' || ss.peek == ')')) // either the end of a list or space between atoms or the end of this list
                data.list.push_back(new Node(next));
        }
        break;
        
    default: // Atom or invalid
        if(indicator == '-' || indicator == '0' || (indicator >= '1' && indicator <= '9'))  // Number
        {
            t = INT;
            ss>>data.i;
        }
        else if(indicator >= 'a' && indicator <= 'z' || indicator >= 'A' && indicator <= 'Z')  // Character
        {
            t = CHAR;
            ss>>data.c;
            // ignores any subsequent characters
        }
        else
        {
            throw invalid_argument(string("Node::Node(")+s+"s is an invalid lisp expression");
        }
        break;
    }
}

Node::Node(const char c): expr(false), t(CHAR)
{
    data.c = c;
}

Node::Node(const unsigned short i): expr(false), t(INT)
{
    data.i = i;
}

Node::Node(const vector<const Node *> l), expr(false), t(LIST)
{
    for(auto i = l.begin(); i != l.end(); i++)
        data.l.push_back(new Node(**i));
}

Node::Node(const Node &other): expr(other.expr), t(other.t)
{
    switch(t)
    {
    case CHAR:
        data.c = other.getChar();
        break;
    case INT:
        data.i = *other.getInt();
        break;
    case LIST:
        for(auto i = other.getList()->begin(); i != other.getList()->end(); i++)
            data.l.push_back(new Node(**i));
        break;
    }
}

const char * const Node::getChar() const
{
    if(t == CHAR)
        return &data.c;
    else
        return NULL;
}

const unsigned short * const Node::getInt() const
{
    if(t == INT)
        return &data.i;
    else
        return NULL;
}

const vector<const Node *> * const getList() const
{
    if(t == LIST)
        return &data.list;
    else
        return NULL;
}
