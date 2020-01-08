#pragma once

#include "..\tgaimage.h"

TGAColor const WHITE(255, 255, 255, 0);
auto const RED   = TGAColor(255, 0, 0, 0);
auto const GREEN = TGAColor(0, 255, 0, 0);
auto const BLUE  = TGAColor(0, 0, 255, 0);
auto const A  = TGAColor(255, 0, 255, 0);

size_t const WIDTH = 800;
size_t const HEIGHT = 800;
size_t const DEPTH = 255;

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

	Vert2 operator+(const Vert2& v) {return Vert2(x + v.x, y + v.y);}
	Vert2 operator-(const Vert2& v) {return Vert2(x - v.x, y - v.y);}
	Vert2 operator*(const Vert2& v) {return Vert2(x * v.x, y * v.y);}
	Vert2 operator*(const float f) {return Vert2(f * x, f * y);}
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

	void set(T const x, T const y, T const z){
		this->x = x;
		this->y = y;
		this->z = z;
	};

	Vert3 operator+(const Vert3& v) {return Vert3(x + v.x, y + v.y, z + v.z);}
	Vert3 operator-(const Vert3& v) {return Vert3(x - v.x, y - v.y, z - v.z);}
	Vert3 operator*(const Vert3& v) {return Vert3(x * v.x, y * v.y, z * v.z);}
	Vert3 operator*(const float f) {return Vert3(f * x, f * y, f * z);}
	//Vert3 operator+(Vert3 l, Vert3 const & r) {l.set(l.x + r.x, l.y + r.y, l.z + p.z); return l;}
	//Vert3 operator=(Vert3 const & p) {this->set(p.x, p.y, p.z); return this*;};
};

typedef Vert3<int> V3I;
typedef Vert3<float> V3F;

void line(int x1, int y1, int x2, int y2, TGAImage &img, TGAColor const &clr);
//void triangle(V2I const &v1, V2I const &v2, V2I const &v3, TGAImage &img, TGAColor const &clr);
//void triangle(V2I &v1, V2I &v2, V2I &v3, TGAImage &img, TGAColor const &clr);
void triangle(V2I v1, V2I v2, V2I v3, TGAImage &img, TGAColor const &clr);
void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr); //, int32_t *const zbuff); //int32_t zbuff[]);
void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr, int32_t *const zbuf);
