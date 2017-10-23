#ifndef __EXPR_H___
#define __EXPR_H___
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Expression {
  protected:
    string espr;
    long eval;

  public:
    virtual string toString() const = 0;
    virtual long evaluate() const = 0;

    string getEspr()
    {
      return espr;
    }

    long getEval()
    {
      return eval;
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
      eval = lg;
    }

    long evaluate() const
    {
      return eval;
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
    long l_eval;
    long r_eval;

  public:
    OperatorExpression(Expression * lhs, Expression * rhs)
    {
      l_espr = "(" + lhs->getEspr();
      r_espr = rhs->getEspr() + ")";
      l_eval = lhs->getEval();
      r_eval = rhs->getEval();
      delete lhs;
      delete rhs;
    }

    long evaluate() const
    {
      return eval;
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
      eval = l_eval + r_eval;
    }
};

class MinusExpression: public OperatorExpression {
  public:
    MinusExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " - " + r_espr;
      eval = l_eval - r_eval;
    }
};


class TimesExpression: public OperatorExpression {
  public:
    TimesExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " * " + r_espr;
      eval = l_eval * r_eval;
    }
};


class DivExpression: public OperatorExpression {
  public:
    DivExpression(Expression * lhs, Expression * rhs): OperatorExpression(lhs, rhs)
    {
      espr = l_espr + " / " + r_espr;
      eval = l_eval / r_eval;
    }
};

#endif
