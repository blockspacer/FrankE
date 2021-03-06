#ifndef _RENDERABLESHAPE_HPP
#define _RENDERABLESHAPE_HPP

#include <Ogre/OgreMain/include/OgreColourValue.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreVector3.h>

#include <vector>
#include <atomic>
#include <memory>

namespace XE
{
	class WLayer;
	class GUIRenderer;
	class LayerRenderer;

	///Structure for a single vertex.		
	struct Vertex
	{
		Vertex(){}
		Vertex(const Ogre::Vector3& pos, const Ogre::ColourValue& col)
			: position(pos)
			 ,colour(col)
		{

		}

		Ogre::Vector3 position;
		Ogre::ColourValue colour;
		Ogre::Vector2 uv;
	};


	//BaseClass
	/// lives in mainthread
	class RenderableShape
	{
	public:

		RenderableShape(WLayer& wLayer);

		~RenderableShape();

		virtual void _refresh() = 0;

		virtual std::vector<Vertex>& _update() = 0;

		bool isDirty;

		bool isVisible;

	protected:

		std::vector<Vertex> m_verticesBuffer;
		GUIRenderer& m_guiRenderer;
		WLayer& m_layer;

	private:

		LayerRenderer* _layerRenderer;

	};


	class RenderableShapesContainer
	{
	public:
		RenderableShapesContainer()
		: m_show(true){

		}

		void Show(bool show)
		{
			for (auto& shape : shapes)
			{
				shape->isVisible = show;
			}
			m_show = show;
		}
	
		std::vector<std::unique_ptr<RenderableShape>> shapes;

	private :
		bool m_show;
	};
}

#endif