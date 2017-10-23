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

//    virtual ~NumExpression(){}
};

class OperatorExpression: public Expression {
  protected:
    string l_espr;
    string r_espr;

  public:
    OperatorExpression(Expression * lhs, Expression * rhs)
    {
      l_espr = "(" + lhs->getEspr();
      r_espr = rhs->getEspr() + ")";
      delete lhs;
      delete rhs;
    }

    string toString() const
    {
      return espr;
    }
};


class PlusExpression: public OperatorExpression {
  public:
    PlusExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " + " + r_espr;
    }
};

class MinusExpression: public OperatorExpression {
  public:
    MinusExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " - " + r_espr;
    }
};


class TimesExpression: public OperatorExpression {
  public:
    TimesExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " * " + r_espr;
    }
};


class DivExpression: public OperatorExpression {
  public:
    DivExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " / " + r_espr;
    }
};

#endif
