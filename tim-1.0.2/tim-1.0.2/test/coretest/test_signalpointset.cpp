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

#include "tim/core/signalpointset.h"
#include "tim/core/signal_tools.h"
#include "tim/core/embed.h"

#include <pastel/sys/view_all.h>
#include <pastel/sys/random.h>
#include <pastel/sys/string_tools.h>

using namespace Tim;

namespace
{

	class SignalPointSetTest
		: public TestSuite
	{
	public:
		SignalPointSetTest()
			: TestSuite(&timTestReport())
		{
		}

		virtual void run()
		{
			testBasic();
		}

		void testBasic()
		{
			SignalPtr xy = 
				SignalPtr(new Signal(5, 3));

			xy->data() |=
				0, 5, 10,
				1, 6, 11,
				2, 7, 12,
				3, 8, 13,
				4, 9, 14;

			SignalPtr signalSet[] = {xy};

			SignalPointSet pointSet(forwardRange(signalSet));

			TEST_ENSURE_OP(pointSet.timeBegin(), ==, pointSet.timeEnd());
			TEST_ENSURE(pointSet.begin() == pointSet.end());
			TEST_ENSURE(pointSet.kdTree().empty());
			TEST_ENSURE_OP(pointSet.samples(), ==, xy->samples());
			TEST_ENSURE_OP(pointSet.dimension(), ==, xy->dimension());

			changeTimeWindow(pointSet, -10, 10);
			changeTimeWindow(pointSet, 0, 10);
			changeTimeWindow(pointSet, 1, 10);
			changeTimeWindow(pointSet, 1, 9);
			changeTimeWindow(pointSet, 1, 4);
			changeTimeWindow(pointSet, 1, 3);
			changeTimeWindow(pointSet, 1, 2);
			changeTimeWindow(pointSet, 1, 1);
			changeTimeWindow(pointSet, 2, 2);
			changeTimeWindow(pointSet, 2, 5);
			changeTimeWindow(pointSet, 0, 5);
			changeTimeWindow(pointSet, 0, 1);
			changeTimeWindow(pointSet, 0, 10);
			changeTimeWindow(pointSet, -10, 10);
			changeTimeWindow(pointSet, -20, 10);
			changeTimeWindow(pointSet, -20, 20);
			changeTimeWindow(pointSet, 2, 3);
			changeTimeWindow(pointSet, 1, 4);
			changeTimeWindow(pointSet, 1, 4);

			TEST_ENSURE((*pointSet.begin())->object() == &(xy->data()(3 * 1)));
			TEST_ENSURE((*(pointSet.end() - 1))->object() == &(xy->data()(3 * 3)));

			{
				SignalPointSet pointSet(forwardRange(signalSet), true);

				TEST_ENSURE_OP(std::distance(pointSet.begin(), pointSet.end()), ==, xy->samples());
				TEST_ENSURE_OP(pointSet.kdTree().objects(), ==, xy->samples());
				TEST_ENSURE_OP(pointSet.samples(), ==, xy->samples());
				TEST_ENSURE_OP(pointSet.dimension(), ==, xy->dimension());
			}
			{
				SignalPointSet pointSet(forwardRange(signalSet), true, 1, 2);

				TEST_ENSURE_OP(std::distance(pointSet.begin(), pointSet.end()), ==, xy->samples());
				TEST_ENSURE_OP(pointSet.kdTree().objects(), ==, xy->samples());
				TEST_ENSURE_OP(pointSet.samples(), ==, xy->samples());
				TEST_ENSURE_OP(pointSet.dimension(), ==, 1);

				TEST_ENSURE((*pointSet.begin())->object() == &(xy->data()(3 * 0 + 1)));
				TEST_ENSURE((*(pointSet.end() - 1))->object() == &(xy->data()(3 * 4 + 1)));
			}
		}

		void changeTimeWindow(SignalPointSet& pointSet, integer begin, integer end)
		{
			pointSet.setTimeWindow(begin, end);
			const integer tWidth = pointSet.timeEnd() - pointSet.timeBegin();
			TEST_ENSURE_OP(std::distance(pointSet.begin(), pointSet.end()), ==, tWidth);
			TEST_ENSURE_OP(pointSet.kdTree().objects(), ==, tWidth);
		}
	};

	void testSignalPointSet()
	{
		SignalPointSetTest test;
		test.run();
	}

	void addTest()
	{
		timTestList().add("SignalPointSet", testSignalPointSet);
	}

	CallFunction run(addTest);

}

