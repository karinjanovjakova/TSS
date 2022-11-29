#pragma once
#include <vector>
int SUM(int a, int b)
{
	return (a + b);
};


std::vector<std::vector<double>> CalcHistStruct(int width, int height, int stride, unsigned int* bmp) {
	std::vector<double> R;
	R.resize(256, 0);
	std::vector<double> G;
	G.resize(256, 0);
	std::vector<double> B;
	B.resize(256, 0);
	int r, g, b, bmpPixel;
	std::vector<std::vector<double>> hist;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			//Sleep(5);
			bmpPixel = bmp[j * stride / 4 + i];
			b = (bmpPixel & 0xff);
			g = (bmpPixel & 0xff00) >> 8;
			r = (bmpPixel & 0xff0000) >> 16;
			B[b] += 1;
			G[g] += 1;
			R[r] += 1;
		}
	}
	hist.push_back(R);
	hist.push_back(G);
	hist.push_back(B);
	return hist;
};