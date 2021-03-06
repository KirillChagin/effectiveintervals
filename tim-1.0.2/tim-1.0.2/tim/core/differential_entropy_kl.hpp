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

#ifndef TIM_DIFFERENTIAL_ENTROPY_KL_HPP
#define TIM_DIFFERENTIAL_ENTROPY_KL_HPP

#include "tim/core/differential_entropy_kl.h"
#include "tim/core/signal_tools.h"
#include "tim/core/signalpointset.h"

#include <pastel/sys/constantiterator.h>
#include <pastel/sys/countingiterator.h>
#include <pastel/sys/randomaccessrange.h>

#include <pastel/geometry/search_all_neighbors_pointkdtree.h>

#include <algorithm>
#include <numeric>

namespace Tim
{

	// Temporal differential entropy
	// -----------------------------

	template <
		typename SignalPtr_Iterator, 
		typename Real_OutputIterator,
		typename NormBijection>
	void temporalDifferentialEntropyKl(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		integer timeWindowRadius,
		Real_OutputIterator result,
		real maxRelativeError,
		integer kNearest,
		const NormBijection& normBijection)
	{
		ENSURE_OP(timeWindowRadius, >=, 0);
		ENSURE_OP(maxRelativeError, >=, 0);
		ENSURE_OP(kNearest, >, 0);

		// This function computes the Kozachenko-Leonenko
		// estimator for the differential entropy.
		// Apparently the original paper seems to be:
		//
		// "A statistical estimate for the entropy of a random vector", 
		// Kozachenko, L.F. and Leonenko, N.N., (1987)
		// Problems Infor. Transmiss., 23(2), 9-16
		//
		// However, I couldn't find or read that paper online
		// so I cite:
		//
		// "Synchronization and Interdependence Measures
		// and their Applications to the Electroencephalogram
		// of Epilepsy Patients and Clustering of Data",
		// Alexander Kraskov, Ph.D. thesis, 2004

		if (signalSet.empty())
		{
			return;
		}

		// This is done to avoid parallelization
		// issues with iterator range caching.

		signalSet.updateCache();

		const integer trials = signalSet.size();
		const integer samples = minSamples(signalSet);
		const integer dimension = signalSet.front()->dimension();

		// We create an own array to hold the results since the
		// 'result' iterator is not necessarily random-access
		// (which is needed for parallelization below).

		std::vector<real> estimateSet(samples);

#pragma omp parallel
		{
		// Each worker thread has to create its own copy of
		// the signal point set. This is because the call
		// to SignalPointSet::setTimeWindow() is mutating.
		// This is a bit wasteful in memory, but I don't
		// know how else this could be done.

		Array<real, 2> distanceArray(1, trials);
		SignalPointSet pointSet(signalSet);

#pragma omp for
		for (integer t = 0;t < samples;++t)
		{
			// Update the position of the time-window.

			pointSet.setTimeWindow(t - timeWindowRadius, t + timeWindowRadius + 1);

			const integer tDelta = t - pointSet.timeBegin();
			const integer tWidth = pointSet.timeEnd() - pointSet.timeBegin();
			
			// For each point at the current time instant in all
			// ensemble signals, find the distance to the k:th nearest 
			// neighbor. Note that the SignalPointSet stores the
			// point iterators interleaved so that for a given time instant
			// the samples of ensemble signals are listed sequentially.
			// I.e. if the ensemble signals are A, B and C, then
			// SignalPointSet stores point iterators to 
			// A(1), B(1), C(1), A(2), B(2), C(2), etc.
			// That is, the distance between subsequent samples of a
			// specific signal are 'trials' samples away.

			searchAllNeighbors(
				pointSet.kdTree(),
				randomAccessRange(pointSet.begin() + tDelta * trials, 
				pointSet.begin() + (tDelta + 1) * trials),
				kNearest - 1,
				kNearest, 
				0,
				&distanceArray,
				randomAccessRange(constantIterator(infinity<real>()), trials),
				maxRelativeError,
				normBijection);

			// After we have found the distances, we simply evaluate
			// the differential entropy estimator over the samples of
			// the current time instant.

			integer acceptedSamples = 0;
			real estimate = 0;
			for (integer i = 0;i < trials;++i)
			{
				// The logarithm of zero would give -infinity,
				// so we must avoid that. Such samples are
				// not taken in the estimate.
				if (distanceArray(i) > 0)
				{
					estimate += normBijection.toLnNorm(distanceArray(i));
					++acceptedSamples;
				}
			}
			if (acceptedSamples > 0)
			{
				estimate *= (real)dimension / acceptedSamples;
			}
			estimate -= digamma<real>(kNearest);
			estimate += digamma<real>(tWidth * trials);
			estimate += normBijection.lnVolumeUnitSphere(dimension);

			estimateSet[t] = estimate;
		}
		}

		// Copy the results to the output.

		std::copy(estimateSet.begin(), estimateSet.end(), result);
	}

	template <
		typename SignalPtr_Iterator, 
		typename Real_OutputIterator>
	void temporalDifferentialEntropyKl(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		integer timeWindowRadius,
		Real_OutputIterator result,
		real maxRelativeError,
		integer kNearest)
	{
		Tim::temporalDifferentialEntropyKl(
			signalSet,
			timeWindowRadius,
			result,
			maxRelativeError,
			kNearest,
			Default_NormBijection());
	}

	template <
		typename Real_OutputIterator,
		typename NormBijection>
	void temporalDifferentialEntropyKl(
		const SignalPtr& signal,
		integer timeWindowRadius,
		Real_OutputIterator result,
		real maxRelativeError,
		integer kNearest,
		const NormBijection& normBijection)
	{
		Tim::temporalDifferentialEntropyKl(
			forwardRange(constantIterator(signal)),
			timeWindowRadius,
			result,
			maxRelativeError,
			kNearest,
			normBijection);
	}

	template <typename Real_OutputIterator>
	void temporalDifferentialEntropyKl(
		const SignalPtr& signal,
		integer timeWindowRadius,
		Real_OutputIterator result,
		real maxRelativeError,
		integer kNearest)
	{
		Tim::temporalDifferentialEntropyKl(
			signal,
			timeWindowRadius,
			result,
			maxRelativeError,
			kNearest, 
			Default_NormBijection());
	}

	template <
		typename SignalPtr_Iterator, 
		typename NormBijection>
	real differentialEntropyKl(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		real maxRelativeError,
		integer kNearest,
		const NormBijection& normBijection)
	{
		ENSURE_OP(kNearest, >, 0);
		ENSURE_OP(maxRelativeError, >=, 0);

		if (signalSet.empty())
		{
			return 0;
		}

		// This is done to avoid parallelization
		// issues with iterator range caching.

		signalSet.updateCache();

		SignalPointSet pointSet(signalSet, true);

		const integer trials = signalSet.size();
		const integer samples = pointSet.samples();
		const integer dimension = signalSet.front()->dimension();
		const integer estimateSamples = samples * trials;

		Array<real, 2> distanceArray(1, estimateSamples);

		// Find the distance to the k:th nearest neighbor for all points.

		searchAllNeighbors(
			pointSet.kdTree(),
			randomAccessRange(pointSet.begin(), pointSet.end()),
			kNearest - 1,
			kNearest, 
			0,
			&distanceArray,
			randomAccessRange(constantIterator(infinity<real>()), estimateSamples),
			maxRelativeError,
			normBijection);

		// After we have found the distances, we simply evaluate
		// the differential entropy estimator over all samples.

		integer acceptedSamples = 0;
		real estimate = 0;
#pragma omp parallel for reduction(+ : estimate, acceptedSamples)
		for (integer i = 0;i < estimateSamples;++i)
		{
			// The logarithm of zero would give -infinity,
			// so we must avoid that. Such samples are
			// not taken in the estimate.
			if (distanceArray(i) > 0)
			{
				estimate += normBijection.toLnNorm(distanceArray(i));
				++acceptedSamples;
			}
		}
		if (acceptedSamples > 0)
		{
			estimate *= (real)dimension / acceptedSamples;
		}

		estimate -= digamma<real>(kNearest);
		estimate += digamma<real>(estimateSamples);
		estimate += normBijection.lnVolumeUnitSphere(dimension);

		return estimate;
	}

	template <typename SignalPtr_Iterator>
	real differentialEntropyKl(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		real maxRelativeError,
		integer kNearest)
	{
		return Tim::differentialEntropyKl(
			signalSet,
			maxRelativeError,
			kNearest,
			Default_NormBijection());
	}

	template <typename NormBijection>
	real differentialEntropyKl(
		const SignalPtr& signal,
		real maxRelativeError,
		integer kNearest,
		const NormBijection& normBijection)
	{
		return Tim::differentialEntropyKl(
			forwardRange(constantIterator(signal)),
			maxRelativeError,
			kNearest,
			normBijection);
	}

}

#endif
