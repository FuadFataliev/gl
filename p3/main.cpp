#include <iostream>
#include "..\tgaimage.h"
#include "painting.h"
#include "model.h"
#include <string>
#include <limits>

//#define __DEBUG 1

using namespace std;

extern size_t const WIDTH;
extern size_t const HEIGHT;
extern size_t const DEPTH;
//string const FILE_3D = "D:\\FDocs\\CodeBlocs\\gl\\p1\\test_3d.obj"; //
string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\african_head\\african_head.obj";
//string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\diablo3_pose\\diablo3_pose.obj";
//string const FILE_3D = "D:\\FDocs\\CodeBlocs\\gl\\p1\\seahorse.obj";

string const FILE_DIF = "D:\\FDocs\\github\\tinyrenderer\\obj\\african_head\\african_head_diffuse.tga";

float calc_brightness(V3F *f){
	V3F light(0, 0, -1);

	V3F m = (f[2] - f[0]) ^ (f[1] - f[0]);
	V3F mult = m.norm();

	return light * mult;
}

void test(TGAImage &i){
	cout << i.get_width();
}

int main()
{
	auto color = GREEN;

	TGAImage *image = new TGAImage(WIDTH, HEIGHT, TGAImage::RGB);

	TGAImage *dif_img = new TGAImage();
	dif_img->read_tga_file(FILE_DIF.c_str());
	dif_img->flip_vertically();
	auto dif_height = dif_img->get_height();
	auto dif_width = dif_img->get_width();

	int32_t *zbuf = new int32_t[WIDTH * HEIGHT];
	for (size_t i = 0; i < WIDTH * HEIGHT; ++i)
		zbuf[i] = std::numeric_limits<int32_t>::min();

	#ifndef __DEBUG
	Model m(FILE_3D.c_str());

	for (size_t f = 0; f < m.nfaces(); ++f){
		V3I v[3];
		V3F world_crd[3];
		V2F tex_crd[3];

		//color = BLACK;
		size_t r = 0, g = 0, b = 0;
		//r, g, b = 0;
		for (size_t i = 0; i < 3; ++i){
			world_crd[i] = m.vertex(m.face(f)[i].v);
			v[i].set((1. + world_crd[i].x) * WIDTH / 2., (1. + world_crd[i].y) * HEIGHT / 2., (1. + world_crd[i].z) * DEPTH / 2.);

			tex_crd[i] = m.texture(m.face(f)[i].t);

			//color.val += dif_img->get(tex_crd[i].x * dif_width, tex_crd[i].y * dif_height).val;
			color = dif_img->get(tex_crd[i].x * dif_width, tex_crd[i].y * dif_height);
			//size_t r(0), g(0), b(0);
			//size_t r, g, b = 0;
			r += color.r;
			g += color.g;
			b += color.b;
		}

		color.raw[0] = b / 3;
		color.raw[1] = g / 3;
		color.raw[2] = r / 3;

		float brightness = calc_brightness(world_crd);

		if (brightness >= 0){
			auto col = TGAColor(color.r * brightness, color.g * brightness, color.b * brightness, color.a);

			triangle(v[0], v[1], v[2], *image, col, zbuf);
		}
	}
	#endif // DEBUG

	#ifdef __DEBUG
//	V3F v1(-1, 0, 1);
//	V3F v2(0, 1, -0.5);
//	V3F v3(1, 0, 1);
//
//	V3I v[3];
//	V3F world_crd[3] = {v1, v2, v3};
//
//	for (size_t i = 0; i < 3; ++i){
//		size_t x = WIDTH / 2. + world_crd[i].x * WIDTH / 2.;
//		size_t y = HEIGHT / 2. + world_crd[i].y * HEIGHT / 2.;
//		size_t z = DEPTH / 2. + world_crd[i].z * DEPTH / 2.;
//
//		v[i].set(x, y, z);
//	}
//
//	float brightness = calc_brightness(world_crd);
//
//	//auto a = (unsigned char)(color.b * brightness);
//	//if (brightness >= 0){
//		auto col = TGAColor(color.r * brightness, color.g * brightness, color.b * brightness, color.a);
//
//		triangle(v[0], v[1], v[2], image, col, zbuf);
	//}
	//triangle(v1, v2, v3, image, A, zbuf);

	V3I v1(100, 100, 15);
	V3I v2(400, 100, 15);
	V3I v3(250, 500, 15);
	triangle(v1, v2, v3, image, color, zbuf);

	v1.set(260, 500, 15);
	v2.set(560, 500, 15);
	v3.set(410, 100, 15);
	triangle(v1, v2, v3, image, color, zbuf);



//	line(105, 400, 400, 400, image, RED);
//	line(10, 10, 200, 10, image, RED);
//	line(10, 20, 200, 10, image, RED);
//	line(10, 30, 200, 10, image, RED);
//	line(10, 40, 200, 10, image, RED);
//	//image.set(10, 10, RED);
	#endif // __DEBUG

	image->flip_vertically();
	image->write_tga_file("result.tga", false);


    cout << "Hello world!" << endl;
    return 0;
}
