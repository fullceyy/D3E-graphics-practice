#include "Camera.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>

using namespace D3E;

static constexpr float kOrbitSensitivity = 0.05f;
static constexpr float kPanSensitivity   = 0.01f;
static constexpr float kZoomSensitivity  = 0.5f;
static constexpr float kMinZoomDist      = 1.0f;
static constexpr float kMaxZoomDist      = 100.0f;
static constexpr float kMinPitch         = -89.0f;
static constexpr float kMaxPitch         =  89.0f;

Camera::Camera(float width = 800.f, float height = 600.f, glm::vec3 spawn = glm::vec3(0.f))
: xAspect(width), yAspect(height), mPos(spawn)
{
    recalculate_vectors();
}

Camera::Camera()
: xAspect(800.f), yAspect(600.f), mPos(glm::vec3(0.f))
{
    recalculate_vectors();
}

void Camera::SetAspectRatio(float x, float y)
{
    xAspect = x;
    yAspect = y;
}

glm::mat4 Camera::ViewMatrix()
{
    return glm::lookAt(mPos, mPos + mTarget, mUp);
}

glm::mat4 Camera::ProjectionMatrix()
{
    return glm::perspective(glm::radians(45.f), xAspect / yAspect, 0.1f, 100.f);
}

void Camera::ProcessInput(move_direction mDir, float deltaTime)
{
    const float cSpeed = mSpeed * deltaTime;

    switch (mDir)
    {
        case move_direction::FORWARD:
                mPos += mTarget * cSpeed;
                break;
        case move_direction::RIGHT:
            mPos += mRight * cSpeed;
            break;
        case move_direction::BACKWARD:
            mPos -= mTarget * cSpeed;
            break;
        case move_direction::LEFT:
            mPos -= mRight * cSpeed;
            break;
        case move_direction::UP:
            mPos += mUp * cSpeed;
            break;
        case move_direction::DOWN:
            mPos -= mUp * cSpeed;
            break;
        case move_direction::ZOOM_IN:
            mPos += mTarget * kZoomSensitivity;
            break;
        case move_direction::ZOOM_OUT:
            mPos -= mTarget * kZoomSensitivity;
            break;
        default:
            break;
    }
}

void Camera::ProcessMouse(float dx, float dy)
{
    const float sensitivity = 0.1f;

    mYaw   += dx * sensitivity;
    mPitch += dy * sensitivity;

    mPitch = glm::clamp(mPitch, -89.f, 89.f);

    recalculate_vectors();
}

void Camera::recalculate_vectors()
{
    const float pitchRad = glm::radians(mPitch);
    const float yawRad   = glm::radians(mYaw);

    mTarget = glm::normalize(glm::vec3{
        std::cos(pitchRad) * std::cos(yawRad),
        std::sin(pitchRad),
        std::cos(pitchRad) * std::sin(yawRad)
    });

    recalculate_right_up();
}

void Camera::recalculate_right_up()
{
    static const glm::vec3 worldUp {0.f, 1.f, 0.f};
    mRight = glm::normalize(glm::cross(mTarget, worldUp));
    mUp    = glm::normalize(glm::cross(mRight,  mTarget));
}
