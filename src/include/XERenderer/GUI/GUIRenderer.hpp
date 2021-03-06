#ifndef _GUIRENDERER_HPP
#define _GUIRENDERER_HPP

#include <map>
#include <string>
#include <vector>
#include <memory>
//#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
//#include <Ogre/OgreMain/include/Math/Array/OgreObjectMemoryManager.h>

#include <XESystem/SystemConfig.hpp>
#include <ThirdParty/sfml/include/sfml/System/String.hpp>
#include <ThirdParty/sfml/include/sfml/System/Vector2.hpp>
#include <XERenderer/GUI/Font.hpp>
#include <XERenderer/GUI/LayerRenderer.hpp>

#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>

#ifdef CompileEditor
#include <XERenderer/Editor/EditorUIRenderer.hpp>
#endif

namespace Ogre {
	class ObjectMemoryManager;
	class SceneManager;
	class Camera;
}

namespace sol { class state;  }

namespace XE
{
	//forwarding
	class ImgGuiMovableObject;
	class WScreenRenderable;
	class WScreen;
	class GraphicsManager;
	class TextureAtlas;


#ifdef CompileEditor
	struct TransformInfo
	{
		Ogre::Vector3 position;
		Ogre::Quaternion rotation;
		Ogre::Vector3 scale;
	};
#endif

	struct AtlasData
	{
		TextureAtlas*  _t_textureAtlasPtr;
		sf::Vector2f    texelOffset;
		sf::Vector2f    textureSize;
	};

	struct SpriteData
	{
		float uvTop, uvLeft, uvRight, uvBottom, spriteWidth, spriteHeight;

		sf::Vector2f    texCoords[4];
	};

	class GUIRenderer
	{
	public:
		GUIRenderer(GraphicsManager& graphicsManager);

		~GUIRenderer();		
		
		void addScreen(WScreen* screen);	

		GraphicsManager& getGraphicsManager() { return m_graphicsManager; }
		
		void registerObject(sol::state& lua);
		
		void loadAtlas(const void *buf);
		
	//	sf::Vector2i GetTextStringMetrics(const std::basic_string<XE::Uint32>& string, unsigned int font_size) const;

		sf::Vector2i GetTextStringMetrics(const sf::String& string, const Font* font) const;

		const SpriteData* getSprite(const std::string& spriteName);

		const Font* getFont(const XE::Uint32 fontId) const;

		AtlasData& getAtlasData(const XE::Uint16& id);

		LayerRenderer& getLayerRenderer();

		void update();

		//returned pointer only usable in renderthread
		TextureAtlas* _t_getAtlas(const XE::Uint16 atlasId);
		void _t_update(float delta);
		void _t_init(TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);

		void _t_resizeRenderWindow(size_t w, size_t h);
		
#ifdef CompileEditor		
		void EnableEditor(bool enable);

		void _t_initEditorUIRenderer(Ogre::Camera* camera);

		EditorUIRenderer* _t_EditorUIRenderer;

		//will be send(copied) to rendererthread each frame

		TransformInfo  m_CurrentGizmoOrigin;
		Ogre::Vector2 m_CurrentPointPosition; //mouse cursor

		//copied from mainthread into renderthread
		TransformInfo _t_CurrentGizmoOrigin;
		Ogre::Vector2 _t_CurrentPointPosition; //mouse cursor

#endif

		//internal
		sf::Vector2f _whitePixelPos;
		
		sf::Vector2f m_ViewportSize;

	private:

#ifdef CompileEditor
		
		bool m_editorEnabled;


#endif

		LayerRenderer m_layerRenderer;
		
		Ogre::Matrix4 m_ProjMatrix;

		std::map<XE::Uint16, std::unique_ptr<TextureAtlas>> _t_atlas;
		
		void  _calculateCoordinates(sf::Vector2f texelOffset, sf::Vector2f inverseTextureSize);

		void addAtlas(const std::string& atlasName, const std::string& texName, const std::string& ressGroup, XE::Uint16 atlasId = 0);

		sf::Vector2f m_TexelOffset;
	
		std::vector<WScreen*> m_screens;
		GraphicsManager& m_graphicsManager;

		std::map<XE::Uint16, std::unique_ptr<AtlasData>> _atlasData;

		//data for mainthread
		std::map<std::string, std::unique_ptr<SpriteData>> _sprites;
		std::map<XE::Uint32, Font> _fonts;

	};

} // namespace XE


#endif // _GUIRENDERER_HPP