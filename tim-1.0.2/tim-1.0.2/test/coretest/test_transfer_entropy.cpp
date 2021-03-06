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

#include "estimation.h"

#include "tim/core/mutual_information.h"
#include "tim/core/partial_transfer_entropy.h"
#include "tim/core/signal_tools.h"
#include "tim/core/embed.h"

#include <pastel/gfx/draw.h>
#include <pastel/gfx/pcx.h>

#include <pastel/device/timer.h>

#include <pastel/sys/random.h>
#include <pastel/sys/string_tools.h>

#include <pastel/math/cholesky_decomposition_tools.h>
#include <pastel/math/matrix_tools.h>

using namespace Tim;

namespace
{

	void generateGaussianTest(
		std::vector<SignalPtr>& xEnsemble,
		std::vector<SignalPtr>& xFutureEnsemble,
		std::vector<SignalPtr>& yEnsemble)
	{
		const integer samples = 10000;
		const integer trials = 50;

		for (integer i = 0;i < trials;++i)
		{
			const SignalPtr xSignal = generateGaussian(samples, 1);
			xEnsemble.push_back(xSignal);

			const SignalPtr xSignalFuture = delayEmbed(xSignal, 1, 1, 1);
			xFutureEnsemble.push_back(xSignalFuture);

			const SignalPtr ySignal = delayEmbed(xSignal, 1, 10, 1);
			yEnsemble.push_back(ySignal);
		}
	}

	void generateCouplingTest(
		Array<SignalPtr, 2>& signalSet)
	{
		const integer samples = 1500;
		const integer trials = 5;
		const integer yxShift = 5;
		const integer zyShift = 10;
		signalSet.setExtent(trials, 3);

		for (integer i = 0;i < trials;++i)
		{
			const SignalPtr xSignal(new Signal(samples, 1));
			const SignalPtr ySignal(new Signal(samples, 1));
			const SignalPtr zSignal(new Signal(samples, 1));

			generateTimeVaryingCoupling(samples, yxShift, zyShift, 
				xSignal, ySignal, zSignal);

			signalSet(i, 0) = xSignal;
			signalSet(i, 1) = ySignal;
			signalSet(i, 2) = zSignal;

		}
	}

	void testTransferEntropy()
	{
		Timer timer;
		timer.setStart();

		log() << "Computing transfer entropies..." << logNewLine;
		log() << "Relative errors to correct analytic results shown in brackets." << logNewLine;

		const integer kNearest = 20;

		Array<SignalPtr, 2> signalSet;

		//generateGaussianTest(
		//	xEnsemble, xFutureEnsemble, yEnsemble);

		//transferEntropy(xEnsemble, xFutureEnsemble,
		//	yEnsemble, zEnsembleSet, 5, 20, estimateSet);

		//drawTransferEntropy(estimateSet, "test_mte_gaussian.pcx");

		generateCouplingTest(signalSet);

		const integer miLags = 50;

		std::cout << "Computing mutual informations for X <-> Z..." << std::endl;

		std::vector<real> xzMiSet;
		xzMiSet.reserve(miLags);

		for (integer i = 0;i < miLags;++i)
		{
			std::cout << i << " ";

			xzMiSet.push_back(
				mutualInformation(
				forwardRange(signalSet.rowBegin(0), signalSet.rowEnd(0)),
				forwardRange(signalSet.rowBegin(2), signalSet.rowEnd(2)),
				i, kNearest));
		}
		std::cout << std::endl;

		{
			const SignalPtr miLag = SignalPtr(
				new Signal(xzMiSet.size(), 1));

			Array<Color, 2> image(xzMiSet.size(), 100);
			
			std::copy(
				xzMiSet.begin(),
				xzMiSet.end(),
				miLag->data().begin());

			drawSignal(miLag, arrayView(image));
			savePcx(image, "test_mi_xz.pcx");
		}

		const integer signals = signalSet.height();

		std::vector<SignalPtr> futureSet;

		delayEmbedFuture(
			signalSet.rowBegin(0), signalSet.rowEnd(0),
			std::back_inserter(futureSet), 1);

		std::vector<real> estimateSet;
		temporalPartialTransferEntropy(
			forwardRange(signalSet.rowBegin(0), signalSet.rowEnd(0)),
			forwardRange(signalSet.rowBegin(1), signalSet.rowEnd(1)),
			forwardRange(signalSet.rowBegin(2), signalSet.rowEnd(2)),
			forwardRange(futureSet.begin(), futureSet.end()),
			5,
			std::back_inserter(estimateSet));

		const SignalPtr estimate = SignalPtr(
			new Signal(estimateSet.size(), 1));
		
		std::copy(
			estimateSet.begin(),
			estimateSet.end(),
			estimate->data().begin());

		Array<Color, 2> image(estimateSet.size(), 100);

		drawSignal(estimate, arrayView(image));
		savePcx(image, "test_mte_coupling.pcx");

		drawSignal(signalSet(0, 0), arrayView(image));
		savePcx(image, "test_mte_x.pcx");

		drawSignal(signalSet(0, 1), arrayView(image));
		savePcx(image, "test_mte_y.pcx");

		drawSignal(futureSet.front(), arrayView(image));
		savePcx(image, "test_mte_xf.pcx");

		timer.store();
		log() << "Finished in " << timer.seconds() << " seconds." << logNewLine;
	}

	void testAdd()
	{
		timTestList().add("transfer_entropy", testTransferEntropy);
	}

	CallFunction run(testAdd);

}
