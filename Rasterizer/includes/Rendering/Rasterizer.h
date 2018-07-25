#pragma once
#include <SceneObjects/Scene.h> 
#include <Graphics/Texture.h> 

using namespace SceneObjects;

namespace Rendering
{

	class Rasterizer
	{

	public:

		Rasterizer();
		~Rasterizer();
		void RenderScene(Scene* scene, Texture* target);

		void DrawTriangle(std::vector<Vertex> triangle, Texture* target);
		void DrawBottomFlatTriangle(const std::vector<Vertex>& triangle, Texture* target);
		void DrawTopFlatTriangle(const std::vector<Vertex>& triangle, Texture* target);
		void DrawHorizontalLine(unsigned int x1, unsigned int x2, unsigned int y, Texture* target);


		static Mat4 CreatePerspectiveProjectionMatrix(const int& width, const int& height, const float& near, const float& far, const float& fov);
		static Mat4 CreatePerspectiveProjectionMatrix(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far);
		static Mat4 CreateOrthographicProjectionMatrix(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far);

	private:
		void DrawLine(int x1, int y1, int x2, int y2, Texture* target);

		void SortVerticesBy(std::vector<Vertex>& p_vertices, bool x = false, bool y = true, bool z = false);

		static Vec4 TransformPos(const Vertex& v, Mat4 transform);

		static void WorldToScreenCoord(int worldWidth, int worldHeight,
			int screenWidth, int screenHeight,
			const Vec3& pos, int& targetX, int& targetY);

		static uint8_t GetLineOctant(int x1, int y1, int x2, int y2);
		static void SwitchToOctantOne(const uint8_t octant, int& x, int& y);
		static void SwitchFromOctantOne(const uint8_t octant, int& x, int& y);
	};
}
