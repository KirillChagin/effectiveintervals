// Description: Dll-keywords for the TIM library
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

#ifndef TIM_TIM_LIBRARY_H
#define TIM_TIM_LIBRARY_H

#include <pastel/sys/environment.h>

#ifdef _USRDLL
#	ifdef TIM_EXPORTS
#		define TIM PASTEL_DLLEXPORT
#	else
#		define TIM PASTEL_DLLIMPORT
#	endif
#else
#	define TIM
#endif

#endif
