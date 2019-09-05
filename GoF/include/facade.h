#ifndef _GOF_FACADE_H_
#define _GOF_FACADE_H_
#include <istream>

class ProgramNodeBuilder;
class ProgramNode;
class CodeGenerator;
class ByteCodeStream;
class ExpressionNode;
class StatementNode;

//class ByteCode, ByteCodeStream and Token definition

class Token
{
public:
    Token();
    ~Token();

private:

};

class Scanner
{
public:
    Scanner(std::istream&);
    virtual ~Scanner();

    virtual Token& Scan();
private:
    std::istream* _inputStream;
};

class Parser
{
public:
    Parser();
    virtual ~Parser();
    virtual void Parse(Scanner&, ProgramNodeBuilder&);
};

class ProgramNodeBuilder
{
public:
    ProgramNodeBuilder();
    virtual ~ProgramNodeBuilder();

    virtual ProgramNode* NewVariable(const char* variableName) const;
    virtual ProgramNode* NewAssignment(ProgramNode* variable,
        ProgramNode* expression) const;
    virtual ProgramNode* NewReturnStatement(ProgramNode* value) const;
    virtual ProgramNode* NewCondition(ProgramNode* condition,
        ProgramNode* truePart, ProgramNode* falsePart) const;
    // ...
    ProgramNode* GetRootNode();
private:
    ProgramNode* _node;
};

class ProgramNode
{
public:
    // Program node manipulation
    virtual void GetSourcePosition(int& line, int& index);
    // ...

    // child manipulation
    virtual void Add(ProgramNode*);
    virtual void Remove(ProgramNode*);
    // ...

    virtual void Traverse(CodeGenerator&);
    
    virtual ~ProgramNode();
protected:
    ProgramNode();
};
// inherited by ExpressiionNode, StatementNode
class CodeGenerator
{
public:
    virtual ~CodeGenerator();
    virtual void Visit(StatementNode*);
    virtual void Visit(ExpressionNode*);
    // ...
protected:
    CodeGenerator(ByteCodeStream&);
private:
    // commented to allow compilation
    //ByteCodeStream& _output;
};
// inherited by StackMachineCodeGenerator, RISCCodeGenerator ...


#endif // _GOF_FACADE_H_