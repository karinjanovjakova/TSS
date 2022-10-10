#include "pch.h"
#include "CppUnitTest.h"
#include "..\TSS\Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(SUM(5, 10), 15);
		}
	};
}
