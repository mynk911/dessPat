#ifndef _GOF_FACADE_H_
#define _GOF_FACADE_H_
#include <istream>

#include "gof_export.h"

namespace gof {

/* Currently the compiler subsystem is devoid of functionality and
 only serves to represent a complex system. For a more cocrete example
 1) Come up a simple toy language. This would need recognition of valid
 tokens, statements, expressions as such. Would need some compiler design
 research.
 2) Do an actual implementation of the below laid out Design
*/

class ProgramNodeBuilder;
class ProgramNode;
class CodeGenerator;
class ByteCodeStream;
class ExpressionNode;
class StatementNode;
class ByteCode;

// encapsulates a machine instruction
class ByteCode
{
public:
    ByteCode();
    ~ByteCode();
private:
};

// stream for bytecode
class ByteCodeStream
{
public:
    ByteCodeStream();
    ~ByteCodeStream();

private:

};

// Tokens in the programming language
class Token
{
public:
    Token();
    ~Token();

private:

};

// Converts a stream of characters into a stream of Tokens
class Scanner
{
public:
    Scanner(std::istream&);
    virtual ~Scanner();

    virtual Token& Scan();
private:
    std::istream* _inputStream;
};

// Uses a ProgramNodeBuilder to build a parse tree from Scanner's
// tokens
class Parser
{
public:
    Parser();
    virtual ~Parser();
    virtual void Parse(Scanner&, ProgramNodeBuilder&);
};

// A Builder Class. Builds a parse tree incrementally.
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

// A composite class heirarchy.
// Defines an interface for manipulating ProgramNode and it's
// children
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
// inherited by ExpressionNode, StatementNode

// A visitor class.
// ProgramNode subclasses use this object to generate
// machine code in form of Bytecode objects on a bytecode
// stream
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

class RISCCodeGenerator : public CodeGenerator
{
public:
    RISCCodeGenerator(ByteCodeStream&);
    ~RISCCodeGenerator();
};

// inherited by StackMachineCodeGenerator, RISCCodeGenerator ...


// Facade over compiler subsystem
class Compiler
{
public:
    Compiler();
    ~Compiler();
    virtual void Compile(std::istream&, ByteCodeStream&);
};

}
#endif // _GOF_FACADE_H_