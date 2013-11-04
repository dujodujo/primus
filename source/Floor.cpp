#include "Floor.h"

Floor::Floor(Ogre::Real width, Ogre::Real height, 
	Ogre::String planeMesh, Ogre::String planeEntity, Ogre::String materialName, Ogre::String textureName) :
  Plane(width, height),
  plane(Ogre::Vector3::UNIT_Y, 0) {

	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(materialName, 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* tuisTexture = mat->getTechnique(0)->getPass(0)->createTextureUnitState(textureName);
 
	Ogre::MovablePlane* plane = new Ogre::MovablePlane("Plane");
	plane->d = 0;
	plane->normal = Ogre::Vector3::UNIT_Y;
 
	Ogre::MeshManager::getSingleton().createPlane(planeMesh, 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		*plane, width, height, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* pe = Game::getScene()->createEntity(planeEntity, planeMesh);
	pe->setMaterialName(materialName);
 
	Ogre::SceneNode* planeNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	planeNode->attachObject(pe);
}

void Floor::createFloorModel() {
	const std::string& name = "terrainMaterial";
	const Ogre::Real detailDensity = 16;

	const unsigned int step = 1 << 0;
	const unsigned int textureSizeWidth = 10;
    const unsigned int textureSizeHeight = 6;

	const Ogre::Real mpp = 8;
	const int realPageSize = 256;
	const unsigned int pageSize = realPageSize / mpp;

    //calculate number of terrain pages
    const unsigned int numPagesWidth = textureSizeWidth / pageSize;
    const unsigned int numPagesHeight = textureSizeHeight / pageSize;

	for(unsigned int k = 0; k < numPagesWidth; ++k) {
        for (unsigned int l = 0; l < numPagesHeight; ++l) {
            //offsets for this cell
            unsigned int originX = k * pageSize;
            unsigned int originY = l * pageSize;

            //create the mesh part
			Ogre::ManualObject* terrainMesh = Game::getScene()->createManualObject(
				"terrain_mesh_" + toString(l) + "_" + toString(k));

            //create the mesh manually by defining triangle pairs - apply the terrain_name material
            terrainMesh->begin(name);

            for (unsigned int i = 0; i + step <= pageSize; i += step) {
				unsigned int is = i + step;
                for (unsigned int j = 0; j + step <= pageSize; j += step) {
                    unsigned int js = j + step;

                    unsigned int positionX[4];
                    unsigned int positionY[4];
                    unsigned int coords;

                    //from bottom left anticlockwise
                    positionX[0] = originX + i;
                    positionY[0] = originY + j;
                    positionX[1] = originX + i;
                    positionY[1] = originY + js;
                    positionX[2] = originX + is;
                    positionY[2] = originY + js;
                    positionX[3] = originX + is;
                    positionY[3] = originY + j;

                    //first bottom-left vertex
					//mps = meters per pixel
                    coords = 0;
                    terrainMesh->position(i * mpp, 0, j * mpp);
                    terrainMesh->textureCoord(positionX[coords] / Ogre::Real(textureSizeWidth),
                                              positionY[coords] / Ogre::Real(textureSizeHeight));
                    terrainMesh->textureCoord(i / detailDensity, j / detailDensity);
                    terrainMesh->normal(0, 0, 0.5);

                    //first bottom-right vertex
                    coords = 1;
                    terrainMesh->position(i * mpp, 0, js * mpp);
                    terrainMesh->textureCoord(positionX[coords] / Ogre::Real(textureSizeWidth),
                                              positionY[coords] / Ogre::Real(textureSizeHeight));
                    terrainMesh->textureCoord(i / detailDensity, js / detailDensity);
					terrainMesh->normal(0, 0, 0.5);

                    //first top-right vertex
                    coords = 2;
                    terrainMesh->position(is * mpp, 0, js * mpp);
                    terrainMesh->textureCoord(positionX[coords] / Ogre::Real(textureSizeWidth),
                                              positionY[coords] / Ogre::Real(textureSizeHeight));
                    terrainMesh->textureCoord(is / detailDensity, js / detailDensity);
					terrainMesh->normal(0, 0, 0.5);

                    //second top-left vertex
                    coords = 3;
                    terrainMesh->position(is * mpp, 0, j * mpp);
                    terrainMesh->textureCoord(positionX[coords] / Ogre::Real(textureSizeWidth),
                                              positionY[coords] / Ogre::Real(textureSizeHeight));
                    terrainMesh->textureCoord(is / detailDensity, j / detailDensity);
					terrainMesh->normal(0, 0, 0.5);

                    //second bottom-left vertex
                    coords = 0;
                    terrainMesh->position(i * mpp, 0, j * mpp);
                    terrainMesh->textureCoord(positionX[coords] / Ogre::Real(textureSizeWidth),
                                              positionY[coords] / Ogre::Real(textureSizeHeight));
                    terrainMesh->textureCoord(i / detailDensity, j / detailDensity);
					terrainMesh->normal(0, 0, 0.5);

                    //second top-right vertex
                    coords = 2;
                    terrainMesh->position(is * mpp, 0, js * mpp);
                    terrainMesh->textureCoord(positionX[coords] / Ogre::Real(textureSizeWidth),
                                              positionY[coords] / Ogre::Real(textureSizeHeight));
                    terrainMesh->textureCoord(is / detailDensity, js / detailDensity);
					terrainMesh->normal(0, 0, 0.5);
                }
            }

            //finished creating traignles
            terrainMesh->end();

            //terrain entity
            terrainMesh->setQueryFlags(1 << 3);
            terrainMesh->setCastShadows(false);

            //attach to a scene node
			Ogre::SceneNode* cellNode = terrainNode->createChildSceneNode();
            cellNode->attachObject(terrainMesh);
			//position cells in agrid
            cellNode->setPosition(originX * mpp, 0, originY * mpp);
        }
    }
}

Floor::~Floor() {}