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

#include "tim/core/embed.h"
#include "tim/core/signal_tools.h"

namespace Tim
{

	TIM SignalPtr delayEmbed(
		const SignalPtr& signal,
		integer k,
		integer shift,
		integer step)
	{
		ENSURE_OP(k, >, 0);
		ENSURE_OP(shift, >=, 0);
		ENSURE_OP(step, >=, 1);

		// Given is a signal S : Z -> R^n.
		// Form a signal R : Z -> R^n : 
		// R(t) = (S(t0 + t), S(t0 + t + dt), ..., S(t0 + t + dt * (k - 1)).
		//
		// Then R is the delay-embedding and
		// t0 is the embedding shift
		// dt is the embedding delay
		// k is the 'embedding factor'
		// d = k n is the embedding dimension

		const integer n = signal->dimension();

		const integer embedDimension = k * n;
		const integer embedSampleWidth = (k - 1) * step + 1;
		const integer embedSamples = (signal->samples() - shift) - embedSampleWidth + 1;

		const SignalPtr embedSignal = SignalPtr(
			new Signal(embedSamples, embedDimension));

		integer sBegin = shift;
		for (integer t = 0;t < embedSamples;++t)
		{
			integer iBegin = 0;
			integer s = sBegin;
			for (integer j = 0;j < k;++j)
			{
				std::copy(
					signal->data().rowBegin(s),
					signal->data().rowEnd(s),
					embedSignal->data().rowBegin(t) + iBegin);

				s += step;
				iBegin += n;
			}
			++sBegin;
		}

		return embedSignal;
	}

	TIM SignalPtr delayEmbedFuture(
		const SignalPtr& signal,
		integer k,
		integer shift,
		integer step)
	{
		ENSURE_OP(k, >, 0);
		ENSURE_OP(shift, >=, 0);
		ENSURE_OP(step, >=, 1);

		const integer futureShift = shift + step * k;

		return delayEmbed(signal, 1, futureShift);
	}

	TIM integer delayEmbedFutureShift(
		integer k, 
		integer shift, 
		integer step)
	{
		ENSURE_OP(k, >, 0);
		ENSURE_OP(shift, >=, 0);
		ENSURE_OP(step, >=, 1);

		return shift + step * k;
	}

}
