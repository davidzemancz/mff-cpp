#include "Expr.h"
#include <stack>
#include "ExprVal.h"
//#include <bits/stdc++.h>

using namespace std;


// Function to find precedence of
// operators.
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '%')
        return 3;
    return 0;
}

// Function to perform arithmetic operations.
ExprVal* applyOp(const ExprVal* a, const ExprVal* b, char op) {
    switch (op) {
    case '+': return a->Plus(b);
    case '-': return a->Minus(b);
    case '*': return a->MultiplyBy(b);
    case '/': return a->DivideBy(b);
    case '%': return a->Mod(b);
    }
    return nullptr;
}

void deleteExprVal(const ExprVal* exprVal) {
    if (!exprVal->IsStored) delete exprVal;
}

// Function that returns value of
// expression after evaluation.
ExprVal* Expr::evaluate(const string_view& tokens) const {
    size_t i;

    // stack to store integer values.
    stack <ExprVal*> values;

    // stack to store operators.
    stack <char> ops;

    try {
        for (i = 0; i < tokens.length(); i++) {

            // Skip spaces
            if (tokens[i] == ' ') {
                continue;
            }

            else if (tokens[i] == '(') {
                ops.push(tokens[i]);
            }
            else if (isdigit(tokens[i])) {
                int whole = 0;
                int decimal = 1; // Set to 1 because of .0001 numbers, needs to be subtracted later
                bool dotFound = false;

                // Read number
                while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.'))
                {
                    if (tokens[i] == '.') {
                        dotFound = true;
                    }
                    else if (!dotFound) {
                        whole = (whole * 10) + (tokens[i] - '0');
                    }
                    else {
                        decimal = (decimal * 10) + (tokens[i] - '0');
                    }
                    i++;
                }

                // Decimal number
                if (dotFound) {
                    // Float
                    if (i < tokens.length() && tokens[i] == 'f') {
                        float val = decimal;
                        while (val >= 10) {
                            val /= 10;
                        }
                        val -= 1; // Subtract that 1 mentioned before
                        val += whole;
                        values.push(new ExprValFloat(val));
                        i++;
                    }
                    // Double
                    else {
                        double val = decimal;
                        while (val >= 10) {
                            val /= 10;
                        }
                        val -= 1; // Subtract that 1 mentioned before
                        val += whole;
                        values.push(new ExprValDouble(val));
                    }
                }
                // Whole number
                else {
                    values.push(new ExprValInt(whole));
                }
                i--;
            }
            // Variable
            else if (tokens[i] == '$') {
                i++;
                size_t j = i;
                while (i < tokens.size() && isalpha(tokens[i])) { i++; }

                string_view key = tokens.substr(j, i - j);
                ExprVal* v = storage.GetVal(key);
                v->IsStored = true;
                values.push(v);
                i--;
            }
            else if (tokens[i] == ')')
            {
                while (!ops.empty() && ops.top() != '(')
                {
                    if (values.size() == 0) return nullptr;
                    const ExprVal* val2 = values.top();
                    values.pop();

                    if (values.size() == 0) return nullptr;
                    const ExprVal* val1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();
                    
                    ExprVal* opRes = applyOp(val1, val2, op);
                    if (opRes == nullptr) return nullptr;
                    values.push(opRes);

                    deleteExprVal(val1);
                    deleteExprVal(val2);
                }

                // Pop opening brace.
                if (!ops.empty())
                    ops.pop();
            }
            // Operator
            else
            {
                while (!ops.empty() && precedence(ops.top())
                    >= precedence(tokens[i])) {
                    if (values.size() == 0) return nullptr;
                    const ExprVal* val2 = values.top();
                    values.pop();

                    if (values.size() == 0) return nullptr;
                    const ExprVal* val1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();

                    ExprVal* opRes = applyOp(val1, val2, op);
                    if (opRes == nullptr) return nullptr;
                    values.push(opRes);

                    deleteExprVal(val1);
                    deleteExprVal(val2);
                }

                ops.push(tokens[i]);
            }
        }

        // Rest
        while (!ops.empty()) {
            char op = ops.top();
            ops.pop();

            if (values.size() == 0) return nullptr;
            const ExprVal* val2 = values.top();
            values.pop();

            if ((op == '-' || op == '+') && values.size() == 0)
                values.push(new ExprValInt(0));
            
            if (values.size() == 0) return nullptr;
            const ExprVal* val1 = values.top();
            values.pop();

            ExprVal* opRes = applyOp(val1, val2, op);
            if (opRes == nullptr) return nullptr;
            values.push(opRes);

            deleteExprVal(val1);
            deleteExprVal(val2);
        }
    }
    catch (...) {
        return nullptr;
    }

    // Return result
    return values.size() == 1 ? values.top() : nullptr; 
}

Expr::Expr(const string& strExpr, Storage& storage) : str(strExpr), storage(storage) {}

const ExprVal* Expr::Evaluate() const
{
    size_t i = 0;
    while (isalpha(str[i++])) { /* pass */ }
    bool isAssignment = str[i-1] == '=';
    
    string_view strView(str.c_str());
    if (isAssignment) {
        ExprVal* res = evaluate(strView.substr(i));
        storage.SetVal(strView.substr(0, i-1), res);
        return res;
    }
    else {
        return evaluate(strView);
    }
}
