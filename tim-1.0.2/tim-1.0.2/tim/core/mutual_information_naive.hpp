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

#ifndef TIM_MUTUAL_INFORMATION_NAIVE_HPP
#define TIM_MUTUAL_INFORMATION_NAIVE_HPP

#include "tim/core/differential_entropy.h"

namespace Tim
{

	template <
		typename SignalPtr_Iterator,
		typename NormBijection,
		typename Real_OutputIterator>
	real mutualInformationFromEntropy(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		integer timeWindowRadius,
		integer kNearest,
		real maxRelativeError,
		const NormBijection& normBijection,
		Real_OutputIterator result)
	{
		ENSURE_OP(kNearest, >, 0);
		ENSURE_OP(maxRelativeError, >=, 0);

		if (signalSet.empty())
		{
			return 0;
		}

		SignalPtr_Iterator iter = signalSet.begin();
		SignalPtr_Iterator iterEnd = signalSet.end();

		std::vector<real> estimate;

		real estimate = 0;
		while(iter != iterEnd)
		{
			const SignalPtr signal = *iter;

			estimate += differentialEntropyKl(
				signal,
				maxRelativeError,
				kNearest,
				normBijection);

			++iter;
		}

		const SignalPtr jointSignal = merge(signalSet);
		estimate -= differentialEntropyKl(
			jointSignal,
			maxRelativeError,
			kNearest,
			normBijection);

		return estimate;
	}

}

#endif
