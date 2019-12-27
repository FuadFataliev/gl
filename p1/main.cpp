#include <iostream>
#include "..\tgaimage.h"
#include "painting.h"

using namespace std;

int main()
{
	V2I v1(10, 10);
	V2I v2(200, 100);
	V2I v3(100, 400);

    TGAImage image(1000, 1000, TGAImage::RGB);
	//line(1, 1, 98, 98, image, A); //BLUE);
	//line(0, 99, 99, 0, image, A); //BLUE);
	//line(v1.x, v1.y, v2.x, v2.y, image, A);
	triangle(v1, v2, v3, image, A);


	v1.set(900, 900);
	v2.set(400, 300);
	v3.set(800, 700);
	triangle(v1, v2, v3, image, A);


	v1.set(200, 500);
	v2.set(800, 550);
	v3.set(500, 950);
	triangle(v1, v2, v3, image, A);

	v1.set(600, 900);
	v2.set(700, 900);
	v3.set(650, 950);
	triangle(v1, v2, v3, image, A);

	v1.set(800, 900);
	v2.set(900, 900);
	v3.set(850, 950);
	triangle(v1, v2, v3, image, A);

	v1.set(800, 200);
	v2.set(900, 200);
	v3.set(850, 100);
	triangle(v1, v2, v3, image, A);

	//image.write_tga_file("D:\FDocs\CodeBlocs\gl\p1\bin\Debug\result.tga", false);
	image.flip_vertically();
	image.write_tga_file("result.tga", false);


    cout << "Hello world!" << endl;
    return 0;
}
