#ifndef SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_
#define SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_

#include "../style/texture.h"
#include <memory>

enum class BoxType {
    DEEPSLATE_BRICKS = 0,
    SPRUCE = 1,
    CHAIN = 2,
    DARK_OAK = 3,
    PORTAL = 4,
    TORCH = 5
};

extern std::shared_ptr<Texture> CHAIN_TEX;
extern std::shared_ptr<Texture> DARK_OAK_PLANKS_TEX;
extern std::shared_ptr<Texture> SPRUCE_PLANKS_TEX;
extern std::shared_ptr<Texture> DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> CRACKED_DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> MOSSY_DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> PORTAL_TEX;

namespace GameConstants {
    void load_textures();
};

#endif  // SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_
