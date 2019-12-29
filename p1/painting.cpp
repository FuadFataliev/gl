#include "..\tgaimage.h"
#include <cmath>
#include "painting.h"
#include "iostream"


void line(int x1, int y1, int x2, int y2, TGAImage &img, TGAColor const &clr){
	//std::cout << "(" << x1 << "," << y1 << ") - (" << x2 << "," << y2 << ")" << std::endl;

	bool changed = false;

	if (std::abs(x2 - x1) < std::abs(y2 - y1)){
		std::swap(x1, y1);
		std::swap(x2, y2);

		changed = true;
	}

	if (x1 > x2){
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	double k = std::abs((double)(y2 - y1) / (double)(x2 - x1));

	double y = y1;
	double delta = 0;

	for (int x = x1; x <= x2; x++){
		if (changed)
			img.set(y, x, clr);
		else
			img.set(x, y, clr);

		delta += k;

		if (delta > 0.5){
			y += (y2 - y1 > 0 ? 1 : -1);
			delta -= 1.;
		}
	}
}

    //static size_t i = 0;

//    for(i = 0; i < 3; ++i){
//		if (vs[i].y > vs[(i + 1) % 3].y)
//			std::swap(vs[i], vs[(i + 1) % 3]);
//    }

void triangle(V2I const &v1, V2I const &v2, V2I const &v3, TGAImage &img, TGAColor const &clr){
    V2I vs[3] = {v1, v2, v3};

	if (vs[0].y > vs[1].y)
		std::swap(vs[0], vs[1]);
	if (vs[1].y > vs[2].y)
		std::swap(vs[1], vs[2]);
	if (vs[0].y > vs[1].y)
		std::swap(vs[0], vs[1]);

    float k02 = (vs[2].x - vs[0].x) / (float)(vs[2].y - vs[0].y);
    float k01 = (vs[1].x - vs[0].x) / (float)(vs[1].y - vs[0].y);
    float k12 = (vs[2].x - vs[1].x) / (float)(vs[2].y - vs[1].y);

    for (int y = vs[0].y; y <= vs[1].y; ++y){
		int x1 = vs[0].x + (y - vs[0].y) * k02;
		int x2 = vs[0].x + (y - vs[0].y) * k01;

		line(x1, y, x2, y, img, clr);
    }

//    line(vs[1].x, 0, vs[1].x, vs[1].y - 1, img, RED);
//    line(vs[1].x, vs[1].y + 1, vs[1].x, vs[1].y + 10, img, RED);

    for (int y = vs[1].y; y <= vs[2].y; ++y){
		int x1 = vs[0].x + (y - vs[0].y) * k02;
		int x2 = vs[1].x + (y - vs[1].y) * k12;

		line(x1, y, x2, y, img, GREEN);
    }
}

//void triangle(V2I *const v1, V2I *const v2, V2I *const v3, TGAImage const &img, TGAColor const &clr){
//    V2I *vs[3] = {v1, v2, v3};
//
//    static size_t i = 0;
//
//    for(i = 0; i < 3; ++i){
//		if (vs[i]->y > vs[(i + 1) % 3]->y)
//			std::swap(vs[i], vs[(i + 1) % 3]);
//    }
//}

void triangle(V2I v1, V2I v2, V2I v3, TGAImage &img, TGAColor const &clr){
	if (v1.y > v2.y)
		std::swap(v1, v2);
	if (v2.y > v3.y)
		std::swap(v2, v3);
	if (v1.y > v2.y)
		std::swap(v1, v2);

    float k13 = (v3.x - v1.x) / (float)(v3.y - v1.y);

    if (v1.y != v2.y){
		float k12 = (v2.x - v1.x) / (float)(v2.y - v1.y);

		for (int y = v1.y; y <= v2.y; ++y){
			int x1 = v1.x + (y - v1.y) * k13;
			int x2 = v1.x + (y - v1.y) * k12;

			line(x1, y, x2, y, img, clr);
		}
	}

	//line(v2.x, 0, v2.x, v2.y - 1, img, RED);
	//line(v2.x, v2.y + 1, v2.x, v2.y + 10, img, RED);

	if (v2.y != v3.y){
		float k23 = (v3.x - v2.x) / (float)(v3.y - v2.y);

		for (int y = v2.y; y <= v3.y; ++y){
			int x1 = v1.x + (y - v1.y) * k13;
			int x2 = v2.x + (y - v2.y) * k23;

			line(x1, y, x2, y, img, GREEN);
		}
	}
}
