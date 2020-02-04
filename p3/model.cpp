#include "model.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//#define __DEBUG 1

Model::Model(char const *file): vertexes(), faces(){
	ifstream ifs(file, ifstream::in);

	if (ifs.is_open())
		cout << file << " is open!" << endl;

	if (!ifs.good())
		return;

	while (ifs.good()){
		string line;
		getline(ifs, line);

		stringstream ss;
		char trash;

		if (line.compare(0, 2, "v ") == 0){
			ss.str(line);
			ss >> trash;

			V3F vert;
			ss >> vert.x >> vert.y >> vert.z;
			//ss >> vert.x >> vert.y >> vert.z;

			//vert.set(vert.x / 270, vert.y / 270, 0);

			vertexes.push_back(vert);


			#ifdef __DEBUG
			if (0 == vertexes.size() % 1000)
				cout << "Read vertexes: " << vertexes.size() << "  faces: " << faces.size() << endl;
			#endif
		}

		if (line.compare(0, 2, "vt") == 0){
			ss.str(line);
			ss >> line;

			V2F tex;
			ss >> tex.x >> tex.y;

			textures.push_back(tex);


			#ifdef __DEBUG
			if (0 == textures.size() % 1000)
				cout << "Read textures: " << textures.size() << "  faces: " << faces.size() << endl;
			#endif
		}

		if (line.compare(0, 2, "f ") == 0){
			ss.str(line);
			ss >> trash;
			int itrash;

			vector<Face> face;
			Face f;

			//size_t i = 0;
			while (ss >> f.v >> trash >> f.t >> trash >> itrash) {
				f.v -= 1;
				f.t -= 1;
				face.push_back(f);
			}

			faces.push_back(face);

			#ifdef __DEBUG
			if (0 == faces.size() % 1000)
				cout << "Read vertexes: " << vertexes.size() << "  faces: " << faces.size() << endl;
			#endif
		}
	}

	cout << "Vertexes = " << nvertexes() << ". Faces = " << nfaces() << endl;

	ifs.close();
}

size_t Model::nfaces(){
	return faces.size();
}

size_t Model::nvertexes(){
	return vertexes.size();
}

size_t Model::ntextures(){
	return textures.size();
}

V3F Model::vertex(size_t i){
	return vertexes[i];
}

V2F Model::texture(size_t i){
	return textures[i];
}

vector<Face> Model::face(size_t i){
	return faces[i];
}
