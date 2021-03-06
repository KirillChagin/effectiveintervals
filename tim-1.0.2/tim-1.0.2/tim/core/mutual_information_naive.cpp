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

#include "tim/core/mutual_information_naive.h"

#include <pastel/math/matrix_tools.h>

#include <pastel/sys/histogram.h>

namespace Tim
{

	namespace
	{

		template <typename ConstIterator>
		real entropy(
			const ConstIterator& begin,
			const ConstIterator& end,
			real binSize)
		{
			real result = 0;
			ConstIterator iter = begin;
			while(iter != end)
			{
				const real value = *iter;
				if (value > 0)
				{
					result -= value * std::log(value) * binSize;
				}
				++iter;
			}
			
			return result;
		}

	}

	TIM void mutualInformationFromBinning(
		const SignalPtr& signal,
		integer bins,
		MatrixD& result)
	{
		ENSURE_OP(bins, >, 0);

		/*
		We consider 'signal' as a set of 1d signals. Each such signal has
		a continuous pdf. We approximate the mutual information
		for two 1d signals (called pairwise mutual information) 
		from their samplings as follows:
		1) Compute the min-max range of a signal.
		2) Divide the min-max range uniformly into bins. Enumerate
		these bins as integers in [0, 'bins'[.
		3) Associate each real number with the bin it falls into, giving
		a piecewise-constant distribution.
		4) Repeat 1-3 for the other signal.
		5) Compute mutual information for the piecewise-constant distributions.
		*/

		const integer samples = signal->samples();
		const integer n = signal->dimension();

		result.setSize(n, n);

		VectorD minBound = min(signal->data());
		VectorD maxBound = max(signal->data());
		VectorD binExtent = (maxBound - minBound) / bins;
		
		// Extend the bin support by a half bin
		// to guarantee that all samples fall into
		// some bin. Strictly, this is not needed,
		// but we want to make this function
		// behave almost equivalent to the implementation
		// in EEGLAB for comparison purposes.

		minBound -= binExtent / 2;
		maxBound += binExtent / 2;
		binExtent = (maxBound - minBound) / bins;

		Array<real, 2> marginalHistogram(bins, n);

		for (integer i = 0;i < n;++i)
		{
			computeHistogram(
				forwardRange(signal->data().columnBegin(i), signal->data().columnEnd(i)),
				minBound[i],
				maxBound[i],
				bins,
				marginalHistogram.rowBegin(i));
		}

		Array<real, 2> jointHistogram(bins, bins);

		for (integer i = 0;i < n;++i)
		{
			for (integer j = i + 1;j < n;++j)
			{
				computeJointHistogram(
					signal->data().columnBegin(i),
					signal->data().columnEnd(i),
					minBound[i],
					maxBound[i],
					signal->data().columnBegin(j),
					signal->data().columnEnd(j),
					minBound[j],
					maxBound[j],
					arrayView(jointHistogram));

				const real binVolume = binExtent[i] * binExtent[j];

				real mi = 0;
				for (integer y = 0;y < bins;++y)
				{
					const real yMass = marginalHistogram(y, j);

					if (yMass > 0)
					{
						for (integer x = 0;x < bins;++x)
						{
							// We choose to do multiplications and division
							// instead of subtracting logarithms.
							// This way we hope to avoid possible cancellation
							// problems.

							const real xMass = marginalHistogram(x, i);
							const real xyMass = jointHistogram(x, y);
							if (xMass > 0 && xyMass > 0)
							{
								mi += xyMass * std::log(xyMass / (xMass * yMass)) * binVolume;
							}
						}
					}
				}

				result(i, j) = mi;
				result(j, i) = mi;
			}

			result(i, i) = entropy(
				marginalHistogram.rowBegin(i),
				marginalHistogram.rowEnd(i),
				binExtent[i]);
		}
	}

}
