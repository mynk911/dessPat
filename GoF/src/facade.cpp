#include "facade.h"

Token::Token()
{
}

Token::~Token()
{
}

Scanner::Scanner(std::istream&)
{
}

Scanner::~Scanner()
{
}

Token & Scanner::Scan()
{
    return *(new Token);
}


Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::Parse(Scanner &, ProgramNodeBuilder &)
{
}

ProgramNodeBuilder::ProgramNodeBuilder()
{
}

ProgramNodeBuilder::~ProgramNodeBuilder()
{
}

ProgramNode * ProgramNodeBuilder::NewVariable(const char * variableName) const
{
    return nullptr;
}

ProgramNode * ProgramNodeBuilder::NewAssignment(ProgramNode * variable, ProgramNode * expression) const
{
    return nullptr;
}

ProgramNode * ProgramNodeBuilder::NewReturnStatement(ProgramNode * value) const
{
    return nullptr;
}

ProgramNode * ProgramNodeBuilder::NewCondition(ProgramNode * condition, ProgramNode * truePart, ProgramNode * falsePart) const
{
    return nullptr;
}

ProgramNode * ProgramNodeBuilder::GetRootNode()
{
    return nullptr;
}

ProgramNode::ProgramNode()
{
}

ProgramNode::~ProgramNode()
{
}

void ProgramNode::GetSourcePosition(int & line, int & index)
{
}

void ProgramNode::Add(ProgramNode *)
{
}

void ProgramNode::Remove(ProgramNode *)
{
}

void ProgramNode::Traverse(CodeGenerator &)
{
}

CodeGenerator::CodeGenerator(ByteCodeStream&)
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::Visit(StatementNode *)
{
}

void CodeGenerator::Visit(ExpressionNode *)
{
}
