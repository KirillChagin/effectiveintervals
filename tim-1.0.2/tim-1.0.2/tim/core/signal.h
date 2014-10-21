// Description: Signal class
// Detail: Models a time series

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

#ifndef TIM_SIGNAL_H
#define TIM_SIGNAL_H

#include "tim/core/mytypes.h"

#include <pastel/math/matrix.h>

#include <pastel/sys/countedptr.h>
#include <pastel/sys/sparseiterator.h>
#include <pastel/sys/countingiterator.h>

#include <vector>

namespace Tim
{

	//! A time series.

	class TIM Signal
		: public ReferenceCounted
	{
	private:
		typedef SparseIterator<CountingIterator<real*> > PointIterator;
		typedef ConstSparseIterator<CountingIterator<const real*> > ConstPointIterator;

	public:
		// Using default copy constructor.
		// Using default assignment.
		// Using default destructor.

		Signal();
		Signal(integer samples, integer dimension);
		Signal(integer samples, integer dimension,
			real* dataToAlias);

		void setName(const std::string& name);
		const std::string& name() const;

		integer dimension() const;
		integer samples() const;

		MatrixD& data();
		const MatrixD& data() const;

		PointIterator pointBegin(integer dimensionBegin = 0);
		ConstPointIterator pointBegin(integer dimensionBegin = 0) const;

		PointIterator pointEnd(integer dimensionBegin = 0);
		ConstPointIterator pointEnd(integer dimensionBegin = 0) const;

	private:
		std::string name_;
		MatrixD data_;
	};

	typedef CountedPtr<Signal> SignalPtr;

}

#include "tim/core/signal.hpp"

#endif
