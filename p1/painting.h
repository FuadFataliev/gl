#pragma once

#include "..\tgaimage.h"

TGAColor const WHITE(255, 255, 255, 0);
auto const RED   = TGAColor(255, 0, 0, 0);
auto const GREEN = TGAColor(0, 255, 0, 0);
auto const BLUE  = TGAColor(0, 0, 255, 0);
auto const A  = TGAColor(255, 0, 255, 0);

template <typename T>
struct Vert2{
	T x;
	T y;

	Vert2(T x, T y) : x(x), y(y) {};
	Vert2() : x(0), y(0) {};

	void set(T const x, T const y){
		this->x = x;
		this->y = y;
	};
};

typedef Vert2<int> V2I;
typedef Vert2<float> V2F;

template <typename T>
struct Vert3{
	T x;
	T y;
	T z;

	Vert3(T x, T y, T z) : x(x), y(y), z(z) {};
	Vert3() : x(0), y(0), z(0) {};
};

typedef Vert3<int> V3I;
typedef Vert3<float> V3F;

void line(int x1, int y1, int x2, int y2, TGAImage &img, TGAColor const &clr);
//void triangle(V2I const &v1, V2I const &v2, V2I const &v3, TGAImage &img, TGAColor const &clr);
//void triangle(V2I &v1, V2I &v2, V2I &v3, TGAImage &img, TGAColor const &clr);
void triangle(V2I v1, V2I v2, V2I v3, TGAImage &img, TGAColor const &clr);
