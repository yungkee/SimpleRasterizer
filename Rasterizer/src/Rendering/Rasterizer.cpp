#include <Rendering/Rasterizer.h>
#include <algorithm>
#include <iostream>
using namespace Rendering;

Rasterizer::Rasterizer()
{
}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::RenderScene(Scene * scene, Texture* target)
{
    target->Clear(Color(0, 0, 0));
  std::vector<Entity> entities = scene->GetEntities();
  for (Entity entity : entities)
  {
    const Mesh* mesh = entity.GetMesh();
    for (unsigned i = 0; i < mesh->GetTriangleCount(); ++i)
    {
      const Vertex* triangle = mesh->GetTriangleVertices(i);
      const std::vector<Vertex> transformedTriangle = { 
        TransformPos(triangle[0].GetPosition(), entity.GetTransformation()).ToVec3(),
        TransformPos(triangle[1].GetPosition(), entity.GetTransformation()).ToVec3(),
        TransformPos(triangle[2].GetPosition(), entity.GetTransformation()).ToVec3() };

      delete[] triangle;
      triangle = nullptr;
      DrawTriangle(transformedTriangle, target);
    }
  }
}

void Rasterizer::DrawTriangle(std::vector<Vertex> triangle, Texture* target)
{
  if (triangle.size() != 3)
    return;

  SortVerticesBy(triangle);
  int v1x, v1y;
  int v2x, v2y;
  int v3x, v3y;

  WorldToScreenCoord(5, 5, target->Width(), target->Height(), triangle[0].GetPosition(), v1x, v1y);
  WorldToScreenCoord(5, 5, target->Width(), target->Height(), triangle[1].GetPosition(), v2x, v2y);
  WorldToScreenCoord(5, 5, target->Width(), target->Height(), triangle[2].GetPosition(), v3x, v3y);
  
  if (v2y == v3y)
  {
    DrawBottomFlatTriangle(std::vector<Vertex> {Vec3(v1x,v1y),Vec3(v2x,v2y),Vec3(v3x,v3y)}, target);
  }
  else if (v1y == v2y)
  {
    DrawTopFlatTriangle(std::vector<Vertex> {Vec3(v1x, v1y), Vec3(v2x, v2y), Vec3(v3x, v3y)}, target);
  }
  else
  {
    const Vec3 v4 = Vec3( (int)(v1x +  (float)(v2y - v1y) / (float)(v3y - v1y) * (v3x - v1x)) , v2y);

    const std::vector<Vertex> bottomFlatTriangle = {Vec3(v1x,v1y), Vec3(v2x,v2y), v4};
    const std::vector<Vertex> topFlatTriangle = {Vec3(v2x,v2y), v4, Vec3(v3x,v3y)};

    DrawBottomFlatTriangle(bottomFlatTriangle, target);
    DrawTopFlatTriangle(topFlatTriangle, target);
  }

}



void Rasterizer::DrawTopFlatTriangle(const std::vector<Vertex>& triangle, Texture* target)
{
  int v1x = triangle[0].GetPosition().m_x;
  int v1y = triangle[0].GetPosition().m_y;

  int v2x = triangle[1].GetPosition().m_x;
  int v2y = triangle[1].GetPosition().m_y;

  int v3x = triangle[2].GetPosition().m_x;
  int v3y = triangle[2].GetPosition().m_y;


  //SETUP 2ND LINE

  const uint8_t octant2 = GetLineOctant(v2x, v2y, v3x, v3y);
  SwitchToOctantOne(octant2, v2x, v2y);
  SwitchToOctantOne(octant2, v3x, v3y);
  int dx2 = v3x - v2x;
  int dy2 = v3y - v2y;

  int e2 = dx2;
  dx2 *= 2;
  dy2 *= 2;

  SwitchFromOctantOne(octant2, v2x, v2y);
  SwitchFromOctantOne(octant2, v3x, v3y);

  //SETUP 1ST LINE

  const uint8_t octant1 = GetLineOctant(v1x, v1y, v3x, v3y);
  SwitchToOctantOne(octant1, v1x, v1y);
  SwitchToOctantOne(octant1, v3x, v3y);
  int dx1 = v3x - v1x;
  int dy1 = v3y - v1y;

  int e1 = dx1;
  dx1 *= 2;
  dy1 *= 2;

  while (v1x <= v3x)
  {
    SwitchFromOctantOne(octant1, v1x, v1y);
    SwitchFromOctantOne(octant1, v3x, v3y);

    SwitchToOctantOne(octant2, v2x, v2y);
    SwitchToOctantOne(octant2, v3x, v3y);

    if (v2x <= v3x)
    {
      SwitchFromOctantOne(octant2, v2x, v2y);
      DrawHorizontalLine(v1x, v2x, v2y, target);
      SwitchToOctantOne(octant2, v2x, v2y);
      ++v2x;
      e2 += dy2;
      if (e2 > 0)
      {
        ++v2y;
        e2 -= dx2;
      }
    }

    SwitchFromOctantOne(octant2, v2x, v2y);
    SwitchFromOctantOne(octant2, v3x, v3y);

    SwitchToOctantOne(octant1, v1x, v1y);
    SwitchToOctantOne(octant1, v3x, v3y);
    ++v1x;
    e1 += dy1;
    if (e1 > 0)
    {
      ++v1y;
      e1 -= dx1;
    }
  }
}


void Rasterizer::DrawBottomFlatTriangle(const std::vector<Vertex>& p_triangle, Texture* p_target)
{
	int v1x = p_triangle[0].GetPosition().m_x;
	int v1y = p_triangle[0].GetPosition().m_y;

	int v2x = p_triangle[1].GetPosition().m_x;
	int v2y = p_triangle[1].GetPosition().m_y;

	int v3x = p_triangle[2].GetPosition().m_x;
	int v3y = p_triangle[2].GetPosition().m_y;

	//SETUP 2ND LINE
	const uint8_t octant2 = GetLineOctant(v3x, v3y, v1x, v1y);
	SwitchToOctantOne(octant2, v3x, v3y);
	SwitchToOctantOne(octant2, v1x, v1y);
	int dx2 = v1x - v3x;
	int dy2 = v1y - v3y;

	int e2 = dx2;
	dx2 *= 2;
	dy2 *= 2;

	SwitchFromOctantOne(octant2, v3x, v3y);
	SwitchFromOctantOne(octant2, v1x, v1y);


	//SETUP 1st LINE
	const uint8_t octant1 = GetLineOctant(v2x, v2y, v1x, v1y);
	SwitchToOctantOne(octant1, v2x, v2y);
	SwitchToOctantOne(octant1, v1x, v1y);
	int dx1 = v1x - v2x;
	int dy1 = v1y - v2y;

	int e1 = dx1;
	dx1 *= 2;
	dy1 *= 2;

	while (v2x <= v1x)
	{
		SwitchFromOctantOne(octant1, v2x, v2y);
		SwitchFromOctantOne(octant1, v1x, v1y);

		if (v2y < v3y)
		{
			SwitchToOctantOne(octant2, v3x, v3y);
			SwitchToOctantOne(octant2, v1x, v1y);
			if (v3x <= v1x)
			{
				SwitchFromOctantOne(octant2, v3x, v3y);
				DrawHorizontalLine(v2x, v3x, v3y, p_target);
				SwitchToOctantOne(octant2, v3x, v3y);
				++v3x;
				e2 += dy2;
				if (e2 > 0)
				{
					++v3y;
					e2 -= dx2;
				}
			}

			SwitchFromOctantOne(octant2, v3x, v3y);
			SwitchFromOctantOne(octant2, v1x, v1y);
		}

		SwitchToOctantOne(octant1, v2x, v2y);
		SwitchToOctantOne(octant1, v1x, v1y);
		++v2x;
		e1 += dy1;
		if (e1 > 0)
		{
			++v2y;
			e1 -= dx1;
		}
	}
}


void Rasterizer::DrawHorizontalLine(unsigned int x1, unsigned int x2, unsigned int y, Texture* p_target)
{
	if (x1 > x2) std::swap(x1, x2);
	for (int x = x1; x <= x2; ++x)
	{
		p_target->SetPixelColor(x, y, Color(255, 255, 255));
	}
}


void Rasterizer::DrawLine(int x1, int y1, int x2, int y2, Texture* target) 
{ 
  Color pixelColor(255, 255, 255); 
  uint8_t octant = GetLineOctant(x1, y1, x2, y2); 
  SwitchToOctantOne(octant, x1, y1); 
  SwitchToOctantOne(octant, x2, y2); 
  int dx = x2 - x1; 
  int dy = y2 - y1; 
 
  int e = dx; 
  dx *= 2; 
  dy *= 2; 
 
  while (x1 <= x2) 
  { 
    SwitchFromOctantOne(octant, x1, y1); 
//    pTarget->SetPixelColor(x1, y1, pixelColor); 
    std::cout << x1 << " " << y1 << std::endl; 
    SwitchToOctantOne(octant, x1, y1); 
    ++x1; 
    e -= dy; 
    if (e < 0) 
    { 
      ++y1; 
      e += dx; 
    } 
  } 
} 
 


void Rasterizer::SortVerticesBy(std::vector<Vertex>& p_vertices, bool x, bool y, bool z)
{
  int coord = 1;
  if (x) coord = 0;
  else if (z) coord = 2;

  std::sort(p_vertices.begin(), p_vertices.end(), [coord](const Vertex & a, const Vertex & b) -> bool
  {
    return a.GetPosition()[coord] < b.GetPosition()[coord];
  });
}

Vec4 Rasterizer::TransformPos(const Vertex& v, Mat4 transform)
{
  return transform * Vec4(v.GetPosition());
}

void Rasterizer::WorldToScreenCoord(int worldWidth, int worldHeight, 
                  int screenWidth, int screenHeight, 
                  const Vec3& pos, int& targetX, int& targetY)
{
  targetX = static_cast<int>(((pos.m_x / worldWidth) + 1) * 0.5f * screenWidth);
  targetY = static_cast<int>(((pos.m_y / worldHeight) + 1) * 0.5f * screenHeight);
}


uint8_t Rasterizer::GetLineOctant(int x1, int y1, int x2, int y2) 
{ 
  int dx = x2 - x1; 
  int dy = y2 - y1; 
 
  if(dx > 0) 
  { 
    if(dy > 0) 
    { 
      if(dx >= dy) return 1; 
      else return 2; 
    } 
    else 
    { 
      if (dx >= -dy) return 8; 
      else return 7; 
    } 
  } 
  else 
  { 
    if (dy > 0) 
    { 
      if (-dx >= dy) return 4; 
      else return 3; 
    } 
    else 
    { 
      if (dx <= dy) return 5; 
      else return 6; 
    } 
  } 
} 
 
void Rasterizer::SwitchToOctantOne(const uint8_t octant, int& x, int& y) 
{ 
  switch (octant) 
  { 
  case 1:    // X,Y 
    return; 
  case 2:    // Y,X 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 3:    // Y,-X 
    x = -x; 
 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 4:    // -X,Y 
    x = -x; 
    break; 
  case 5:    // -X,-Y 
    x = -x; 
    y = -y; 
    break; 
  case 6:    // -Y,-X 
    x = -x; 
    y = -y; 
 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 7:    // -Y,X 
    y = -y; 
 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 8:    // X,-Y 
    y = -y; 
    break; 
  default: 
    break; 
  } 
} 
 
void Rasterizer::SwitchFromOctantOne(const uint8_t octant, int& x, int& y) 
{ 
  switch (octant) 
  { 
  case 1:    // X,Y 
    return; 
  case 2:    // Y,X 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 3:    // -Y,X 
    y = -y; 
 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 4:    // -X,Y 
    x = -x; 
    break; 
  case 5:    // -X,-Y 
    x = -x; 
    y = -y; 
    break; 
  case 6:    // -Y,-X 
    x = -x; 
    y = -y; 
 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 7:    // Y,-X 
    x = -x; 
 
    x ^= y; 
    y ^= x; 
    x ^= y; 
    break; 
  case 8:    // X,-Y 
    y = -y; 
    break; 
  default: 
    break; 
  } 
} 



Mat4 Rasterizer::CreatePerspectiveProjectionMatrix(const int& p_width, const int& p_height, const float& p_near,
	const float& p_far, const float& p_fov)
{
	const float ratio = p_width / (float)p_height;
	const float dist = p_far - p_near;
	const float scale = 1 / tanf(p_fov * 0.5f * (float)M_PI / 180.f);

	// FOV Based perspective
	return Mat4{
		scale, 0, 0, 0,
		0, scale * ratio, 0, 0,
		0, 0, -p_far / dist, -(p_far * p_near) / dist,
		0, 0, -1, 0
	};
}

Mat4 Rasterizer::CreatePerspectiveProjectionMatrix(const float& p_left, const float& p_right, const float& p_bottom,
	const float& p_top, const float& p_near, const float& p_far)
{
	// Top-Bottom-Left-Right Based perspective
	return Mat4{
		2 * p_near / (p_right - p_left), 0, (p_right + p_left) / (p_right - p_left), 0,
		0, 2 * p_near / (p_top - p_bottom), (p_top + p_bottom) / (p_top - p_bottom), 0,
		0, 0, -(p_far + p_near) / (p_far - p_near) , -2 * p_far * p_near / (p_far - p_near),
		0, 0, -1, 0
	};
}

Mat4 Rasterizer::CreateOrthographicProjectionMatrix(const float& p_left, const float& p_right, const float& p_bottom,
	const float& p_top, const float& p_near, const float& p_far)
{
	// Orthographic Projection
	return Mat4{
		2 / (p_right - p_left), 0, 0, -(p_right + p_left) / (p_right - p_left),
		0, 2 / (p_top - p_bottom), 0, -(p_top + p_bottom) / (p_top - p_bottom),
		0, 0, -2 / (p_far - p_near) , -(p_far + p_near) / (p_far - p_near),
		0, 0, 0, 1
	};
}