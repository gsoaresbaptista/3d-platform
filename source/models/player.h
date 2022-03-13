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
    float yaw;
    float pitch;
    float block_size;
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

        //
        GLboolean idle;
        GLboolean walking;
        GLfloat angles[22];
        GLfloat accumulated_time_bow_animation;
        GLfloat accumulated_time_leg_animation;
        GLfloat accumulated_time_idle_animation;
        GLint bow_animation_angle_id;
        GLint idle_animation_angle_id;
        GLint leg_animation_angle_id;
        GLint bow_state_id;
        GLboolean returning;

        virtual void display_character();
        GLboolean show_collision_boundary;

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
        virtual GLfloat get_on_air_time();
        virtual GLboolean is_falling();
        virtual GLboolean is_rising();
        virtual void set_falling(GLboolean flag);
        virtual void set_rising(GLboolean flag);
        virtual void clear_on_air_time();
        virtual void increment_on_air_time(GLfloat dt);

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
        void set_show_collision_boundary(GLboolean value);
        void clear_walking();
        void set_returning();

        //
        void increment_bow_animation(float dt);

        void display(float dt);

        //
        bool ready2shoot();
        vec3 get_hand_position();
};

#endif  // SOURCE_MODELS_PLAYER_H_
