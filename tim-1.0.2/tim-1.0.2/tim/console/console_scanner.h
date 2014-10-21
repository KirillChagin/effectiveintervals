// Description: Tokenizer definitions
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

#ifndef TIM_CONSOLE_SCANNER_H
#define TIM_CONSOLE_SCANNER_H

#include "tim/console/ast.h"

#include <tim/core/mytypes.h>
#include <tim/core/signal.h>

#include <pastel/sys/array.h>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>

namespace Tim
{

	typedef Array<SignalPtr> Cell;
	typedef boost::shared_ptr<Cell> CellPtr;

	typedef std::vector<std::string> StringSet;
	typedef std::vector<StringSet*> StringSetSet;

	typedef std::vector<real> RealSet;
	typedef std::vector<RealSet*> RealSetSet;

	typedef std::vector<boost::any> AnySet;

}

#include "tim/console/console_parser.tab.h"

#endif
