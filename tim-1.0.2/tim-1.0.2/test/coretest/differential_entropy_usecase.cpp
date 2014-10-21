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

#include "tim/core/differential_entropy.h"
#include "tim/core/signal_tools.h"

#include <pastel/sys/nulliterator.h>

#include <pastel/math/normbijection.h>

using namespace Tim;

namespace
{

	void useCase()
	{
		SignalPtr xSignal = generateGaussian(10000, 3);
		SignalPtr ySignal = generateGaussian(10000, 5);

		SignalPtr signalSet[2] = {xSignal, ySignal};

		const integer timeWindowRadius = 10;
		const real maxRelativeError = 0;
		const integer kNearest = 1;
		real averageEstimate = 0;

		NullIterator estimateSet;
		Euclidean_NormBijection<real> normBijection;

		// To compute differential entropy for
		// a single signal:

		averageEstimate = differentialEntropyKl(
			xSignal);
		averageEstimate = differentialEntropyKl(
			xSignal, maxRelativeError);
		averageEstimate = differentialEntropyKl(
			xSignal, maxRelativeError, kNearest);

		// To compute temporal differential
		// entropy where the neighborhood is given by
		// a time-window:

		temporalDifferentialEntropyKl(
			xSignal, timeWindowRadius, estimateSet,
			maxRelativeError, kNearest, normBijection);

		averageEstimate = differentialEntropyKl(
			xSignal, maxRelativeError, kNearest, normBijection);

		temporalDifferentialEntropyKl(xSignal, timeWindowRadius, estimateSet, 
			maxRelativeError, kNearest);
		temporalDifferentialEntropyKl(xSignal, timeWindowRadius, estimateSet,
			maxRelativeError, kNearest, normBijection);

		// To compute differential entropy for
		// a set of signals, where each signal is a 
		// different trial of the same experiment:

		averageEstimate = differentialEntropyKl(
			forwardRange(signalSet));
		averageEstimate = differentialEntropyKl(
			forwardRange(signalSet), maxRelativeError);
		averageEstimate = differentialEntropyKl(
			forwardRange(signalSet), maxRelativeError, kNearest);
		averageEstimate = differentialEntropyKl(
			forwardRange(signalSet), maxRelativeError, 
			kNearest, normBijection);

		// To compute temporal differential entropy for
		// a set of signals, where each signal is a 
		// different trial of the same experiment:

		temporalDifferentialEntropyKl(
			forwardRange(signalSet), 
			timeWindowRadius, estimateSet); 
		temporalDifferentialEntropyKl(
			forwardRange(signalSet), 
			timeWindowRadius, estimateSet, 
			maxRelativeError); 
		temporalDifferentialEntropyKl(
			forwardRange(signalSet), 
			timeWindowRadius, estimateSet, 
			maxRelativeError, kNearest);
		temporalDifferentialEntropyKl(
			forwardRange(signalSet), timeWindowRadius, 
			estimateSet,
			maxRelativeError, kNearest,
			normBijection);
	}

}
