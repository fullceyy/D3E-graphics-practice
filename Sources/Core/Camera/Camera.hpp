#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"


namespace D3E
{
    enum class move_direction
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        ORBIT_LEFT,
        ORBIT_RIGHT,
        ORBIT_UP,
        ORBIT_DOWN,
        ZOOM_IN,
        ZOOM_OUT,
        LOCK_ORBIT,
    };

    class Camera
    {
    private:
        float      mVelocity    = 0.f;
        float      mSpeed       = 2.f;
        // free-look euler angles
        float      mYaw         = -90.f;   // faces -Z by default
        float      mPitch       = 0.f;
        // camera basis
        glm::vec3  mPos    {0.f, 0.f, 3.f};
        glm::vec3  mUp     {0.f, 1.f, 0.f};
        glm::vec3  mRight  {0.f};
        glm::vec3  mTarget {0.f};

        float      xAspect = 0.f;
        float      yAspect = 0.f;

        void recalculate_right_up();
        void recalculate_vectors();
    public:
        Camera(float width, float height, glm::vec3 pos);
        Camera();
        ~Camera() = default;

        glm::mat4 ViewMatrix();
        glm::mat4 ProjectionMatrix();
        
        void SetAspectRatio(float x, float y);
        void ProcessInput(move_direction mDir, float deltaTime);
        void ProcessMouse(float dx, float dy);
    };
}
