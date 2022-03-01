#include "gameConstants.h"

std::shared_ptr<Texture> CHAIN_TEX = nullptr;
std::shared_ptr<Texture> STONE_TEX = nullptr;
std::shared_ptr<Texture> BRICKS_TEX = nullptr;
std::shared_ptr<Texture> ANDESITE_TEX = nullptr;
std::shared_ptr<Texture> COAL_TEX = nullptr;
std::shared_ptr<Texture> COBBLESTONE_TEX = nullptr;
std::shared_ptr<Texture> OAK_PLANKS_TEX = nullptr;
std::shared_ptr<Texture> SPRUCE_PLANKS_TEX = nullptr;
std::shared_ptr<Texture> DARK_OAK_PLANKS_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_BRICKS_TEX = nullptr;
std::shared_ptr<Texture> CRACKED_DEEPSLATE_BRICKS_TEX = nullptr;
std::shared_ptr<Texture> MOSSY_DEEPSLATE_BRICKS_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_COAL_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_DIAMOND_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_REDSTONE_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_GOLD_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_IRON_TEX = nullptr;
std::shared_ptr<Texture> DEEPSLATE_TEX = nullptr;
std::shared_ptr<Texture> PORTAL_TEX = nullptr;

void GameConstants::load_textures() {
    PORTAL_TEX = Texture::load("resources/portal.png", true);
    CHAIN_TEX = Texture::load("resources/chain.png", true);
    STONE_TEX = Texture::load("resources/stone.png", true);
    BRICKS_TEX = Texture::load("resources/bricks.png", true);
    ANDESITE_TEX = Texture::load("resources/andesite.png", true);
    COAL_TEX = Texture::load("resources/coal_ore.png", true);
    COBBLESTONE_TEX = Texture::load("resources/cobblestone.png", true);
    OAK_PLANKS_TEX = Texture::load("resources/oak_planks.png", true);
    SPRUCE_PLANKS_TEX = Texture::load("resources/spruce_planks.png", true);
    DARK_OAK_PLANKS_TEX = Texture::load("resources/dark_oak_planks.png", true);
    DEEPSLATE_TEX = Texture::load("resources/deepslate_tiles.png", true);
    DEEPSLATE_COAL_TEX = Texture::load(
        "resources/deepslate_coal_ore.png", true);
    DEEPSLATE_IRON_TEX = Texture::load(
        "resources/deepslate_iron_ore.png", true);
    DEEPSLATE_GOLD_TEX = Texture::load(
        "resources/deepslate_gold_ore.png", true);
    DEEPSLATE_DIAMOND_TEX = Texture::load(
        "resources/deepslate_diamond_ore.png", true);
    DEEPSLATE_REDSTONE_TEX = Texture::load(
        "resources/deepslate_redstone_ore.png", true);
    DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/deepslate_bricks.png", true);
    CRACKED_DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/cracked_deepslate_bricks.png", true);
    MOSSY_DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/mossy_deepslate_bricks.png", true);
}
