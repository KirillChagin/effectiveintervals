// Description: ErrorLog class
// Detail: Stores the errors emitted by the interpreter.
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

#ifndef TIM_ERRORLOG_H
#define TIM_ERRORLOG_H

#include <tim/core/mytypes.h>

#include <string>
#include <map>
#include <iostream>

namespace Tim
{

	class ErrorLog
	{
	public:
		typedef std::multimap<integer, std::string> Container;
		typedef Container::const_iterator ConstIterator;

		ErrorLog();

		void pushNamespace(const std::string& name);
		void popNamespace();
		std::string prefix() const;

		void report(const std::string& text);
		void report(integer line, const std::string& text);

		const Container& map() const;
		
		void setLine(integer line);
		integer line() const;

	private:
		 Container errorMap_;
		 integer line_;
		 std::vector<std::string> nameStack_;
	};

	ErrorLog& errorLog();

	std::ostream& operator<<(std::ostream& stream, const ErrorLog& errorLog);

	void reportError(const std::string& text);
	void reportError(integer line, const std::string& text);

	class ErrorLog_Namespace
	{
	public:
		explicit ErrorLog_Namespace(
			const std::string& name)
		{
			errorLog().pushNamespace(name);
		}
		
		~ErrorLog_Namespace()
		{
			errorLog().popNamespace();
		}
	};

}

#endif
