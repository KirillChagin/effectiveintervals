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

#ifndef TIM_TRANSFER_ENTROPY_HPP
#define TIM_TRANSFER_ENTROPY_HPP

#include "tim/core/transfer_entropy.h"
#include "tim/core/signal_tools.h"
#include "tim/core/signalpointset.h"
#include "tim/core/entropy_combination.h"

#include <pastel/sys/constantiterator.h>
#include <pastel/sys/nulliterator.h>

namespace Tim
{

	namespace Detail_TransferEntropy
	{

		template <
			typename SignalPtr_X_Iterator,
			typename SignalPtr_Y_Iterator,
			typename SignalPtr_W_Iterator,
			typename Real_OutputIterator>
		real transferEntropy(
			const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
			const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet,
			const ForwardRange<SignalPtr_W_Iterator>& wSignalSet,
			integer timeWindowRadius,
			Real_OutputIterator result,
			integer xLag,
			integer yLag,
			integer wLag,
			integer kNearest,
			bool wantTemporal)
		{
			ENSURE_OP(timeWindowRadius, >=, 0);
			ENSURE_OP(kNearest, >, 0);
			PENSURE_OP(xSignalSet.size(), ==, ySignalSet.size());
			PENSURE_OP(xSignalSet.size(), ==, wSignalSet.size());
			PENSURE(equalDimension(xSignalSet));
			PENSURE(equalDimension(ySignalSet));

			if (xSignalSet.empty())
			{
				return 0;
			}

			const integer trials = xSignalSet.size();

			// Form the joint signal. Note the signals 
			// are merged in wXY order.

			std::vector<SignalPtr> jointSignalSet;
			jointSignalSet.reserve(trials);

			Array<SignalPtr, 2> signalSet(trials, 3);
			std::copy(wSignalSet.begin(), wSignalSet.end(), signalSet.rowBegin(0));
			std::copy(xSignalSet.begin(), xSignalSet.end(), signalSet.rowBegin(1));
			std::copy(ySignalSet.begin(), ySignalSet.end(), signalSet.rowBegin(2));

			integer lagSet[] = {wLag, xLag, yLag};

			// Describe the marginal signals.

			Integer3 rangeSet[] = 
			{
				Integer3(0, 2, 1),
				Integer3(1, 3, 1),
				Integer3(1, 2, -1)
			};

			if (wantTemporal)
			{
				temporalEntropyCombination(
					signalSet,
					forwardRange(rangeSet),
					timeWindowRadius,
					result,
					forwardRange(lagSet),
					kNearest);
				
				return 0;
			}

			return entropyCombination(
				signalSet,
				forwardRange(rangeSet),
				forwardRange(lagSet),
				kNearest);
		}

	}

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator,
		typename SignalPtr_W_Iterator,
		typename Real_OutputIterator>
	void temporalTransferEntropy(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet,
		const ForwardRange<SignalPtr_W_Iterator>& wSignalSet,
		integer timeWindowRadius,
		Real_OutputIterator result,
		integer xLag,
		integer yLag,
		integer wLag,
		integer kNearest)
	{
		Tim::Detail_TransferEntropy::transferEntropy(
			xSignalSet, ySignalSet, wSignalSet,
			timeWindowRadius,
			result,
			xLag, yLag, wLag,
			kNearest,
			true);
	}

	template <typename Real_OutputIterator>
	void temporalTransferEntropy(
		const SignalPtr& xSignal,
		const SignalPtr& ySignal,
		const SignalPtr& wSignal,
		integer timeWindowRadius,
		Real_OutputIterator result,
		integer xLag, integer yLag, integer wLag,
		integer kNearest)
	{
		Tim::temporalTransferEntropy(
			forwardRange(constantIterator(xSignal)),
			forwardRange(constantIterator(ySignal)),
			forwardRange(constantIterator(wSignal)),
			timeWindowRadius,
			result,
			xLag, yLag, wLag,
			kNearest);
	}

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator,
		typename SignalPtr_W_Iterator>
	real transferEntropy(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet,
		const ForwardRange<SignalPtr_W_Iterator>& wSignalSet,
		integer xLag, integer yLag, integer wLag,
		integer kNearest)
	{
		return Tim::Detail_TransferEntropy::transferEntropy(
			xSignalSet, ySignalSet, wSignalSet,
			0,
			NullIterator(),
			xLag, yLag, wLag,
			kNearest,
			false);
	}

}

#endif
