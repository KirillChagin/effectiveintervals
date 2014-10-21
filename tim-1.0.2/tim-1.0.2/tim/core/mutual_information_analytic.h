// Description: Analytic solutions for mutual information

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

#ifndef TIM_MUTUAL_INFORMATION_ANALYTIC_H
#define TIM_MUTUAL_INFORMATION_ANALYTIC_H

#include "tim/core/mytypes.h"

namespace Tim
{

	//! Mutual information between marginals of a correlated gaussian.
	/*!
	Let X be a correlated gaussian random variable consisting of marginal
	random variables (X_1, ..., X_m). Then the mutual information
	(total correlation) between X_i is given by:
	
	I(X_1, ..., X_m) = 0.5 log((|cov(X_1)| ... |cov(X_m)| / |cov(X)))

	marginalCovarianceDeterminantProduct:
	|cov(X_1)| ... |cov(X_m)|

	jointCovarianceDeterminant:
	|cov(X)|
	*/

	TIM real correlatedGaussianMutualInformation(
		real marginalCovarianceDeterminantProduct,
		real jointCovarianceDeterminant);

}

#endif
