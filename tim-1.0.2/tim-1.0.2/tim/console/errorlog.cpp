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

#include "tim/console/errorlog.h"

namespace Tim
{

	ErrorLog::ErrorLog()
		: errorMap_()
		, line_(0)
		, nameStack_()
	{
	}

	void ErrorLog::pushNamespace(const std::string& name)
	{
		nameStack_.push_back(name);
	}

	void ErrorLog::popNamespace()
	{
		nameStack_.pop_back();
	}

	std::string ErrorLog::prefix() const
	{
		std::string namePrefix;
		const integer names = nameStack_.size();
		for (integer i = 0;i < names;++i)
		{
			namePrefix += nameStack_[i];
		}
		
		return namePrefix;
	}

	void ErrorLog::report(const std::string& text)
	{
		errorMap_.insert(std::make_pair(line_, prefix() + text));
	}

	void ErrorLog::report(integer line, const std::string& text)
	{
		errorMap_.insert(std::make_pair(line, prefix() + text));
	}

	const ErrorLog::Container& ErrorLog::map() const
	{
		return errorMap_;
	}

	void ErrorLog::setLine(integer line)
	{
		line_ = line;
	}

	integer ErrorLog::line() const
	{
		return line_;
	}

	ErrorLog& errorLog()
	{
		static ErrorLog theErrorLog;
		return theErrorLog;
	}

	std::ostream& operator<<(
		std::ostream& stream, 
		const ErrorLog& errorLog)
	{
		ErrorLog::ConstIterator iter = errorLog.map().begin();
		const ErrorLog::ConstIterator iterEnd = errorLog.map().end();
		while(iter != iterEnd)
		{
			stream << "Line " << iter->first << ": ";
			stream << iter->second << std::endl;
			++iter;
		}

		return stream;
	}

	void reportError(integer line, const std::string& text)
	{
		errorLog().report(line, text);
	}

	void reportError(const std::string& text)
	{
		errorLog().report(text);
	}

}
