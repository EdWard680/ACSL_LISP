#include "Problems.h"
#include "LISP.h"

const string reverse(const string &in)
{
    Node parsed(in);
    if(!parsed.isExpr())
        throw invalid_argument(string("reverse(s==\"")+in+"\"): not a LISP expression");
    
    auto primaryList = *parsed.getList();
    vector<const Node *> reversedList;
    for(auto i = primaryList.rbegin(); i != primaryList.rend(); i++)
        reversedList.push_back(new Node(**i));
    
    Node reversed(reversedList, true);
    return reversed;
}

const string compressCommon(const string &in, const bool dupOnly)
{
    Node parsed(in);
    if(!parsed.isExpr())
        throw invalid_argument(string("compress(s=\"")+in+"\"): not a LISP expressin");
    
    auto primaryList = *parsed.getList();
    auto consecIter = primaryList.begin();
    
    vector<const Node *> compressedList;
    
    unsigned short nConsecs = 1;
    for(auto i = consecIter+1; i != primaryList.end(); i++)
    {
        if(**consecIter != **i || *i == primaryList.back())
        {
            if(**(primaryList.end()-2) == *primaryList.back() && i == primaryList.end()-1)
                nConsecs++;
            
            if(dupOnly && nConsecs < 2)
            {
                compressedList.push_back(new Node(**consecIter));
            }
            else
            {
                compressedList.push_back(new Node(vector<const Node *>({new Node(nConsecs), new Node(**consecIter)})));
            }
            
            consecIter = i;
            nConsecs = 1;
            if(**(primaryList.end()-2) != *primaryList.back() && i == primaryList.end()-1)
            {
                if(dupOnly)
                    compressedList.push_back(new Node(*primaryList.back()));
                else
                    compressedList.push_back(new Node(vector<const Node *>({new Node((unsigned short)(1)), new Node(*primaryList.back())})));
            }
        }
        else
        {
            nConsecs++;
        }
    }
    
    Node compressed(compressedList, true);
    return compressed;
}

const string compress(const string &in)
{
    return compressCommon(in, false);
}

const string compressDuplicatesOnly(const string &in)
{
    return compressCommon(in, true);
}

const string shrink(const string &in)
{
	Node parsed(in);
    if(!parsed.isExpr())
        throw invalid_argument(string("compress(s=\"")+in+"\"): not a LISP expressin");
    
    auto primaryList = *parsed.getList();
	
	if(primaryList.back()->getType() != Node::INT)
	{
		throw invalid_argument(string("compress(s=\"")+in+"\"): last element \""+primaryList.back()->toString()+"\" is not a number");
	}
	
	const int n = *primaryList.back()->getInt();
	
	vector<const Node *> shrunkList;
	for(int i = 1; i <= primaryList.size(); i++)
	{
		if(i % n)
			shrunkList.push_back(new Node(*primaryList[i-1]));
	}
	
	Node shrunk(shrunkList, true);
	
    return shrunk;
}

const string split(const string &in)
{
	Node parsed(in);
    if(!parsed.isExpr())
        throw invalid_argument(string("compress(s=\"")+in+"\"): not a LISP expressin");
    
    auto primaryList = *parsed.getList();
	
	if(primaryList.back()->getType() != Node::INT)
	{
		throw invalid_argument(string("compress(s=\"")+in+"\"): last element \""+primaryList.back()->toString()+"\" is not a number");
	}
	
	const int n = *primaryList.back()->getInt();
	
	vector<const Node *> headList, tailList;
	for(int i = 0; i < n; i++)
	{
		headList.push_back(new Node(*primaryList[i]));
	}
	
	for(int i = n; i < primaryList.size(); i++)
	{
		tailList.push_back(new Node(*primaryList[i]));
	}
	
	Node head(headList, true), tail(tailList, true);
	
    return head.toString()+' '+tail.toString();
}





