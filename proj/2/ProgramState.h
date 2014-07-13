// ProgramState.h
//
// CS 32 / Summer 2014
// Project #2: What's Simple Is True
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * An array of 26 integers, holding the current values of the 26
//      variables.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// I've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <iostream>
#include "globals.h"
#include "Stack.h"

struct Variable
{
    char name;
    int value;
};

class ProgramState
{
public:
	ProgramState(int numLines);

    int getCounter();
    void setCounter(int line, std::ostream &outf);
    void incrementCounter();

    int getVariable(char var) const;
    bool setVariable(char var, int val);

    bool isInBounds(int line) const;

    Stack<int>* gosub_returns;

	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.


private:
	int m_numLines;
    int program_counter;
    Variable variables[ALPHABET_LENGTH];
    int charToArrayPosition(char c) const;
    char arrayPositionToChar(int i) const;
    bool arrayPositionInBounds(int pos) const;
};

#endif
