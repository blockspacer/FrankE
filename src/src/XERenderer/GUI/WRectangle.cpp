#include <XERenderer/GUI/WRectangle.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XEUI/DAL/FB_UI_StateData_generated.h> //need to include ... else link error
#include <XERenderer/GUI/WLayer.hpp>


//#include <Ogre/OgreMain/include/OgreLogManager.h>

namespace XE
{
	WRectangle::WRectangle(WLayer& wLayer, float left, float top, float width, float height)
		: RenderableShape(wLayer)
		, m_position(left, top)
		, _backgroundColor()
		, m_size(width, height)
		, _spriteImagePtr(0)
	{
		//m_position.x = left;
		//m_position.y = top;
		//m_size.x = width;
		//m_size.y = height;

		//std::stringstream tmp;
		//tmp << "x:" << left << "top" << top << "width" << width << "width" << height;
		//Ogre::LogManager::getSingleton().logMessage(tmp.str());
	}

	WRectangle::~WRectangle() 
	{	
	
	}

	const SpriteData* WRectangle::setBackgroundImage(const std::string& imageName)
	{
		_spriteImagePtr = m_guiRenderer.getSprite(imageName);
		background_image(_spriteImagePtr);

		return _spriteImagePtr;
	}

	void WRectangle::setPosition(const sf::Vector2f& position)
	{
		m_position = position;
		RenderableShape::isDirty = true;
	}

	void WRectangle::setSize(const sf::Vector2f& size) {

		m_size = size;
		RenderableShape::isDirty = true;
	}

	void WRectangle::setBackground(const XFB_UI::Colour* colour) {

		_backgroundColor.r = colour->r();
		_backgroundColor.g = colour->g();
		_backgroundColor.b = colour->b();
		_backgroundColor.a = colour->a();

		RenderableShape::isDirty = true;
	}

	void WRectangle::setBackground(const Colours::Colour& colour)
	{
		_backgroundColor = webcolour(colour);
		RenderableShape::isDirty = true;
	}

	void WRectangle::setBackground(const Ogre::ColourValue& colour)
	{
		_backgroundColor = colour;
		RenderableShape::isDirty = true;
	}

	sf::Vector2f& WRectangle::getPosition() { return m_position; }

	sf::Vector2f& WRectangle::getSize() { return m_size; }


	bool WRectangle::intersects(const Ogre::Vector2& coordinates) const
	{
		return ((coordinates.x >= m_position.x && coordinates.x <= m_position.x + m_size.x) && (coordinates.y >= m_position.y - m_size.y  && coordinates.y <= m_position.y));
	}

	void WRectangle::_refresh()
	{
	//	if (_spriteImagePtr)
			background_image(_spriteImagePtr);
	}

	void  WRectangle::background_image(const SpriteData* sprite)
	{
		if (sprite == 0 || m_layer.atlasData.textureSize.x == 0 || m_layer.atlasData.textureSize.y == 0)
		{
			//auto tmp = m_guiRenderer.getSprite("whitepixel.png");
			//_UV[0] = _UV[1] = _UV[2] = _UV[3] = Ogre::Vector2(tmp->texCoords().x, tmp->texCoords().y);// m_layer._t_Layer->_getSolidUV();
			//_UV[0].x = _UV[3].x = m_guiRenderer._whitePixelPos.x;
			//_UV[0].y = _UV[1].y = m_guiRenderer._whitePixelPos.y + 1;
			//_UV[1].x = _UV[2].x = m_guiRenderer._whitePixelPos.x +1;
			//_UV[2].y = _UV[3].y = m_guiRenderer._whitePixelPos.y;
			_UV[0] = _UV[1] = _UV[2] = _UV[3] = m_guiRenderer._whitePixelPos;
		}
		else
		{
			float texelOffsetX = m_layer.atlasData.texelOffset.x, texelOffsetY = m_layer.atlasData.texelOffset.y;
			texelOffsetX /= m_layer.atlasData.textureSize.x;
			texelOffsetY /= m_layer.atlasData.textureSize.y;
			_UV[0].x = _UV[3].x = sprite->uvLeft - texelOffsetX;
			_UV[0].y = _UV[1].y = sprite->uvBottom - texelOffsetY;
			_UV[1].x = _UV[2].x = sprite->uvRight + texelOffsetX;
			_UV[2].y = _UV[3].y = sprite->uvTop + texelOffsetY;
		}

		RenderableShape::isDirty = true;
	}

	std::vector<Vertex>&  WRectangle::_update()
	{
		if (!RenderableShape::isDirty)
			return RenderableShape::m_verticesBuffer;

		RenderableShape::m_verticesBuffer.clear();

		float texelOffsetX = m_layer.atlasData.texelOffset.x,
			texelOffsetY = m_layer.atlasData.texelOffset.y;

		//Ogre::Vector2 a, b, c, d;
		//a.x = m_position.x + texelOffsetX;
		//a.y = (m_position.y - m_size.y) + texelOffsetY;
		//b.x = (m_position.x + m_size.x) + texelOffsetX;
		//b.y = (m_position.y - m_size.y) + texelOffsetY;
		//c.x = m_position.x + texelOffsetX;
		//c.y = m_position.y + texelOffsetY;
		//d.x = (m_position.x + m_size.x) + texelOffsetX;
		//d.y = m_position.y + texelOffsetY;

		// Fill
		if (_backgroundColor.a != 0)
		{
			Vertex temp;

			// Triangle A
			//PUSH_VERTEX(getVerticesBuffer(), temp,
			//	-0.2, 0.2,
			//	_UV[3], _backgroundColor);    // Left/Bottom  3
			//PUSH_VERTEX(getVerticesBuffer(), temp,
			//	0,-0.2,
			//	_UV[1], _backgroundColor);    // Right/Top    1
			//PUSH_VERTEX(getVerticesBuffer(), temp,
			//	-0.2, -0.2,
			//	_UV[0], _backgroundColor);    // Left/Top     0

			//								  // Triangle B
			//PUSH_VERTEX(getVerticesBuffer(), temp,
			//	-0.2, -0.2,
			//	_UV[3], _backgroundColor);    // Left/Bottom   3
			//PUSH_VERTEX(getVerticesBuffer(), temp,
			//	0.2, 0.2,
			//	_UV[2], _backgroundColor);    // Right/Bottom  2
			//PUSH_VERTEX(getVerticesBuffer(), temp,
			//	0.2,-0.2,
			//	_UV[1], _backgroundColor);    // Right/Top     1

			//return; // test

			// Triangle A
			PUSH_VERTEX(m_verticesBuffer, temp,
				m_position.x + texelOffsetX,
				(m_position.y + m_size.y) + texelOffsetY,
				_UV[0], _backgroundColor);    // Left/Top     0
			PUSH_VERTEX(m_verticesBuffer, temp,
				(m_position.x + m_size.x) + texelOffsetX,
				(m_position.y + m_size.y) + texelOffsetY,
				_UV[1], _backgroundColor);    // Right/Top    1

			PUSH_VERTEX(m_verticesBuffer, temp,
				m_position.x + texelOffsetX,
				m_position.y + texelOffsetY,
				_UV[3], _backgroundColor);    // Left/Bottom  3

			// Triangle B
			PUSH_VERTEX(m_verticesBuffer, temp,
				(m_position.x + m_size.x) + texelOffsetX,
				(m_position.y + m_size.y) + texelOffsetY,
				_UV[1], _backgroundColor);    // Right/Top     1u																		 
			PUSH_VERTEX(m_verticesBuffer, temp,
				(m_position.x + m_size.x) + texelOffsetX,
				m_position.y + texelOffsetY,
				_UV[2], _backgroundColor);    // Right/Bottom  2

			PUSH_VERTEX(m_verticesBuffer, temp,
				m_position.x + texelOffsetX,
				m_position.y + texelOffsetY,
				_UV[3], _backgroundColor);    // Left/Bottom   3

			RenderableShape::isDirty = false;
		}

		return RenderableShape::m_verticesBuffer;
	}

} // namespace XE