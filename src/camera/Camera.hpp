/*******************************************\
| A camera that applys it's transformations |
|										    |
| @author David Saxon						|
\*******************************************/

#ifndef OMICRON_CAMERA_CAMERA_H_
#	define OMICRON_CAMERA_CAMERA_H_

#include <cmath>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <SDL/SDL.h>

#include "src/Utilities/MacroUtil.hpp"
#include "src/Utilities/ValuesUtil.hpp"
#include "src/Utilities/vector/Vector3D.hpp"

class Camera {
public:

	//CONSTRUCTORS
	/*!Creates a camera with not transformations applied*/
	Camera();

	/*!Creates a camera with the given intial translations
	@trans the translation amount
	@preRot the pre-translation rotation amount
	@postRot the post-translation rotation amount*/
	Camera(const util::vec::Vector3D& trans,
		const util::vec::Vector3D& preRot,
		const util::vec::Vector3D& postRot);

	//DESTRUCTOR
	/*!Destroys this camera*/
	~Camera();

	//PUBLIC MEMBER FUNCTIONS
	/*!Apply the camera transformations to the scene*/
	void apply();

	/*!^INL
	@return the translation vector*/
	util::vec::Vector3D& getTranslation();

	/*!^INL
	@return the pre-translation rotation vector*/
	util::vec::Vector3D& getPreRotation();

	/*!^INL
	@return the post-translation rotation vector*/
	util::vec::Vector3D& getPostRotation();

	/*!^INL
	@trans the new translation vector*/
	void setTranslation(const util::vec::Vector3D& trans);

	/*!^INL
	@preRot the new pre-translation rotation vector*/
	void setPreRotation(const util::vec::Vector3D& preRot);

	/*^INL
	@postRot the new post-translation vector*/
	void setPostRotation(const util::vec::Vector3D& postRot);

private:

	//VARIABLES
	//the translation vector
	util::vec::Vector3D translation;
	//the pre-translation rotation vector
	util::vec::Vector3D preRotation;
	//the post-translation rotation vector
	util::vec::Vector3D postRotation;
	
	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(Camera);

};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline util::vec::Vector3D& Camera::getTranslation() {

	return translation;
}

inline util::vec::Vector3D& Camera::getPreRotation() {

	return preRotation;
}

inline util::vec::Vector3D& Camera::getPostRotation() {

	return postRotation;
}

inline void Camera::setTranslation(const util::vec::Vector3D& trans) {

	translation = trans;
}

inline void Camera::setPreRotation(const util::vec::Vector3D& preRot) {

	preRotation = preRot;
}

inline void Camera::setPostRotation(const util::vec::Vector3D& postRot) {

	postRotation = postRot;
}

#endif