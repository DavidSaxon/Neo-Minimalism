#include "src/camera/Camera.hpp"

Camera::Camera() {
}

Camera::Camera(const util::vec::Vector3D& trans,
	const util::vec::Vector3D& preRot,
	const util::vec::Vector3D& postRot) :
	translation(trans),
	preRotation(preRot),
	postRotation(postRotation) {
}

Camera::~Camera() {
}

void Camera::apply() {

	//post-translation rotation
	glRotatef(postRotation.getX(), 1.0, 0.0, 0.0);
	glRotatef(postRotation.getY(), 0.0, 1.0, 0.0);
	glRotatef(postRotation.getZ(), 0.0, 0.0, 1.0);
	//translation
	glTranslatef(-translation.getX(), -translation.getY(), -translation.getZ());
	//post-translation rotation
	//x-axis
	glRotatef(preRotation.getX(), 1.0, 0.0, 0.0);
	//y-axis
	glRotatef(preRotation.getY(), 0.0, 1.0, 0.0);
	//z-axis
	glRotatef(preRotation.getZ(), 0.0, 0.0, 1.0);
}