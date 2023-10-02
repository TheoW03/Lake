#include <iostream>
#include <string>
#include <vector>
#include "../../src/CompilerFrontend/Lexxer.h"
using namespace std;

#define OFFSET 65536

#ifndef STAT_H
#define STAT_H
enum status
{
    N_NULL,
    NUM,
    OPERATOR
};
#endif
#ifndef NODE_H
#define NODE_H

struct Node
{
    struct Node *left;
    struct Node *right;
    status s;
    virtual ~Node();
    Node() : left(nullptr), right(nullptr) {}
};
struct VaraibleReference : public Node
{
    Node *expression;
    Tokens *varaible;
};
struct VaraibleDeclaration : public Node
{
    Node *expression;
    Tokens *varaible;
    Tokens *typeOfVar;
    int size;
    int constant;
};

struct BoolExpressionNode : public Node
{
    Node *right;
    Node *left;
    Tokens *op;
};
struct BooleanLiteralNode : public Node
{
    Tokens *value;
};
struct LoopNode : public Node
{
    BoolExpressionNode *condition;
    vector<Node *> statements;
};
struct ElseNode : public Node
{

    vector<Node *> statements;
};
struct IfSatementNode : public Node
{

    BoolExpressionNode *condition;
    vector<Node *> statements;
    ElseNode *Else;
};
struct funcCallNode : public Node
{
    Tokens *funcCall;
    vector<Node *> params;
};

struct FloatNode : public Node
{
    string num;
};

struct IntegerNode : public Node
{
    string num;
};
struct StringNode : public Node
{
    string stringBuffer;
};
struct OperatorNode : public Node
{
    struct Tokens *token;
};
struct StatementNode : public Node
{
    struct Node *expression;
    struct Tokens *nameOfVar;
};
struct ReturnStatment : public Node
{
    Node *expression;
};
// struct ConstantVarNode : public Node
// {
//     Node *expression;
//     Tokens *varailbe;
//     Tokens *typeOfVar;
//     int size;
// };
struct FunctionNode : public Node
{
    struct Tokens *nameOfFunction;
    vector<VaraibleDeclaration *> params;
    vector<Node *> statements;
    Tokens *returnType;
};
struct ForLoopNode : public Node
{
    Node *incrimentorVar;
    BoolExpressionNode *condition;
    vector<Node *> statements;
};
#endif // NODE_H

vector<FunctionNode *> parse(vector<Tokens> &tokens);

Node *term(vector<Tokens> &tokens);
Node *factor(vector<Tokens> &tokens);

Node *expression(vector<Tokens> &tokens);

Tokens *matchAndRemove(vector<Tokens> &tokens, type type, string caller);
bool isNull(Node *n);
Node *handleFunctions(vector<Tokens> &tokens);
void printParams(vector<Tokens *> a);
Node *testParse(vector<Tokens> &tokens);

vector<FunctionNode *> functionParse(vector<Tokens> &tokens);
Node *parseVar(vector<Tokens> &tokens, Tokens *name);
Node *handleCalls(vector<Tokens> &tokens, Tokens *checkIfFunct);
Node *handleSatements(vector<Tokens> &tokens);
Node *testExpressionParse(vector<Tokens> &tokens);