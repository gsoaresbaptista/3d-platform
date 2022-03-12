#include "gameConstants.h"
#include "objReader.h"

// Textures
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
std::shared_ptr<Texture> BOW_TEX = nullptr;
std::shared_ptr<Texture> ARROW_TEX = nullptr;

// Materials
std::shared_ptr<Material> STONE_MATERIAL = nullptr;
std::shared_ptr<Material> WOOD_MATERIAL = nullptr;
std::shared_ptr<Material> PORTAL_MATERIAL = nullptr;

// Models
GLuint BOW_MODEL[80];
GLuint ARROW_MODEL;

void GameConstants::load_materials() {
    STONE_MATERIAL = std::make_shared<Material>(
        0.3f, 0.3f, 0.3f,  // Ambient
        0.8f, 0.8f, 0.8f,  // Diffuse
        0.05f, 0.05f, 0.05f,  // Specular
        0.5f);
    WOOD_MATERIAL = std::make_shared<Material>(
        0.3f, 0.3f, 0.3f,  // Ambient
        0.8f, 0.8f, 0.8f,  // Diffuse
        0.5f, 0.5f, 0.5f,  // Specular
        0.8f);
    PORTAL_MATERIAL = std::make_shared<Material>(
        1.0f, 1.0f, 1.0f,  // Ambient
        1.0f, 1.0f, 1.0f,  // Diffuse
        1.0f, 1.0f, 1.0f,  // Specular
        1.0f,
        1.0f, 1.0f, 1.0f);
}

void GameConstants::load_textures() {
    STEVE_TEX = Texture::load(
        "resources/textures/steve.png", true, true);
    SKELETON_TEX = Texture::load(
        "resources/textures/skeleton.png", true, true);
    PORTAL_TEX = Texture::load(
        "resources/textures/portal.png", true);
    CHAIN_TEX = Texture::load(
        "resources/textures/chain.png", true);
    SPRUCE_PLANKS_TEX = Texture::load(
        "resources/textures/spruce_planks.png", true);
    DARK_OAK_PLANKS_TEX = Texture::load(
        "resources/textures/dark_oak_planks.png", true);
    TORCH_TEX = Texture::load(
        "resources/textures/torch.png", true);
    FLAME_TEX = Texture::load(
        "resources/textures/flame.png", true);
    DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/textures/deepslate_bricks.png", true);
    CRACKED_DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/textures/cracked_deepslate_bricks.png", true);
    MOSSY_DEEPSLATE_BRICKS_TEX = Texture::load(
        "resources/textures/mossy_deepslate_bricks.png", true);
    CROSSHAIR_TEX = Texture::load(
        "resources/textures/crosshair013.png", true);
    BOW_TEX = Texture::load(
        "resources/textures/Bow_basecolor.png", false, true);
    ARROW_TEX = Texture::load(
        "resources/textures/arrow_texture.tga.png", false, true);
}

void GameConstants::load_models() {
    // Load bow models
    BOW_MODEL[0] = glGenLists(80);

    for (int i = 0; i < 80; i++) {
        BOW_MODEL[i] = BOW_MODEL[0] + i;
        char model_path[100];
        snprintf(model_path, sizeof(model_path),
            "resources/models/bow_%06d.obj", i + 1);
        ObjReader::load_obj(&BOW_MODEL[i], model_path, BOW_TEX);
    }

    // Load arrow model
    ARROW_MODEL = glGenLists(1);
    ObjReader::load_obj(&ARROW_MODEL, "resources/models/arrow.obj", ARROW_TEX);
}
