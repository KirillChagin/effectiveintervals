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

#include "tim/matlab/tim_mex.h"

#include "tim/core/entropy_combination.h"

using namespace Tim;

void mexFunction(int outputs, mxArray *outputSet[],
				 int inputs, const mxArray *inputSet[])
{
	enum
	{
		signalSetIndex,
		rangeSetIndex,
		lagSetIndex,
		kNearestIndex,
		threadsIndex
	};

	Array<SignalPtr, 2> signalSet;
	getSignalArray(inputSet[signalSetIndex], signalSet);

	std::vector<integer> lagSet;
	getIntegers(inputSet[lagSetIndex], std::back_inserter(lagSet));

	const integer marginals = mxGetM(inputSet[rangeSetIndex]);
	//printf("%d marginals", marginals);
	std::vector<Integer3> rangeSet;
	rangeSet.reserve(marginals);
	{
		real* rawData = mxGetPr(inputSet[rangeSetIndex]);
		for (integer i = 0;i < marginals;++i)
		{
			rangeSet.push_back(Integer3(*rawData - 1, *(rawData + marginals), *(rawData + 2 * marginals)));
			//printf("%d %d %d ", rangeSet.back()[0], rangeSet.back()[1], rangeSet.back()[2]);
			++rawData;
		}
	}

	const integer kNearest = getInteger(inputSet[kNearestIndex]);
	const integer threads = getInteger(inputSet[threadsIndex]);
	setNumberOfThreads(threads);

	outputSet[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
	real* rawResult = mxGetPr(outputSet[0]);

	*rawResult = entropyCombination(
		signalSet,
		forwardRange(rangeSet.begin(), rangeSet.end()),
		forwardRange(lagSet.begin(), lagSet.end()),
		kNearest);
}
