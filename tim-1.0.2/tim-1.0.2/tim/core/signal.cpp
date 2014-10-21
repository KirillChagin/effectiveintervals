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

#include "tim/core/signal.h"

#include <pastel/sys/subview.h>
#include <pastel/sys/view_tools.h>

namespace Tim
{

	Signal::Signal()
		: name_()
		, data_()
	{
	}

	Signal::Signal(integer samples, integer dimension)
		: name_()
		, data_(samples, dimension)
	{
	}

	Signal::Signal(integer samples, integer dimension, 
		real* dataToAlias)
		: name_()
		, data_(samples, dimension, withAliasing(dataToAlias))
	{
	}

	void Signal::setName(const std::string& name)
	{
		name_ = name;
	}

	const std::string& Signal::name() const
	{
		return name_;
	}

	integer Signal::dimension() const
	{
		return data_.width();
	}

	integer Signal::samples() const
	{
		return data_.height();
	}

	MatrixD& Signal::data()
	{
		return data_;
	}

	const MatrixD& Signal::data() const
	{
		return data_;
	}

	Signal::PointIterator Signal::pointBegin(integer dimensionBegin)
	{
		return sparseIterator(countingIterator(
			data_.rawBegin() + dimensionBegin), dimension());
	}

	Signal::ConstPointIterator Signal::pointBegin(integer dimensionBegin) const
	{
		return constSparseIterator(countingIterator(
			data_.rawBegin() + dimensionBegin), dimension());
	}

	Signal::PointIterator Signal::pointEnd(integer dimensionBegin)
	{
		return sparseIterator(countingIterator(
			data_.rawBegin() + dimensionBegin + samples() * dimension()), 
			dimension());
	}

	Signal::ConstPointIterator Signal::pointEnd(integer dimensionBegin) const
	{
		return constSparseIterator(countingIterator(
			data_.rawBegin() + dimensionBegin + samples() * dimension()), 
			dimension());
	}

}
