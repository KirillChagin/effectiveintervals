// Description: Parser definitions
// Detail: GNU Bison is used to generate a scanner from a grammar.
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

#ifndef TIM_CONSOLE_PARSER_H
#define TIM_CONSOLE_PARSER_H

#include "tim/console/console_scanner.h"
#include "tim/console/ast.h"

#include <iostream>
#include <string>

int console_parse();
extern int console_debug;

namespace Tim
{

	extern Program_AstNode* programAst;

}

#endif
