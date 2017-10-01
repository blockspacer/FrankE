#pragma once

#include <OgreRenderable.h>
#include <OgreRenderOperation.h>
#include <XERenderer/private/ScreenRenderable.hpp>

class ImguiRenderable : public XE::ScreenRenderable
{
public:
	ImguiRenderable();
	~ImguiRenderable();

	//builds the vertex buffer
	void updateVertexData(const ImDrawVert* vtxBuf, const ImDrawIdx* idxBuf, unsigned int vtxCount, unsigned int idxCount);

	//Overrides from Renderable
	void getWorldTransforms(Ogre::Matrix4* xform) const;
	void getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass);
	const Ogre::LightList& getLights(void) const;

private:
	Ogre::v1::RenderOperation mRenderOp;
	int mVertexBufferSize, mIndexBufferSize;
};