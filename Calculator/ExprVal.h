#pragma once
#include <iostream>

class ExprVal {
public:
    virtual ExprVal* Plus(const ExprVal* expr) const = 0;
    virtual ExprVal* Minus(const ExprVal* expr) const = 0;
    virtual ExprVal* DivideBy(const ExprVal* expr) const = 0;
    virtual ExprVal* MultiplyBy(const ExprVal* expr) const = 0;
};

std::ostream& operator << (std::ostream& stream, const ExprVal& exprVal);

class ExprValInt : public ExprVal {

public:
    int val;

    ExprValInt(int val);
    ExprVal* Plus(const ExprVal* expr) const;
    ExprVal* Minus(const ExprVal* expr) const;
    ExprVal* DivideBy(const ExprVal* expr) const;
    ExprVal* MultiplyBy(const ExprVal* expr) const;
};

std::ostream& operator << (std::ostream& stream, const ExprValInt& exprVal);

class ExprValFloat : public ExprVal {

public:
    float val;

    ExprValFloat(float val);
    ExprVal* Plus(const ExprVal* expr) const;
    ExprVal* Minus(const ExprVal* expr) const;
    ExprVal* DivideBy(const ExprVal* expr) const;
    ExprVal* MultiplyBy(const ExprVal* expr) const;
};

std::ostream& operator << (std::ostream& stream, const ExprValFloat& exprVal);

class ExprValDouble : public ExprVal {

public:
    double val;

    ExprValDouble(double val);
    ExprVal* Plus(const ExprVal* expr) const;
    ExprVal* Minus(const ExprVal* expr) const;
    ExprVal* DivideBy(const ExprVal* expr) const;
    ExprVal* MultiplyBy(const ExprVal* expr) const;
};

std::ostream& operator << (std::ostream& stream, const ExprValDouble& exprVal);


