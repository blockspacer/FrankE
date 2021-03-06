// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_FBUIATLAS_XFBTYPE_H_
#define FLATBUFFERS_GENERATED_FBUIATLAS_XFBTYPE_H_

#include "flatbuffers/flatbuffers.h"


namespace XFBType {

struct Sprite;
struct KerningData;
struct Glyph;
struct Font;
struct Atlas;

struct Sprite FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  float width() const { return GetField<float>(4, 0); }
  float height() const { return GetField<float>(6, 0); }
  float posX() const { return GetField<float>(8, 0); }
  float posY() const { return GetField<float>(10, 0); }
  const flatbuffers::String *name() const { return GetPointer<const flatbuffers::String *>(12); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, 4 /* width */) &&
           VerifyField<float>(verifier, 6 /* height */) &&
           VerifyField<float>(verifier, 8 /* posX */) &&
           VerifyField<float>(verifier, 10 /* posY */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 12 /* name */) &&
           verifier.Verify(name()) &&
           verifier.EndTable();
  }
};

struct SpriteBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_width(float width) { fbb_.AddElement<float>(4, width, 0); }
  void add_height(float height) { fbb_.AddElement<float>(6, height, 0); }
  void add_posX(float posX) { fbb_.AddElement<float>(8, posX, 0); }
  void add_posY(float posY) { fbb_.AddElement<float>(10, posY, 0); }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) { fbb_.AddOffset(12, name); }
  SpriteBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  SpriteBuilder &operator=(const SpriteBuilder &);
  flatbuffers::Offset<Sprite> Finish() {
    auto o = flatbuffers::Offset<Sprite>(fbb_.EndTable(start_, 5));
    return o;
  }
};

inline flatbuffers::Offset<Sprite> CreateSprite(flatbuffers::FlatBufferBuilder &_fbb,
   float width = 0,
   float height = 0,
   float posX = 0,
   float posY = 0,
   flatbuffers::Offset<flatbuffers::String> name = 0) {
  SpriteBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_posY(posY);
  builder_.add_posX(posX);
  builder_.add_height(height);
  builder_.add_width(width);
  return builder_.Finish();
}

///Distances between two characters next to each other.
struct KerningData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  uint32_t character() const { return GetField<uint32_t>(4, 0); }
  float kerning() const { return GetField<float>(6, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, 4 /* character */) &&
           VerifyField<float>(verifier, 6 /* kerning */) &&
           verifier.EndTable();
  }
};

struct KerningDataBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_character(uint32_t character) { fbb_.AddElement<uint32_t>(4, character, 0); }
  void add_kerning(float kerning) { fbb_.AddElement<float>(6, kerning, 0); }
  KerningDataBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  KerningDataBuilder &operator=(const KerningDataBuilder &);
  flatbuffers::Offset<KerningData> Finish() {
    auto o = flatbuffers::Offset<KerningData>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<KerningData> CreateKerningData(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t character = 0,
   float kerning = 0) {
  KerningDataBuilder builder_(_fbb);
  builder_.add_kerning(kerning);
  builder_.add_character(character);
  return builder_.Finish();
}

///Texture and size information about a single character loaded from a TextureAtlas.
struct Glyph FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  uint32_t code() const { return GetField<uint32_t>(4, 0); }
  float uvTop() const { return GetField<float>(6, 0); }
  float uvBottom() const { return GetField<float>(8, 0); }
  float uvWidth() const { return GetField<float>(10, 0); }
  float uvHeight() const { return GetField<float>(12, 0); }
  float uvLeft() const { return GetField<float>(14, 0); }
  float uvRight() const { return GetField<float>(16, 0); }
  float glyphWidth() const { return GetField<float>(18, 0); }
  float glyphHeight() const { return GetField<float>(20, 0); }
  float glyphAdvance() const { return GetField<float>(22, 0); }
  float verticalOffset() const { return GetField<float>(24, 0); }
  const flatbuffers::Vector<flatbuffers::Offset<KerningData>> *kerningList() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<KerningData>> *>(26); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, 4 /* code */) &&
           VerifyField<float>(verifier, 6 /* uvTop */) &&
           VerifyField<float>(verifier, 8 /* uvBottom */) &&
           VerifyField<float>(verifier, 10 /* uvWidth */) &&
           VerifyField<float>(verifier, 12 /* uvHeight */) &&
           VerifyField<float>(verifier, 14 /* uvLeft */) &&
           VerifyField<float>(verifier, 16 /* uvRight */) &&
           VerifyField<float>(verifier, 18 /* glyphWidth */) &&
           VerifyField<float>(verifier, 20 /* glyphHeight */) &&
           VerifyField<float>(verifier, 22 /* glyphAdvance */) &&
           VerifyField<float>(verifier, 24 /* verticalOffset */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 26 /* kerningList */) &&
           verifier.Verify(kerningList()) &&
           verifier.VerifyVectorOfTables(kerningList()) &&
           verifier.EndTable();
  }
};

struct GlyphBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(uint32_t code) { fbb_.AddElement<uint32_t>(4, code, 0); }
  void add_uvTop(float uvTop) { fbb_.AddElement<float>(6, uvTop, 0); }
  void add_uvBottom(float uvBottom) { fbb_.AddElement<float>(8, uvBottom, 0); }
  void add_uvWidth(float uvWidth) { fbb_.AddElement<float>(10, uvWidth, 0); }
  void add_uvHeight(float uvHeight) { fbb_.AddElement<float>(12, uvHeight, 0); }
  void add_uvLeft(float uvLeft) { fbb_.AddElement<float>(14, uvLeft, 0); }
  void add_uvRight(float uvRight) { fbb_.AddElement<float>(16, uvRight, 0); }
  void add_glyphWidth(float glyphWidth) { fbb_.AddElement<float>(18, glyphWidth, 0); }
  void add_glyphHeight(float glyphHeight) { fbb_.AddElement<float>(20, glyphHeight, 0); }
  void add_glyphAdvance(float glyphAdvance) { fbb_.AddElement<float>(22, glyphAdvance, 0); }
  void add_verticalOffset(float verticalOffset) { fbb_.AddElement<float>(24, verticalOffset, 0); }
  void add_kerningList(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<KerningData>>> kerningList) { fbb_.AddOffset(26, kerningList); }
  GlyphBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  GlyphBuilder &operator=(const GlyphBuilder &);
  flatbuffers::Offset<Glyph> Finish() {
    auto o = flatbuffers::Offset<Glyph>(fbb_.EndTable(start_, 12));
    return o;
  }
};

inline flatbuffers::Offset<Glyph> CreateGlyph(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t code = 0,
   float uvTop = 0,
   float uvBottom = 0,
   float uvWidth = 0,
   float uvHeight = 0,
   float uvLeft = 0,
   float uvRight = 0,
   float glyphWidth = 0,
   float glyphHeight = 0,
   float glyphAdvance = 0,
   float verticalOffset = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<KerningData>>> kerningList = 0) {
  GlyphBuilder builder_(_fbb);
  builder_.add_kerningList(kerningList);
  builder_.add_verticalOffset(verticalOffset);
  builder_.add_glyphAdvance(glyphAdvance);
  builder_.add_glyphHeight(glyphHeight);
  builder_.add_glyphWidth(glyphWidth);
  builder_.add_uvRight(uvRight);
  builder_.add_uvLeft(uvLeft);
  builder_.add_uvHeight(uvHeight);
  builder_.add_uvWidth(uvWidth);
  builder_.add_uvBottom(uvBottom);
  builder_.add_uvTop(uvTop);
  builder_.add_code(code);
  return builder_.Finish();
}

struct Font FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  uint16_t id() const { return GetField<uint16_t>(4, 0); }
  const flatbuffers::Vector<flatbuffers::Offset<Glyph>> *glyphs() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Glyph>> *>(6); }
  float rangeBegin() const { return GetField<float>(8, 0); }
  float rangeEnd() const { return GetField<float>(10, 0); }
  float spaceLength() const { return GetField<float>(12, 0); }
  float lineHeight() const { return GetField<float>(14, 0); }
  float baseline() const { return GetField<float>(16, 0); }
  float lineSpacing() const { return GetField<float>(18, 0); }
  float letterSpacing() const { return GetField<float>(20, 0); }
  float monoWidth() const { return GetField<float>(22, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* id */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* glyphs */) &&
           verifier.Verify(glyphs()) &&
           verifier.VerifyVectorOfTables(glyphs()) &&
           VerifyField<float>(verifier, 8 /* rangeBegin */) &&
           VerifyField<float>(verifier, 10 /* rangeEnd */) &&
           VerifyField<float>(verifier, 12 /* spaceLength */) &&
           VerifyField<float>(verifier, 14 /* lineHeight */) &&
           VerifyField<float>(verifier, 16 /* baseline */) &&
           VerifyField<float>(verifier, 18 /* lineSpacing */) &&
           VerifyField<float>(verifier, 20 /* letterSpacing */) &&
           VerifyField<float>(verifier, 22 /* monoWidth */) &&
           verifier.EndTable();
  }
};

struct FontBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint16_t id) { fbb_.AddElement<uint16_t>(4, id, 0); }
  void add_glyphs(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Glyph>>> glyphs) { fbb_.AddOffset(6, glyphs); }
  void add_rangeBegin(float rangeBegin) { fbb_.AddElement<float>(8, rangeBegin, 0); }
  void add_rangeEnd(float rangeEnd) { fbb_.AddElement<float>(10, rangeEnd, 0); }
  void add_spaceLength(float spaceLength) { fbb_.AddElement<float>(12, spaceLength, 0); }
  void add_lineHeight(float lineHeight) { fbb_.AddElement<float>(14, lineHeight, 0); }
  void add_baseline(float baseline) { fbb_.AddElement<float>(16, baseline, 0); }
  void add_lineSpacing(float lineSpacing) { fbb_.AddElement<float>(18, lineSpacing, 0); }
  void add_letterSpacing(float letterSpacing) { fbb_.AddElement<float>(20, letterSpacing, 0); }
  void add_monoWidth(float monoWidth) { fbb_.AddElement<float>(22, monoWidth, 0); }
  FontBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  FontBuilder &operator=(const FontBuilder &);
  flatbuffers::Offset<Font> Finish() {
    auto o = flatbuffers::Offset<Font>(fbb_.EndTable(start_, 10));
    return o;
  }
};

inline flatbuffers::Offset<Font> CreateFont(flatbuffers::FlatBufferBuilder &_fbb,
   uint16_t id = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Glyph>>> glyphs = 0,
   float rangeBegin = 0,
   float rangeEnd = 0,
   float spaceLength = 0,
   float lineHeight = 0,
   float baseline = 0,
   float lineSpacing = 0,
   float letterSpacing = 0,
   float monoWidth = 0) {
  FontBuilder builder_(_fbb);
  builder_.add_monoWidth(monoWidth);
  builder_.add_letterSpacing(letterSpacing);
  builder_.add_lineSpacing(lineSpacing);
  builder_.add_baseline(baseline);
  builder_.add_lineHeight(lineHeight);
  builder_.add_spaceLength(spaceLength);
  builder_.add_rangeEnd(rangeEnd);
  builder_.add_rangeBegin(rangeBegin);
  builder_.add_glyphs(glyphs);
  builder_.add_id(id);
  return builder_.Finish();
}

struct Atlas FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::String *name() const { return GetPointer<const flatbuffers::String *>(4); }
  const flatbuffers::Vector<flatbuffers::Offset<Sprite>> *sprites() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Sprite>> *>(6); }
  const flatbuffers::Vector<flatbuffers::Offset<Font>> *fonts() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Font>> *>(8); }
  const flatbuffers::String *texture() const { return GetPointer<const flatbuffers::String *>(10); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* name */) &&
           verifier.Verify(name()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* sprites */) &&
           verifier.Verify(sprites()) &&
           verifier.VerifyVectorOfTables(sprites()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 8 /* fonts */) &&
           verifier.Verify(fonts()) &&
           verifier.VerifyVectorOfTables(fonts()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 10 /* texture */) &&
           verifier.Verify(texture()) &&
           verifier.EndTable();
  }
};

struct AtlasBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) { fbb_.AddOffset(4, name); }
  void add_sprites(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Sprite>>> sprites) { fbb_.AddOffset(6, sprites); }
  void add_fonts(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Font>>> fonts) { fbb_.AddOffset(8, fonts); }
  void add_texture(flatbuffers::Offset<flatbuffers::String> texture) { fbb_.AddOffset(10, texture); }
  AtlasBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AtlasBuilder &operator=(const AtlasBuilder &);
  flatbuffers::Offset<Atlas> Finish() {
    auto o = flatbuffers::Offset<Atlas>(fbb_.EndTable(start_, 4));
    return o;
  }
};

inline flatbuffers::Offset<Atlas> CreateAtlas(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> name = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Sprite>>> sprites = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Font>>> fonts = 0,
   flatbuffers::Offset<flatbuffers::String> texture = 0) {
  AtlasBuilder builder_(_fbb);
  builder_.add_texture(texture);
  builder_.add_fonts(fonts);
  builder_.add_sprites(sprites);
  builder_.add_name(name);
  return builder_.Finish();
}

inline const XFBType::Atlas *GetAtlas(const void *buf) { return flatbuffers::GetRoot<XFBType::Atlas>(buf); }

inline bool VerifyAtlasBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<XFBType::Atlas>(); }

inline void FinishAtlasBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<XFBType::Atlas> root) { fbb.Finish(root); }

}  // namespace XFBType

#endif  // FLATBUFFERS_GENERATED_FBUIATLAS_XFBTYPE_H_
