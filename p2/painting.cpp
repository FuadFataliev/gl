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

void triangle_old(V2I v1, V2I v2, V2I v3, TGAImage &img, TGAColor const &clr){
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

template <typename T>
T sqr(T x) {return x * x;};


float calc_kz(V3I const &v1, V3I const &v2){
	return (v2.z - v1.z) / (float)sqrt(sqr(v2.x - v1.x) + sqr(v2.y - v1.y));
}

void triangle_old(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr, int32_t *const zbuff){
	if (v1.y > v2.y)
		std::swap(v1, v2);
	if (v2.y > v3.y)
		std::swap(v2, v3);
	if (v1.y > v2.y)
		std::swap(v1, v2);

    float k13 = (v3.x - v1.x) / (float)(v3.y - v1.y);
    float z13 = calc_kz(v1, v3);

    if (v1.y != v2.y){
		float k12 = (v2.x - v1.x) / (float)(v2.y - v1.y);

		//float kz = (v2.z - v1.z) / (float)sqrt(sqr(v2.x - v1.x) + sqr(v2.y - v1.y));
		float z12 = calc_kz(v1, v2);

		for (int y = v1.y; y <= v2.y; ++y){
			int x1 = v1.x + (y - v1.y) * k13;
			int x2 = v1.x + (y - v1.y) * k12;

			int z1 = (v3.x - x1) * z13;
			int z2 = (v2.x - x2) * z12;

			float kz = (x2 == x1)? 0 : (z2 - z1) / (float)(x2 - x1);

//			if (x2 == x1)
//				kz = 0;
//			else
//				float kz = (z2 - z1) / (float)(x2 - x1);

			//line(x1, y, x2, y, img, clr);
			for (int x = x1; x <= x2; ++x){
				int z = z1 + x * kz;

				if (z > zbuff[y * WIDTH + x]){
					zbuff[y * WIDTH + x] = z;

					img.set(y, x, clr);
				}
			}
		}
	}

	//line(v2.x, 0, v2.x, v2.y - 1, img, RED);
	//line(v2.x, v2.y + 1, v2.x, v2.y + 10, img, RED);

	if (v2.y != v3.y){
		float k23 = (v3.x - v2.x) / (float)(v3.y - v2.y);
		float z23 = calc_kz(v2, v3);

		for (int y = v2.y; y <= v3.y; ++y){
			int x1 = v1.x + (y - v1.y) * k13;
			int x2 = v2.x + (y - v2.y) * k23;

			int z1 = (v3.x - x1) * z13;
			int z2 = (v3.x - x2) * z23;

			float kz = (x2 == x1)? 0 : (z2 - z1) / (float)(x2 - x1);

//			if (x2 == x1)
//				kz = 0;
//			else
//				float kz = (z2 - z1) / (float)(x2 - x1);

			//line(x1, y, x2, y, img, clr);
			for (int x = x1; x <= x2; ++x){
				int z = z1 + x * kz;

				try{
					if (z > zbuff[y * WIDTH + x]){
						zbuff[y * WIDTH + x] = z;

						img.set(y, x, clr);
					}
				} catch (int e){
					std::cout << (y * WIDTH + x) << std::endl;
					return;
				}
			}
		}
	}
}

//#define GRID_ENABLED = 1

void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr, int32_t *const zbuf){
	if (v1.y > v2.y)
		std::swap(v1, v2);
	if (v2.y > v3.y)
		std::swap(v2, v3);
	if (v1.y > v2.y)
		std::swap(v1, v2);

	//int h13 = v3.y - v1.y;
	//int w13 = v3.x - v1.x;
	V3I main_dif = v3 - v1;

	size_t x1;
	int32_t z1;
	size_t x2;
	int32_t z2;

	for (int y = 0; y <= main_dif.y; ++y){
		bool first_half = v1.y + y <= v2.y;

		V3I dif = first_half ? v2 - v1 : v3 - v2;

		if (dif.y == 0){
			if (first_half){
				x1 = v1.x;
				z1 = v1.z;
			} else {
				x1 = v3.x;
				z1 = v3.z;
			}

			x2 = v2.x;
			z2 = v2.z;
		} else {
			V3I a = first_half ? v1 : v2;

			float coef = (y - (first_half ? 0 : a.y - v1.y)) / (float)dif.y;

			x1 = a.x + dif.x * coef; //(y - (first_half ? 0 : a.y - v1.y)) / (float)dif.y;
			z1 = a.z + dif.z * coef;

			coef = y / (float)main_dif.y;
			x2 = v1.x + main_dif.x * coef; //(y / (float)main_dif.y);
			z2 = v1.z + main_dif.z * coef;
		}

		if (x1 > x2){
			std::swap(x1, x2);
			std::swap(z1, z2);
		}

		for (size_t x = x1; x <= x2; ++x) {
			TGAColor col = clr;

			#ifdef GRID_ENABLED
			if ((x == x1) || (x == x2) || (y == 0) || (y == main_dif.y))
				col = GREEN;
			#endif // GRID_ENABLED

			int32_t z = z1;

			if (x1 != x2)
				z = z1 + (z2 - z1) * ((x - x1) / (float)(x2 - x1));

			if (z > zbuf[(v1.y + y) * WIDTH + x]){
				zbuf[(v1.y + y) * WIDTH + x] = z;

				img.set(x, v1.y + y, col);
			}
		}
	}
}

//void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr, int32_t *const zbuf){
//	if (v1.y > v2.y)
//		std::swap(v1, v2);
//	if (v2.y > v3.y)
//		std::swap(v2, v3);
//	if (v1.y > v2.y)
//		std::swap(v1, v2);
//
//	//int h13 = v3.y - v1.y;
//	//int w13 = v3.x - v1.x;
//	V3I main_dif = v3 - v1;
//
//	for (int y = 0; y <= main_dif.y; ++y){
////		if (y == h13)
////			int i = 10;
//
//
//		bool first_half = v1.y + y <= v2.y;
//
//		V3I a = first_half ? v1 : v2;
//
//		V3I dif = first_half ? v2 - v1 : v3 - v2;
//
//		if (dif.y == 0)
//			continue;
//
//		float coef = (y - (first_half ? 0 : a.y - v1.y)) / (float)dif.y;
//
//		size_t x1 = a.x + dif.x * coef; //(y - (first_half ? 0 : a.y - v1.y)) / (float)dif.y;
//		int32_t z1 = a.z + dif.z * coef;
//
//		coef = y / (float)main_dif.y;
//		size_t x2 = v1.x + main_dif.x * coef; //(y / (float)main_dif.y);
//		int32_t z2 = v1.z + main_dif.z * coef;
//
//		if (x1 > x2){
//			std::swap(x1, x2);
//			std::swap(z1, z2);
//		}
//
//		for (size_t x = x1; x <= x2; ++x) {
//			TGAColor col;
//
//			if (x == x1 || x == x2)
//				col = GREEN;
//			else
//				//col = TGAColor(clr.val * brightness, clr.bytespp);
//				col = clr; //TGAColor(clr.r * brightness, clr.g * brightness, clr.b * brightness, clr.bytespp);
//			//col = clr;
//			int32_t z = z1;
//
//			if (x1 != x2)
//				z = z1 + (z2 - z1) * ((x - x1) / (float)(x2 - x1));
//
//			if (z > zbuf[(v1.y + y) * WIDTH + x]){
//				zbuf[(v1.y + y) * WIDTH + x] = z;
//
//				img.set(x, v1.y + y, col);
//			}
//		}
//	}
//}
