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

#include "tim/core/differential_entropy_kl.h"

using namespace Tim;

void mexFunction(int outputs, mxArray *outputSet[],
				 int inputs, const mxArray *inputSet[])
{
	enum
	{
		xIndex,
		timeWindowRadiusIndex,
		maxRelativeErrorIndex,
		kNearestIndex,
		threadsIndex
	};

	std::vector<SignalPtr> xEnsemble;
	getSignals(inputSet[xIndex], std::back_inserter(xEnsemble));

	const integer timeWindowRadius = getInteger(inputSet[timeWindowRadiusIndex]);
	const real maxRelativeError = getReal(inputSet[maxRelativeErrorIndex]);
	const integer kNearest = getInteger(inputSet[kNearestIndex]);
	const integer threads = getInteger(inputSet[threadsIndex]);
	setNumberOfThreads(threads);

	std::vector<real> estimateSet;
	estimateSet.reserve(minSamples(forwardRange(xEnsemble.begin(), xEnsemble.end())));

	temporalDifferentialEntropyKl(
		forwardRange(xEnsemble.begin(), xEnsemble.end()), 
		timeWindowRadius, std::back_inserter(estimateSet),
		maxRelativeError,
		kNearest);

	outputSet[0] = mxCreateDoubleMatrix(1, estimateSet.size(), mxREAL);
	real* rawResult = mxGetPr(outputSet[0]);

	std::copy(estimateSet.begin(), estimateSet.end(),
		rawResult);
}
