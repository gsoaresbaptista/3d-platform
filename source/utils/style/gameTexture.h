#ifndef SOURCE_UTILS_STYLE_GAMETEXTURE_H_
#define SOURCE_UTILS_STYLE_GAMETEXTURE_H_

#include "texture.h"
#include <memory>

extern std::shared_ptr<Texture> STONE_TEX;
extern std::shared_ptr<Texture> BRICKS_TEX;
extern std::shared_ptr<Texture> ANDESITE_TEX;
extern std::shared_ptr<Texture> COAL_TEX;
extern std::shared_ptr<Texture> COBBLESTONE_TEX;
extern std::shared_ptr<Texture> OAK_PLANKS_TEX;
extern std::shared_ptr<Texture> SPRUCE_PLANKS_TEX;

namespace GameTexture {
    void load();
};

#endif  // SOURCE_UTILS_STYLE_GAMETEXTURE_H_
