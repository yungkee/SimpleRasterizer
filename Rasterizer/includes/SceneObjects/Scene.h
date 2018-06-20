#pragma once
#include <SceneObjects/Entity.h>
namespace SceneObjects
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		std::shared_ptr<Mesh> GetMesh() const;
		const Mat4& GetTransformation() const;
	};
}
