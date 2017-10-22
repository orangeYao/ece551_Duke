#ifndef __EXPR_H___
#define __EXPR_H___
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Expression {
  protected:
    string espr;

  public:
    virtual string toString() const = 0;
    string getEspr()
    {
        return espr;
    }
    virtual ~Expression(){}
};

class NumExpression: public Expression {
  public:
    NumExpression(long lg)
    {
      stringstream ss;
      ss << lg;
      espr = ss.str(); 
    }

    string toString() const
    {
      return espr;
    }
};

class PlusExpression: public Expression {

  public:
    PlusExpression(Expression * lhs, Expression * rhs)
    {
      espr = "(" + lhs->getEspr() + " + " + rhs->getEspr() + ")";
    }

    string toString() const
    {
      return espr;
    }
};

#endif
