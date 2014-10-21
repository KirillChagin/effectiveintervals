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

/*
#include "tim/core/mutual_information.h"

#include <pastel/sys/nulliterator.h>

#include <pastel/math/normbijection.h>

using namespace Tim;

namespace
{

	void useCase()
	{
		SignalPtr xSignal;
		SignalPtr ySignal;

		SignalPtr signalSet[2] = {xSignal, ySignal};

		const integer timeWindowRadius = 10;
		const real maxRelativeError = 0;
		const integer kNearest = 1;
		real averageEstimate = 0;

		NullIterator estimateSet;
		Euclidean_NormBijection<real> normBijection;

		// To compute differential entropy for
		// a single signal:

		averageEstimate = mutualInformation(
			xSignal);
		averageEstimate = mutualInformation(
			xSignal, maxRelativeError);
		averageEstimate = mutualInformation(
			xSignal, maxRelativeError, kNearest);

		// To compute temporal differential
		// entropy where the neighborhood is given by
		// a time-window:

		temporalMutualInformation(
			xSignal, timeWindowRadius, estimateSet,
			maxRelativeError, kNearest, normBijection);

		averageEstimate = mutualInformation(
			xSignal, maxRelativeError, kNearest, normBijection);

		temporalMutualInformation(xSignal, timeWindowRadius, estimateSet, 
			maxRelativeError, kNearest);
		temporalMutualInformation(xSignal, timeWindowRadius, estimateSet,
			maxRelativeError, kNearest, normBijection);

		// To compute differential entropy for
		// a set of signals, where each signal is a 
		// different trial of the same experiment:

		averageEstimate = mutualInformation(
			forwardRange(signalSet));
		averageEstimate = mutualInformation(
			forwardRange(signalSet), maxRelativeError);
		averageEstimate = mutualInformation(
			forwardRange(signalSet), maxRelativeError, kNearest);
		averageEstimate = mutualInformation(
			forwardRange(signalSet), maxRelativeError, 
			kNearest, normBijection);

		// To compute temporal differential entropy for
		// a set of signals, where each signal is a 
		// different trial of the same experiment:

		temporalMutualInformation(
			forwardRange(signalSet), 
			timeWindowRadius, estimateSet); 
		temporalMutualInformation(
			forwardRange(signalSet), 
			timeWindowRadius, estimateSet, 
			maxRelativeError); 
		temporalMutualInformation(
			forwardRange(signalSet), 
			timeWindowRadius, estimateSet, 
			maxRelativeError, kNearest);
		temporalMutualInformation(
			forwardRange(signalSet), timeWindowRadius, 
			estimateSet,
			maxRelativeError, kNearest,
			normBijection);
	}

}
*/
