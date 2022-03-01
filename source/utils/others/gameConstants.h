#ifndef SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_
#define SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_

#include "../style/texture.h"
#include <memory>

extern std::shared_ptr<Texture> STONE_TEX;
extern std::shared_ptr<Texture> BRICKS_TEX;
extern std::shared_ptr<Texture> ANDESITE_TEX;
extern std::shared_ptr<Texture> COAL_TEX;
extern std::shared_ptr<Texture> COBBLESTONE_TEX;
extern std::shared_ptr<Texture> OAK_PLANKS_TEX;
extern std::shared_ptr<Texture> SPRUCE_PLANKS_TEX;
extern std::shared_ptr<Texture> DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> MOSSY_DEEPSLATE_BRICKS_TEX;

namespace GameConstants {
    void load_textures();
};

#endif  // SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_
