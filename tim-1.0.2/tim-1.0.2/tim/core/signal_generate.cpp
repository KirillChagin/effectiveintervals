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

#include "tim/core/signal_generate.h"

#include <pastel/math/matrix_tools.h>

#include <pastel/sys/random.h>

#include <boost/bind.hpp>

namespace Tim
{

	TIM SignalPtr generateUniform(
		integer samples,
		integer dimension)
	{
		ENSURE_OP(dimension, >, 0);
		ENSURE_OP(samples, >=, 0);

		SignalPtr signal = SignalPtr(new Signal(samples, dimension));

		MatrixD::Iterator iter = signal->data().begin();
		const MatrixD::Iterator iterEnd = signal->data().end();

		while(iter != iterEnd)
		{
			*iter = 2 * random<real>() - 1;
			++iter;
		}

		return signal;
	}

	TIM SignalPtr generateGaussian(
		integer samples,
		integer dimension)
	{
		ENSURE_OP(dimension, >, 0);
		ENSURE_OP(samples, >=, 0);

		SignalPtr signal = SignalPtr(new Signal(samples, dimension));

		std::generate(signal->data().begin(), signal->data().end(),
			boost::bind(randomGaussian<real>));

		return signal;
	}

	TIM SignalPtr generateCorrelatedGaussian(
		integer samples,
		integer dimension,
		const CholeskyDecompositionD& covarianceCholesky)
	{
		ENSURE_OP(dimension, >, 0);
		ENSURE_OP(samples, >=, 0);
		ENSURE_OP(covarianceCholesky.lower().width(), ==, dimension);
		ENSURE(covarianceCholesky.succeeded());

		SignalPtr correlatedGaussian = generateGaussian(samples, dimension);

		correlatedGaussian->data() *= transpose(covarianceCholesky.lower());

		return correlatedGaussian;
	}

	TIM SignalPtr generateGeneralizedGaussian(
		integer samples,
		integer dimension,
		real shape,
		real scale)
	{
		ENSURE_OP(dimension, >, 0);
		ENSURE_OP(samples, >=, 0);

		SignalPtr signal = SignalPtr(new Signal(samples, dimension));

		std::generate(signal->data().begin(), signal->data().end(),
			boost::bind(randomGeneralizedGaussian<real>, shape, scale));

		return signal;
	}

	TIM void generateTimeVaryingCoupling(
		integer samples,
		integer yxShift,
		integer zyShift,
		const SignalPtr& xSignal,
		const SignalPtr& ySignal,
		const SignalPtr& zSignal)
	{
		ENSURE_OP(samples, >=, 0);
		ENSURE_OP(yxShift, >=, 0);
		ENSURE_OP(zyShift, >=, 0);

		xSignal->data().setSize(samples, 1);
		ySignal->data().setSize(samples, 1);
		zSignal->data().setSize(samples, 1);

		if (samples == 0)
		{
			return;
		}

		const integer couplingStart = samples / 3;
		const integer couplingEnd = (samples * 2) / 3;
		const integer couplingSamples = couplingEnd - couplingStart;
		const real cyclesPerSample = 
			(2 * constantPi<real>()) / couplingSamples;

		MatrixD::Iterator xIter = xSignal->data().begin();
		MatrixD::Iterator yIter = ySignal->data().begin();
		MatrixD::Iterator zIter = zSignal->data().begin();

		for (integer i = 0;i < samples;++i)
		{
			real couplingYx = 0;
			real couplingZy = 0;
			if (i >= couplingStart && i < couplingEnd)
			{
				const real t = cyclesPerSample * (i - couplingStart);
				couplingYx = std::sin(t);
				couplingZy = std::cos(t);
			}

			real xPrevious = 0;
			real yPrevious = 0;
			real zPrevious = 0;
			if (i >= 1)
			{
				xPrevious = *(xIter - 1);
				yPrevious = *(yIter - 1);
				zPrevious = *(zIter - 1);
			}
			
			real xHistory = 0;
			if (i >= yxShift)
			{
				xHistory = *(xIter - yxShift);
			}

			real yHistory = 0;
			if (i >= zyShift)
			{
				yHistory = *(yIter - zyShift);
			}

			*xIter = 0.4 * xPrevious + 
				randomGaussian<real>();
			*yIter = 0.5 * yPrevious + 
				couplingYx * std::sin(xHistory) + 
				randomGaussian<real>();
			*zIter = 0.5 * zPrevious + 
				couplingZy * std::sin(yHistory) + 
				randomGaussian<real>();

			++xIter;
			++yIter;
			++zIter;
		}
	}

}
