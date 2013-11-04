#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
#include <OIS.h>

const float PI = 4 * std::atan(1.f);

typedef std::pair<int, int> iPair;
typedef std::pair<unsigned int, unsigned int> uiPair;
typedef std::pair<float, float> fPair;

template <typename T> inline int toInt(const T& t) {
	std::stringstream stream;
	int value;
	stream << t;
	stream >> value;
	return value;
}

template <typename T> inline Ogre::Real toReal(const T& t) {
	std::stringstream stream;
	Ogre::Real value;
	stream << t;
	stream >> value;
	return value;
}

template <typename T> inline std::string toString(const T& t) {
	std::stringstream stream;
	std::string value;
	stream << t;
	stream >> value;
	return value;
}

inline std::string vectorToString(Ogre::Vector3& t) {
	std::stringstream stream;
	std::string value;
	stream << "(" <<t.x << "," << t.y << "," << t.z << ")";
	stream >> value;
	return value;
}

inline std::string vectorToString2(Ogre::Vector2& t) {
	std::stringstream stream;
	std::string value;
	stream << "(" <<t.x << "," << t.y << ")";
	stream >> value;
	return value;
}

inline std::string orientationToString(const Ogre::Quaternion& t) {
	std::stringstream stream;
	std::string value;
	stream << "(" <<t.x << "," << t.y << "," << t.z << "," << t.w << "," << t.getPitch() << ","
		<< t.getRoll() << "," << t.getYaw() << ")";
	stream >> value;
	return value;
}

#endif