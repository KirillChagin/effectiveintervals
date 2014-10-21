// Description: Divergence estimation
// Detail: Wang-Kulkarni-Verdu nearest neighbor estimator

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

#ifndef PASTEL_DIVERGENCE_WKV_H
#define PASTEL_DIVERGENCE_WKV_H

#include "tim/core/mytypes.h"
#include "tim/core/signal.h"

#include "pastel/sys/forwardrange.h"

namespace Tim
{

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator>
	real divergenceWkv(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet);

	TIM real divergenceWkv(
		const SignalPtr& xSignal,
		const SignalPtr& ySignal);

}

#include "tim/core/divergence_wkv.hpp"

#endif
