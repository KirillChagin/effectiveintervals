// Description: Printer_AstVisitor class
// Detail: Visualizes the program's AST.
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

#ifndef TIM_PRINTER_ASTVISITOR_H
#define TIM_PRINTER_ASTVISITOR_H

#include "tim/console/astvisitor.h"

#include <iostream>

namespace Tim
{

	class Printer_AstVisitor
		: public AstVisitor
	{
	public:
		explicit Printer_AstVisitor(std::ostream& stream);

		virtual void visit(const Program_AstNode& node);
		virtual void visit(const Statement_AstNode& node);
		virtual void visit(const Expression_AstNode& node);
		virtual void visit(const Declaration_AstNode& node);
		virtual void visit(const Print_AstNode& node);
		virtual void visit(const Identifier_AstNode& node);
		virtual void visit(const Integer_AstNode& node);
		virtual void visit(const Real_AstNode& node);
		virtual void visit(const String_AstNode& node);
		virtual void visit(const CellArray_AstNode& node);
		virtual void visit(const RealArray_AstNode& node);
		virtual void visit(const FunctionCall_AstNode& node);

	private:
		template <typename Type>
		void doVisit(const Type& node);

		std::ostream& output();
		void increaseIndentation();
		void decreaseIndentation();

		std::ostream* stream_;
		integer indentation_;
	};


}

#endif
