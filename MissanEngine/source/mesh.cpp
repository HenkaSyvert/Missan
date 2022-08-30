#include "mesh.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/projection.hpp>

#include <vector>
#include <string>

using namespace Missan;
using namespace std;
using namespace glm;

Mesh::Mesh(int vaoId, const vector<float>& vs, const vector<unsigned int>& indices) {

    this->vaoId = vaoId;
    for (unsigned int i = 0; i < vs.size(); i += 3) vertices.push_back(vec3(vs[i], vs[i + 1], vs[i + 2]));  
    for (unsigned int i = 0; i < indices.size(); i += 3) normals.push_back(cross(vertices[indices[i]], vertices[indices[i + 1]]));   
	
}
