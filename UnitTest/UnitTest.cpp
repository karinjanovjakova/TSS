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

		TEST_METHOD(histogram)
		{
			bool R = true , G = true, B = true;
			std::vector<double> r, g, b;
			r.resize(256, 0);
			g.resize(256, 0);
			b.resize(256, 0);
			int height = 100, width = 100, i=0, j=0;
			int stride = 400;
			unsigned int* bmp=new unsigned int [width*height];
			std::vector<std::vector<double>> hist; 
			for (j = 0; j < height; j++) {
				for (i = 0; i < width; i++) {
					bmp[j * stride / 4 + j] = 0x05010203;
					r[1] += 1;
					g[2] += 1;
					b[3] += 1;
				}
			}
			hist=CalcHistStruct(width, height, stride, bmp);
			if (r == hist[0])
				R;
			if (g == hist[1])
				G;
			if (b == hist[2])
				B;
			Assert::IsTrue(R && G && B, L"so far so good");
		}
	};
}
