/******************************************************************************/
/*!
\file	Camera3.cpp
\author 3000 Lines Studio
\brief
Functions for the 3D FirstPerson Camera
*/
/******************************************************************************/

#include "Camera3.h"
#include "MyMath.h"
#include "Application.h"
#include "Mtx44.h"

#include "SharedData.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
    //phi = 0;
    active = 0;
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera3::~Camera3()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera3::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/

static float ROTSPEED = 5.f;
static float CAMSPEED = 2.f * ROTSPEED;

void Camera3::Update(double dt)
{
    MoveCamera(dt);

    /*if (Application::IsKeyPressed('R')) {       //reset
        Reset();
    }*/
}

void Camera3::MoveCamera(double dt)
{
    if (SharedData::GetInstance()->cursor_newxpos != SharedData::GetInstance()->cursor_xpos) {
        double diff_xpos = SharedData::GetInstance()->cursor_xpos - SharedData::GetInstance()->cursor_newxpos;
        SharedData::GetInstance()->cursor_xpos = SharedData::GetInstance()->cursor_newxpos;

        Mtx44 rotation;
        rotation.SetToIdentity();
        rotation.SetToRotation((float)(diff_xpos * ROTSPEED * dt), 0, 1, 0);
        Vector3 view = target - position;
        view = rotation * view;
        target = position + view;

        view = view.Normalized();
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        up = right.Cross(view).Normalized();
    }

    if (SharedData::GetInstance()->cursor_newypos != SharedData::GetInstance()->cursor_ypos) {
        double diff_ypos = SharedData::GetInstance()->cursor_ypos - SharedData::GetInstance()->cursor_newypos;
        SharedData::GetInstance()->cursor_ypos = SharedData::GetInstance()->cursor_newypos;

        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        up = right.Cross(view).Normalized();
        Mtx44 rotation;
        rotation.SetToIdentity();
        rotation.SetToRotation((float)(diff_ypos * ROTSPEED * dt), right.x, right.y, right.z);
        view = rotation * view;
        //phi += (float)(diff_ypos * ROTSPEED * dt);
        if (view.y < 0.8f && view.y > -0.8f) {
            target = position + view;
        }
    }

}
