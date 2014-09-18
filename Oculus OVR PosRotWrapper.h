// Oculus OVR PosRotWrapper.h

#pragma once

#include "OVR.h"

namespace OculusOVRPosRotWrapper {

	class OVRWrapper
	{
		public:
			ovrHmd hmd;
			OVRWrapper();
			~OVRWrapper();
			void startSensor();
			void getRotation(float &pitch, float &yaw, float &roll);
			void getRotationQuat(float &x, float &y, float &z, float &w);
			void getPosition(float &x, float &y, float &z);
			void resetOrientation();
	};
}

typedef struct _Vector3f {
	float x, y, z;
} Vector3f;

typedef struct _Quat {
	float x, y, z, w;
} Quat;

#define C_DLLEXPORT extern "C" __declspec(dllexport)
C_DLLEXPORT void *wrapper_init();
C_DLLEXPORT void wrapper_destroy(void *wrapper);
C_DLLEXPORT void wrapper_start_sensor(void *wrapper);
C_DLLEXPORT Vector3f wrapper_get_rotation(void *wrapper);
C_DLLEXPORT Vector3f wrapper_get_position(void *wrapper);
C_DLLEXPORT void wrapper_reset_orientation(void *wrapper);
C_DLLEXPORT Quat wrapper_get_quat_rotation(void *wrapper);
