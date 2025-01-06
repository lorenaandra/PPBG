#pragma once

#include "utils/glm_utils.h"

namespace transform2D
{
    // Translation matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // TODO(student): Ex. 1
        // de retinut: glm e column-major
        return glm::transpose(
            glm::mat3(
                1, 0, translateX,
                0, 1, translateY,
                0, 0, 1
            )
        );

        /* alta metoda:
        glm::mat3( 
        	 1,  0,  0,     // coloana 1 in memorie 
		     0,  1,  0,     // coloana 2 in memorie 
		     tx, ty, 1);    // coloana 3 in memorie 
        */
    }

    // Scaling matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        // TODO(student): Ex. 1
        return glm::mat3(
                scaleX, 0, 0,
                0, scaleY, 0,
                0, 0, 1
        );
    }

    // Rotation matrix
    inline glm::mat3 Rotate(float radians)
    {
        // TODO(student): Ex. 1
        return glm::transpose(
            glm::mat3(
                cos(radians), -sin(radians), 0,
                sin(radians), cos(radians), 0,
                0, 0, 1
            )
        );
    }

    struct ViewportSpace
    {
        ViewportSpace() : x(0), y(0), width(1), height(1) {}
        ViewportSpace(int x, int y, int width, int height)
            : x(x), y(y), width(width), height(height) {}
        int x;
        int y;
        int width;
        int height;
    };

    struct LogicSpace
    {
        LogicSpace() : x(0), y(0), width(1), height(1) {}
        LogicSpace(float x, float y, float width, float height)
            : x(x), y(y), width(width), height(height) {}
        float x;
        float y;
        float width;
        float height;
    };

    // Viewport transformation
    inline glm::mat3 Viewport(
        const LogicSpace& logic_space,
        const ViewportSpace& viewport_space)
    {
        // TODO(student): Ex. 1
        //
        // You can use the translation and scaling transformations
        float scaleX = viewport_space.width / logic_space.width;
        float scaleY = viewport_space.height / logic_space.height;

        // Translation to origin and scaling
        glm::mat3 translate = transform2D::Translate(viewport_space.x, viewport_space.y);
        glm::mat3 scale = transform2D::Scale(scaleX, scaleY);
        glm::mat3 logic_translate = transform2D::Translate(-logic_space.x, -logic_space.y);

        return translate * scale * logic_translate;        //return glm::mat3(1);
    }

}   // namespace transform2D