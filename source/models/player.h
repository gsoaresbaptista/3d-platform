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
    protected:
        Cylinder* collision_boundary;
        GLfloat height;
        CoordinateSystem* coordinateSystem;

        //
        GLboolean falling;
        GLboolean rising;
        GLfloat on_air_time;

        GLuint head, body, arm0, arm1, leg0, leg1;
        GLfloat dheight;

        void display_character();

    public:
        Player(vec3 center, GLfloat height);
        ~Player();

        virtual void draw(
            std::shared_ptr<Texture> texture = nullptr,
            GLenum mode = GL_FILL,
            Outline outline = Outline::SPLITTED);

        void move_left_right(vec3 direction);
        void move_forward_backward(vec3 direction);
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
        vec3 get_position();
        GLfloat get_collision_radius();
        GLfloat get_head_height();
        void set_x(GLfloat x);
        void set_y(GLfloat y);
        void set_z(GLfloat z);
        GLfloat get_width();
        GLfloat get_height();
        GLfloat get_depth();

        virtual void display(float dt);
};

#endif  // SOURCE_MODELS_PLAYER_H_
