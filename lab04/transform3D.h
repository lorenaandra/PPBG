#pragma once

#include "utils/glm_utils.h"
// pt perspective:
#include <glm/ext/matrix_clip_space.hpp>
/* template <typename valType>
GLM_FUNC_QUALIFIER detail::tmat4x4<valType, defaultp> perspective
(
    valType const& fovy,
    valType const& aspect,
    valType const& zNear,
    valType const& zFar
)
{
    assert(aspect != valType(0));
    assert(zFar != zNear);

#ifdef GLM_FORCE_RADIANS
    valType const rad = fovy;
#else
#   pragma message("GLM: perspective function taking degrees as a parameter is deprecated.     #define GLM_FORCE_RADIANS before including GLM headers to remove this message.")
    valType const rad = glm::radians(fovy);
#endif

    valType tanHalfFovy = tan(rad / valType(2));

    detail::tmat4x4<valType, defaultp> Result(valType(0));
    Result[0][0] = valType(1) / (aspect * tanHalfFovy);
    Result[1][1] = valType(1) / (tanHalfFovy);
    Result[2][2] = -(zFar + zNear) / (zFar - zNear);
    Result[2][3] = -valType(1);
    Result[3][2] = -(valType(2) * zFar * zNear) / (zFar - zNear);
    return Result;
}
*/


namespace transform3D
{
    // Translation matrix
    inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
    {
        // TODO(student): Ex. 1
        return glm::transpose(glm::mat4(
            1, 0, 0, translateX,
            0, 1, 0, translateY,
            0, 0, 1, translateZ,
            0, 0, 0, 1
        ));
    }

    // Scaling matrix
    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        // TODO(student): Ex. 1
        return glm::transpose(glm::mat4(
            scaleX, 0, 0, 0,
            0, scaleY, 0, 0,
            0, 0, scaleZ, 0,
            0, 0, 0, 1
        ));
    }

    // Rotation matrix relative to the OZ axis
    inline glm::mat4 RotateOZ(float radians)
    {
        // TODO(student): Ex. 1
        return glm::transpose(glm::mat4(
            cos(radians), -sin(radians), 0, 0,
            sin(radians), cos(radians), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ));
    }

    // Rotation matrix relative to the OY axis
    inline glm::mat4 RotateOY(float radians)
    {
        // TODO(student): Ex. 1
        return glm::transpose(glm::mat4(
            cos(radians), 0, sin(radians), 0,
            0, 1, 0, 0,
            -sin(radians), 0, cos(radians), 0,
            0, 0, 0, 1
        ));
    }

    // Rotate matrix relative to the OX axis
    inline glm::mat4 RotateOX(float radians)
    {
        // TODO(student): Ex. 1
        return glm::transpose(glm::mat4(
            1, 0, 0, 0,
            0, cos(radians), -sin(radians), 0,
            0, sin(radians), cos(radians), 0,
            0, 0, 0, 1
        ));
    }

    // Perspective projection matrix
    inline glm::mat4 Perspective(
        float fovy, float aspect, float zNear, float zFar)
    {
        // TODO(student): Ex. 2
        return glm::perspective(fovy, aspect, zNear, zFar);
    }

    // View matrix
    inline glm::mat4 View(
        const glm::vec3& position,
        const glm::vec3& forward,
        const glm::vec3& right,
        const glm::vec3& up)
    {
        // TODO(student): Ex. 4
        return glm::transpose(glm::mat4(
            right.x, right.y, right.z, 0,
            up.x, up.y, up.z, 0,
            forward.x, forward.y, forward.z, 0,
            0, 0, 0, 1
        )) * glm::transpose(glm::mat4(
            1, 0, 0, -position.x,
            0, 1, 0, -position.y,
            0, 0, 1, -position.z,
            0, 0, 0, 1
        ));
    }

}   // namespace transform3D
