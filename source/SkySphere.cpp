#include "SkySphere.h"

SkySphere::SkySphere(const std::string& material, Ogre::Real r) :
  radius(r) {
	Ogre::Entity* skySphereEntity = Game::getScene()->createEntity("SkySphereEntity", "SkySphere");
	skySphereEntity->setMaterialName(material);
	skySphereEntity->setRenderQueueGroup(Ogre::RENDER_QUEUE_WORLD_GEOMETRY_1);
	skySphereEntity->setCastShadows(false);
	Game::getScene()->getRootSceneNode()->createChildSceneNode()->attachObject(skySphereEntity);
}

SkySphere::~SkySphere() {
}

void SkySphere::loadSphere() {
    const int rings = 10;
    const int segments = 18;

	Ogre::MeshPtr sphere = Ogre::MeshManager::getSingleton().createManual("SkySphere", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::SubMesh *sphereVertex = sphere->createSubMesh();
	sphereVertex->vertexData = new Ogre::VertexData();
	sphereVertex->useSharedVertices = false;

	Ogre::VertexData* vertexData = sphereVertex->vertexData;
	Ogre::IndexData* indexData = sphereVertex->indexData;

    // the vertex format
	Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
	size_t currentOffset = 0;

	// positions
	vertexDecl->addElement(0, currentOffset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	currentOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    // colors
    vertexDecl->addElement(0, currentOffset, Ogre::VET_FLOAT1, Ogre::VES_TEXTURE_COORDINATES);
    currentOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);

	// allocate the vertex buffer
	vertexData->vertexCount = (rings + 1) * (segments + 1);
	Ogre::HardwareVertexBufferSharedPtr vBuf = 
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0),
		vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
	binding->setBinding(0, vBuf);
	float* vertex = static_cast<float*>(vBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

	// allocate index buffer
	indexData->indexCount = 6 * rings * (segments + 1);
	indexData->indexBuffer = 
		Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
		indexData->indexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	Ogre::HardwareIndexBufferSharedPtr iBuf = indexData->indexBuffer;
	unsigned short* indices = static_cast<unsigned short*>(iBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

	float deltaRingAngle = Ogre::Math::PI / rings;
	float deltaSegAngle = 2 * Ogre::Math::PI / segments;
	unsigned short verticeIndex = 0;

	// Generate the group of rings for the sphere
	for(int ring = 0; ring <= rings; ring++) {
		float r0 = radius * std::sin(ring * deltaRingAngle);
		float y0 = radius * std::cos(ring * deltaRingAngle);

		// Generate the group of segments for the current ring
		for(int seg = 0; seg <= segments; seg++) {
			float x0 = r0 * std::sin(seg * deltaSegAngle);
			float z0 = r0 * std::cos(seg * deltaSegAngle);

			// Add one vertex to the strip which makes up the sphere
			*vertex++ = x0;
			*vertex++ = y0;
			*vertex++ = z0;

            Ogre::Vector3 normal = Ogre::Vector3(x0, y0, z0).normalisedCopy();

            // Calculate color
            const Ogre::Vector3 dirToLight = Ogre::Vector3(0.0f, 1.0f, 0.0f);
			const float texSize = 512.0f;
            float factor = (dirToLight.dotProduct(normal) * 0.5f + 0.5f) * (texSize-2)/texSize + 1.0f/texSize;
            *vertex++ = factor;

			if (ring != rings) {
				// each vertex (except the last) has six indices pointing to it
				*indices++ = verticeIndex + segments + 1;
				*indices++ = verticeIndex;
				*indices++ = verticeIndex + segments;
				*indices++ = verticeIndex + segments + 1;
				*indices++ = verticeIndex + 1;
				*indices++ = verticeIndex;
				verticeIndex ++;
			}
		}
	}
	
	// Unlock
	vBuf->unlock();
	iBuf->unlock();

    // Set bounds
	sphere->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-radius, -radius, -radius),
		Ogre::Vector3(radius, radius, radius) ), false);
	sphere->_setBoundingSphereRadius(radius);
	sphere->load();
}

void SkySphere::setVisible(bool visible) {
	Game::getScene()->getEntity("SkySphereEntity")->setVisible(visible);
}

void SkySphere::update(Ogre::Real radius) {
	Game::getScene()->getRootSceneNode()->setPosition(Game::camera->getCamera()->getDerivedPosition());
	Game::getScene()->getRootSceneNode()->setScale(radius, radius, radius);
}