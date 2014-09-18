// This is the main DLL file.

#include "Oculus OVR PosRotWrapper.h"

using namespace OculusOVRPosRotWrapper;

OVRWrapper::OVRWrapper() {
	ovr_Initialize();
	hmd = ovrHmd_Create(0);
}

OVRWrapper::~OVRWrapper() {
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
}

void OVRWrapper::startSensor() {
	ovrHmd_ConfigureTracking(hmd,
		ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position,
		0);
}

void OVRWrapper::getRotation(float &pitch, float &yaw, float &roll) {
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, 0.0);
	OVR::Posef pose = ts.HeadPose.ThePose;
	pose.Rotation.GetEulerAngles<OVR::Axis_Y, OVR::Axis_X, OVR::Axis_Z>(&yaw, &pitch, &roll);
}

void OVRWrapper::getRotationQuat(float &x, float &y, float &z, float &w) {
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, 0.0);
	OVR::Posef pose = ts.HeadPose.ThePose;
	x = pose.Rotation.x;
	y = pose.Rotation.y;
	z = pose.Rotation.z;
	w = pose.Rotation.w;
}

void OVRWrapper::resetOrientation() {
	ovrHmd_RecenterPose(hmd);
}

void OVRWrapper::getPosition(float &x, float &y, float &z) {
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, 0.0);
	OVR::Posef pose = ts.HeadPose.ThePose;
	OVR::Vector3f pos = pose.Translation;
	x = pos.x;
	y = pos.y;
	z = pos.z;
}

using namespace OculusOVRPosRotWrapper;

C_DLLEXPORT void *wrapper_init() {
	OVRWrapper *res = new OVRWrapper;
	return (void*) res;
}

C_DLLEXPORT void wrapper_destroy(void *wrapper) {
	OVRWrapper *wr = (OVRWrapper*) wrapper;
	delete wr;
}

C_DLLEXPORT void wrapper_start_sensor(void *wrapper) {
	OVRWrapper *wr = (OVRWrapper*) wrapper;
	wr->startSensor();
}

C_DLLEXPORT Vector3f wrapper_get_rotation(void *wrapper) {
	OVRWrapper *wr = (OVRWrapper*) wrapper;
	Vector3f res;
	wr->getRotation(res.x, res.y, res.z);
	return res;
}

C_DLLEXPORT Vector3f wrapper_get_position(void *wrapper) {
	OVRWrapper *wr = (OVRWrapper*) wrapper;
	Vector3f res;
	wr->getPosition(res.x, res.y, res.z);
	return res;
}

C_DLLEXPORT void wrapper_reset_orientation(void *wrapper) {
	OVRWrapper *wr = (OVRWrapper*) wrapper;
	wr->resetOrientation();
}

C_DLLEXPORT Quat wrapper_get_quat_rotaton(void *wrapper) {
	OVRWrapper *wr = (OVRWrapper*) wrapper;
	Quat res;
	wr->getRotationQuat(res.x, res.y, res.z, res.w);
	return res;
}
