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

    // Camera should :
    // Lock onto the object and provide orbit movement
    // Zoom in or out
    // If not locked in the orbit, move around X axis using mouse
    // If not locked in the orbit, holding shift and using mouse to rotate around the center

    class Camera
    {
        private:
            float      m_Velocity    = 0.f;
            float      m_Speed       = 2.f;
            // free-look euler angles
            float      m_Yaw         = -90.f;   // faces -Z by default
            float      m_Pitch       = 0.f;
            // camera basis
            glm::vec3  m_Pos    {0.f, 0.f, 3.f};
            glm::vec3  m_Up     {0.f, 1.f, 0.f};
            glm::vec3  m_Right  {0.f};
            glm::vec3  m_Target {0.f};

            void recalculate_right_up();
            void recalculate_vectors();
        public:
            Camera();
            Camera(glm::vec3 spawn);
            ~Camera() = default;

            glm::mat4 view_matrix();
            void process_input(move_direction mDir, float deltaTime);
            void process_mouse(float dx, float dy);
            // void lock_orbit(glm::vec3 target);   // call this to snap-lock onto an object
            // bool is_orbit_locked() const { return m_OrbitLocked; }
    };
}
