// Description: Type definitions for the TIM library
// Detail: Simply imports the type definitions of the Pastel library
// Documentation: basics.txt

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

#ifndef TIM_MYTYPES_H
#define TIM_MYTYPES_H

#include "tim/core/tim_library.h"

#include <pastel/sys/mytypes.h>
#include <pastel/sys/vector_tools.h>

#include <pastel/math/maximum_normbijection.h>

namespace Tim
{

	using namespace Pastel;

	typedef Maximum_NormBijection<real> Default_NormBijection;

}

#endif
