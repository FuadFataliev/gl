#include <iostream>
#include "..\tgaimage.h"
#include "painting.h"
#include "model.h"
#include <string>
#include <limits>
#include <exception>

//#define __DEBUG 1

using namespace std;

extern size_t const WIDTH;
extern size_t const HEIGHT;
extern size_t const DEPTH;

string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\african_head\\african_head.obj";
string const FILE_DIF = "D:\\FDocs\\github\\tinyrenderer\\obj\\african_head\\african_head_diffuse.tga";

//string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\boggie\\head.obj";
//string const FILE_DIF = "D:\\FDocs\\github\\tinyrenderer\\obj\\boggie\\head_diffuse.tga";

//string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\boggie\\eyes.obj";
//string const FILE_DIF = "D:\\FDocs\\github\\tinyrenderer\\obj\\boggie\\eyes_diffuse.tga";

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
	//auto color = GREEN;

	TGAImage *image = new TGAImage(WIDTH, HEIGHT, TGAImage::RGB);

	TGAImage *dif_img = new TGAImage();
	dif_img->read_tga_file(FILE_DIF.c_str());
	dif_img->flip_vertically();

	int32_t *zbuf = new int32_t[WIDTH * HEIGHT];
	for (size_t i = 0; i < WIDTH * HEIGHT; ++i)
		zbuf[i] = std::numeric_limits<int32_t>::min();

	#ifndef __DEBUG
	Model m(FILE_3D.c_str());
	try{
	for (size_t f = 0; f < m.nfaces(); ++f){
		V3I v[3];
		V3F world_crd[3];
		V2F tex_crd[3];

		for (size_t i = 0; i < 3; ++i){
			world_crd[i] = m.vertex(m.face(f)[i].v);

			//world_crd[i] = world_crd[i] * 10.;

			v[i].set((1. + world_crd[i].x) * WIDTH / 2., (1. + world_crd[i].y) * HEIGHT / 2., (1. + world_crd[i].z) * DEPTH / 2.);

			//v[i] = v[i] * 2;

			tex_crd[i] = m.texture(m.face(f)[i].t);
		}

		float brightness = calc_brightness(world_crd);

		if (brightness >= 0){
			//auto col = TGAColor(color.r * brightness, color.g * brightness, color.b * brightness, color.a);
			cout << "face = " << f << endl;
			cout << v[0]; cout << v[1]; cout << v[2];
			triangle(v[0], v[1], v[2], tex_crd[0], tex_crd[1], tex_crd[2], *image, *dif_img, brightness, zbuf);

		}
	}
	} catch (exception &e){
				cout << "error" << e.what();
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
	triangleAB(v1, v2, v3, *image, zbuf);

	v1.set(260, 500, 15);
	v2.set(560, 500, 30);
	v3.set(410, 100, 15);
	triangleAB(v1, v2, v3, *image, zbuf);



	//line(252, 500, 408, 500, *image, RED);
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
