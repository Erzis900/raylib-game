#include "pch.hpp"

class Map
{
  public:
	Map(const std::string &projectPath);

	void initRenderTexture();
    void drawRenderTexture();

  private:
	ldtk::Project ldtkProject;
    float scale;

	Texture2D texture;
	RenderTexture2D renderTexture;
};