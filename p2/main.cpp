#include <iostream>
#include "..\tgaimage.h"
#include "painting.h"
#include "model.h"
#include <string>
#include <limits>

//#define __DEBUG 1

using namespace std;

//int main()
//{
//	V2I v1(10, 10);
//	V2I v2(200, 100);
//	V2I v3(100, 400);
//
//    TGAImage image(1000, 1000, TGAImage::RGB);
//	//line(1, 1, 98, 98, image, A); //BLUE);
//	//line(0, 99, 99, 0, image, A); //BLUE);
//	//line(v1.x, v1.y, v2.x, v2.y, image, A);
//	triangle(v1, v2, v3, image, A);
//
//
//	v1.set(900, 900);
//	v2.set(400, 300);
//	v3.set(800, 700);
//	triangle(v1, v2, v3, image, A);
//
//
//	v1.set(200, 500);
//	v2.set(800, 550);
//	v3.set(500, 950);
//	triangle(v1, v2, v3, image, A);
//
//	v1.set(600, 900);
//	v2.set(700, 900);
//	v3.set(650, 950);
//	triangle(v1, v2, v3, image, A);
//
//	v1.set(800, 900);
//	v2.set(900, 900);
//	v3.set(850, 950);
//	triangle(v1, v2, v3, image, A);
//
//	v1.set(800, 200);
//	v2.set(900, 200);
//	v3.set(850, 100);
//	triangle(v1, v2, v3, image, A);
//
//	//image.write_tga_file("D:\FDocs\CodeBlocs\gl\p1\bin\Debug\result.tga", false);
//	image.flip_vertically();
//	image.write_tga_file("result.tga", false);
//
//
//    cout << "Hello world!" << endl;
//    return 0;
//}

extern size_t const WIDTH;
extern size_t const HEIGHT;
extern size_t const DEPTH;
//string const FILE_3D = "D:\\FDocs\\CodeBlocs\\gl\\p1\\test_3d.obj"; //
string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\african_head\\african_head.obj";
//string const FILE_3D = "D:\\FDocs\\github\\tinyrenderer\\obj\\diablo3_pose\\diablo3_pose.obj";
//string const FILE_3D = "D:\\FDocs\\CodeBlocs\\gl\\p1\\seahorse.obj";

int main()
{
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	Model m(FILE_3D.c_str());

	//size_t zbuf[WIDTH * HEIGHT] = {0};
	int32_t *zbuf = new int32_t[WIDTH * HEIGHT];
	for (size_t i = 0; i < WIDTH * HEIGHT; ++i)
		zbuf[i] = std::numeric_limits<int32_t>::min();

	#ifndef __DEBUG
	for (size_t f = 0; f < m.nfaces(); ++f){
		V3I v[3];

		for (size_t i = 0; i < 3; ++i){
			size_t x = WIDTH / 2. + m.vertex(m.face(f)[i]).x * WIDTH / 2.;
			size_t y = HEIGHT / 2. + m.vertex(m.face(f)[i]).y * HEIGHT / 2.;
			size_t z = DEPTH / 2. + m.vertex(m.face(f)[i]).z * DEPTH / 2.;

			v[i].set(x, y, z); //v[i].set(WIDTH / 2. + m.vertex(m.face(f)[i]).x * WIDTH / 2., HEIGHT / 2. + m.vertex(m.face(f)[i]).y * HEIGHT / 2.);
		}

		//for (size_t i = 0; i < 3; ++i)
		//	line(v[i].x, v[i].y, v[(i+1) % 3].x, v[(i+1) % 3].y, image, A);
		triangle(v[0], v[1], v[2], image, A, zbuf);
	}
	#endif // DEBUG

	#ifdef __DEBUG
	V3I v1(10, 10, 10);
	V3I v2(200, 100, 10);
	V3I v3(100, 300, 60);
	triangle(v1, v2, v3, image, A, zbuf);

//	v1.set(50, 50, 15);
//	v2.set(200, 100, 15);
//	v3.set(100, 400, 15);
//	triangle(v1, v2, v3, image, A, zbuf);



//	line(105, 400, 400, 400, image, RED);
//	line(10, 10, 200, 10, image, RED);
//	line(10, 20, 200, 10, image, RED);
//	line(10, 30, 200, 10, image, RED);
//	line(10, 40, 200, 10, image, RED);
//	//image.set(10, 10, RED);
	#endif // __DEBUG

	image.flip_vertically();
	image.write_tga_file("result.tga", false);


    cout << "Hello world!" << endl;
    return 0;
}
