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

#include "tim/core/mutual_information_naive.h"

using namespace Tim;

void mexFunction(int outputs, mxArray *outputSet[],
				 int inputs, const mxArray *inputSet[])
{
	enum
	{
		xIndex,
		binsIndex
	};

	const integer samples = mxGetN(inputSet[xIndex]);
	const integer dimension = mxGetM(inputSet[xIndex]);
	real* rawData = mxGetPr(inputSet[xIndex]);

	integer bins = getInteger(inputSet[binsIndex]);

	const SignalPtr data = SignalPtr(
		new Signal(samples, dimension, withAliasing(rawData)));
	
	outputSet[0] = mxCreateDoubleMatrix(dimension, dimension, mxREAL);
	real* rawResult = mxGetPr(outputSet[0]);

	MatrixD result(dimension, dimension, withAliasing(rawResult));

	mutualInformationFromBinning(data, bins, result);
}
