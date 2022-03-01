#include "circle.h"
#include "../../math/math.h"

#include <cmath>

void Circle::draw(GLfloat radius, GLuint n_segs, Color color, Outline outline) {
    float delta_theta = 2*M_PI/n_segs;

    // Apply color to shape
    glColor3fv(color);

    if (outline == Outline::SPLITTED) {
        // Create the next triangle with center, next and last points
        vec2 last_vertex(0, 0);

        glBegin(GL_TRIANGLES);
            for (int i = 0; i <= n_segs; i++) {
                // Center point
                glTexCoord2f(0, 0);
                glVertex2f(0, 0);

                // Last point
                glTexCoord2fv(&last_vertex.x);
                glVertex2fv(&last_vertex.x);

                // Next point
                last_vertex = vec2(
                    cosf(delta_theta*i)*radius,
                    sinf(delta_theta*i)*radius);

                glTexCoord2fv(&last_vertex.x);
                glVertex2fv(&last_vertex.x);
            }
        glEnd();
    } else {
            // Create circle outline
            glBegin(GL_POLYGON);
            for (int i = 0; i < n_segs; i++) {
                glTexCoord2f(
                    cosf(delta_theta*i)*radius + 0.5,
                    sinf(delta_theta*i)*radius + 0.5);

                glVertex2f(
                    cosf(delta_theta*i)*radius,
                    sinf(delta_theta*i)*radius);
            }
        glEnd();
    }
}
