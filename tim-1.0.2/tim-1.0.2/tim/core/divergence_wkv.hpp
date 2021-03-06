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

#ifndef TIM_DIVERGENCE_WKV_HPP
#define TIM_DIVERGENCE_WKV_HPP

#include "tim/core/divergence_wkv.h"
#include "tim/core/signalpointset.h"

#include <pastel/geometry/search_nearest_one_pointkdtree.h>

namespace Tim
{

	template <
		typename SignalPtr_X_Iterator,
		typename SignalPtr_Y_Iterator>
	real divergenceWkv(
		const ForwardRange<SignalPtr_X_Iterator>& xSignalSet,
		const ForwardRange<SignalPtr_Y_Iterator>& ySignalSet)
	{
		// "A Nearest-Neighbor Approach to Estimating
		// Divergence between Continuous Random Vectors"
		// Qing Wang, Sanjeev R. Kulkarni, Sergio Verdu,
		// IEEE International Symposium on Information Theory (ISIT), 
		// 2006.

		if (xSignalSet.empty() || ySignalSet.empty())
		{
			return 0;
		}

		const integer xDimension = xSignalSet.front()->dimension();
		const integer yDimension = ySignalSet.front()->dimension();

		ENSURE_OP(xDimension, ==, yDimension);

		typedef SignalPointSet::ConstObjectIterator ConstObjectIterator;

		// Construct point-sets.

		SignalPointSetPtr xPointSet(new SignalPointSet(xSignalSet, true));
		SignalPointSetPtr yPointSet(new SignalPointSet(ySignalSet, true));

		const integer xSamples = xPointSet->samples();
		const integer ySamples = yPointSet->samples();

		integer acceptedSamples = 0;
		real estimate = 0;
//#pragma omp parallel for reduction(+ : estimate, acceptedSamples)
		for (integer i = 0;i < xSamples;++i)
		{
			// Find out the nearest neighbor in X for a point in X.

			const real xxDistance2 = 
				searchNearestOne(xPointSet->kdTree(), *(xPointSet->begin() + i)).key();
			
			if (xxDistance2 > 0)
			{		
				// Find out the nearest neighbor in Y for a point in X.

				const Vector<real> queryPoint(ofDimension(xDimension), 
					withAliasing((real*)(*(xPointSet->begin() + i))->object()));

				const real xyDistance2 = 
					searchNearestOne(yPointSet->kdTree(), queryPoint).key();
				
				if (xyDistance2 > 0)
				{
					estimate += std::log(xyDistance2 / xxDistance2);
					++acceptedSamples;
				}
			}
		}

		if (acceptedSamples > 0)
		{
			// The factor 2 in the denominator is because 
			// 'xyDistance' and 'xxDistance' are squared distances
			// and thus need to be taken a square root. However,
			// this can be taken outside the logarithm with a 
			// division by 2.
			estimate *= (real)xDimension / (2 * acceptedSamples);
		}
		estimate += std::log((real)ySamples / (xSamples - 1));

		return estimate;
	}

}

#endif
