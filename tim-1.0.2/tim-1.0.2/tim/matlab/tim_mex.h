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

#ifndef TIM_TIM_MEX_H
#define TIM_TIM_MEX_H

#include "mex.h"

#include "tim/core/mytypes.h"
#include "tim/core/signal.h"

#include <pastel/sys/array.h>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace Tim
{

	namespace Detail
	{

		enum
		{
			RealIsDouble = boost::is_same<real, double>::value
		};
		BOOST_STATIC_ASSERT(RealIsDouble);

	}

	template <typename SignalPtr_OutputIterator>
	void getSignals(const mxArray* input,
					SignalPtr_OutputIterator output);

	template <typename Integer_OutputIterator>
	void getIntegers(const mxArray* input,
					 Integer_OutputIterator output);

	integer getInteger(const mxArray* input);

	real getReal(const mxArray* input);

	void setNumberOfThreads(integer threads);

	void getSignalArray(
		const mxArray* signalSetArray, 
		Array<SignalPtr, 2>& signalSet);
	
}

#include "tim/matlab/tim_mex.hpp"

#endif
