#include "graphics/mesh.hpp"

using namespace missan;

// PUBLIC
Mesh::Mesh
(
    GLuint newVaoID,
    const std::string& newFileName,
    const std::vector<float>& newVertices,
    const std::vector<unsigned int> newIndices
)
    : vaoID(newVaoID),
    fileName(newFileName),
    vertices(newVertices),
    indices(newIndices)
{

}