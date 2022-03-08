#ifndef SOURCE_UTILS_STYLE_MATERIAL_H_
#define SOURCE_UTILS_STYLE_MATERIAL_H_

class Material {
    private:
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float shininess;
        float emission[4];
    public:
        Material(
            float amb_r, float amb_g, float amb_b,
            float diff_r, float diff_g, float diff_b,
            float spec_r, float spec_g, float spec_b,
            float _shininess,
            float emiss_r = 0, float emiss_g = 0, float emiss_b = 0);
        ~Material();
        void activate();
};

#endif  // SOURCE_UTILS_STYLE_MATERIAL_H_
