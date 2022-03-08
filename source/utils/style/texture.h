#ifndef SOURCE_UTILS_STYLE_TEXTURE_H_
#define SOURCE_UTILS_STYLE_TEXTURE_H_

#include <string>
#include <memory>

class Texture {
    private:
        unsigned int id;
        int width, height, channels;

    public:
        Texture();
        ~Texture();

        static std::shared_ptr<Texture> load(
            std::string file_path,
            bool mipmap = false, bool not_flip = false);

        void bind();
        void unbind();
};

#endif  // SOURCE_UTILS_STYLE_TEXTURE_H_
