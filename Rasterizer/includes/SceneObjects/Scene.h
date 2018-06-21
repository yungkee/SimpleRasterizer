#pragma once
#include <SceneObjects/Entity.h>
namespace SceneObjects
{
	class Scene
	{
	private:
		std::vector<Entity> m_entities;
	public:

		Scene();
		~Scene();

		std::shared_ptr<Mesh> GetMesh() const;
		const Mat4& GetTransformation() const;

		void AddEntity(const Entity& p_entity);
		std::vector<Entity>& GetEntities();
	};
}
