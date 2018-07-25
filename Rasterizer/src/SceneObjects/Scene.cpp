#include <SceneObjects/Scene.h>

using namespace SceneObjects;

Scene::Scene()
{
}


Scene::~Scene()
{
}




void Scene::AddLight(const Light& p_light)
{
	this->m_lights.push_back(p_light);
}

void Scene::AddLight(const Vec3& pos, float ambient, float diffuse, float specular)
{
	this->m_lights.emplace_back(pos, ambient, diffuse, specular);
}

void Scene::AddLight(float x, float y, float z, float ambient, float diffuse, float specular)
{
	this->m_lights.emplace_back(x, y, z, ambient, diffuse, specular);
}

void Scene::AddEntity(const Entity& entity)
{
	this->m_entities.push_back(entity);
}

std::vector<Entity>& Scene::GetEntities()
{
	return m_entities;
}
