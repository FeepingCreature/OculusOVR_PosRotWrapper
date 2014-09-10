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
			void getPosition(float &x, float &y, float &z);
	};
}

typedef struct _Vector3f {
	float x, y, z;
} Vector3f;

#define C_DLLEXPORT extern "C" __declspec(dllexport)
C_DLLEXPORT void *wrapper_init();
C_DLLEXPORT void wrapper_destroy(void *wrapper);
C_DLLEXPORT void wrapper_start_sensor(void *wrapper);
C_DLLEXPORT Vector3f wrapper_get_rotation(void *wrapper);
C_DLLEXPORT Vector3f wrapper_get_position(void *wrapper);
