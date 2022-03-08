#include "gameConstants.h"

std::shared_ptr<Texture> CHAIN_TEX = nullptr;
std::shared_ptr<Texture> SPRUCE_PLANKS_TEX = nullptr;
std::shared_ptr<Texture> DARK_OAK_PLANKS_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_BRICKS_TEX = nullptr;
std::shared_ptr<Texture> CRACKED_DEEPSLATE_BRICKS_TEX = nullptr;
std::shared_ptr<Texture> MOSSY_DEEPSLATE_BRICKS_TEX = nullptr;
std::shared_ptr<Texture> PORTAL_TEX = nullptr;
std::shared_ptr<Texture> TORCH_TEX = nullptr;
std::shared_ptr<Texture> FLAME_TEX = nullptr;
std::shared_ptr<Texture> CROSSHAIR_TEX = nullptr;
std::shared_ptr<Texture> STEVE_TEX = nullptr;
std::shared_ptr<Texture> SKELETON_TEX = nullptr;

void GameConstants::load_textures() {
    //
    STEVE_TEX = Texture::load("resources/steve.png", true, true);
    SKELETON_TEX = Texture::load("resources/skeleton.png", true, true);
    PORTAL_TEX = Texture::load("resources/portal.png", true);
    CHAIN_TEX = Texture::load("resources/chain.png", true);
    SPRUCE_PLANKS_TEX = Texture::load("resources/spruce_planks.png", true);
    DARK_OAK_PLANKS_TEX = Texture::load("resources/dark_oak_planks.png", true);
    TORCH_TEX = Texture::load("resources/torch.png", true);
    FLAME_TEX = Texture::load("resources/flame.png", true);
    DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/deepslate_bricks.png", true);
    CRACKED_DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/cracked_deepslate_bricks.png", true);
    MOSSY_DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/mossy_deepslate_bricks.png", true);

    //
    CROSSHAIR_TEX = Texture::load("resources/crosshair013.png", true);
}
