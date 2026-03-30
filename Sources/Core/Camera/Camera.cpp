#include "Camera.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>


namespace D3E
{
    static constexpr float kOrbitSensitivity = 0.05f;
    static constexpr float kPanSensitivity   = 0.01f;
    static constexpr float kZoomSensitivity  = 0.5f;
    static constexpr float kMinZoomDist      = 1.0f;
    static constexpr float kMaxZoomDist      = 100.0f;
    static constexpr float kMinPitch         = -89.0f;
    static constexpr float kMaxPitch         =  89.0f;

    Camera::Camera()
        : Camera(glm::vec3(0.f, 0.f, 3.f))
    {}

    Camera::Camera(glm::vec3 spawn)
        : m_Pos(spawn)
    {
        recalculate_vectors();
    }

    glm::mat4 Camera::view_matrix()
    {
        return glm::lookAt(m_Pos, m_Pos + m_Target, m_Up);
    }

    void Camera::process_input(move_direction mDir, float deltaTime)
    {
        const float cSpeed = m_Speed * deltaTime;

        switch (mDir)
        {
            case move_direction::FORWARD:
                 m_Pos += m_Target * cSpeed;
                 break;
            case move_direction::RIGHT:
                m_Pos += m_Right * cSpeed;
                break;
            case move_direction::BACKWARD:
                m_Pos -= m_Target * cSpeed;
                break;
            case move_direction::LEFT:
                m_Pos -= m_Right * cSpeed;
                break;
            case move_direction::UP:
                m_Pos += m_Up * cSpeed;
                break;
            case move_direction::DOWN:
                m_Pos -= m_Up * cSpeed;
                break;
            case move_direction::ZOOM_IN:
                m_Pos += m_Target * kZoomSensitivity;
                break;
            case move_direction::ZOOM_OUT:
                m_Pos -= m_Target * kZoomSensitivity;
                break;
            default:
                break;
        }
    }

    void Camera::process_mouse(float dx, float dy)
    {
        const float sensitivity = 0.1f;

        m_Yaw   += dx * sensitivity;
        m_Pitch += dy * sensitivity;

        m_Pitch = glm::clamp(m_Pitch, -89.f, 89.f);

        recalculate_vectors();
    }

    void Camera::recalculate_vectors()
    {
        const float pitchRad = glm::radians(m_Pitch);
        const float yawRad   = glm::radians(m_Yaw);

        m_Target = glm::normalize(glm::vec3{
            std::cos(pitchRad) * std::cos(yawRad),
            std::sin(pitchRad),
            std::cos(pitchRad) * std::sin(yawRad)
        });

        recalculate_right_up();
    }

    void Camera::recalculate_right_up()
    {
        static const glm::vec3 worldUp {0.f, 1.f, 0.f};
        m_Right = glm::normalize(glm::cross(m_Target, worldUp));
        m_Up    = glm::normalize(glm::cross(m_Right,  m_Target));
    }
}
