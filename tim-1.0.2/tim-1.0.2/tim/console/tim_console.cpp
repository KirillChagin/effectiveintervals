// Description: Main program
// Documentation: tim_console_cpp.txt

// TIM 1.0.2
// Kalle Rutanen
// http://kaba.hilvi.org
// Copyright (c) 2009, 2010
//
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published 
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <string>

#include "tim/console/console_parser.h"
#include "tim/console/interpreter_astvisitor.h"
#include "tim/console/printer_astvisitor.h"
#include "tim/console/errorlog.h"

using namespace Tim;

int main(int argc, char **argv)
{
	// Parse and construct an Abstract Syntax Tree.

	//std::cout << "Parsing..." << std::endl;
	//console_debug = 1;
	console_parse();

	// * If there is an error in the tokenizing phase,
	// the program will have already exited.
	// * If there is a syntax error in the parsing phase,
	// the program will continue here.

	if (programAst)
	{
		//Printer_AstVisitor printer(std::cout);
		//programAst->accept(printer);

		//std::cout << "Interpreting..." << std::endl;

		// Interpret the program.
		
		Interpreter_AstVisitor interpreter;
		try
		{
			programAst->accept(interpreter);
		}
		catch(const Interpreter_Exception&)
		{
			std::cerr << "Semantic errors found!" << std::endl;
		}

		delete programAst;
		programAst = 0;
	}

	// Output the possible error reports.

	std::cerr << errorLog();

	return 0;
}

