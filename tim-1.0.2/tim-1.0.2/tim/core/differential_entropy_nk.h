// Description: Differential entropy estimation
// Detail: Nilsson-Kleijn manifold nearest neighbor estimator

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

#ifndef TIM_DIFFERENTIAL_ENTROPY_NK_H
#define TIM_DIFFERENTIAL_ENTROPY_NK_H

#include "tim/core/mytypes.h"

#include <pastel/sys/iteratorrange.h>

namespace Tim
{

	template <
		typename SignalPtr_Iterator, 
		typename NormBijection>
	real differentialEntropyNk(
		const ForwardRange<SignalPtr_Iterator>& signalSet,
		real maxRelativeError,
		const NormBijection& normBijection,
		integer* outIntrinsicDimension = 0);

}

#include "tim/core/differential_entropy_nk.hpp"

#endif
