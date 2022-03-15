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

static bool gravity_on = true;
static bool collision_on = true;
static bool player_collision_box = false;
static bool enemies_collision_box = false;
static bool move_enemies = true;
static float* mouse_sensitivity;

static char str[1000];
// void * font = GLUT_BITMAP_9_BY_15;
void * font =  GLUT_BITMAP_TIMES_ROMAN_24;


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

        ImGui::Checkbox("Enemies Movement", &move_enemies);
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

static std::vector<std::shared_ptr<Enemy>> copy(std::vector<std::shared_ptr<Enemy>> const &input) {
    std::vector<std::shared_ptr<Enemy>> ret;

    for(auto const &p: input) {
        ret.push_back(p->clone());
    }
    return ret;
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
    this->player_speed = block_size * 4.5;
    this->player_jump_speed = block_size * 15;

    // this->enemies = data->enemies;
    this->enemies = copy(data->enemies);

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

    //
    this->handCamera = new HandCamera(
        this->player->get_coordinate_system(),
        player->get_center(), block_size);

    this->orbitalCamera = new OrbitalCamera(
        this->player->get_coordinate_system(),
        player->get_center(),
        block_size);

    this->freeCamera = new FreeCamera(
        this->player->get_coordinate_system(),
        this->player->get_center(),
        this->data, this->block_size);

    // Create camera
    this->update_camera_type();

    this->controller->disable_mouse_warp = false;
    mouse_sensitivity = &(this->controller->mouse_sensitivity);
    *mouse_sensitivity = 3;

    this->game_state = 0;
}

void Game::create_lights() {
    if (!controller->night_mode) {
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

        float spot[] = {0, 0, -1};
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
    } else {
        vec3 c0 = player->get_center() + player->get_position();

        float light[4][4] = {
            { 1.f, 1.f, 1.f, 1.f },  // ambient
            { 0.80, 0.80, 0.80, 0.80f },  // diffuse
            { 0.25, 0.25, 0.25, 0.80f },  // specular
            { c0.x, c0.y, c0.z, 1.f },  // position
        };

        glLightfv(GL_LIGHT0, GL_AMBIENT, &light[0][0]);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, &light[1][0]);
        glLightfv(GL_LIGHT0, GL_SPECULAR, &light[2][0]);
        glLightfv(GL_LIGHT0, GL_POSITION, &light[3][0]);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,
            &(player->get_coordinate_system()->direction).x);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.2);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0002);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0002);
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

void Game::gravity(float dt, Player* player) {
    if (gravity_on) {
        float acceleration = (-player->get_on_air_time() * block_size * 18.0);

        if ((player->is_falling() || player->is_rising())) {
            if ((player->is_rising()) &&
                (this->player_jump_speed + acceleration <= 0)) {
                //
                player->set_rising(false);
                player->set_falling(true);
                player->clear_on_air_time();
            } else {
                if ((player->get_feet_height() + acceleration * dt >= 0) &&
                    (!obstacle_collision(
                        vec3(0, acceleration * dt, 0), player))) {
                    //
                    player->move_up(acceleration * dt);
                } else {
                    player->set_rising(false);
                    player->set_falling(false);
                    player->clear_on_air_time();
                }
                //
                if (player->get_feet_height() + acceleration*dt <= 0) {
                    player->set_y(block_size);
                }
            }
        } else if (
            !obstacle_collision(vec3(0, acceleration * dt, 0), player)) {
            player->move_up(acceleration * dt);
            player->set_falling(true);
        }
    }
}

bool Game::obstacle_collision(vec3 movement, Player* player) {
    if (!collision_on) return false;

    // Obstacle Collision
    CoordinateSystem* coord = player->get_coordinate_system();
    vec3 pos = coord->position + player->get_center() + movement;

    if (player == this->player &&
        pos.x >= data->arena_width) {
        game_state = 1;
        return true;
    }

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
            if (player != this->player) {
                ((Enemy*)player)->set_platform(obstacle);
            }

            return true;
        }
    }

    // Player Collision

    for (auto& enemy : enemies) {
        vec3 center = enemy->get_center() + enemy->get_position();

        if ((player != enemy.get()) &&
            (pos.x + block_size/2.f > center.x - block_size/2.f) &&
            (pos.x - block_size/2.f < center.x + block_size/2.f) &&
            (pos.y + block_size > center.y - block_size) &&
            (pos.y - block_size < center.y + block_size) &&
            (pos.z + block_size/2.f > center.z - block_size/2.f) &&
            (pos.z - block_size/2.f < center.z + block_size/2.f)) {
            //
            return true;
        }
    }

    vec3 center = this->player->get_center() +
                  this->player->get_position();

    if ((player != this->player) &&
        (pos.x + block_size/2.f > center.x - block_size/2.f) &&
        (pos.x - block_size/2.f < center.x + block_size/2.f) &&
        (pos.y + block_size > center.y - block_size) &&
        (pos.y - block_size < center.y + block_size) &&
        (pos.z + block_size/2.f > center.z - block_size/2.f) &&
        (pos.z - block_size/2.f < center.z + block_size/2.f)) {
        //
        return true;
    }

    return false;
}

bool Game::shoot_collision(vec3 movement, std::shared_ptr<Shoot> shoot) {
    vec3 future_point = shoot->get_point() + movement;

    if ((future_point.x > data->arena_width) || 
        (future_point.x < 0) || 
        (future_point.y > data->arena_height) ||
        (future_point.y < 0) || 
        (future_point.z > data->arena_depth) || 
        (future_point.z < 0)) {
            return true;
        }

    // Obstacle Colision
    for (auto& obstacle : obstacles) {
        vec3 center = obstacle->get_center();
        double w2 = obstacle->get_width()/2.f;
        double h2 = obstacle->get_height()/2.f;
        double d2 = obstacle->get_depth()/2.f;

        if ((future_point.x > center.x - w2) &&
            (future_point.x < center.x + w2) &&
            (future_point.y > center.y - h2) &&
            (future_point.y < center.y + h2) &&
            (future_point.z > center.z - d2) &&
            (future_point.z < center.z + d2)) {

            return true;
        }
    }

    int enemy_counter = 0;
    // Enemy Collision
    for (auto& enemy : enemies) {
        vec3 center = enemy->get_center() + enemy->get_position();

        if ((player != enemy.get()) &&
            (future_point.x < center.x + block_size/2.f) &&
            (future_point.x > center.x - block_size/2.f) &&
            (future_point.y > center.y - block_size) &&
            (future_point.y < center.y + block_size) &&
            (future_point.z > center.z - block_size/2.f) &&
            (future_point.z < center.z + block_size/2.f)) {
            //

            enemies.erase(enemies.begin() + enemy_counter);
            return true;
        }
        enemy_counter++;
    }

    // Player Collision
    vec3 center = this->player->get_center() +
                  this->player->get_position();

    if ((future_point.x > center.x - block_size/2.f) &&
        (future_point.x < center.x + block_size/2.f) &&
        (future_point.y > center.y - block_size) &&
        (future_point.y < center.y + block_size) &&
        (future_point.z > center.z - block_size/2.f) &&
        (future_point.z < center.z + block_size/2.f)) {

        game_state = -1;
        return true;
    }

    return false;
}

void Game::update_player_move(float dt) {
    vec3 movement;
    CoordinateSystem* coord = player->get_coordinate_system();
    bool clear = true;

    if (controller->keys['d']) {
        movement = coord->left * -1 * dt * player_speed;

        if (!obstacle_collision(movement, this->player)) {
            player->move_left_right(movement);
        }
        clear = false;
    } else if (controller->keys['a']) {
        movement = coord->left * dt * player_speed;

        if (!obstacle_collision(movement, this->player)) {
            player->move_left_right(movement);
        }
        clear = false;
    }

    if (controller->keys['w']) {
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
        clear = false;
    } else if (controller->keys['s']) {
        movement = coord->direction * -1 * dt * player_speed;
        movement.y = 0;

        if (!obstacle_collision(movement, this->player)) {
            player->move_forward_backward(movement);
        }
        clear = false;
    }

    if (clear) player->clear_walking();
}

void Game::update_player_jump(float dt, Player* player) {
    // Jump logic
    if ((this->controller->keys[' '] && !gravity_on) ||
        (this->controller->keys[' '] && (player->is_rising() ||
        (!player->is_rising() && !player->is_falling())))) {
        //
        if (
            !obstacle_collision(vec3(0, player_jump_speed*dt, 0),
                                player)) {
            // Pressing space, in floor or rising
            player->set_rising(true);
            player->move_up(player_jump_speed*dt);
            player->increment_on_air_time(dt);
        } else {
            player->set_rising(false);
            player->set_falling(true);
            player->clear_on_air_time();
        }
    } else if (gravity_on && player->is_falling()) {
        // Player falling, increment time falling
        player->increment_on_air_time(dt);

    } else if (!controller->keys[' '] && player->is_rising()) {
        // Space key up, update player conditition
        player->clear_on_air_time();
        player->set_rising(false);
        player->set_falling(true);
    }
}

void Game::update_camera_type() {
    static bool first = true;
    static bool pressing_right = false;
    static bool changing_right_mouse = false;

    // TODO
    if ((controller->keys['1'] && current_camera != 1) || first ||
        (!controller->right_mouse_button && changing_right_mouse) || game_state == -1) {
        this->current_camera = 1;
        this->camera = this->defaultCamera;
        changing_right_mouse = false;
        pressing_right = false;
        ((DefaultCamera*)this->camera)->set_player_angles();

        //
        first = false;
        MouseListener::set_camera((DefaultCamera*)this->camera);
    } else if ((controller->keys['2'] || controller->right_mouse_button) &&
                current_camera != 2) {
        if (controller->right_mouse_button) {
            pressing_right = true;
            changing_right_mouse = true;
        }
        this->current_camera = 2;
        this->camera = this->handCamera;
        ((HandCamera*)this->camera)->set_player_angles();

        //
        first = false;
        MouseListener::set_camera((DefaultCamera*)this->handCamera);

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
        MouseListener::set_camera((FreeCamera*)this->camera);

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

    if (controller->keys['n']) {
        controller->keys['n'] = false;  // Disable

        if (!controller->night_mode) {
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            glDisable(GL_LIGHT3);
            glDisable(GL_LIGHT4);
            glDisable(GL_LIGHT5);
            glDisable(GL_LIGHT6);
        } else {
            glEnable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
            glEnable(GL_LIGHT4);
            glEnable(GL_LIGHT5);
            glEnable(GL_LIGHT6);
        }

        controller->night_mode = !controller->night_mode;
    }

    if (controller->keys['r'] && game_state != 0) {
        this->enemies = copy(data->enemies);
        this->player = new Player(data->player_pos, data->block_size);
        this->shoots.clear();
        this->player->draw();

        for (auto& enemy : enemies) {
            enemy->draw();
        }

        //
        this->defaultCamera = new DefaultCamera(
            this->player->get_coordinate_system(),
            player->get_center());

        //
        this->handCamera = new HandCamera(
            this->player->get_coordinate_system(),
            player->get_center(), block_size);

        this->orbitalCamera = new OrbitalCamera(
            this->player->get_coordinate_system(),
            player->get_center(),
            block_size);

        this->freeCamera = new FreeCamera(
            this->player->get_coordinate_system(),
            this->player->get_center(),
            this->data, this->block_size);

        // Create camera
        this->update_camera_type();
        this->game_state = 0;
    }

    //
    if (controller->left_mouse_button) {
        player->increment_bow_animation(dt);
    } else {
        // Verifica se o jogador pode atirar
        if (player->ready2shoot()) {
            player->set_returning();
            this->shoots.push_back(std::make_shared<Shoot>(
                player->get_coordinate_system()->yaw,
                player->get_coordinate_system()->pitch,
                block_size/2.25f,
                player->get_center() + player->get_position(),
                player->get_coordinate_system()->direction));
        }

        player->increment_bow_animation(-dt);
    }
}

void Game::update(float dt) {
    std::vector<std::shared_ptr<Shoot>>::iterator it;

    for (it = shoots.begin(); it != shoots.end();) {
        vec3 dir = (*it)->get_direction();
        vec3 velocity = dir.normalize() * player_speed * 4 * dt;

        if (!shoot_collision(velocity, (*it))) {
            (*it)->set_position(vec3(velocity.x, velocity.y, velocity.z));
            ++it;
        } else {
            it = this->shoots.erase(it);
        }
    }

    //
    if (controller->keys[27]) {
        glutLeaveMainLoop();
    }
    
    //
    this->update_camera_type();
    this->update_controller(dt);
    this->camera->update();

    // Update player position
    this->gravity(dt, this->player);
    this->update_player_move(dt);
    this->update_player_jump(dt, this->player);

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

    // Move os inimigos
    for (auto& enemy : enemies) {
        // Faz ele atirar
        if (enemy->ready2shoot() && enemy->get_shoot_time() <= 0) {
            enemy->clear_walking();
            enemy->set_returning();
            enemy->increment_shoot(-dt);

            // Define a direção do inimigo no sentido do jogador
            CoordinateSystem* coord = enemy->get_coordinate_system();
            CoordinateSystem* nc = new CoordinateSystem();

            vec3 player_pos = (player->get_coordinate_system()->position +
                player->get_center());
            vec3 dist = player_pos -
                 (enemy->get_position() + enemy->get_center());

            nc->direction = dist.normalize();
            nc->yaw = atan2(dist.x, dist.z) * 180/M_PI + 180;
            nc->position = coord->position;

            if (player_pos.x > enemy->get_center().x + enemy->get_position().x) {
                nc->pitch = 0 + atan2(dist.y, dist.x) * 180/M_PI;
                if (nc->pitch > 45) nc->pitch = 45;
                if (nc->pitch < -45) nc->pitch = -45;
            } else {
                nc->pitch = 90+ atan2(dist.x, dist.y) * 180/M_PI;
                if (nc->pitch < -45) nc->pitch = -45;
                if (nc->pitch > 45) nc->pitch = 45;
            }
            // Fix max angles
            float yaw = nc->yaw * M_PI/180.0;
            float pitch = nc->pitch * M_PI/180.0;
            nc->direction = vec3(-sin(yaw), sin(pitch), -cos(yaw)*cos(pitch)).normalize();
            nc->left = vec3(0, 1, 0) * nc->direction;
            nc->up = nc->direction * nc->left;
            enemy->set_coordinate_system(nc);

            // cria o tiro
            this->shoots.push_back(std::make_shared<Shoot>(
                nc->yaw,
                nc->pitch,
                block_size/2.25f,
                enemy->get_center() + enemy->get_position(),
                enemy->get_coordinate_system()->direction));
        } else  {
            enemy->increment_bow_animation(dt);
            enemy->increment_shoot(dt);

            if (move_enemies) {
                this->gravity(dt, (Player*)enemy.get());
                vec3 movement = enemy->get_coordinate_system()->direction;
                movement = movement * player_speed * dt;
                enemy->move(dt, player_speed);

                if ((!obstacle_collision(movement, enemy.get()) &&
                    (!enemy->out_platform(movement)) &&
                    (!enemy->is_falling()))) {
                    //
                    enemy->move_forward_backward(movement);
                } else {
                    if (enemy->get_feet_height() <= 0) {
                        enemy->set_y(block_size);
                    }

                    // Vira o inimigo
                    if (!enemy->is_falling()) {
                        enemy->move(1000, player_speed);
                    } else {
                        enemy->increment_on_air_time(dt);
                    }
                }
            } else {
                enemy->clear_walking();
            }
        }

    }
}

static void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b) {
    //Push to recover original attributes
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //Draw text in the x, y, z position
        glColor3f(r,g,b);
        // glTranslatef(0.5, 0.5, 0);
        // glScalef(100, 100, 1);
        // glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"The game over!");

        glRasterPos3f(x, y, z);
        const char* tmpStr;
        tmpStr = text;
        while( *tmpStr ){
            glutBitmapCharacter(font, *tmpStr);
            tmpStr++;
        }
    glPopAttrib();
}

static void PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b, int scale) {
    //Draw text considering a 2D space (disable all 3d features)
    glMatrixMode (GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
        glLoadIdentity ();
        glOrtho (0, 1, 0, 1, 0, 1);
        RasterChars(x, y, 0, text, r, g, b);    
    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}

void Game::display_hud() {
    // Draw static info, first set ortogonal projection
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -1, 1);
        if (controller->disable_mouse_warp)
        update_imgui();
    // Clear the model_view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!game_state) {
        PORTAL_MATERIAL->activate();
        this->crosshair.draw(CROSSHAIR_TEX);
    }
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

    this->update(dt);
    if (game_state == 0) {

        //
        glLoadIdentity();
        this->camera->activate();

        //
        this->create_lights();
        this->create_portal();

        this->player->display(dt);

        for (auto& enemy : enemies) {
            enemy->display(dt);
        }

        for (auto& shoot : shoots) {
            shoot->display(dt);
        }

        // Draw arena obstacles
        for (auto& obstacle : obstacles) {
            obstacle->display(dt, controller);
        }

        this->display_hud();
    } else if (game_state == -1) {
        PrintText(0.43, 0.5, "You Lose!", 1, 0, 0, 3);
        PrintText(0.39, 0.45, "Press R to restart", 1, 0, 0, 3);
        // PERDEU
        // you_lose()
    } else if (game_state == 1) {
        PrintText(0.43, 0.5, "You Won!", 0, 0, 1, 3);
        PrintText(0.39, 0.45, "Press R to restart", 1, 0, 0, 3);
        // GANHOU
        // you_win()
    }
}
