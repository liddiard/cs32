// Facile.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "GotoStatement.h"
#include "GosubStatement.h"
#include "ReturnStatement.h"
#include "EndStatement.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iostream>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
    cout << "Enter Facile program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile)
    {
            cout << "Cannot open " << filename << "!" << endl;
            return 1;
    }
    interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(nullptr);

	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);

        stringstream ss;
        string type;

        ss << line;
        ss >> type;
        if (type == ".") break; // end of program

		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;
	stringstream ss;
	string type;
	char var;
	int val;

	ss << line;
	ss >> type;

	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal Facile program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable (single character) and then an integer value.
		statement = new LetStatement(var, val);
	}

    else if ( type == "PRINT" )
    {
        ss >> var;
        statement = new PrintStatement(var);
    }

    else if ( type == "ADD" )
    {
        ss >> var;
        ss >> val;
        statement = new AddStatement(var, val);
    }

    else if ( type == "SUB" )
    {
        ss >> var;
        ss >> val;
        statement = new SubStatement(var, val);
    }

    else if ( type == "MULT" )
    {
        ss >> var;
        ss >> val;
        statement = new MultStatement(var, val);
    }

    else if ( type == "DIV" )
    {
        ss >> var;
        ss >> val;
        statement = new DivStatement(var, val);
    }

    else if ( type == "GOTO" )
    {
        ss >> val;
        statement = new GotoStatement(val);
    }

    else if ( type == "GOSUB" )
    {
        ss >> val;
        statement = new GosubStatement(val);
    }

    else if ( type == "RETURN" )
    {
        statement = new ReturnStatement();
    }

    else if ( type == "END" )
    {
        statement = new EndStatement();
    }


	// Incomplete;  TODO:  Finish this function!



	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );

    ProgramState* state = new ProgramState(program.size());

    int line = 1; // point of entry (line 1)

    while (line < program.size())
    {
        program[line]->execute(state, outf);
        line = state->getCounter();
    }
}
