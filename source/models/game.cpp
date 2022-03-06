#include "game.h"
#include "../utils/others/gameConstants.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "camera/freeCamera.h"
#include "camera/defaultCamera.h"
#include "camera/orbitalCamera.h"
#include "../utils/shapes/2d/rectangle.h"
#include "../controllers/mouseListener.h"

#define acceleration (-player->get_on_air_time() * block_size/3.0)

Game::Game(
        std::shared_ptr<SVGData> data,
        std::shared_ptr<ControllerData> flags)
            : Shape(vec3(data->arena_width/2.0,
                data->arena_height/2.0,
                data->arena_depth/2.0)) {
    this->obstacles = data->rects;
    this->block_size = data->block_size;
    this->data = data;
    this->controller = flags;
    this->current_camera = 4;
    this->player_speed = block_size * 3.5;
    this->player_jump_speed = block_size * 0.24;

    // Create player
    this->player = new Player(data->player_pos, data->block_size);

    // Create camera
    this->update_camera_type();

    //
    this->crosshair  = Plane(
        vec3(-0.08, 0.08, 0),
        vec3(-0.08, -0.08, 0),
        vec3(0.08, -0.08, 0),
        vec3(0.08, 0.08, 0));
}

void Game::draw(
        std::shared_ptr<Texture> texture,
        GLenum mode,
        Outline outline) {
    // Draw all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->draw_block(block_size, GL_FILL);
    }

    this->player->draw();
}

void Game::gravity(float dt) {
    if ((player->is_falling() || player->is_rising())) {
        // float acceleration = -player->get_on_air_time() * block_size/3.f * dt;

        if (player->is_rising() && (this->player_jump_speed + acceleration * dt <= 0)) {
            player->set_rising(false);
            player->set_falling(true);
            this->player->clear_on_air_time();
        }

        // TODO(all): Verificar aqui as plataformos além do >= 0
        if (player->get_feet_height() + acceleration * dt >= 0 && !floor_collision_obstacle(dt)) {
        // if ((player->get_feet_height() + acceleration >= 0) &&
            // !this->player_will_collide(vec3(0, acceleration, 0))) {
            this->player->move_up(acceleration);
        } else {
            this->player->set_rising(false);
            this->player->set_falling(false);
            // this->player->set_y(0);
            this->player->clear_on_air_time();
        }
    }
}

bool Game::x_obstacle_collision(float dt, GLfloat x_player, GLfloat radius, std::shared_ptr<Shape> obstacle) {
    GLfloat x_obstacle = obstacle->get_center().x;
    GLfloat width_obstacle = obstacle->get_width();

    if ((x_player + dt * player_speed + radius > x_obstacle - width_obstacle/2.0) &&
        (x_player + dt * player_speed - radius < x_obstacle + width_obstacle/2.0) && 
        x_obstacle > 0) {
            return true;
        }
    
    return false;
}

bool Game::y_obstacle_collision(GLfloat head_player, GLfloat feet_player, std::shared_ptr<Shape> obstacle) {
    GLfloat y_obstacle = obstacle->get_center().y;
    GLfloat height_obstacle = obstacle->get_height();

    if (feet_player < y_obstacle + height_obstacle/2.0 &&
         head_player > y_obstacle - height_obstacle/2.0) {
        return true;
    }

    return false;
}

bool Game::lateral_collision(float dt) {
    GLfloat x_player = this->player->get_position().x + this->player->get_center().x;
    GLfloat radius = this->player->get_collision_radius();
    GLfloat head_player = this->player->get_head_height();
    GLfloat feet_player = this->player->get_feet_height();

    for (auto& obstacle : obstacles) {
        if (x_obstacle_collision(dt, x_player, radius, obstacle) &&
         y_obstacle_collision(head_player, feet_player, obstacle)) {
             return true;
         }
    }
    return false;
}

bool Game::floor_collision_obstacle(float dt) {
    GLfloat x_player = this->player->get_position().x + this->player->get_center().x;
    GLfloat radius = this->player->get_collision_radius();
    GLfloat head_player = this->player->get_head_height();
    GLfloat feet_player = this->player->get_feet_height();
    GLfloat on_air_time = this->player->get_on_air_time();

    for (auto& obstacle: obstacles) {
        GLfloat y_obstacle = obstacle->get_center().y;
        GLfloat height_obstacle = obstacle->get_height();

        if (feet_player + acceleration * dt < y_obstacle + height_obstacle/2.0 &&
            head_player + acceleration * dt > y_obstacle - height_obstacle/2.0 &&
            x_obstacle_collision(0, x_player, radius, obstacle)) {

            this->player->set_y(y_obstacle + height_obstacle/2.0);
            return true;
        }
    }

    return false;
}


void Game::update_player_move(float dt) {
    if (controller->keys['d']) {
        if (current_camera == 4){
            if (!lateral_collision(dt)) 
                player->move_forward_backward(player_speed * dt);
            }
        else
            player->move_left_right(-player_speed * dt);

    } else if (controller->keys['a']) {
        if (current_camera == 4){
            if (!lateral_collision(-dt)) 
                player->move_forward_backward(-player_speed * dt);
        }
        else
            player->move_left_right(player_speed * dt);
    }

    if (controller->keys['w']) {
        if (current_camera == 4)
            player->move_left_right(player_speed * dt);
        else
            player->move_forward_backward(player_speed * dt);

    } else if (controller->keys['s']) {
        if (current_camera == 4)
            player->move_left_right(-player_speed * dt);
        else
            player->move_forward_backward(-player_speed * dt);
    }
}

void Game::update_player_jump(float dt) {
    // Jump logic
    static bool first_falling = true;

    if (this->controller->keys[' '] && (this->player->is_rising() ||
        (!this->player->is_rising() && !this->player->is_falling()))) {
        // Pressing space, in floor or rising
        this->player->set_rising(true);
        this->player->move_up(this->player_jump_speed);
        player->increment_on_air_time(dt);
        first_falling = true;

    } else if (this->player->is_falling()) {
        // Player falling, clear on_air_time and increment time falling
        if (first_falling) {
            first_falling = false;
            this->player->clear_on_air_time();
        } else {
            player->increment_on_air_time(dt);
        }

    } else if (!this->controller->keys[' '] && this->player->is_rising()) {
        // Space key up, update player conditition
        this->player->clear_on_air_time();
        this->player->set_rising(false);
        this->player->set_falling(true);
    }
}

void Game::update_camera_type() {
    static bool first = true;

    if (controller->keys['1'] && current_camera != 1 || first) {
        this->current_camera = 1;
        this->camera = new DefaultCamera(
            this->player->get_coordinate_system(),
            player->get_center());

        //
        first = false;
        MouseListener::set_camera((DefaultCamera*)this->camera);

    } else if (controller->keys['3'] && current_camera != 3) {
        this->current_camera = 3;
        this->camera = new OrbitalCamera(
            this->player->get_coordinate_system(),
            player->get_center(),
            block_size);

        //
        first = false;
        controller->move_orbital_camera = false;
        MouseListener::set_camera((OrbitalCamera*)this->camera);

    } else if (controller->keys['4'] && current_camera != 4) {
        //
        CoordinateSystem* coord = new CoordinateSystem();
        coord->direction = vec3(1, 0, 0);
        coord->left = vec3(0, 0, -1);
        coord->position = player->get_coordinate_system()->position;
        coord->up = vec3(0, 1, 0);
        this->player->set_coordinate_system(coord);

        //
        this->current_camera = 4;
        this->camera = new FreeCamera(
            this->player->get_coordinate_system(),
            this->data, this->block_size);


        //
        first = false;
        MouseListener::clear_camera();
    }
}

void Game::update_mouse(float dt) {
    if (current_camera == 1) {
        DefaultCamera* cam = (DefaultCamera*)this->camera;
        this->controller->to_rotate.x = cam->get_yaw();
        this->controller->to_rotate.y = cam->get_pitch();

    } else if (current_camera == 3) {
        OrbitalCamera* orbital = (OrbitalCamera*)this->camera;

        if (controller->keys['+']) {
            orbital->zoom_in();
        } else if (controller->keys['-']) {
            orbital->zoom_out();
        }

        if (controller->keys['x']) {
            controller->keys['x'] = false;
            controller->move_orbital_camera = !controller->move_orbital_camera;
        }
    }
}

void Game::update(float dt) {
    //
    if (controller->keys[27]) {
        glutLeaveMainLoop();
    }

    //
    this->update_camera_type();
    this->update_mouse(dt);
    this->camera->update();

    // Update player position
    this->update_player_move(dt);
    this->update_player_jump(dt);
    this->gravity(dt);
}

void Game::display_hud() {
    // Draw static info, first set ortogonal projection
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    // Clear the model_view matrix
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    // Draw static info
        glColor3f(1, 0, 0);
        if (current_camera <= 2)
            this->crosshair.draw(CROSSHAIR_TEX);
}

void Game::display(float dt) {
    //
    this->update(dt);

    //
    glLoadIdentity();
    this->camera->activate();
    this->player->display(dt);

    // Draw arena obstacles
    for (auto& obstacle : obstacles) {
        obstacle->display(dt, controller);
    }

    this->display_hud();
}
