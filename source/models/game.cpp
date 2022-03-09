#include "game.h"
#include "../utils/others/gameConstants.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "../utils/shapes/2d/rectangle.h"
#include "../controllers/mouseListener.h"
#include "../utils/libs/imgui/imgui.h"
#include "../utils/libs/imgui/imgui_impl_glut.h"
#include "../utils/libs/imgui/imgui_impl_opengl2.h"

#define acceleration (-player->get_on_air_time() * block_size * 18.0)

static bool gravity_on = true;
static bool collision_on = true;
static bool player_collision_box = false;
static bool enemies_collision_box = false;
static float* mouse_sensitivity;

static void display_imgui() {
    {
        ImGui::SetNextWindowSize(ImVec2(0, 0));
        ImGui::SetNextWindowPos(ImVec2(5, 5));
        ImGui::Begin("Geral Settings", nullptr, 0);

        //
        ImGui::Checkbox("Player Cylinder", &player_collision_box);
        ImGui::Checkbox("Enemies Cylinder", &enemies_collision_box);

        //
        ImGui::Checkbox("Gravity", &gravity_on);
        ImGui::Checkbox("Collision", &collision_on);

        ImGui::InputFloat("Sensitivity", mouse_sensitivity, 1);

        ImGui::End();
    }
}

static void update_imgui() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    // Display menu
    display_imgui();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

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

    this->controller->disable_mouse_warp = false;
    mouse_sensitivity = &(this->controller->mouse_sensitivity);
    *mouse_sensitivity = 3;
}

void Game::create_lights() {
    for (int i = 0; i < 7; i++) {
        vec3 c0 = data->torchs[i]->get_center();
        c0.z += block_size;
        c0.y += block_size;

        float light[4][4] = {
            { 0.35, 0.35, 0.35, 0.30f },  // ambient
            { 0.80, 0.80, 0.80, 0.80f },  // diffuse
            { 0.25, 0.25, 0.25, 0.80f },  // specular
            { c0.x, c0.y, c0.z, 1.f },  // position
        };

        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, &light[0][0]);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, &light[1][0]);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, &light[2][0]);
        glLightfv(GL_LIGHT0 + i, GL_POSITION, &light[3][0]);
        glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 0.15);
        glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.005);
        glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.001);
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
    if (gravity_on) {
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
                        vec3(0, acceleration * dt, 0), this->player))) {
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
        } else if (!obstacle_collision(vec3(0, acceleration * dt, 0), this->player)) {
            this->player->move_up(acceleration * dt);
            player->set_falling(true);
        }
    }
}

bool Game::obstacle_collision(vec3 movement, Player* player) {
    if (!collision_on) return false;

    // Obstacle Collision

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

    // Player Collision

    float radius = this->player->get_collision_radius();

    for (auto& enemy : enemies) {
        vec3 center = enemy->get_center();
        float radius_distance = distance_xz(pos, center);

        if (player->get_center() == enemy->get_center()) continue;

        if (radius_distance < 2* radius &&
        (pos.y + block_size > center.y - block_size) &&
        (pos.y - block_size < center.y + block_size)) {
            //
            return true;
        }
    }

    float radius_distance = distance_xz(pos, this->player->get_center());

    if (player->get_center() == this->player->get_center()) return false;

    if (radius_distance < 2* radius &&
    (pos.y + block_size > center.y - block_size) &&
    (pos.y - block_size < center.y + block_size)) {
        //
        return true;
    }

    return false;
}

void Game::update_player_move(float dt) {
    vec3 movement;
    CoordinateSystem* coord = player->get_coordinate_system();

    if (controller->keys['d']) {
        if (current_camera == 4) {
            movement = coord->direction * dt * player_speed;

            if (!obstacle_collision(movement, this->player)) {
                player->move_forward_backward(movement);
            }

        } else {
            movement = coord->left * -1 * dt * player_speed;

            if (!obstacle_collision(movement, this->player)) {
                player->move_left_right(movement);
            }
        }
    } else if (controller->keys['a']) {
        if (current_camera == 4) {
            movement = coord->direction * -1 * dt * player_speed;

            if (!obstacle_collision(movement, this->player)) {
                player->move_forward_backward(movement);
            }
        } else {
            movement = coord->left * dt * player_speed;

            if (!obstacle_collision(movement, this->player)) {
                player->move_left_right(movement);
            }
        }
    }

    if (controller->keys['w']) {
        if (current_camera == 4) {
            movement = coord->left * dt * player_speed;
            movement.y = 0;

            if (!obstacle_collision(movement, this->player)) {
                player->move_left_right(movement);
            }

        } else {
            movement = coord->direction * dt * player_speed;
            movement.y = 0;

            if (!obstacle_collision(movement, this->player)) {
                player->move_forward_backward(movement);

            } else {
                vec3 movement0 = vec3(movement.x, 0, 0);
                vec3 movement1 = vec3(0, 0, movement.z);

                if (!obstacle_collision(movement0, this->player)) {
                    player->move_forward_backward(movement0);
                } else if (!obstacle_collision(movement1, this->player)) {
                    player->move_forward_backward(movement1);
                }
            }
        }
    } else if (controller->keys['s']) {
        if (current_camera == 4) {
            movement = coord->left * -1 * dt * player_speed;
            movement.y = 0;

            if (!obstacle_collision(movement, this->player)) {
                player->move_left_right(movement);
            }

        } else {
            movement = coord->direction * -1 * dt * player_speed;
            movement.y = 0;

            if (!obstacle_collision(movement, this->player)) {
                player->move_forward_backward(movement);
            }
        }
    }
}

void Game::update_player_jump(float dt) {
    // Jump logic
    if ((this->controller->keys[' '] && !gravity_on) ||
        (this->controller->keys[' '] && (this->player->is_rising() ||
        (!this->player->is_rising() && !this->player->is_falling())))) {
        //
        if (
            !obstacle_collision(vec3(0, this->player_jump_speed*dt, 0),
                                this->player)) {
            // Pressing space, in floor or rising
            this->player->set_rising(true);
            this->player->move_up(this->player_jump_speed*dt);
            player->increment_on_air_time(dt);

        } else {
            this->player->set_rising(false);
            this->player->set_falling(true);
            this->player->clear_on_air_time();
        }
    } else if (gravity_on && this->player->is_falling()) {
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
            controller->keys['x'] = false;  // Disable
            controller->move_orbital_camera = !controller->move_orbital_camera;
        }
    }

    if (!gravity_on && controller->keys['q']) {
        if (!obstacle_collision(vec3(0, -block_size*0.15, 0), player)) {
            this->player->move_up(-block_size*0.15);
        }
    }

    //
    if (controller->keys['m']) {
        controller->keys['m'] = false;  // Disable
        controller->disable_mouse_warp = !controller->disable_mouse_warp;

        //
        if (controller->disable_mouse_warp) {
            glutSetCursor(GLUT_CURSOR_INHERIT);
        } else {
            glutSetCursor(GLUT_CURSOR_NONE);
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

    //
    static bool last_player_box_state = false;
    static bool last_enemies_box_state = false;

    if (last_player_box_state != player_collision_box) {
        player->set_show_collision_boundary(player_collision_box);
        last_player_box_state = !last_player_box_state;
    }

    if (last_enemies_box_state != enemies_collision_box) {
        for (auto& enemy : enemies)
            enemy->set_show_collision_boundary(enemies_collision_box);
        last_enemies_box_state = !last_enemies_box_state;
    }
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
    if (current_camera <= 2) {
        PORTAL_MATERIAL->activate();
        this->crosshair.draw(CROSSHAIR_TEX);
    }

    if (controller->disable_mouse_warp)
        update_imgui();
}

void Game::create_portal() {
    float portal[4][4] = {
        { 0.60, 0.20, 0.60, 1.0f },  // ambient
        { 0.60, 0.20, 0.60, 1.0f },  // diffuse
        { 0.60, 0.20, 0.60, 1.0f },  // specular
        { data->arena_width, block_size,  // position
          data->arena_depth/2.f, 1.f }};

    glLightfv(GL_LIGHT7, GL_AMBIENT, &portal[0][0]);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, &portal[1][0]);
    glLightfv(GL_LIGHT7, GL_SPECULAR, &portal[2][0]);
    glLightfv(GL_LIGHT7, GL_POSITION, &portal[3][0]);
    glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0.15);
    glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.005);
    glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.0008);
}

void Game::display(float dt) {
    //
    this->update(dt);

    //
    glLoadIdentity();
    this->camera->activate();

    //
    this->create_lights();
    this->create_portal();

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
