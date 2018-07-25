#pragma once
#include <SceneObjects/Entity.h>
#include <SceneObjects/Light.h>

namespace SceneObjects
{
	class Scene
	{
	private:
		std::vector<Light> m_lights;
		std::vector<Entity> m_entities;
	public:

		Scene();
		~Scene();

		void AddLight(const Light& light);
		void AddLight(const Vec3& pos, float ambient, float diffuse, float specular);
		void AddLight(float x, float y, float z, float ambient, float diffuse, float specular);


		std::shared_ptr<Mesh> GetMesh() const;
		void AddEntity(const Entity& entity);
		std::vector<Entity>& GetEntities();
	};
}
