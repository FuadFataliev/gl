#pragma once
#include <string>
#include <vector>
#include "painting.h"

using namespace std;

class Model{
	string file;
	vector<V3F> vertexes;
	vector<vector<int>> faces;
public:
	//Model(string const &file);
	Model(char const *file);

	size_t nfaces();

	size_t nvertexes();

	V3F vertex(size_t i);

	vector<int> face(size_t i);
};
