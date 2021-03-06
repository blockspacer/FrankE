#include <XERenderer/GUI/LayerRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XERenderer/GUI/RenderableLayer.hpp>
#include <XERenderer/GUI/RenderableShape.hpp>

#include <XERenderer/GUI/WLayer.hpp>

#include "Vao/OgreVaoManager.h"
#include "Vao/OgreVertexArrayObject.h"

#include <Ogre/OgreMain/include/OgreSceneManager.h>

namespace XE {
	
	LayerRenderer::LayerRenderer(GraphicsManager& graphMgr)
		: m_graphMgr(graphMgr)
		, _t_OgreSceneMgrPtr(0)
	{

	}

	RenderableLayer* LayerRenderer::_t_createRenderableLayer(XE::Uint32 id, const XE::Uint16 atlasId)
	{
		assert(_t_OgreSceneMgrPtr);
			

		RenderableLayer* layer = new RenderableLayer(id,
													m_graphMgr.getGUIRenderer(),
													&_t_OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_STATIC)
													, _t_OgreSceneMgrPtr,
													atlasId);
		_t_renderableLayerPtrs.emplace_back(layer);

		return _t_renderableLayerPtrs.back();
	}

	void LayerRenderer::_t_onResizeRenderWindow(size_t w, size_t h)
	{
		Ogre::Matrix4 projMatrix(2.0f / w, 0.0f, 0.0f, -1.0f,
			0.0f, -2.0f / h, 0.0f, 1.0f,
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		for each (auto layer in _t_renderableLayerPtrs)
		{
			for each (auto renderable in layer->mRenderables)
			{
				static_cast<ScreenRenderable*>(renderable)->setCustomProjectionMatrix(true, projMatrix);
			}		
		}
	}

	void LayerRenderer::_t_destroyRenderableLayer(RenderableLayer* layer)
	{
		_t_renderableLayerPtrs.erase(std::find(_t_renderableLayerPtrs.begin(), _t_renderableLayerPtrs.end(), layer));
	}

	void LayerRenderer::addWlayer(WLayer* wlayer)
	{
		m_wLayers.emplace_back(wlayer);
	}

	void LayerRenderer::removeWlayer(WLayer* wlayer)
	{
		m_wLayers.erase(std::find(m_wLayers.begin(), m_wLayers.end(), wlayer));
	}

	void LayerRenderer::_t_initRenderer(TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr)
	{
		 _t_OgreSceneMgrPtr = sceneMgr;
	}

	void LayerRenderer::redrawAllLayers()
	{
		for each (auto wlayerPtr in m_wLayers)
		{
			for each (auto shape in wlayerPtr->getRenderableShapes())
			{
				shape->_refresh();
				shape->isDirty =  true;
			}
			wlayerPtr->isDirty = true;
		}
	}

	void LayerRenderer::update()
	{
		for each (auto wlayerPtr in m_wLayers)
		{
			wlayerPtr->update();
		}
	}
}