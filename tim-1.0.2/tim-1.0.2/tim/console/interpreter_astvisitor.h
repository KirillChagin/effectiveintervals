// Description: Interpreter_AstVisitor class
// Detail: Interprets the program stored in the AST.
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

#ifndef TIM_INTERPRETER_ASTVISITOR_H
#define TIM_INTERPRETER_ASTVISITOR_H

#include "tim/console/astvisitor.h"

#include <map>
#include <string>

#include <boost/any.hpp>

namespace Tim
{

	class Interpreter_AstVisitor
		: public AstVisitor
	{
	public:
		Interpreter_AstVisitor();

		virtual void visit(const Program_AstNode& node);
		virtual void visit(const Statement_AstNode& node);
		virtual void visit(const Declaration_AstNode& node);
		virtual void visit(const Print_AstNode& node);

	private:
		typedef std::map<std::string, boost::any> SymbolMap;
		typedef SymbolMap::const_iterator SymbolIterator;

		boost::any evaluate(const Expression_AstNode* expression);

		SymbolMap symbolMap_;
	};

	class Interpreter_Exception
	{
	};

}

#endif
