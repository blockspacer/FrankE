#include <XERenderer/GUI/WCaption.hpp>
#include <XERenderer/GUI/WLayer.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/RenderableShape.hpp>

#include <ThirdParty/plog/Log.h>

namespace XE
{
	WCaption::WCaption(WLayer& wLayer, Uint16 fontId)
		: RenderableShape(wLayer)
		, m_color()
		, m_font(m_guiRenderer.getFont(fontId))
	{

	}

	WCaption::~WCaption()
	{
	
	}

	void  WCaption::_refresh()
	{
		RenderableShape::isDirty = true;
	}

	void WCaption::setPosition(const sf::Vector2f& position)
	{
		m_position = position;

		RenderableShape::isDirty = true;
	}

	void WCaption::setSize(const float width, const float height)	{

		m_size.x = width;
		m_size.y = height;

		RenderableShape::isDirty = true;
	}

	sf::Vector2f& WCaption::getPosition()	{
		return m_position;
	}
	sf::Vector2f& WCaption::getSize()	{
		return m_size;
	}

	const sf::String&  WCaption::getText()
	{
		return m_text;
	}

	sf::Vector2i WCaption::GetTextStringMetrics(const sf::String& string) const
	{
		return m_guiRenderer.GetTextStringMetrics(string, m_font);
	}

	void WCaption::setText(const sf::String& text)
	{
	//	auto test = m_guiRenderer.GetTextStringMetrics(text,20);

		m_text = text;


		RenderableShape::isDirty = true;
	}

	bool WCaption::intersects(const Ogre::Vector2& coordinates) const
	{
		return ((coordinates.x >= m_position.x && coordinates.x <= m_position.x + m_size.x) && (coordinates.y >= m_position.y - m_size.y  && coordinates.y <= m_position.y));
	}

	std::vector<Vertex>&  WCaption::_update()
	{
		if (!RenderableShape::isDirty)
			return m_verticesBuffer;

		m_verticesBuffer.clear();
		
		float left = 0, top = 0, right = 0, bottom = 0, cursorX = 0, cursorY = 0, kerning = 0, texelOffsetX = m_layer.atlasData.texelOffset.x, texelOffsetY = m_layer.atlasData.texelOffset.y;
		Ogre::Vector2 knownSize;
		const FontGlyph* glyph = 0;
		const FontGlyph* lastGlyph = 0;

		cursorX = m_position.x;
	//	cursorY = m_position.y + (m_size.y * 0.5) - (font->mLineHeight * 0.5); //middle?
		cursorY = m_position.y + m_size.y - m_font->mLineHeight; //bottom

		cursorX = Ogre::Math::Floor(cursorX);
		cursorY = Ogre::Math::Floor(cursorY);
		
		unsigned char thisChar = 0, lastChar = 0;

		for (size_t i = 0; i < m_text.getSize(); i++)
		{
			thisChar = m_text.toWideString()[i];

			if (thisChar == ' ')
			{
				lastChar = thisChar;
				lastGlyph = glyph;
				cursorX += m_font->mSpaceLength;
				continue;
			}

			/*if (thisChar < font->mRangeBegin || thisChar > font->mRangeEnd)
			{
				lastChar = 0;
				continue;
			}
*/
			//if (thisChar == 246 || thisChar == 196 || thisChar == 192)
			//	top = top;

			glyph = m_font->getGlyph(thisChar);
			if (glyph == 0)
				continue;
			if (lastGlyph == 0)
				lastGlyph = glyph;

			kerning = lastGlyph->getKerning(thisChar);
			if (kerning == 0)
				kerning = m_font->mLetterSpacing;

			cursorX += kerning; //cursorX += kerning;
			lastChar = thisChar;
			lastGlyph = glyph;

			left = cursorX - texelOffsetX;
			top = cursorY - texelOffsetY + glyph->verticalOffset;
			right = left + glyph->glyphWidth + texelOffsetX;
			bottom = top + glyph->glyphHeight + texelOffsetY;
		
			cursorX += _getAdvance(glyph, kerning);


		/*	if (fixedWidth())
			{
				float offset = std::floor((mGlyphData->mMonoWidth - glyph->glyphWidth) / 2.0f);
				left += offset;
				right += offset;
			}*/
		

			Vertex temp;

			//PUSH_VERTEX(getVerticesBuffer(), temp, left, bottom, Ogre::Vector2(0.4,0.5), m_color);  // Left/Bottom  3
			//PUSH_VERTEX(getVerticesBuffer(), temp, right, top, Ogre::Vector2(0.6, 0.5), m_color);    // Right/Top    1
			//PUSH_VERTEX(getVerticesBuffer(), temp, left, top, Ogre::Vector2(0.4, 0.4), m_color);     // Left/Top     0

			//																						   // Triangle B
			//PUSH_VERTEX(getVerticesBuffer(), temp, left, bottom, Ogre::Vector2(0 ,15), m_color);  // Left/Bottom  3
			//PUSH_VERTEX(getVerticesBuffer(), temp, right, bottom, Ogre::Vector2(15, 15), m_color); // Right/Bottom 2
			//PUSH_VERTEX(getVerticesBuffer(), temp, right, top, Ogre::Vector2(15, 0), m_color);    // Right/Top    1

			// Triangle A
			PUSH_VERTEX(m_verticesBuffer, temp, left, bottom, glyph->texCoords[BottomLeft], m_color);  // Left/Bottom  3
			PUSH_VERTEX(m_verticesBuffer, temp, right, top, glyph->texCoords[TopRight], m_color);    // Right/Top    1
			PUSH_VERTEX(m_verticesBuffer, temp, left, top, glyph->texCoords[TopLeft], m_color);     // Left/Top     0

			// Triangle B
			PUSH_VERTEX(m_verticesBuffer, temp, left, bottom, glyph->texCoords[BottomLeft], m_color);  // Left/Bottom  3
			PUSH_VERTEX(m_verticesBuffer, temp, right, bottom, glyph->texCoords[BottomRight], m_color); // Right/Bottom 2
			PUSH_VERTEX(m_verticesBuffer, temp, right, top, glyph->texCoords[TopRight], m_color);    // Right/Top    1


			RenderableShape::isDirty = false;
		} // for

		return m_verticesBuffer;
	}

	float WCaption::_getAdvance(const FontGlyph* glyph, float kerning)
	{
		/*if (mFixedWidth)
			return mGlyphData->mMonoWidth;
		else*/
		return glyph->glyphAdvance + kerning;
	}


} // namespace XE