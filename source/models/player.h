#ifndef SOURCE_MODELS_PLAYER_H_
#define SOURCE_MODELS_PLAYER_H_

#include "../utils/math/math.h"
#include "../utils/shapes/shape.h"
#include "../utils/shapes/3d/cylinder.h"

struct CoordinateSystem {
    vec3 position;
    vec3 direction;
    vec3 left;
    vec3 up;
};


class Player: public Shape {
    private:
        Cylinder* collision_boundary;
        GLfloat height;
        CoordinateSystem* coordinateSystem;

        //
        GLboolean falling;
        GLboolean rising;
        GLfloat on_air_time;

    public:
        Player(vec3 center, GLfloat height);
        ~Player();

        void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void move_left_right(GLfloat direction);
        void move_forward_backward(GLfloat direction);
        void move_up(GLfloat direction);

        //
        GLfloat get_on_air_time();
        GLboolean is_falling();
        GLboolean is_rising();
        void set_falling(GLboolean flag);
        void set_rising(GLboolean flag);
        void clear_on_air_time();
        void increment_on_air_time(GLfloat dt);

        //
        GLfloat get_feet_height();

        CoordinateSystem* get_coordinate_system();
        void set_coordinate_system(CoordinateSystem* system);
        void set_y(GLfloat y);

        void display(float dt);
};

#endif  // SOURCE_MODELS_PLAYER_H_
