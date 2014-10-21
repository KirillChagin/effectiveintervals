// Description: Generation of common signals

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

#ifndef TIM_SIGNAL_GENERATE_H
#define TIM_SIGNAL_GENERATE_H

#include "tim/core/signal.h"

#include <pastel/math/cholesky_decomposition.h>

namespace Tim
{

	//! Generates uniform random variables in [0, 1]^n.
	/*!
	Preconditions:
	dimension > 0
	size >= 0
	*/

	TIM SignalPtr generateUniform(
		integer samples,
		integer dimension);

	//! Generates standard gaussian random variables in R^n.
	/*!
	Preconditions:
	dimension > 0
	samples >= 0
	*/

	TIM SignalPtr generateGaussian(
		integer samples,
		integer dimension);

	//! Generates correlated gaussian random variables in R^n.
	/*!
	Preconditions:
	dimension > 0
	samples >= 0

	The correlated gaussian random variable is given by
	multiplying a standard gaussian random variable
	with the lower triangular part of the cholesky decomposition 
	of the correlation matrix.

	If the given correlation matrix turns out not to
	be numerically positive definite then
	the function call is equivalent to calling
	generateGaussian() (resulting in the 
	correlation matrix being identity).
	*/

	TIM SignalPtr generateCorrelatedGaussian(
		integer samples,
		integer dimension,
		const CholeskyDecompositionD& covarianceCholesky);

	TIM SignalPtr generateGeneralizedGaussian(
		integer samples,
		integer dimension,
		real shape,
		real scale);

	//! Generates a signal with time-varying coupling.
	/*!
	Preconditions:
	samples >= 0
	yzShift >= 0
	zyShift >= 0

	The signals are divide into three time regions.
	In the first and the third time regions, there is
	no coupling between x, y, and z. However, in
	the second time region x drives y, and y drives z.
	The amplitudes of these drives are given by a sine
	wave for the x->y, and by a cosine wave for the
	y->z. Thus, those estimators which are sensitive
	to temporal changes in coupling (e.g. partial 
	transfer entropy) should give similar coupling curves.	
	*/
	TIM void generateTimeVaryingCoupling(
		integer samples,
		integer yxShift,
		integer zyShift,
		const SignalPtr& xSignal,
		const SignalPtr& ySignal,
		const SignalPtr& zSignal);

}

#endif
