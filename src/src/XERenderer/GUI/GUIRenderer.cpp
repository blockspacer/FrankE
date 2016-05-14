#include <XERenderer/GUI/GUIRenderer.hpp>

#include <Ogre/OgreMain/include/OgreVector2.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/Screen.hpp>
#include <XERenderer/GUI/WScreen.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include <XEUI/DAL/FB_UI_Atlas_generated.h>

#include <XESystem/Logging.hpp>

#include <XEDAL/PhysFS/PhysFsStream.hpp>

#include <XEScripts/LUAEngine.h>
#include <XEUI/Font.hpp>
#include <XEUI/Glyph.hpp>

namespace XE
{

	GUIRenderer::GUIRenderer(GraphicsManager& graphicsManager)
		: m_graphicsManager(graphicsManager)
		, m_layerRenderer(graphicsManager)
	{
		//create default atlas with id 0
		std::unique_ptr<AtlasData> atlasData = std::unique_ptr<AtlasData>(new AtlasData());
		_atlasData[0] = std::move(atlasData);

	}

	GUIRenderer::~GUIRenderer()
	{
	}

	void GUIRenderer::_t_init(TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr)
	{
		m_layerRenderer._t_initRenderer(atlas, objManager, sceneMgr);
	}

	void GUIRenderer::update()
	{
		m_layerRenderer.update();
	}

	void GUIRenderer::_t_update()
	{
		//todo lock m_screens (dont add delete while renderonce is called)
	/*		m_graphicsManager.getIntoRendererQueue().push([this]()
		{*/

	//	m_layerRenderer._t_update();
	//	done in gorilla renderqueue!?
			/*for each (WScreen* var in m_screens)
			{
				var->_t_screen->renderOnce();
			}*/
	//	});
	}

	void GUIRenderer::addScreen(WScreen* screen)
	{
		m_screens.push_back(screen);
	}


	const SpriteData* GUIRenderer::getSprite(const std::string& spriteName)
	{
		if (_sprites.find(spriteName) == _sprites.end());
		LOG(ERROR) << "sprite not found: " << spriteName;

		return _sprites[spriteName].get();
	}

	void GUIRenderer::registerObject(sol::state& lua)
	{
		lua.new_usertype<GUIRenderer>("GUIRenderer",

			//properties
			//"guiRenderer", sol::property(&GraphicsManager::getGUIRenderer)

			//functions
			"loadAtlas", &GUIRenderer::loadAtlas
			);

		auto stateView = lua.set("GUIRenderer", this); //set object instance
	}

	void GUIRenderer::loadAtlas(const std::string& fileName)
	{
		PhysFsStream wonderfullStream;
		if (wonderfullStream.open(fileName.c_str()))//"UI/TestAtlas.fbbin"))
		{
			// Make sure that the stream's reading position is at the beginning
			wonderfullStream.seek(0);

			std::vector<char> buffer(wonderfullStream.getSize());
			if (wonderfullStream.read(buffer.data(), wonderfullStream.getSize()))
			{
				auto atlas = XFBType::GetAtlas(&buffer[0]);

				std::string atlasName = atlas->name()->c_str();
				addAtlas(atlasName, atlas->texture()->c_str(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

				LOG(INFO) << "load sprite data";
				
				//sprites
				for (auto it = atlas->sprites()->begin(); it != atlas->sprites()->end(); ++it)
				{
					std::unique_ptr<SpriteData> newSprite = std::unique_ptr<SpriteData>(new SpriteData());
					newSprite->spriteWidth = (*it)->width(); // width
					newSprite->spriteHeight = (*it)->height(); // height
					newSprite->uvLeft = (*it)->posX();
					newSprite->uvBottom = (*it)->posY() - (*it)->height();
					newSprite->uvTop = (*it)->posY();
					newSprite->uvRight = newSprite->uvLeft + (*it)->posX();

					_sprites[(*it)->name()->c_str()] = std::move(newSprite);
				}

				//fonts
				for (auto it = atlas->fonts()->begin(); it != atlas->fonts()->end(); ++it)
				{
					std::unique_ptr<Font> newFont = std::unique_ptr<Font>(new Font());
					
					//glyphs
					for (auto itGlyph = (*it)->glyphs()->begin(); itGlyph != (*it)->glyphs()->end(); ++itGlyph)
					{
						LOG(INFO) << "Glyph:";
						LOG(INFO) << "code:" << (*itGlyph)->code();

						std::unique_ptr<FontGlyph> newGlyph = std::unique_ptr<FontGlyph>(new FontGlyph());
						newGlyph->glyphAdvance = (*itGlyph)->glyphAdvance();
						newGlyph->glyphHeight = (*itGlyph)->glyphHeight();
						newGlyph->glyphWidth = (*itGlyph)->glyphWidth();

						if ((*itGlyph)->kerningList())
						{
							//kerning
							for (auto itKerning = (*itGlyph)->kerningList()->begin(); itKerning != (*itGlyph)->kerningList()->end(); ++itKerning)
							{
								std::unique_ptr<GlyphKerning> newKerning = std::unique_ptr<GlyphKerning>(new GlyphKerning((*itKerning)->character()
									, (*itKerning)->kerning()));
								newGlyph->kerning.emplace_back(std::move(newKerning));
							}
						}
						
						newGlyph->uvBottom = (*itGlyph)->uvBottom();
						newGlyph->uvHeight = (*itGlyph)->uvHeight();
						newGlyph->uvLeft = (*itGlyph)->uvLeft();
						newGlyph->uvRight = (*itGlyph)->uvRight();
						newGlyph->uvTop = (*itGlyph)->uvTop();
						newGlyph->uvWidth = (*itGlyph)->uvWidth();
						newGlyph->verticalOffset = (*itGlyph)->verticalOffset();

						newFont->mGlyphs[(*itGlyph)->code()] = std::move(newGlyph);
					}

					newFont->mBaseline = (*it)->baseline();
					newFont->mLetterSpacing = (*it)->letterSpacing();
					newFont->mLineHeight = (*it)->lineHeight();
					newFont->mLineSpacing = (*it)->lineSpacing();
					newFont->mMonoWidth = (*it)->monoWidth();
				//	newFont->mRangeBegin = (*it)->rangeBegin();
				//	newFont->mRangeEnd = (*it)->rangeEnd();
					newFont->mSpaceLength = (*it)->spaceLength();

					_fonts[(*it)->id()] = std::move(newFont);
				}

				//todo from renderthread! ?? into main thread_calculateCoordinates();
			}
		}
	}

	XE::Uint16  GUIRenderer::GetFontLineHeight(XE::Uint16 font_size) const
	{
		return 22;
	}

	void  GUIRenderer::_calculateCoordinates(sf::Vector2f texelOffset , sf::Vector2f inverseTextureSize)
	{
		for (std::map<XE::Uint32, std::unique_ptr<Font>>::iterator gd_it = _fonts.begin(); gd_it != _fonts.end(); gd_it++)
		{
			for (std::unordered_map<Uint32, std::unique_ptr<FontGlyph>>::iterator it = (*gd_it).second.get()->mGlyphs.begin(); it != (*gd_it).second.get()->mGlyphs.end(); it++)
			{

				(*it).second->uvLeft -= texelOffset.x;
				(*it).second->uvTop += texelOffset.y;
				(*it).second->uvRight += texelOffset.x;
				(*it).second->uvBottom -= texelOffset.y;

				(*it).second->uvLeft *= inverseTextureSize.x;
				(*it).second->uvTop *= inverseTextureSize.y;
				(*it).second->uvRight *= inverseTextureSize.x;
				(*it).second->uvBottom *= inverseTextureSize.y;

				(*it).second->texCoords[TopLeft].x = (*it).second->uvLeft;
				(*it).second->texCoords[TopLeft].y = (*it).second->uvTop;
				(*it).second->texCoords[TopRight].x = (*it).second->uvRight;
				(*it).second->texCoords[TopRight].y = (*it).second->uvTop;
				(*it).second->texCoords[BottomRight].x = (*it).second->uvRight;
				(*it).second->texCoords[BottomRight].y = (*it).second->uvBottom;
				(*it).second->texCoords[BottomLeft].x = (*it).second->uvLeft;
				(*it).second->texCoords[BottomLeft].y = (*it).second->uvBottom;

				(*it).second->glyphWidth = (*it).second->uvWidth;
				(*it).second->glyphHeight = (*it).second->uvHeight;

			}
		}

		for (std::map<std::string, std::unique_ptr<SpriteData>>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
		{
			(*it).second->uvRight = (*it).second->uvLeft + (*it).second->spriteWidth;
			(*it).second->uvBottom = (*it).second->uvTop + (*it).second->spriteHeight;

			(*it).second->uvLeft *= inverseTextureSize.x;
			(*it).second->uvTop *= inverseTextureSize.y;
			(*it).second->uvRight *= inverseTextureSize.x;
			(*it).second->uvBottom *= inverseTextureSize.y;

			(*it).second->texCoords[TopLeft].x = (*it).second->uvLeft;
			(*it).second->texCoords[TopLeft].y = (*it).second->uvTop;
			(*it).second->texCoords[TopRight].x = (*it).second->uvRight;
			(*it).second->texCoords[TopRight].y = (*it).second->uvTop;
			(*it).second->texCoords[BottomRight].x = (*it).second->uvRight;
			(*it).second->texCoords[BottomRight].y = (*it).second->uvBottom;
			(*it).second->texCoords[BottomLeft].x = (*it).second->uvLeft;
			(*it).second->texCoords[BottomLeft].y = (*it).second->uvBottom;
		}
	}

	//todo dont use global func!?
	float _getAdvance(const FontGlyph* glyph, float kerning)
	{
		//if (mFixedWidth)
		//	return mGlyphData->mMonoWidth;
		//else
		return glyph->glyphAdvance + kerning;
	}

	sf::Vector2i GUIRenderer::GetTextStringMetrics(const std::basic_string<XE::Uint32>& string, unsigned int font_size) const
	{
		const Font* font = getFont(20); //fontsize 9 = Id

		sf::Vector2i retSize;

		if (!font)
			return retSize;

		float cursor = 0,
			kerning = 0;

		unsigned char thisChar = 0, lastChar = 0;
		const FontGlyph* glyph = 0;
		retSize.x = 0;
		retSize.y = GetFontLineHeight(font_size);// mGlyphData->mLineHeight;

		for (size_t i = 0; i < string.length(); i++)
		{
			thisChar = string[i];

			if (thisChar == ' ')
			{
				lastChar = thisChar;
				cursor += font->mSpaceLength;
				continue;
			}

			/*if (thisChar < font->mRangeBegin || thisChar > font->mRangeEnd)
			{
				lastChar = 0;
				continue;
			}*/

			glyph = font->getGlyph(thisChar);
			if (glyph == 0)
				continue;
			kerning = glyph->getKerning(lastChar);
			if (kerning == 0)
				kerning = font->mLetterSpacing;

			cursor += _getAdvance(glyph, kerning);
			lastChar = thisChar;

		} // for

		retSize.x = cursor - kerning;

		return retSize;
	}

    const Font* GUIRenderer::getFont(const XE::Uint32 fontId) const
	{
		std::map<XE::Uint32, std::unique_ptr<Font>>::const_iterator it = _fonts.find(fontId);
		if (it == _fonts.end())
		{
			LOG(ERROR) << "Glyph not found: " << fontId;
			return 0;
		}
		else
			return (*it).second.get();
	}

	sf::Vector2i GUIRenderer::GetTextStringMetrics(const sf::String& string, unsigned int font_size) const
	{
		const Font* font = getFont(20); //fontsize 9 = Id

		sf::Vector2i retSize;

		if (!font)
			return retSize;

		float cursor = 0,
			kerning = 0;

		unsigned char thisChar = 0, lastChar = 0;
		const FontGlyph* glyph = 0;
		retSize.x = 0;
		retSize.y = GetFontLineHeight(font_size);// mGlyphData->mLineHeight;

		for (size_t i = 0; i < string.getSize(); i++)
		{
			thisChar = string[i];

			if (thisChar == ' ')
			{
				lastChar = thisChar;
				cursor += font->mSpaceLength;
				continue;
			}

		/*	if (thisChar < font->mRangeBegin || thisChar > font->mRangeEnd)
			{
				lastChar = 0;
				continue;
			}*/

			glyph = font->getGlyph(thisChar);
			if (glyph == 0)
				continue;
			kerning = glyph->getKerning(lastChar);
			if (kerning == 0)
				kerning = font->mLetterSpacing;

			cursor += _getAdvance(glyph, kerning);
			lastChar = thisChar;

		} // for

		retSize.x = cursor - kerning;

		return retSize;
	}


	LayerRenderer& GUIRenderer::getLayerRenderer()
	{
		return m_layerRenderer;
	}

	AtlasData& GUIRenderer::getAtlasData(const XE::Uint16& id)
	{
		return *(*_atlasData.find(id)).second.get();
	}

	void GUIRenderer::addAtlas(const std::string& atlasName, const std::string& texName, const std::string& ressGroup, XE::Uint16 atlasId)
	{
		//create atlasdata in mainthread
		auto atlasDataPtr = &getAtlasData(atlasId);
		if (!atlasDataPtr)
		{
			std::unique_ptr<AtlasData> atlasData = std::unique_ptr<AtlasData>(new AtlasData());
			atlasDataPtr = (_atlasData[atlasId] = std::move(atlasData)).get();
		}

		m_graphicsManager.getIntoRendererQueue().push([this, atlasName, texName, ressGroup, atlasDataPtr, atlasId]() {
						
			//load Textures -> todo getByName without file extension!?
			Ogre::TexturePtr texture = Ogre::TextureManager::getSingletonPtr()->getByName(texName, ressGroup);

			if (texture.isNull())
				texture = Ogre::TextureManager::getSingletonPtr()->load(texName, ressGroup, Ogre::TEX_TYPE_2D, 0);

			std::unique_ptr<TextureAtlas> atlas = std::unique_ptr<TextureAtlas>(new TextureAtlas(texture)); // t1 + ".gorilla", t2));

			XE::Uint32 texWidth = texture->getWidth();
			XE::Uint32 textHeight = texture->getHeight();

			Ogre::RenderSystem* rs = Ogre::Root::getSingletonPtr()->getRenderSystem();

			sf::Vector2f texelOffset;
			texelOffset.x = rs->getHorizontalTexelOffset();
			texelOffset.y = rs->getVerticalTexelOffset();

			sf::Vector2f inverseTextureSize;
			inverseTextureSize.x = 1.0f / texture->getWidth();
			inverseTextureSize.y = 1.0f / texture->getHeight();

			atlasDataPtr->_t_textureAtlasPtr = atlas.get();

			auto sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MyFirstSceneManager");

			_t_init(atlasDataPtr->_t_textureAtlasPtr, &sceneMgr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), sceneMgr);

			//calculation in mainthread
			m_graphicsManager.getFromRendererQueue().push([this, texelOffset, inverseTextureSize, atlasDataPtr, texWidth, textHeight]() {
				
				atlasDataPtr->texelOffset = texelOffset;
				atlasDataPtr->textureSize = sf::Vector2f(texWidth, textHeight);
				_calculateCoordinates(texelOffset, inverseTextureSize);
				
				auto tmp = getSprite("whitepixel.png");
				float texelOffsetX = atlasDataPtr->texelOffset.x, texelOffsetY = atlasDataPtr->texelOffset.y;
				texelOffsetX /= atlasDataPtr->textureSize.x;
				texelOffsetY /= atlasDataPtr->textureSize.y;
				_whitePixelPos.x = tmp->uvLeft - texelOffsetX;
				_whitePixelPos.y = tmp->uvTop + texelOffsetY;

				//redraw all uv's
				m_layerRenderer.redrawAllLayers();
			});

			_t_atlas[atlasId] = std::move(atlas);
		});
	}

	//void addAtlas(TextureAtlas* atlas){ _t_atlas.push_back(atlas); }

	//WScreenRenderable* createScreenRenderable(Ogre::Vector3 position, const std::string& atlasName);
	//WScreen* createScreen(const std::string& atlasName);

	//change only in renderthread!
	//	TextureAtlas* _t_atlas;

	//return value only usable in renderthread
	TextureAtlas* GUIRenderer::_t_getAtlas(const XE::Uint16 atlasId) {
		return (*_t_atlas.find(atlasId)).second.get();
	}


} // namespace XE