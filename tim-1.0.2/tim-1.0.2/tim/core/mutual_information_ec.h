// Description: Mutual information estimation via entropy combination

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

#ifndef TIM_MUTUAL_INFORMATION_EC_H
#define TIM_MUTUAL_INFORMATION_EC_H

#include "tim/core/signal.h"

#include <pastel/math/matrix.h>
#include <pastel/math/cholesky_decomposition.h>

#include <pastel/sys/smallset.h>
#include <pastel/sys/forwardrange.h>

namespace Tim
{

	//! Computes temporal mutual information.
	/*!
	Preconditions:
	timeWindowRadius >= 0
	kNearest > 0
	ySignalSet.size() == xSignalSet.size()

	xSignalSet:
	A set of measurements (trials) of signal X. 

	ySignalSet:
	A set of measurements (trials) of signal Y. 

	xLag:
	The delay in samples that is applied to signal X.

	yLag:
	The delay in samples that is applied to signal Y.

	timeWindowRadius:
	The radius of a time-window in samples over which
	the mutual information is estimated for a given
	time instant. Smaller values give sensitivity to
	temporal changes in mutual information, while larger 
	values give smaller variance.

	kNearest:
	The number of nearest neighbors to use in the estimation.

	If the number of samples varies between trials, 
	then the minimum number of samples among the trials
	is used.
	*/

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator,
		typename Real_OutputIterator>
	void temporalMutualInformation(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet,
		integer timeWindowRadius,
		Real_OutputIterator result,
		integer xLag = 0,
		integer yLag = 0,
		integer kNearest = 1);

	//! Computes temporal mutual information.
	/*!
	This is a convenience function that calls:

	temporalMutualInformation(
		forwardRange(constantIterator(xSignal)), 
		forwardRange(constantIterator(ySignal)), 
		timeWindowRadius, result,
		xLag, yLag, kNearest);

	See the documentation for that function.
	*/

	template <typename Real_OutputIterator>
	void temporalMutualInformation(
		const SignalPtr& xSignal,
		const SignalPtr& ySignal,
		integer timeWindowRadius,
		Real_OutputIterator result,
		integer xLag = 0,
		integer yLag = 0,
		integer kNearest = 1);

	//! Computes mutual information.
	/*!
	Preconditions:
	kNearest > 0
	ySignalSet.size() == xSignalSet.size()

	xSignalSet:
	A set of measurements (trials) of signal X. 

	ySignalSet:
	A set of measurements (trials) of signal Y. 

	xLag:
	The delay in samples that is applied to signal X.

	yLag:
	The delay in samples that is applied to signal Y.

	kNearest:
	The number of nearest neighbors to use in the estimation.

	If the number of samples varies between trials, 
	then the minimum number of samples among the trials
	is used.
	*/

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator>
	real mutualInformation(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet,
		integer xLag = 0,
		integer yLag = 0,
		integer kNearest = 1);

	//! Computes mutual information.
	/*!
	This is a convenience function that calls:

	mutualInformation(
		forwardRange(constantIterator(xSignal)), 
		forwardRange(constantIterator(ySignal)), 
		xLag, yLag, kNearest);

	See the documentation for that function.
	*/

	TIM real mutualInformation(
		const SignalPtr& xSignal,
		const SignalPtr& ySignal,
		integer xLag = 0,
		integer yLag = 0,
		integer kNearest = 1);

}

#include "tim/core/mutual_information_ec.hpp"

#endif
