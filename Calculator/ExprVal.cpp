#include "ExprVal.h"
#include <ostream>
#include <iostream>


std::ostream& operator<< (std::ostream& stream, const ExprVal& expr) {
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(&expr);
    if (exprInt != nullptr) return std::cout << exprInt->val;

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(&expr);
    if (exprFloat != nullptr)  return std::cout << exprFloat->val;

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(&expr);
    if (exprDouble != nullptr)   return std::cout << exprDouble->val;
}

ExprValInt::ExprValInt(int val) : val(val) {}

ExprVal* ExprValInt::Plus(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValInt(val + exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val + exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val + exprDouble->val);
    
    return nullptr;
}

ExprVal* ExprValInt::Minus(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValInt(val - exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val - exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val - exprDouble->val);

    return nullptr;
}

ExprVal* ExprValInt::DivideBy(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValInt(val / exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val / exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val / exprDouble->val);

    return nullptr;
}

ExprVal* ExprValInt::MultiplyBy(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValInt(val * exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val * exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val * exprDouble->val);

    return nullptr;
}

std::ostream& operator<< (std::ostream& stream, const ExprValInt& expr) {
    return std::cout << expr.val;
}

ExprValFloat::ExprValFloat(float val) : val(val) {}

ExprVal* ExprValFloat::Plus(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValFloat(val + exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val + exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val + exprDouble->val);

    return nullptr;
}

ExprVal* ExprValFloat::Minus(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValFloat(val - exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val - exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val - exprDouble->val);

    return nullptr;
}

ExprVal* ExprValFloat::DivideBy(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValFloat(val / exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val / exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val / exprDouble->val);

    return nullptr;
}

ExprVal* ExprValFloat::MultiplyBy(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValFloat(val * exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValFloat(val * exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val * exprDouble->val);

    return nullptr;
}

std::ostream& operator<< (std::ostream& stream, const ExprValFloat& expr) {
    return std::cout << expr.val;
}

ExprValDouble::ExprValDouble(double val) : val(val) {}

ExprVal* ExprValDouble::Plus(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValDouble(val + exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValDouble(val + exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val + exprDouble->val);

    return nullptr;
}


ExprVal* ExprValDouble::Minus(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValDouble(val - exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValDouble(val - exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val - exprDouble->val);

    return nullptr;
}

ExprVal* ExprValDouble::DivideBy(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValDouble(val / exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValDouble(val / exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val / exprDouble->val);

    return nullptr;
}

ExprVal* ExprValDouble::MultiplyBy(const ExprVal* expr) const
{
    const ExprValInt* exprInt = dynamic_cast<const ExprValInt*>(expr);
    if (exprInt != nullptr) return new ExprValDouble(val * exprInt->val);

    const ExprValFloat* exprFloat = dynamic_cast<const ExprValFloat*>(expr);
    if (exprFloat != nullptr) return new ExprValDouble(val * exprFloat->val);

    const ExprValDouble* exprDouble = dynamic_cast<const ExprValDouble*>(expr);
    if (exprDouble != nullptr) return new ExprValDouble(val * exprDouble->val);

    return nullptr;
}

std::ostream& operator<< (std::ostream& stream, const ExprValDouble& expr) {
    return std::cout << expr.val;
}
