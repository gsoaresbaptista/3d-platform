#include "game.h"
#include "../utils/others/gameConstants.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "../utils/shapes/2d/rectangle.h"
#include "../controllers/mouseListener.h"

#define acceleration (-player->get_on_air_time() * block_size * 18.0)

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
    this->player_jump_speed = block_size * 14;
    this->enemies = data->enemies;

    // Create player
    this->player = new Player(data->player_pos, data->block_size);

    //
    this->crosshair  = Plane(
        vec3(-0.08, 0.08, 0),
        vec3(-0.08, -0.08, 0),
        vec3(0.08, -0.08, 0),
        vec3(0.08, 0.08, 0),
        vec3(0, 0, 0));

    //
    this->defaultCamera = new DefaultCamera(
        this->player->get_coordinate_system(),
        player->get_center());

    this->orbitalCamera = new OrbitalCamera(
        this->player->get_coordinate_system(),
        player->get_center(),
        block_size);

    this->freeCamera = new FreeCamera(
        this->player->get_coordinate_system(),
        this->data, this->block_size);

    // Create camera
    this->update_camera_type();

    //
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
}

void Game::create_lights() {
    for (int i = 0; i < 3; i++) {
        vec3 c0 = data->torchs[i]->get_center();
        c0.z += block_size;
        c0.y += block_size;

        float light0[4][4] = {
            { 0.08, 0.08, 0.08, 0.0f },  // ambient
            { 0.30, 0.30, 0.30, 1.f },  // diffuse
            { 0.05, 0.05, 0.05, 0.3f },  // specular
            { c0.x, c0.y, c0.z, 1.f },  // position
        };

        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, &light0[0][0]);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, &light0[1][0]);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, &light0[2][0]);
        glLightfv(GL_LIGHT0 + i, GL_POSITION, &light0[3][0]);
    }
}

GLfloat Game::get_width() {
    return this->data->arena_width;
}

GLfloat Game::get_height() {
    return this->data->arena_height;
}

GLfloat Game::get_depth() {
    return this->data->arena_depth;
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

    for (auto& enemy : enemies) {
        enemy->draw();
    }
}

void Game::gravity(float dt) {
    if ((player->is_falling() || player->is_rising())) {
        if ((player->is_rising()) &&
            (this->player_jump_speed + acceleration <= 0)) {
            //
            player->set_rising(false);
            player->set_falling(true);
            this->player->clear_on_air_time();
        } else {
            if ((player->get_feet_height() + acceleration * dt >= 0) &&
                (!obstacle_collision(
                    vec3(0, acceleration * dt, 0)))) {
                //
                this->player->move_up(acceleration * dt);
            } else {
                this->player->set_rising(false);
                this->player->set_falling(false);
                this->player->clear_on_air_time();
            }
            //
            if (player->get_feet_height() + acceleration*dt <= 0) {
                player->set_y(0);
            }
        }
    } else if (!obstacle_collision(vec3(0, acceleration * dt, 0))) {
        this->player->move_up(acceleration * dt);
        player->set_falling(true);
    }
}

bool Game::obstacle_collision(vec3 movement) {
    //
    CoordinateSystem* coord = player->get_coordinate_system();
    vec3 pos = coord->position + player->get_center() + movement;

    for (auto& obstacle : obstacles) {
        vec3 center = obstacle->get_center();
        double w2 = obstacle->get_width()/2.f;
        double h2 = obstacle->get_height()/2.f;
        double d2 = obstacle->get_depth()/2.f;

        if ((pos.x + block_size/2.f > center.x - w2) &&
            (pos.x - block_size/2.f < center.x + w2) &&
            (pos.y + block_size > center.y - h2) &&
            (pos.y - block_size < center.y + h2) &&
            (pos.z + block_size/2.f > center.z - d2) &&
            (pos.z - block_size/2.f < center.z + d2)) {
            //
            return true;
        }
    }
    return false;
}

void Game::update_player_move(float dt) {
    vec3 movement;
    CoordinateSystem* coord = player->get_coordinate_system();

    if (controller->keys['d']) {
        if (current_camera == 4) {
            movement = coord->direction * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_forward_backward(movement);
            }

        } else {
            movement = coord->left * -1 * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_left_right(movement);
            }
        }
    } else if (controller->keys['a']) {
        if (current_camera == 4) {
            movement = coord->direction * -1 * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_forward_backward(movement);
            }
        } else {
            movement = coord->left * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_left_right(movement);
            }
        }
    }

    if (controller->keys['w']) {
        if (current_camera == 4) {
            movement = coord->left * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_left_right(movement);
            }

        } else {
            movement = coord->direction * dt * player_speed;
            movement.y = 0;

            if (!obstacle_collision(movement)) {
                player->move_forward_backward(movement);

            } else {
                vec3 movement0 = vec3(movement.x, 0, 0);
                vec3 movement1 = vec3(0, 0, movement.z);

                if (!obstacle_collision(movement0)) {
                    player->move_forward_backward(movement0);
                } else if (!obstacle_collision(movement1)) {
                    player->move_forward_backward(movement1);
                }
            }
        }
    } else if (controller->keys['s']) {
        if (current_camera == 4) {
            movement = coord->left * -1 * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_left_right(movement);
            }

        } else {
            movement = coord->direction * -1 * dt * player_speed;

            if (!obstacle_collision(movement)) {
                player->move_forward_backward(movement);
            }
        }
    }
}

// TODO(all): Arrumar quando solta o espaço durante a queda
//            dps de segurar até a velocidade ficar negativa.
void Game::update_player_jump(float dt) {
    // Jump logic

    if ((this->controller->keys[' ']) && (this->player->is_rising() ||
        (!this->player->is_rising() && !this->player->is_falling()))) {
        //
        if (!obstacle_collision(vec3(0, this->player_jump_speed*dt, 0))) {
            // Pressing space, in floor or rising
            this->player->set_rising(true);
            this->player->move_up(this->player_jump_speed*dt);
            player->increment_on_air_time(dt);

        } else {
            this->player->set_rising(false);
            this->player->set_falling(true);
            this->player->clear_on_air_time();
        }
    } else if (this->player->is_falling()) {
        // Player falling, increment time falling
        player->increment_on_air_time(dt);

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
        this->camera = this->defaultCamera;

        //
        first = false;
        MouseListener::set_camera((DefaultCamera*)this->camera);

    } else if (controller->keys['3'] && current_camera != 3) {
        this->current_camera = 3;
        this->camera = this->orbitalCamera;

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
        this->camera = this->freeCamera;
        this->controller->to_rotate.x = 0;
        this->controller->to_rotate.y = 0;

        //
        first = false;
        MouseListener::clear_camera();
    }
}

void Game::update_controller(float dt) {
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
    this->update_controller(dt);
    this->camera->update();

    // Update player position
    this->gravity(dt);
    this->update_player_move(dt);
    this->update_player_jump(dt);
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
        if (current_camera <= 2)
            this->crosshair.draw(CROSSHAIR_TEX);
}

void Game::display(float dt) {
    //
    this->update(dt);

    //
    glLoadIdentity();
    this->camera->activate();

    //
    this->create_lights();

    //
    glColor3f(1, 1, 1);

    // Draw arena obstacles
    for (auto& obstacle : obstacles) {
        obstacle->display(dt, controller);
    }

    this->player->display(dt);

    for (auto& enemy : enemies) {
        enemy->display(dt);
    }

    this->display_hud();
}
