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
    return 0;
}

// Function to perform arithmetic operations.
ExprVal* applyOp(const ExprVal* a, const ExprVal* b, char op) {
    switch (op) {
    case '+': return a->Plus(b);
    case '-': return a->Minus(b);
    case '*': return a->MultiplyBy(b);
    case '/': return a->DivideBy(b);
    }
    return nullptr;
}

// Function that returns value of
// expression after evaluation.
const ExprVal* Expr::evaluate(const string_view& tokens) const {
    size_t i;

    // stack to store integer values.
    stack <const ExprVal*> values;

    // stack to store operators.
    stack <char> ops;

    for (i = 0; i < tokens.length(); i++) {

        // Current token is a whitespace,
        // skip it.
        if (tokens[i] == ' ')
            continue;

        // Current token is an opening
        // brace, push it to 'ops'
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if (isdigit(tokens[i])) {
            int val = 0;

            // There may be more than one
            // digits in number.
            while (i < tokens.length() &&
                isdigit(tokens[i]))
            {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }

            values.push(new ExprValInt(val));

            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            //  token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
            i--;
        }

        // Current token is dolar sing, 
        //  read variables value from storage
        else if (tokens[i] == '$') {
            i++;
            size_t j = i;
            while (i < tokens.size() && isalpha(tokens[i])) { i++; }
            
            string_view key = tokens.substr(j, i-j);
            const ExprVal* v = storage.GetVal(key);
            values.push(v);
            i--;
        }

        // Closing brace encountered, solve
        // entire brace.
        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                const ExprVal* val2 = values.top();
                values.pop();

                const ExprVal* val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));

                //delete val1, val2;
            }

            // pop opening brace.
            if (!ops.empty())
                ops.pop();
        }

        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top())
                >= precedence(tokens[i])) {
                const ExprVal* val2 = values.top();
                values.pop();

                const ExprVal* val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));

                //delete val1, val2;
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while (!ops.empty()) {
        const ExprVal* val2 = values.top();
        values.pop();

        const ExprVal* val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));

        //delete val1, val2;
    }

    // Top of 'values' contains result, return it.
    return values.top();
}


Expr::Expr(const string& strExpr, Storage& storage) : str(strExpr), storage(storage) {}

const ExprVal* Expr::Evaluate() const
{
    size_t i = 0;
    while (isalpha(str[i++])) { /* pass */ }
    bool isAssignment = str[i-1] == '=';
    
    string_view strView(str.c_str());
    if (isAssignment) {
        const ExprVal* res = evaluate(strView.substr(i));
        storage.SetVal(string(strView.substr(0, i-1)), res);
        return res;
    }
    else {
        return evaluate(strView);
    }
}
