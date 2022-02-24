#include "rectangle.h"
#include "../../linear/vec3.h"
#include <vector>

void Rectangle::draw(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3,
        vec2 t0, vec2 t2, GLuint n_segs,
        GLuint n_stacks, Color color,
        Outline outline) {
    // Calculate others contour pointers
    vec2 t1(t0.x, t2.y);  // bottom left
    vec2 t3(t2.x, t0.y);  // upper right

    Rectangle::draw(
        p0, p1, p2, p3, t0, t1, t2, t3,
        n_segs, n_stacks, color, outline);
}

void Rectangle::draw(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3,
        GLuint n_segs, GLuint n_stacks,
        Color color, Outline outline) {
    // Use the entire figure as a texture
    vec2 t0(0, 1);
    vec2 t1(0, 0);
    vec2 t2(1, 0);
    vec2 t3(1, 1);

    Rectangle::draw(
        p0, p1, p2, p3, t0, t1, t2, t3,
        n_segs, n_stacks, color, outline);
}

void Rectangle::draw(
        vec3 p0, vec3 p1, vec3 p2, vec3 p3,
        vec2 t0, vec2 t1, vec2 t2, vec2 t3,
        GLuint n_segs, GLuint n_stacks,
        Color color, Outline outline) {
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

    for (float i = 0; i <= 1; i += delta_y) {
        vec3 q1 = p0 * (1 - i) + p1 * i;
        vec3 qn = p3 * (1 - i) + p2 * i;

        vec2 pt1 = tex1 * (1 - i) + tex2 * i;
        vec2 ptn = tex4 * (1 - i) + tex3 * i;

        std::vector<vec3> lines;
        std::vector<vec2> tex_lines;

        for (float j = 0; j <= 1; j += delta_x) {
            vec3 qj = q1 * (1 - j) + qn * j;
            vec2 ptj = pt1 * (1 - j) + ptn * j;
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
                glTexCoord2fv(&texture[i][j].x);
                glVertex3fv(&square[i][j].x);

                glTexCoord2fv(&texture[i + 1][j].x);
                glVertex3fv(&square[i + 1][j].x);

                glTexCoord2fv(&texture[i + 1][j + 1].x);
                glVertex3fv(&square[i + 1][j + 1].x);

                glTexCoord2fv(&texture[i][j + 1].x);
                glVertex3fv(&square[i][j + 1].x);
            }
        }
    glEnd();
}
