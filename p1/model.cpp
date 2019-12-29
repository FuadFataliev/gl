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

			//vert.set(vert.x / 270, vert.y / 270, 0);

			vertexes.push_back(vert);


			#ifdef __DEBUG
			if (0 == vertexes.size() % 1000)
				cout << "Read vertexes: " << vertexes.size() << "  faces: " << faces.size() << endl;
			#endif
		}

		if (line.compare(0, 2, "f ") == 0){
			ss.str(line);
			ss >> trash;
			int itrash;

			vector<int> face;
			int f;

			while (ss >> f >> trash >> itrash >> trash >> itrash) {
				face.push_back(f - 1);
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

V3F Model::vertex(size_t i){
	return vertexes[i];
}

vector<int> Model::face(size_t i){
	return faces[i];
}
