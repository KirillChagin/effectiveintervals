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

#include "tim/core/partial_transfer_entropy.h"

namespace Tim
{

	TIM real partialTransferEntropy(
		const SignalPtr& xSignal,
		const SignalPtr& ySignal,
		const SignalPtr& zSignal,
		const SignalPtr& wSignal,
		integer xLag,
		integer yLag,
		integer zLag,
		integer wLag,
		integer kNearest)
	{
		return Tim::partialTransferEntropy(
			forwardRange(constantIterator(xSignal)),
			forwardRange(constantIterator(ySignal)),
			forwardRange(constantIterator(zSignal)),
			forwardRange(constantIterator(wSignal)),
			xLag, yLag, zLag, wLag,
			kNearest);
	}

}
