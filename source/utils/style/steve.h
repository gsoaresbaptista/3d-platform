#ifndef SOURCE_UTILS_STYLE_STEVE_H_
#define SOURCE_UTILS_STYLE_STEVE_H_

#include <GL/gl.h>
#include "../math/math.h"
#include "../others/gameConstants.h"
#include <vector>
#include <memory>

namespace steve {
    void draw_rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, vec2 t1, vec2 t2) {
        //
        int total = 2;
        float delta = 1.f / (float)total;
        std::vector< std::vector<vec3>> square;
        std::vector< std::vector<vec2>> texture;

        vec2 tex1 = vec2(t1.x, t1.y);
        vec2 tex2 = vec2(t1.x, t2.y);
        vec2 tex3 = vec2(t2.x, t2.y);
        vec2 tex4 = vec2(t2.x, t1.y);

        for (float i = 0; i <= 1; i += delta) {
            vec3 q1 = p1 * (1 - i) + p2 * i;
            vec3 qn = p4 * (1 - i) + p3 * i;

            vec2 pt1 = tex1 * (1 - i) + tex2 * i;
            vec2 ptn = tex4 * (1 - i) + tex3 * i;

            std::vector<vec3> lines;
            std::vector<vec2> tex_lines;

            for (float j = 0; j <= 1; j += delta) {
                vec3 qj = q1 * (1 - j) + qn * j;
                vec2 ptj = pt1 * (1 - j) + ptn * j;
                lines.push_back(qj);
                tex_lines.push_back(ptj);
            }

            square.push_back(lines);
            texture.push_back(tex_lines);
            lines.clear();
        }

        glBegin(GL_QUADS);
            for (int i = 0; i < total; i++) {
                for (int j = 0; j < total; j++) {
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

    void draw_head(GLuint id, float s) {
        float d = s/2.0;

        // Front
        vec3 v1 = { -d,  d,  d };
        vec3 v2 = { -d, -d,  d };
        vec3 v3 = {  d, -d,  d };
        vec3 v4 = {  d,  d,  d };
        // Back
        vec3 v5 = {  d,  d, -d };
        vec3 v6 = {  d, -d, -d };
        vec3 v7 = { -d, -d, -d };
        vec3 v8 = { -d,  d, -d };

        float specular[] = { 1.f, 1.f, 1.f, 1.f};
        float ambient[] = { 0.5f, 0.5f, 0.5f, 1.f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialf(GL_FRONT, GL_SHININESS, 128);

        glNewList(id, GL_COMPILE);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            STEVE_TEX->bind();
            glNormal3f(0.f, 0.f, 1.f);
            draw_rect(v1, v2, v3, v4, vec2(8.0/64.0, 8.0/64.0), vec2(16.0/64.0, 16.0/64.0)); // FRENTE
            glNormal3f(1.f, 0.f, 0.f);
            draw_rect(v4, v3, v6, v5, vec2(16.0/64.0, 8.0/64.0), vec2(24.0/64.0, 16.0/64.0)); // DIREITA
            glNormal3f(0.f, 0.f, -1.f);
            draw_rect(v5, v6, v7, v8, vec2(24.0/64.0, 8.0/64.0), vec2(32.0/64.0, 16.0/64.0)); // TRAS
            glNormal3f(-1.f, 0.f, 0.f);
            draw_rect(v8, v7, v2, v1, vec2(0.0/64.0, 8.0/64.0), vec2(8.0/64.0, 16.0/64.0)); // ESQUERDA
            glNormal3f(0.f, 1.f, 0.f);
            draw_rect(v8, v1, v4, v5, vec2(8.0/64.0, 0.0/64.0), vec2(16.0/64.0, 8.0/64.0)); // CIMA
            glNormal3f(0.f, -1.f, 0.f);
            draw_rect(v2, v7, v6, v3, vec2(16.0/64.0, 0.0/64.0), vec2(24.0/64.0, 8.0/64.0)); // BAIXO
            STEVE_TEX->unbind();
        glEndList();
    }

    void draw_body(GLuint id, float s) {
        float d = s/2.0;

        // Front
        vec3 v1 = { -d,  d,  d/2 };
        vec3 v2 = { -d, -2*d,  d/2 };
        vec3 v3 = {  d, -2*d,  d/2 };
        vec3 v4 = {  d,  d,  d/2 };
        // Back
        vec3 v5 = {  d,  d, -d/2 };
        vec3 v6 = {  d, -2*d, -d/2 };
        vec3 v7 = { -d, -2*d, -d/2 };
        vec3 v8 = { -d,  d, -d/2 };

        float specular[] = { 1.f, 1.f, 1.f, 1.f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 128);

        glNewList(id, GL_COMPILE);
            glPolygonMode(GL_FRONT, GL_FILL);
            STEVE_TEX->bind();
            glNormal3f(-1.f, 0.f, 0.f);
            draw_rect(v8, v7, v2, v1, vec2(16.0/64.0, 20.0/64.0), vec2(20.0/64.0, 32.0/64.0));
            glNormal3f(0.f, 1.f, 0.f);
            draw_rect(v8, v1, v4, v5, vec2(20.0/64.0, 16.0/64.0), vec2(28.0/64.0, 20.0/64.0));
            glNormal3f(0.f, 0.f, 1.f);
            draw_rect(v1, v2, v3, v4, vec2(20.0/64.0, 20.0/64.0), vec2(28.0/64.0, 32.0/64.0));
            glNormal3f(1.f, 0.f, 0.f);
            draw_rect(v4, v3, v6, v5, vec2(28.0/64.0, 20.0/64.0), vec2(32.0/64.0, 32.0/64.0));
            glNormal3f(0.f, -1.f, 0.f);
            draw_rect(v2, v7, v6, v3, vec2(28.0/64.0, 16.0/64.0), vec2(36.0/64.0, 20.0/64.0));
            glNormal3f(0.f, 0.f, -1.f);
            draw_rect(v5, v6, v7, v8, vec2(32.0/64.0, 20.0/64.0), vec2(40.0/64.0, 32.0/64.0));
            STEVE_TEX->unbind();
        glEndList();
    }

    void draw_arm(GLuint id1, GLuint id2, float s) {
        float d = s/2.0;

        // Front
        vec3 v1 = { -d/2,  d,  d/2 };
        vec3 v2 = { -d/2, -d,  d/2 };
        vec3 v3 = {  d/2, -d,  d/2 };
        vec3 v4 = {  d/2,  d,  d/2 };
        // Back
        vec3 v5 = {  d/2,  d, -d/2 };
        vec3 v6 = {  d/2, -d, -d/2 };
        vec3 v7 = { -d/2, -d, -d/2 };
        vec3 v8 = { -d/2,  d, -d/2 };

        glNewList(id1, GL_COMPILE);
            glPolygonMode(GL_FRONT, GL_FILL);
            STEVE_TEX->bind();
            glNormal3f(-1.f, 0.f, 0.f);
            draw_rect(v8, v7, v2, v1, vec2(52/64.0, 20/64.0), vec2(56/64.0, 28/64.0)); // Esquerda
            glNormal3f(0.f, 1.f, 0.f);
            draw_rect(v8, v1, v4, v5, vec2(44.0/64.0, 16.0/64.0), vec2(48.0/64.0, 20.0/64.0)); // Cima
            glNormal3f(0.f, 0.f, 1.f);
            draw_rect(v1, v2, v3, v4, vec2(44.0/64.0, 20.0/64.0), vec2(48.0/64.0, 28.0/64.0)); // Frente
            glNormal3f(1.f, 0.f, 0.f);
            draw_rect(v4, v3, v6, v5, vec2(44.0/64.0, 20.0/64.0), vec2(40.0/64.0, 28.0/64.0)); // Direita
            glNormal3f(0.f, -1.f, 0.f);
            draw_rect(v2, v7, v6, v3, vec2(44.0/64.0, 24.0/64.0), vec2(48.0/64.0, 28.0/64.0)); // Baixo
            glNormal3f(0.f, 0.f, -1.f);
            draw_rect(v5, v6, v7, v8, vec2(48.0/64.0, 20.0/64.0), vec2(52.0/64.0, 28.0/64.0)); // Tras
            STEVE_TEX->unbind();
        glEndList();

        glNewList(id2, GL_COMPILE);
            glPolygonMode(GL_FRONT, GL_FILL);
            STEVE_TEX->bind();
            glNormal3f(-1.f, 0.f, 0.f);
            draw_rect(v8/1.01, v7/1.01, v2/1.01, v1/1.01, vec2(52.0/64.0, 28.0/64.0), vec2(56.0/64.0, 32.0/64.0));
            glNormal3f(0.f, 1.f, 0.f);
            draw_rect(v8/1.01, v1/1.01, v4/1.01, v5/1.01, vec2(44.0/64.0, 24.0/64.0), vec2(48.0/64.0, 28.0/64.0)); // Cima
            glNormal3f(0.f, 0.f, 1.f);
            draw_rect(v1/1.01, v2/1.01, v3/1.01, v4/1.01, vec2(44.0/64.0, 28.0/64.0), vec2(48.0/64.0, 32.0/64.0)); // Frente
            glNormal3f(1.f, 0.f, 0.f);
            draw_rect(v4/1.01, v3/1.01, v6/1.01, v5/1.01, vec2(44.0/64.0, 28.0/64.0), vec2(40.0/64.0, 32.0/64.0)); // Direita
            glNormal3f(0.f, -1.f, 0.f);
            draw_rect(v2/1.01, v7/1.01, v6/1.01, v3/1.01, vec2(48.0/64.0, 16.0/64.0), vec2(52.0/64.0, 20.0/64.0)); // Baixo
            glNormal3f(0.f, 0.f, -1.f);
            draw_rect(v5/1.01, v6/1.01, v7/1.01, v8/1.01, vec2(48.0/64.0, 28.0/64.0), vec2(52.0/64.0, 32.0/64.0));
            STEVE_TEX->unbind();
        glEndList();
    }

    void draw_leg(GLuint id1, GLuint id2, float s) {
        float d = s/2.0;

        // Front
        vec3 v1 = { -d/2,  d,  d/2 };
        vec3 v2 = { -d/2, -d,  d/2 };
        vec3 v3 = {  d/2, -d,  d/2 };
        vec3 v4 = {  d/2,  d,  d/2 };
        // Back
        vec3 v5 = {  d/2,  d, -d/2 };
        vec3 v6 = {  d/2, -d, -d/2 };
        vec3 v7 = { -d/2, -d, -d/2 };
        vec3 v8 = { -d/2,  d, -d/2 };

        glNewList(id1, GL_COMPILE);
            glPolygonMode(GL_FRONT, GL_FILL);
            STEVE_TEX->bind();
            glNormal3f(-1.f, 0.f, 0.f);
            draw_rect(v8, v7, v2, v1, vec2(0/64.0, 20/64.0), vec2(4/64.0, 28/64.0)); // Esquerda
            glNormal3f(0.f, 1.f, 0.f);
            draw_rect(v8, v1, v4, v5, vec2(4.0/64.0, 16.0/64.0), vec2(8.0/64.0, 20.0/64.0)); // Cima
            glNormal3f(0.f, 0.f, 1.f);
            draw_rect(v1, v2, v3, v4, vec2(4.0/64.0, 20.0/64.0), vec2(8.0/64.0, 28.0/64.0)); // Frente
            glNormal3f(1.f, 0.f, 0.f);
            draw_rect(v4, v3, v6, v5, vec2(4.0/64.0, 20.0/64.0), vec2(0.0/64.0, 28.0/64.0)); // Direita
             glNormal3f(0.f, -1.f, 0.f);
            draw_rect(v2, v7, v6, v3, vec2(4.0/64.0, 24.0/64.0), vec2(8.0/64.0, 28.0/64.0)); // Baixo
            glNormal3f(0.f, 0.f, -1.f);
            draw_rect(v5, v6, v7, v8, vec2(12.0/64.0, 20.0/64.0), vec2(16.0/64.0, 28.0/64.0));
            STEVE_TEX->unbind();
        glEndList();

        glNewList(id2, GL_COMPILE);
            glPolygonMode(GL_FRONT, GL_FILL);
            STEVE_TEX->bind();
            glNormal3f(-1.f, 0.f, 0.f);
            draw_rect(v8/1.01, v7/1.01, v2/1.01, v1/1.01, vec2(0.0/64.0, 28.0/64.0), vec2(4.0/64.0, 32.0/64.0)); // // Esquerda
            glNormal3f(0.f, 1.f, 0.f);
            draw_rect(v8/1.01, v1/1.01, v4/1.01, v5/1.01, vec2(4.0/64.0, 24.0/64.0), vec2(8.0/64.0, 28.0/64.0)); // Cima
            glNormal3f(0.f, 0.f, 1.f);
            draw_rect(v1/1.01, v2/1.01, v3/1.01, v4/1.01, vec2(4.0/64.0, 28.0/64.0), vec2(8.0/64.0, 32.0/64.0)); // Frente
            glNormal3f(1.f, 0.f, 0.f);
            draw_rect(v4/1.01, v3/1.01, v6/1.01, v5/1.01, vec2(4.0/64.0, 28.0/64.0), vec2(0.0/64.0, 32.0/64.0)); // Direita
            glNormal3f(0.f, -1.f, 0.f);
            draw_rect(v2/1.01, v7/1.01, v6/1.01, v3/1.01, vec2(8.0/64.0, 16.0/64.0), vec2(12.0/64.0, 20.0/64.0)); // Baixo
            glNormal3f(0.f, 0.f, -1.f);
            draw_rect(v5/1.01, v6/1.01, v7/1.01, v8/1.01, vec2(12.0/64.0, 28.0/64.0), vec2(16.0/64.0, 32.0/64.0));
            STEVE_TEX->unbind();
        glEndList();
    }
}  // namespace steve

#endif  // SOURCE_UTILS_STYLE_STEVE_H_
