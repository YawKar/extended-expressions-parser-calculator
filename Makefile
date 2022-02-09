# C compiler
CC=gcc
NDS=src/Nodes
ENUMS=src/EnumTypes
FLAGS=-lm -Wall -Wextra

all: main.o ConstantTypes.o OperatorTypes.o StdFunctionTypes.o EvaluateNodesFunctions.o ExpressionFunctions.o InputFunctions.o BaseNode.o ConstantNode.o NumberNode.o OperatorNode.o StdFunctionNode.o VariableNode.o OperandsContainer.o Parser.o StringFunctions.o VariablesTable.o
	$(CC) main.o ConstantTypes.o OperatorTypes.o StdFunctionTypes.o EvaluateNodesFunctions.o ExpressionFunctions.o InputFunctions.o BaseNode.o ConstantNode.o NumberNode.o OperatorNode.o StdFunctionNode.o VariableNode.o OperandsContainer.o Parser.o StringFunctions.o VariablesTable.o $(FLAGS)

main.o:
	$(CC) -c src/main.c -o main.o

ConstantTypes.o:
	$(CC) -c $(ENUMS)/ConstantTypes.c -o ConstantTypes.o

OperatorTypes.o:
	$(CC) -c $(ENUMS)/OperatorTypes.c -o OperatorTypes.o

StdFunctionTypes.o:
	$(CC) -c $(ENUMS)/StdFunctionTypes.c -o StdFunctionTypes.o

EvaluateNodesFunctions.o:
	$(CC) -c src/EvaluateNodesFunctions/EvaluateNodesFunctions.c -o EvaluateNodesFunctions.o

ExpressionFunctions.o:
	$(CC) -c src/ExpressionFunctions/ExpressionFunctions.c -o ExpressionFunctions.o

InputFunctions.o:
	$(CC) -c src/InputFunctions/InputFunctions.c -o InputFunctions.o

BaseNode.o:
	$(CC) -c $(NDS)/BaseNode/BaseNode.c -o BaseNode.o

ConstantNode.o:
	$(CC) -c $(NDS)/ConstantNode/ConstantNode.c -o ConstantNode.o

NumberNode.o:
	$(CC) -c $(NDS)/NumberNode/NumberNode.c -o NumberNode.o

OperatorNode.o:
	$(CC) -c $(NDS)/OperatorNode/OperatorNode.c -o OperatorNode.o

StdFunctionNode.o:
	$(CC) -c $(NDS)/StdFunctionNode/StdFunctionNode.c -o StdFunctionNode.o

VariableNode.o:
	$(CC) -c $(NDS)/VariableNode/VariableNode.c -o VariableNode.o

OperandsContainer.o:
	$(CC) -c src/OperandsContainer/OperandsContainer.c -o OperandsContainer.o

Parser.o:
	$(CC) -c src/Parser/Parser.c -o Parser.o

StringFunctions.o:
	$(CC) -c src/StringFunctions/StringFunctions.c -o StringFunctions.o

VariablesTable.o:
	$(CC) -c src/VariablesTable/VariablesTable.c -o VariablesTable.o

clean:
	rm -Rf *.o
