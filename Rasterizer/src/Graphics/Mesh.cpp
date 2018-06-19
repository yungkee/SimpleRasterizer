#include <Graphics/Mesh.h>
#include <iostream>

using namespace Graphics;

Mesh::Mesh()
{
	std::cout << "Mesh created" << std::endl;
}


Mesh::~Mesh()
{
	std::cout << "Mesh destroyed" << std::endl;
}
