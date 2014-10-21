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

#include "tim/core/differential_entropy_nk.h"

#include <pastel/math/euclidean_normbijection.h>

using namespace Tim;

void mexFunction(int outputs, mxArray *outputSet[],
				 int inputs, const mxArray *inputSet[])
{
	enum
	{
		xIndex,
		maxRelativeErrorIndex,
		threadsIndex
	};

	std::vector<SignalPtr> xEnsemble;
	getSignals(inputSet[xIndex], std::back_inserter(xEnsemble));

	const real maxRelativeError = getReal(inputSet[maxRelativeErrorIndex]);
	const integer threads = getInteger(inputSet[threadsIndex]);
	setNumberOfThreads(threads);

	integer intrinsicDimension = 0;

	const real entropy = 
		differentialEntropyNk(
		forwardRange(xEnsemble.begin(), xEnsemble.end()), 
		maxRelativeError,
		Euclidean_NormBijection<real>(),
		&intrinsicDimension);

	if (outputs > 0)
	{
		outputSet[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
		real* outEntropy = mxGetPr(outputSet[0]);
		*outEntropy = entropy;
	}

	if (outputs > 1)
	{
		outputSet[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
		real* outIntrinsicDimension = mxGetPr(outputSet[1]);
		*outIntrinsicDimension = intrinsicDimension;
	}
}
