#pragma once
#include <string>
#include <vector>
#include "painting.h"

using namespace std;

class Face{
public:
	size_t v, t;
};

class Model{
	string file;
	vector<V3F> vertexes;
	vector<V2F> textures;
	vector<vector<Face>> faces;
public:
	//Model(string const &file);
	Model(char const *file);

	size_t nfaces();

	size_t nvertexes();

	size_t ntextures();

	V3F vertex(size_t i);
	V2F texture(size_t i);

	vector<Face> face(size_t i);
};
