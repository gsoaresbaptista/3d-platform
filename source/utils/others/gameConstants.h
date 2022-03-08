#ifndef SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_
#define SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_

#include "../style/texture.h"
#include "../style/material.h"
#include <GL/gl.h>
#include <memory>

enum class BoxType {
    DEEPSLATE_BRICKS = 0,
    SPRUCE = 1,
    CHAIN = 2,
    DARK_OAK = 3,
    PORTAL = 4,
    TORCH = 5,
    FLAME = 6
};

// Materials
extern std::shared_ptr<Material> STONE_MATERIAL;
extern std::shared_ptr<Material> WOOD_MATERIAL;
extern std::shared_ptr<Material> PORTAL_MATERIAL;

// Textures
extern std::shared_ptr<Texture> CHAIN_TEX;
extern std::shared_ptr<Texture> DARK_OAK_PLANKS_TEX;
extern std::shared_ptr<Texture> SPRUCE_PLANKS_TEX;
extern std::shared_ptr<Texture> DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> CRACKED_DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> MOSSY_DEEPSLATE_BRICKS_TEX;
extern std::shared_ptr<Texture> PORTAL_TEX;
extern std::shared_ptr<Texture> TORCH_TEX;
extern std::shared_ptr<Texture> FLAME_TEX;
extern std::shared_ptr<Texture> CROSSHAIR_TEX;
extern std::shared_ptr<Texture> STEVE_TEX;
extern std::shared_ptr<Texture> SKELETON_TEX;
extern std::shared_ptr<Texture> BOW_TEX;

// Models
extern GLuint BOW_MODEL;

namespace GameConstants {
    void load_textures();
    void load_materials();
    void load_models();
};

#endif  // SOURCE_UTILS_OTHERS_GAMECONSTANTS_H_
