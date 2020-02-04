#pragma once

#include <cmath>
#include "..\tgaimage.h"
#include "iostream"

TGAColor const WHITE(255, 255, 255, 0);
auto const BLACK = TGAColor(0, 0, 0, 0);
auto const RED   = TGAColor(255, 0, 0, 0);
auto const GREEN = TGAColor(0, 255, 0, 0);
auto const BLUE  = TGAColor(0, 0, 255, 0);
auto const LBLUE = TGAColor(10, 100, 255, 0);
auto const A     = TGAColor(255, 0, 255, 0);

size_t const WIDTH = 800;
size_t const HEIGHT = 800;
size_t const DEPTH = 255;

template<typename T>
int32_t sign(T x){
	return (x == 0) ? 0 : ((x < 0) ? -1 : 1);
}

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
	//T operator*(const Vert2& v) {return x * v.x + y * v.y;}
	Vert2 operator*(const float f) {return Vert2(f * x, f * y);}
//	Vert2<int> operator = (const Vert2<float> v) {return Vert2<int>(v.x, v.y);}
//	//Vert2<T> operator = (const Vert2<T> v) {return Vert2<T>(v.x, v.y);}
//	Vert2<int> operator = (const Vert2<int> v) {return Vert2<int>(v.x, v.y);}
//	Vert2<float> operator = (const Vert2<float> v) {return Vert2<float>(v.x, v.y);}
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

	Vert3 norm() {
		//size_t len = sqrt(x*x + y*y + z*z);
		return (*this) * (1 / sqrt(x*x + y*y + z*z));
	}

	Vert3 operator+(const Vert3& v) {return Vert3(x + v.x, y + v.y, z + v.z);}
	Vert3 operator-(const Vert3& v) {return Vert3(x - v.x, y - v.y, z - v.z);}
	T operator*(const Vert3& v) {return x * v.x + y * v.y + z * v.z;}
	//Vert3 operator * (const float f) {return Vert3(f * x + .5 * sign<float>(f * x), f * y + .5 * sign<float>(f * y), f * z + .5 * sign<float>(f * z));}
	Vert3 operator*(const float f) {return Vert3(f * x, f * y, f * z);}
	//Vert3<int> operator*(const float f) {return Vert3<int>(f * x, f * y, f * z);}
	Vert3 operator^(const Vert3& v) {return Vert3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}

	//Vert3<float> operator=(const Vert3<int>& v) {return Vert3<float>(v.x, v.y, v.z);}
	//Vert3 operator+(Vert3 l, Vert3 const & r) {l.set(l.x + r.x, l.y + r.y, l.z + p.z); return l;}
	//Vert3 operator=(Vert3 const & p) {this->set(p.x, p.y, p.z); return this*;};
	friend std::ostream& operator << (std::ostream &l, Vert3 const &r) {l << "x = " << r.x << " y = " << r.y << " z = " << r.z << std::endl; return l;}
};

typedef Vert3<int> V3I;
typedef Vert3<float> V3F;

void line(int x1, int y1, int x2, int y2, TGAImage &img, TGAColor const &clr);
//void triangle(V2I const &v1, V2I const &v2, V2I const &v3, TGAImage &img, TGAColor const &clr);
//void triangle(V2I &v1, V2I &v2, V2I &v3, TGAImage &img, TGAColor const &clr);
void triangle(V2I v1, V2I v2, V2I v3, TGAImage &img, TGAColor const &clr);
void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr); //, int32_t *const zbuff); //int32_t zbuff[]);
void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAColor const &clr, int32_t *const zbuf);

//void triangle(V3I v1, V3I v2, V3I v3, TGAImage &img, TGAImage &dif_img, float const b, int32_t *const zbuf);
void triangle(V3I v1, V3I v2, V3I v3, V2F t1, V2F t2, V2F t3, TGAImage &img, TGAImage &dif_img, float const b, int32_t *const zbuf);
void triangleAB(V3I v1, V3I v2, V3I v3, TGAImage &img, int32_t *const zbuf);
