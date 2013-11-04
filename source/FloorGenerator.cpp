#include "FloorGenerator.h"
#include "Game.h"
#include "Floor.h"
#include "noiseutils.h"

#include <noise.h>
#include <math.h>
#include <time.h>
#include <random>
#include <cstdlib>

FloorGenerator::FloorGenerator(const std::string& floorName) {
	createFloor(floorName);
}

FloorGenerator::~FloorGenerator() {
	delete points;
	delete lines;
}

void FloorGenerator::createFloor(const std::string& floorName) {
	module::Billow baseFlatTerrain;
	baseFlatTerrain.SetFrequency(0.5);
	module::ScaleBias flatTerrain;
	flatTerrain.SetSourceModule(0, baseFlatTerrain);
	flatTerrain.SetScale(0.125);

	utils::NoiseMap map;
	utils::NoiseMapBuilderPlane builder;
	builder.SetSourceModule(flatTerrain);
	builder.SetDestNoiseMap(map);
	builder.SetDestSize(214, 214);
	builder.SetBounds(6, 10, 1, 5);
	builder.Build();

	noise::utils::RendererImage renderer;
	noise::utils::Image image;
	renderer.SetSourceNoiseMap(map);
	renderer.SetDestImage(image);

	std::srand((unsigned int)std::time(NULL));
	Ogre::Vector2 start = Ogre::Vector2(5, 100);
	Ogre::Vector2 end = Ogre::Vector2(550, 400);

	points = createLine(start, end);

	for(int i = 0; i < 214; i++) {
		for(int j = 0; j < 214; j++) {
			Ogre::Vector2 currentPoint;
			currentPoint.x = i;
			currentPoint.y = j;
			float minDistance = 99999.f;
			for(int k = 0; k < (DEPTH*DEPTH)-1; k++) {
				Ogre::Vector2 p0 = points[i];
				Ogre::Vector2 p1 = points[i+1];
				float distance = lineDistance(p0, p1, currentPoint);
				if(distance < minDistance) {
					minDistance = distance;
				}
			}
			if(minDistance < 45) {
				float value = map.GetValue(i, j);
				float functionValue = valley(value);
				map.SetValue(i, j, value-(0.5f-functionValue));
			}
		}
	}

	renderer.Render();
	noise::utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("C:\\Users\\dujo\\Documents\\Visual Studio 2010\\Projects\\Omecha\\Omecha\\data\\texture\\" + floorName);
	writer.WriteDestFile();
}

float FloorGenerator::lineDistance(Ogre::Vector2 v, Ogre::Vector2 w, Ogre::Vector2 p) {
	const float l = (w.x-v.x)*(w.x-v.x) + (w.y-v.y)*(w.y-v.y);
	if(l == 0)
		return Ogre::Math::Abs(p.x-v.x) + Ogre::Math::Abs(p.y-v.y);
	const float t = (p-v).dotProduct(w-v)/l;
	if(t < 0)
		return Ogre::Math::Abs(p.x-v.x) + Ogre::Math::Abs(p.y-v.y);
	else if(t > 1)
		return Ogre::Math::Abs(p.x-w.x) + Ogre::Math::Abs(p.y-w.y);
	const Ogre::Vector2 projection = v+t * (w-v);
	return Ogre::Math::Abs(p.x-projection.x) + Ogre::Math::Abs(p.y-projection.y);
}

Ogre::Vector2* FloorGenerator::createLine(Ogre::Vector2 start, Ogre::Vector2 end) {
	int totalPoints = DEPTH * DEPTH;
	Ogre::Vector2* ppoints = new Ogre::Vector2[totalPoints];
	ppoints[0] = start;
	ppoints[(totalPoints-1)] = end;
	return point(ppoints, 0, (totalPoints-1), 0);
}

Ogre::Vector2* FloorGenerator::point(Ogre::Vector2* points, int start, int end, int depth) {
	if(depth >= DEPTH) {
		return points;
	}

	Ogre::Vector2 midpoint;
	midpoint.x = (points[start].x + points[end].x)/2;
	midpoint.y = (points[start].y + points[end].y)/2;

	float xrand = randomDepth(depth);
	float yrand = randomDepth(depth);

	midpoint.y += yrand;
	int current = (start+end)/2;
	points[current] = midpoint;
	points = point(points, start, current, depth+1);
	points = point(points, current, end, depth+1);
	return points;
}

float FloorGenerator::valley(float x) {
	return 1/(1+std::pow(2.718f, -(x*10.f-5.f)))/2;
}

Ogre::Vector2* FloorGenerator::getLine() {
	lines = new Ogre::Vector2[DEPTH*DEPTH];
	
	for(int i = 0; i < DEPTH * DEPTH; i++) {
		lines[i].x = points[i].x;
		lines[i].y = points[i].y;
	}
	return lines;
}

float FloorGenerator::randomDepth(int depth) {
	float reduce = std::pow(0.5f, depth+1);
	float random = (((float)rand())/RAND_MAX)*reduce;
	float max = 300;
	return max * random;
}