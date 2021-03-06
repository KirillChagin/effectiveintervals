// Description: Delay embedding

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

#ifndef TIM_EMBED_H
#define TIM_EMBED_H

#include "tim/core/signal.h"

#include <vector>

namespace Tim
{

	//! Delay-embeds a signal into a higher dimensional space.
	/*!
	Preconditions:
	k > 0
	shift >= 0
	step >= 1

	Given is a signal S : Z -> R^n.
	Form a signal R : Z -> R^n : 
	R(t) = (S(t0 + t), S(t0 + t + dt), ..., S(t0 + t + dt * (k - 1)).
	
	Then R is the delay-embedding and
	t0 is the embedding shift
	dt is the embedding delay
	k is the 'embedding factor'
	d = k n is the embedding dimension
	*/

	TIM SignalPtr delayEmbed(
		const SignalPtr& signal,
		integer k,
		integer shift = 0,
		integer step = 1);

	//! Performs delay embedding for a set of signals.
	/*!
	Preconditions:
	k > 0
	shift >= 0
	step >= 1
	SignalPtr_Iterator dereferences to a SignalPtr.
	OutputIterator dereferences to a SignalPtr&.
	*/
	template <typename SignalPtr_Iterator, typename OutputIterator>
	void delayEmbed(
		const SignalPtr_Iterator& signalBegin,
		const SignalPtr_Iterator& signalEnd,
		const OutputIterator& outputBegin,
		integer k,
		integer shift = 0,
		integer step = 1);

	//! Time shift to produce the future of a delay-embedded signal.
	/*!
	Preconditions:
	k > 0
	shift >= 0
	step >= 1

	Assume that a signal x : R -> R^n was embedded to a signal X : R -> R^(kn)
	using the function 'delayEmbed' with an embedding factor k. 
	Then the future of x is defined as the last R^n component of the 
	otherwise same embedding but with an embedding factor (k + 1).

	The future of x can be obtained simply by shifting x by
	a proper 'tDelta' amount of samples: 

	xFuture[t] = x[t + tDelta]
	
	This function computes 'tDelta' from the parameters that were used 
	for the delay embedding.
	*/

	TIM integer delayEmbedFutureShift(
		integer k, 
		integer shift = 0, 
		integer step = 1);


	TIM SignalPtr delayEmbedFuture(
		const SignalPtr& signal,
		integer k,
		integer shift = 0,
		integer step = 1);

	template <typename SignalPtr_Iterator, typename OutputIterator>
	void delayEmbedFuture(
		const SignalPtr_Iterator& signalBegin,
		const SignalPtr_Iterator& signalEnd,
		const OutputIterator& outputBegin,
		integer k,
		integer shift = 0,
		integer step = 1);

}

#include "tim/core/embed.hpp"

#endif
