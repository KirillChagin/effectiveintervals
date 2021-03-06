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

#ifndef TIM_SIGNAL_TOOLS_HPP
#define TIM_SIGNAL_TOOLS_HPP

#include "tim/core/signal_tools.h"

#include <pastel/sys/view_tools.h>
#include <pastel/sys/constantiterator.h>

#include <pastel/gfx/draw.h>

#include <iostream>

namespace Tim
{

	template <typename SignalPtr_Iterator>
	integer minSamples(
		const ForwardRange<SignalPtr_Iterator>& signalSet)
	{
		if (signalSet.empty())
		{
			return 0;
		}

		SignalPtr_Iterator iter = signalSet.begin();
		const SignalPtr_Iterator iterEnd = signalSet.end();

		integer samples = (*iter)->samples();
		++iter;

		while(iter != iterEnd)
		{
			samples = std::max(samples, (*iter)->samples());

			++iter;
		}

		return samples;
	}

	template <typename SignalPtr_Iterator>
	bool equalDimension(
		const ForwardRange<SignalPtr_Iterator>& signalSet)
	{
		if (signalSet.empty())
		{
			return true;
		}

		SignalPtr_Iterator iter = signalSet.begin();
		const SignalPtr_Iterator iterEnd = signalSet.end();

		integer dimension = signalSet.front()->dimension();
		++iter;

		while(iter != iterEnd)
		{
			if ((*iter)->dimension() != dimension)
			{
				return false;
			}

			++iter;
		}

		return true;
	}

	template <
		typename SignalPtr_Iterator,
		typename Integer_Iterator>
	SignalPtr merge(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		const ForwardRange<Integer_Iterator>& lagSet)
	{
		ENSURE_OP(signalSet.size(), ==, lagSet.size());

		if (signalSet.empty() ||
			lagSet.empty())
		{
			return SignalPtr();
		}

		integer samples = 0;
		integer maxLag = 0;
		{
			Integer_Iterator lagIter = lagSet.begin();
			const Integer_Iterator lagIterEnd = lagSet.end();
			SignalPtr_Iterator signalIter = signalSet.begin();

			integer tLeftMax = (*lagIter);
			integer tRightMin = tLeftMax + (*signalIter)->samples();

			while(lagIter != lagIterEnd)
			{
				const integer lag = *lagIter;

				if (lag > maxLag)
				{
					maxLag = lag;
				}

				const integer tLeft = lag;
				const integer tRight = lag + (*signalIter)->samples();

				if (tLeft > tLeftMax)
				{
					tLeftMax = tLeft;
				}
				if (tRight < tRightMin)
				{
					tRightMin = tRight;
				}

				++lagIter;
				++signalIter;
			}
			
			samples = tRightMin - tLeftMax;
		}

		if  (samples <= 0)
		{
			return SignalPtr();
		}

		// Compute joint dimension.

		integer jointDimension = 0;
		SignalPtr_Iterator signalIter = signalSet.begin();
		const SignalPtr_Iterator signalIterEnd = signalSet.end();

		while(signalIter != signalIterEnd)
		{
			const SignalPtr signal = *signalIter;
			jointDimension += signal->dimension();

			++signalIter;
		}

		// Allocate the joint signal.

		SignalPtr jointSignal(new Signal(samples, jointDimension));
		
		// Copy the signals into parts of the joint signal.

		integer dimensionOffset = 0;

		Integer_Iterator lagIter = lagSet.begin();
		const Integer_Iterator lagIterEnd = lagSet.end();

		signalIter = signalSet.begin();
		while(lagIter != lagIterEnd)
		{
			const SignalPtr signal = *signalIter;
			const integer lagOffset = maxLag - *lagIter;
			const integer dimension = signal->dimension();

			for (integer i = 0;i < samples;++i)
			{
				std::copy(
					signal->data().rowBegin(i + lagOffset),
					signal->data().rowEnd(i + lagOffset),
					jointSignal->data().rowBegin(i) + dimensionOffset);
			}

			dimensionOffset += dimension;

			++signalIter;
			++lagIter;
		}

		return jointSignal;
	}

	template <typename SignalPtr_Iterator>
	SignalPtr merge(
		const ForwardRange<SignalPtr_Iterator>& signalSet)
	{
		return Tim::merge(signalSet,
			forwardRange(constantIterator(0)));
	}

	template <
		typename SignalPtr_OutputIterator,
		typename Integer_Iterator>
	void merge(
		const Array<SignalPtr, 2>& ensembleSet,
		SignalPtr_OutputIterator result,
		const ForwardRange<Integer_Iterator> lagSet)
	{
		ENSURE_OP(lagSet.size(), ==, ensembleSet.height());

		const integer trials = ensembleSet.width();
		for (integer i = 0;i < trials;++i)
		{
			*result = merge(
				forwardRange(ensembleSet.columnBegin(i),
				ensembleSet.columnEnd(i)), lagSet);
			++result;
		}
	}

	template <typename SignalPtr_OutputIterator>
	void merge(
		const Array<SignalPtr, 2>& ensembleSet,
		SignalPtr_OutputIterator result)
	{
		Tim::merge(ensembleSet, result,
			forwardRange(constantIterator(0), ensembleSet.height()));
	}

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator,
		typename SignalPtr_OutputIterator>
	void merge(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet,
		SignalPtr_OutputIterator result,
		integer yLag)
	{
		ENSURE_OP(xSignalSet.size(), ==, ySignalSet.size());
		
		SignalPtr_X_Iterator xIter = xSignalSet.begin();
		const SignalPtr_X_Iterator xIterEnd = xSignalSet.end();
		SignalPtr_Y_Iterator yIter = ySignalSet.begin();

		while(xIter != xIterEnd)
		{
			*result = merge(*xIter, *yIter, yLag);
			
			++result;
			++xIter;
			++yIter;
		}
	}

	template <typename SignalPtr_OutputIterator>
	void split(
		const SignalPtr& jointSignal,
		SignalPtr_OutputIterator signalSet)
	{
		const integer dimension = jointSignal->dimension();

		SmallSet<integer> partition;
		partition.reserve(dimension + 1);
		for (integer i = 0;i <= dimension;++i)
		{
			partition.insert(i);
		}

		Tim::split(jointSignal, partition, signalSet);
	}

	template <typename SignalPtr_OutputIterator>
	void split(
		const SignalPtr& jointSignal,
		const SmallSet<integer>& partition,
		SignalPtr_OutputIterator signalSet)
	{
		ENSURE_OP(partition.size(), >=, 2);

		const integer dimension = jointSignal->dimension();
		const integer samples = jointSignal->samples();
		const integer signals = partition.size() - 1;

		for (integer x = 0;x < signals;++x)
		{
			const integer marginalDimension = 
				partition[x + 1] - partition[x];

			*signalSet = Tim::split(jointSignal, partition[x], 
				partition[x] + marginalDimension);
			++signalSet;
		}
	}

	template <typename Image_View>
	void drawSignal(
		const SignalPtr& signal,
		const View<2, Color, Image_View>& image)
	{
		const integer dimension = signal->dimension();
		const integer samples = signal->samples();

		const integer width = image.width();
		const integer height = image.height();

		clear(Color(0), image);

		if (dimension == 1)
		{
			const real yMax = max(abs(signal->data()))[0];
			std::cout << yMax << std::endl;

			for (integer x = 0;x < samples;++x)
			{
				const real y = mabs(signal->data()(x)) / yMax;

				drawPixel(Vector2(x + 0.5, y * (height - 1)), 
					Color(0, 1, 0), image);
			}
		}
	}

	template <typename SignalPtr_Iterator>
	void constructPointSet(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		integer sampleBegin,
		integer sampleEnd,
		integer dimensionBegin,
		integer dimensionEnd,
		std::vector<const real*>& pointSet)
	{
		if (signalSet.empty())
		{
			pointSet.clear();
			return;
		}

		ENSURE(equalDimension(signalSet));

		const integer signalSamples = minSamples(signalSet);
		const integer signalDimension = signalSet.front()->dimension();

		ENSURE_OP(sampleBegin, <=, sampleEnd);
		ENSURE_OP(sampleBegin, >= , 0);
		ENSURE_OP(sampleEnd, <=, signalSamples);
		ENSURE_OP(dimensionBegin, <=, dimensionEnd);
		ENSURE_OP(dimensionBegin, >=, 0);
		ENSURE_OP(dimensionEnd, <=, signalDimension);

		const integer dimension = dimensionEnd - dimensionBegin;
		const integer samples = sampleEnd - sampleBegin;
		const integer trials = signalSet.size();

		if (dimension == 0 ||
			samples == 0)
		{
			pointSet.clear();
			return;
		}

		pointSet.resize(samples * trials);

		SignalPtr_Iterator iter = signalSet.begin();
		const SignalPtr_Iterator iterEnd = signalSet.end();
		integer trial = 0;
		while(iter != iterEnd)
		{
			const SignalPtr signal = *iter;

			for (integer i = sampleBegin;i < sampleEnd;++i)
			{
				// The samples from the trials are interleaved.

				const integer index = (i - sampleBegin) * trials + trial;
				pointSet[index] = &signal->data()(i, dimensionBegin);
			}

			++trial;
			++iter;
		}
	}

}

#endif
