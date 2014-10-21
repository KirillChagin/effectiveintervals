// Description: Analytical solutions for differential entropies

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

#ifndef TIM_DIFFERENTIAL_ENTROPY_ANALYTIC_H
#define TIM_DIFFERENTIAL_ENTROPY_ANALYTIC_H

#include "tim/core/mytypes.h"

namespace Tim
{

	//! Differential entropy of a gaussian distribution.
	/*!
	Preconditions:
	dimension > 0
	covarianceDeterminant >= 0

	dimension:
	The dimension of the distribution.

	covarianceDeterminant:
	Determinant of the covariance matrix of the distribution.

	Returns:
	The differential entropy of the distribution.
	*/
	TIM real gaussianDifferentialEntropy(
		integer dimension, real covarianceDeterminant);

	//! Differential entropy of a uniform distribution.
	/*!
	Preconditions:
	supportVolume >= 0

	supportVolume:
	The measure m of the support of the probability density
	function p: m({x in R^n: p(x) != 0})

	Returns:
	The differential entropy of the distribution.
	*/
	TIM real uniformDifferentialEntropy(
		real supportVolume);

	//! Differential entropy of a generalized gaussian distribution.
	/*!
	Preconditions:
	dimension > 0
	shape > 0
	scale > 0

	dimension:
	The dimension of the distribution.

	shape:
	The shape parameter of the distribution.

	scale:
	The scale parameter of the distribution.

	Returns:
	The differential entropy of the distribution.
	*/
	TIM real generalizedGaussianDifferentialEntropy(
		integer dimension, real shape, real scale);

}

#endif
