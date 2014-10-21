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

#ifndef TIM_TIM_MEX_HPP
#define TIM_TIM_MEX_HPP

#include "tim/matlab/tim_mex.h"

#include "tim/core/signal.h"

#include <pastel/sys/ensure.h>
#include <pastel/sys/pastelomp.h>
#include <pastel/sys/stdext_copy_n.h>

namespace Tim
{

	template <typename SignalPtr_OutputIterator>
	void getSignals(const mxArray* input,
					SignalPtr_OutputIterator output)
	{
		const integer trials = mxGetNumberOfElements(input);

		for (integer i = 0;i < trials;++i)
		{
			const mxArray* signalArray = mxGetCell(input, i);

			// It is intentional to assign the width
			// and height the wrong way. The reason
			// is that Matlab uses column-major storage
			// while we use row-major storage.
			const integer samples = mxGetN(signalArray);
			const integer dimension = mxGetM(signalArray);

			real* rawData = mxGetPr(signalArray);

			*output = SignalPtr(
				new Signal(samples, dimension, rawData));
			++output;
		}
	}

	template <typename Integer_OutputIterator>
	void getIntegers(const mxArray* input,
					 Integer_OutputIterator output)
	{
		const integer integers = mxGetNumberOfElements(input);
		StdExt::copy_n(mxGetPr(input), integers, output);
	}

	inline integer getInteger(const mxArray* input)
	{
		return *mxGetPr(input);
	}

	inline real getReal(const mxArray* input)
	{
		return *mxGetPr(input);
	}

	inline void setNumberOfThreads(integer threads)
	{
		ENSURE_OP(threads, >, 0);
#if PASTEL_ENABLE_OMP != 0
		omp_set_num_threads(threads);
#endif
	}

	inline void getSignalArray(
		const mxArray* signalSetArray, 
		Array<SignalPtr, 2>& signalSet)
	{
		const integer signals = mxGetM(signalSetArray);
		const integer trials = mxGetN(signalSetArray);
		
		signalSet.setExtent(trials, signals);

		for (integer y = 0;y < signals;++y)
		{
			for (integer x = 0;x < trials;++x)
			{
				const mxArray* signalArray = mxGetCell(signalSetArray, signals * x + y);

				const integer samples = mxGetN(signalArray);
				const integer dimension = mxGetM(signalArray);

				real* rawData = mxGetPr(signalArray);

				signalSet(x, y) = SignalPtr(
					new Signal(samples, dimension, rawData));
			}
		}
	}

}

#endif
