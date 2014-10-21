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

#include "estimation.h"

#include "tim/core/signal_tools.h"
#include "tim/core/embed.h"

#include <pastel/sys/random.h>

#include "tim/core/divergence_wkv.h"

using namespace Tim;

namespace
{

	void testDivergence()
	{
		SignalPtr xSignal = generateGaussian(10000, 10);
		SignalPtr ySignal = generateGaussian(10000, 10);

		const real div = divergenceWkv(xSignal, ySignal);
		log() << "Divergence = " << div << logNewLine;
	}

	void addTest()
	{
		timTestList().add("Divergence", testDivergence);
	}

	CallFunction run(addTest);

}
