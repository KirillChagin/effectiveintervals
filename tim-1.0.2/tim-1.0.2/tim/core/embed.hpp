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

#ifndef TIM_EMBED_HPP
#define TIM_EMBED_HPP

#include "tim/core/embed.h"

namespace Tim
{

	template <typename SignalPtr_Iterator, typename OutputIterator>
	void delayEmbed(
		const SignalPtr_Iterator& signalBegin,
		const SignalPtr_Iterator& signalEnd,
		const OutputIterator& outputBegin,
		integer k,
		integer shift,
		integer step)
	{
		ENSURE_OP(k, >, 0);
		ENSURE_OP(shift, >=, 0);
		ENSURE_OP(step, >=, 1);

		SignalPtr_Iterator signalIter = signalBegin;
		OutputIterator outputIter = outputBegin;
		while(signalIter != signalEnd)
		{
			*outputIter = delayEmbed(*signalIter, k, shift, step);
			++outputIter;
			++signalIter;
		}
	}

	template <typename SignalPtr_Iterator, typename OutputIterator>
	void delayEmbedFuture(
		const SignalPtr_Iterator& signalBegin,
		const SignalPtr_Iterator& signalEnd,
		const OutputIterator& outputBegin,
		integer k,
		integer shift,
		integer step)
	{
		ENSURE_OP(k, >, 0);
		ENSURE_OP(shift, >=, 0);
		ENSURE_OP(step, >=, 1);

		SignalPtr_Iterator signalIter = signalBegin;
		OutputIterator outputIter = outputBegin;
		while(signalIter != signalEnd)
		{
			*outputIter = Tim::delayEmbedFuture(*signalIter, k, shift, step);
			++outputIter;
			++signalIter;
		}
	}

}

#endif
