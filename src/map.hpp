#include "pch.hpp"

class Map
{
  public:
	Map(const std::string &projectPath);

	void initRenderTexture(entt::registry &registry);
    void drawRenderTexture();
  private:
	ldtk::Project ldtkProject;
    float scale;

	Texture2D texture;
	RenderTexture2D renderTexture;

	entt::entity createCollider(entt::registry &registry, Rectangle collider);
};