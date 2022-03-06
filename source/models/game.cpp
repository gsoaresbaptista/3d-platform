#include "game.h"
#include "../utils/others/gameConstants.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "camera/freeCamera.h"
#include "camera/defaultCamera.h"

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

    // Create player
    this->player = new Player(data->player_pos, data->block_size);

    // Create camera
    this->update_camera_type();
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
        float acceleration = -player->get_on_air_time() * block_size/3.f;

        if (player->is_rising() && (block_size * 0.24 + acceleration <= 0)) {
            player->set_rising(false);
            player->set_falling(true);
            this->player->clear_on_air_time();
        }

        // TODO(all): Verificar aqui as plataformos além do >= 0
        if (player->get_feet_height() + acceleration >= 0) {
        // if ((player->get_feet_height() + acceleration >= 0) &&
            // !this->player_will_collide(vec3(0, acceleration, 0))) {
            this->player->move_up(acceleration);
        } else {
            this->player->set_rising(false);
            this->player->set_falling(false);
            this->player->set_y(0);
            this->player->clear_on_air_time();
        }
    }
}

void Game::update_player_move(float dt) {
    if (controller->keys['d']) {
        if (current_camera == 4)
            player->move_forward_backward(block_size * 0.065);
        else
            player->move_left_right(-block_size * 0.065);

    } else if (controller->keys['a']) {
        if (current_camera == 4)
            player->move_forward_backward(-block_size * 0.065);
        else
            player->move_left_right(block_size * 0.065);
    }

    if (controller->keys['w']) {
        if (current_camera == 4)
            player->move_left_right(block_size * 0.065);
        else
            player->move_forward_backward(block_size * 0.065);

    } else if (controller->keys['s']) {
        if (current_camera == 4)
            player->move_left_right(-block_size * 0.065);
        else
            player->move_forward_backward(-block_size * 0.065);
    }
}

void Game::update_player_jump(float dt) {
    // Jump logic
    static bool first_falling = true;

    if (this->controller->keys[' '] && (this->player->is_rising() ||
        (!this->player->is_rising() && !this->player->is_falling()))) {
        // Pressing space, in floor or rising
        this->player->set_rising(true);
        this->player->move_up(block_size * 0.24);
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
        this->controller->to_rotate = vec3(0, 0, 0);

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
        this->controller->to_rotate = vec3(0, 0, 0);
        first = false;
    }
}

void Game::update_mouse(float dt) {
    if (current_camera == 1) {
        DefaultCamera* cam = (DefaultCamera*)this->camera;
        cam->increment_pitch(-controller->mouse_delta.y);
        cam->increment_yaw(-controller->mouse_delta.x);
        this->controller->to_rotate.x = cam->get_yaw();
        this->controller->to_rotate.y = cam->get_pitch();
        controller->mouse_delta = vec2(0, 0);
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

void Game::display(float dt) {
    //
    this->update(dt);

    //
    this->camera->activate();

    // Draw arena obstacles
    for (auto& obstacle : obstacles) {
        obstacle->display(dt, controller);
    }

    this->player->display(dt);
}
