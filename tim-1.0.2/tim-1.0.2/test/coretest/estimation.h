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

#ifndef TIM_ESTIMATION_H
#define TIM_ESTIMATION_H

#include <pastel/sys/testrunner.h>
#include <pastel/sys/callfunction.h>
#include <pastel/sys/testsuite.h>

#include "tim/core/mytypes.h"

namespace Tim
{

	inline Pastel::TestRunner& timTestList()
	{
		static Pastel::TestRunner timTestRunner("Tim library");
		return timTestRunner;
	}

	inline Pastel::TestReport& timTestReport()
	{
		static Pastel::TestReport theTestReport("Tim");
		return theTestReport;
	}

}

#endif
