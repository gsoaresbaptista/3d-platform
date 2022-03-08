#include "rectangle.h"
#include "../../math/math.h"
#include "../../others/gameConstants.h"
#include <vector>
#include <iostream>
#include <cmath>

void Rectangle::draw(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3,
        vec2 t0, vec2 t2, GLuint n_segs,
        GLuint n_stacks, Color color,
        Outline outline, bool repeat_texture) {
    // Calculate others contour pointers
    vec2 t1(t0.x, t2.y);  // bottom left
    vec2 t3(t2.x, t0.y);  // upper right

    Rectangle::draw(
        p0, p1, p2, p3, t0, t1, t2, t3,
        n_segs, n_stacks, color, outline, repeat_texture);
}

void Rectangle::draw(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3,
        GLuint n_segs, GLuint n_stacks,
        Color color, Outline outline, bool repeat_texture) {
    // Use the entire figure as a texture
    vec2 t0(0, 1);
    vec2 t1(0, 0);
    vec2 t2(1, 0);
    vec2 t3(1, 1);

    Rectangle::draw(
        p0, p1, p2, p3, t0, t1, t2, t3,
        n_segs, n_stacks, color, outline, repeat_texture);
}

void Rectangle::draw(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3,
        vec2 t0, vec2 t1, vec2 t2, vec2 t3,
        GLuint n_segs, GLuint n_stacks,
        Color color, Outline outline, bool repeat_texture) {
    // Apply color to shape
    glColor3fv(color);

    // Texture boundary points
    vec2 tex1 = vec2(t0.x, t0.y);
    vec2 tex2 = vec2(t0.x, t2.y);
    vec2 tex3 = vec2(t2.x, t2.y);
    vec2 tex4 = vec2(t2.x, t0.y);

    // Calculates texture and shape points
    std::vector< std::vector<vec3>> square;
    std::vector< std::vector<vec2>> texture;
    float delta_x = 1.0/n_segs;
    float delta_y = 1.0/n_stacks;

    for (int i = 0; i <= n_stacks; i++) {
        float step_y = delta_y * i;
        vec3 q1 = p0 * (1 - step_y) + p1 * step_y;
        vec3 qn = p3 * (1 - step_y) + p2 * step_y;

        vec2 pt1 = tex1 * (1 - step_y) + tex2 * step_y;
        vec2 ptn = tex4 * (1 - step_y) + tex3 * step_y;

        std::vector<vec3> lines;
        std::vector<vec2> tex_lines;

        for (int j = 0; j <= n_segs; j++) {
            float step_x = delta_x * j;
            vec3 qj = q1 * (1 - step_x) + qn * step_x;
            vec2 ptj = pt1 * (1 - step_x) + ptn * step_x;
            lines.push_back(qj);
            tex_lines.push_back(ptj);
        }

        square.push_back(lines);
        texture.push_back(tex_lines);
        lines.clear();
    }

    // Draw points
     if (outline == Outline::SPLITTED) {
        // Create two triangles
        glBegin(GL_TRIANGLE_FAN);
    } else {
        // Create square outline
        glBegin(GL_QUADS);
    }
        for (int i = 0; i < n_stacks; i++) {
            for (int j = 0; j < n_segs; j++) {
                if (repeat_texture)
                    glTexCoord2f(1, 0);
                else
                    glTexCoord2fv(&texture[i][j].x);
                glVertex3fv(&square[i][j].x);

                if (repeat_texture)
                    glTexCoord2f(0, 0);
                else
                    glTexCoord2fv(&texture[i + 1][j].x);
                glVertex3fv(&square[i + 1][j].x);

                if (repeat_texture)
                    glTexCoord2f(0, 1);
                else
                    glTexCoord2fv(&texture[i + 1][j + 1].x);
                glVertex3fv(&square[i + 1][j + 1].x);

                if (repeat_texture)
                    glTexCoord2f(1, 1);
                else
                    glTexCoord2fv(&texture[i][j + 1].x);
                glVertex3fv(&square[i][j + 1].x);
            }
        }
    glEnd();
}

void Rectangle::draw_block(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3, vec2 t0, vec2 t2,
        GLfloat block_size, Color color, Outline outline, BoxType type) {
    // Calculate box dimensions
    float width = p3.distance(p0);
    float height = p1.distance(p0);

    int n_stacks = height/block_size;
    int n_segs = width/block_size;
    int step_increment_x = 0;
    int step_increment_y = 0;

    n_segs = (n_segs == 0) ? 1:n_segs;
    n_stacks = (n_stacks == 0) ? 1:n_stacks;

    // Correction number of splits to complete difference with block size
    if (block_size*n_stacks < height) {
        n_stacks++;
        step_increment_y++;
    }

    if (block_size*n_segs < width) {
        n_segs++;
        step_increment_x++;
    }

    // Calcule delta for block size
    float ph = (width/block_size) * block_size/width;
    float pv = (height/block_size) * block_size/height;
    float delta_y = pv/(n_stacks - step_increment_y);
    float delta_x = ph/(n_segs - step_increment_x);

    // Calculete texture points
    vec2 tex1(t0.x, t0.y);
    vec2 tex2(t0.x, t2.y);
    vec2 tex3(t2.x, t2.y);
    vec2 tex4(t2.x, t0.y);

    // Calculates texture and shape points
    std::vector< std::vector<vec3>> square;
    std::vector< std::vector<vec2>> texture;

    for (int i = 0; i <= n_stacks; i++) {
        float step_y = delta_y * i;
        if (i == n_stacks) step_y = 1;

        // Calcule new points
        vec3 q1 = p0 * (1 - step_y) + p1 * step_y;
        vec3 qn = p3 * (1 - step_y) + p2 * step_y;

        // Calcule correction value for size difference with block_size
        float correction;

        if (i != 0)
            correction = q1.distance(square[i-1][0]);
        else
            correction = p0.distance(q1);

        // Create texture points
        float step_tex = i * correction/block_size;
        vec2 pt1 = tex1 * (1 - step_tex) + tex2 * step_tex;
        vec2 ptn = tex4 * (1 - step_tex) + tex3 * step_tex;

        std::vector<vec3> lines;
        std::vector<vec2> tex_lines;

        for (int j = 0; j <= n_segs; j++) {
            float step_x = delta_x * j;
            if (j == n_segs) step_x = 1;

            float step_tex = j;
            float correcao;

            // Calcule new horrizontal point
            vec3 qj = q1 * (1 - step_x) + qn * step_x;

            // Calcule correction value for size difference with block_size
            if (j != 0)
                correction = qj.distance(lines[j-1]);
            else
                correction = p0.distance(qj);

            step_tex = j * correction/block_size;

            // Create new texture point
            vec2 ptj = pt1 * (1 - step_tex) + ptn * step_tex;

            lines.push_back(qj);
            tex_lines.push_back(ptj);
        }

        square.push_back(lines);
        texture.push_back(tex_lines);
    }

    std::shared_ptr<Texture> tex;

    // Draw points
    for (int i = 0; i < n_stacks; i++) {
        for (int j = 0; j < n_segs; j++) {
            float val = random_float(0, 1);

            // Choosing the texture
            if (type == BoxType::SPRUCE) {
                WOOD_MATERIAL->activate();
                tex = SPRUCE_PLANKS_TEX;

            } else if (type == BoxType::PORTAL) {
                tex = PORTAL_TEX;
                PORTAL_MATERIAL->activate();

            } else if (type == BoxType::TORCH) {
                tex = TORCH_TEX;
            } else if (type == BoxType::FLAME) {
                tex = FLAME_TEX;
            } else if (type == BoxType::DARK_OAK) {
                tex = DARK_OAK_PLANKS_TEX;
                WOOD_MATERIAL->activate();

            } else if (type == BoxType::DEEPSLATE_BRICKS) {
                STONE_MATERIAL->activate();

                if (val <= 0.75) {
                    tex = DEEPSLATE_BRICKS_TEX;
                } else if (val <= 0.875) {
                    tex = MOSSY_DEEPSLATE_BRICKS_TEX;
                } else if (val <= 1.0) {
                    tex = CRACKED_DEEPSLATE_BRICKS_TEX;
                }
            }

            tex->bind();
            if (outline == Outline::SPLITTED) {
                // Create two triangles
                glBegin(GL_TRIANGLE_FAN);
            } else {
                // Create square outline
                glBegin(GL_QUADS);
            }
                glTexCoord2fv(&texture[i][j].x);
                glVertex3fv(&square[i][j].x);

                glTexCoord2fv(&texture[i + 1][j].x);
                glVertex3fv(&square[i + 1][j].x);

                glTexCoord2fv(&texture[i + 1][j + 1].x);
                glVertex3fv(&square[i + 1][j + 1].x);

                glTexCoord2fv(&texture[i][j + 1].x);
                glVertex3fv(&square[i][j + 1].x);
            glEnd();
            tex->unbind();
        }
    }
}

void Rectangle::draw_block(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3, GLfloat block_size,
        Color color, Outline outline, BoxType type) {
    // Use the entire figure as a texture
    vec2 t0(0, 1);
    vec2 t2(1, 0);

    Rectangle::draw_block(
        p0, p1, p2, p3, t0, t2,
        block_size, color, outline, type);
}
