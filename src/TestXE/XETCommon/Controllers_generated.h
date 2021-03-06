// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_CONTROLLERS_CONTROLLERSETTINGS_H_
#define FLATBUFFERS_GENERATED_CONTROLLERS_CONTROLLERSETTINGS_H_

#include "flatbuffers/flatbuffers.h"


namespace ControllerSettings {

struct Event;
struct Action;
struct ControllerMap;
struct ControllerList;

enum KeyID {
  ///< Unhandled key fb array index starts with 0!
  KeyID_SDL_SCANCODE_UNKNOWN = 0,
  KeyID_SDL_SCANCODE_A = 4,
  KeyID_SDL_SCANCODE_B = 5,
  KeyID_SDL_SCANCODE_C = 6,
  KeyID_SDL_SCANCODE_D = 7,
  KeyID_SDL_SCANCODE_E = 8,
  KeyID_SDL_SCANCODE_F = 9,
  KeyID_SDL_SCANCODE_G = 10,
  KeyID_SDL_SCANCODE_H = 11,
  KeyID_SDL_SCANCODE_I = 12,
  KeyID_SDL_SCANCODE_J = 13,
  KeyID_SDL_SCANCODE_K = 14,
  KeyID_SDL_SCANCODE_L = 15,
  KeyID_SDL_SCANCODE_M = 16,
  KeyID_SDL_SCANCODE_N = 17,
  KeyID_SDL_SCANCODE_O = 18,
  KeyID_SDL_SCANCODE_P = 19,
  KeyID_SDL_SCANCODE_Q = 20,
  KeyID_SDL_SCANCODE_R = 21,
  KeyID_SDL_SCANCODE_S = 22,
  KeyID_SDL_SCANCODE_T = 23,
  KeyID_SDL_SCANCODE_U = 24,
  KeyID_SDL_SCANCODE_V = 25,
  KeyID_SDL_SCANCODE_W = 26,
  KeyID_SDL_SCANCODE_X = 27,
  KeyID_SDL_SCANCODE_Y = 28,
  KeyID_SDL_SCANCODE_Z = 29,
  KeyID_SDL_SCANCODE_1 = 30,
  KeyID_SDL_SCANCODE_2 = 31,
  KeyID_SDL_SCANCODE_3 = 32,
  KeyID_SDL_SCANCODE_4 = 33,
  KeyID_SDL_SCANCODE_5 = 34,
  KeyID_SDL_SCANCODE_6 = 35,
  KeyID_SDL_SCANCODE_7 = 36,
  KeyID_SDL_SCANCODE_8 = 37,
  KeyID_SDL_SCANCODE_9 = 38,
  KeyID_SDL_SCANCODE_0 = 39,
  KeyID_SDL_SCANCODE_RETURN = 40,
  KeyID_SDL_SCANCODE_ESCAPE = 41,
  KeyID_SDL_SCANCODE_BACKSPACE = 42,
  KeyID_SDL_SCANCODE_TAB = 43,
  KeyID_SDL_SCANCODE_SPACE = 44,
  KeyID_SDL_SCANCODE_MINUS = 45,
  KeyID_SDL_SCANCODE_EQUALS = 46,
  KeyID_SDL_SCANCODE_LEFTBRACKET = 47,
  KeyID_SDL_SCANCODE_RIGHTBRACKET = 48,
  KeyID_SDL_SCANCODE_BACKSLASH = 49,
  KeyID_SDL_SCANCODE_NONUSHASH = 50,
  KeyID_SDL_SCANCODE_SEMICOLON = 51,
  KeyID_SDL_SCANCODE_APOSTROPHE = 52,
  KeyID_SDL_SCANCODE_GRAVE = 53,
  KeyID_SDL_SCANCODE_COMMA = 54,
  KeyID_SDL_SCANCODE_PERIOD = 55,
  KeyID_SDL_SCANCODE_SLASH = 56,
  KeyID_SDL_SCANCODE_CAPSLOCK = 57,
  KeyID_SDL_SCANCODE_F1 = 58,
  KeyID_SDL_SCANCODE_F2 = 59,
  KeyID_SDL_SCANCODE_F3 = 60,
  KeyID_SDL_SCANCODE_F4 = 61,
  KeyID_SDL_SCANCODE_F5 = 62,
  KeyID_SDL_SCANCODE_F6 = 63,
  KeyID_SDL_SCANCODE_F7 = 64,
  KeyID_SDL_SCANCODE_F8 = 65,
  KeyID_SDL_SCANCODE_F9 = 66,
  KeyID_SDL_SCANCODE_F10 = 67,
  KeyID_SDL_SCANCODE_F11 = 68,
  KeyID_SDL_SCANCODE_F12 = 69,
  KeyID_SDL_SCANCODE_PRINTSCREEN = 70,
  KeyID_SDL_SCANCODE_SCROLLLOCK = 71,
  KeyID_SDL_SCANCODE_PAUSE = 72,
  KeyID_SDL_SCANCODE_INSERT = 73,
  KeyID_SDL_SCANCODE_HOME = 74,
  KeyID_SDL_SCANCODE_PAGEUP = 75,
  KeyID_SDL_SCANCODE_DELETE = 76,
  KeyID_SDL_SCANCODE_END = 77,
  KeyID_SDL_SCANCODE_PAGEDOWN = 78,
  KeyID_SDL_SCANCODE_RIGHT = 79,
  KeyID_SDL_SCANCODE_LEFT = 80,
  KeyID_SDL_SCANCODE_DOWN = 81,
  KeyID_SDL_SCANCODE_UP = 82,
  KeyID_SDL_SCANCODE_NUMLOCKCLEAR = 83,
  KeyID_SDL_SCANCODE_KP_DIVIDE = 84,
  KeyID_SDL_SCANCODE_KP_MULTIPLY = 85,
  KeyID_SDL_SCANCODE_KP_MINUS = 86,
  KeyID_SDL_SCANCODE_KP_PLUS = 87,
  KeyID_SDL_SCANCODE_KP_ENTER = 88,
  KeyID_SDL_SCANCODE_KP_1 = 89,
  KeyID_SDL_SCANCODE_KP_2 = 90,
  KeyID_SDL_SCANCODE_KP_3 = 91,
  KeyID_SDL_SCANCODE_KP_4 = 92,
  KeyID_SDL_SCANCODE_KP_5 = 93,
  KeyID_SDL_SCANCODE_KP_6 = 94,
  KeyID_SDL_SCANCODE_KP_7 = 95,
  KeyID_SDL_SCANCODE_KP_8 = 96,
  KeyID_SDL_SCANCODE_KP_9 = 97,
  KeyID_SDL_SCANCODE_KP_0 = 98,
  KeyID_SDL_SCANCODE_KP_PERIOD = 99,
  KeyID_SDL_SCANCODE_NONUSBACKSLASH = 100,
  KeyID_SDL_SCANCODE_APPLICATION = 101,
  KeyID_SDL_SCANCODE_POWER = 102,
  KeyID_SDL_SCANCODE_KP_EQUALS = 103,
  KeyID_SDL_SCANCODE_F13 = 104,
  KeyID_SDL_SCANCODE_F14 = 105,
  KeyID_SDL_SCANCODE_F15 = 106,
  KeyID_SDL_SCANCODE_F16 = 107,
  KeyID_SDL_SCANCODE_F17 = 108,
  KeyID_SDL_SCANCODE_F18 = 109,
  KeyID_SDL_SCANCODE_F19 = 110,
  KeyID_SDL_SCANCODE_F20 = 111,
  KeyID_SDL_SCANCODE_F21 = 112,
  KeyID_SDL_SCANCODE_F22 = 113,
  KeyID_SDL_SCANCODE_F23 = 114,
  KeyID_SDL_SCANCODE_F24 = 115,
  KeyID_SDL_SCANCODE_EXECUTE = 116,
  KeyID_SDL_SCANCODE_HELP = 117,
  KeyID_SDL_SCANCODE_MENU = 118,
  KeyID_SDL_SCANCODE_SELECT = 119,
  KeyID_SDL_SCANCODE_STOP = 120,
  KeyID_SDL_SCANCODE_AGAIN = 121,
  KeyID_SDL_SCANCODE_UNDO = 122,
  KeyID_SDL_SCANCODE_CUT = 123,
  KeyID_SDL_SCANCODE_COPY = 124,
  KeyID_SDL_SCANCODE_PASTE = 125,
  KeyID_SDL_SCANCODE_FIND = 126,
  KeyID_SDL_SCANCODE_MUTE = 127,
  KeyID_SDL_SCANCODE_VOLUMEUP = 128,
  KeyID_SDL_SCANCODE_VOLUMEDOWN = 129,
  KeyID_SDL_SCANCODE_KP_COMMA = 133,
  KeyID_SDL_SCANCODE_KP_EQUALSAS400 = 134,
  KeyID_SDL_SCANCODE_INTERNATIONAL1 = 135,
  KeyID_SDL_SCANCODE_INTERNATIONAL2 = 136,
  KeyID_SDL_SCANCODE_INTERNATIONAL3 = 137,
  KeyID_SDL_SCANCODE_INTERNATIONAL4 = 138,
  KeyID_SDL_SCANCODE_INTERNATIONAL5 = 139,
  KeyID_SDL_SCANCODE_INTERNATIONAL6 = 140,
  KeyID_SDL_SCANCODE_INTERNATIONAL7 = 141,
  KeyID_SDL_SCANCODE_INTERNATIONAL8 = 142,
  KeyID_SDL_SCANCODE_INTERNATIONAL9 = 143,
  KeyID_SDL_SCANCODE_LANG1 = 144,
  KeyID_SDL_SCANCODE_LANG2 = 145,
  KeyID_SDL_SCANCODE_LANG3 = 146,
  KeyID_SDL_SCANCODE_LANG4 = 147,
  KeyID_SDL_SCANCODE_LANG5 = 148,
  KeyID_SDL_SCANCODE_LANG6 = 149,
  KeyID_SDL_SCANCODE_LANG7 = 150,
  KeyID_SDL_SCANCODE_LANG8 = 151,
  KeyID_SDL_SCANCODE_LANG9 = 152,
  KeyID_SDL_SCANCODE_ALTERASE = 153,
  KeyID_SDL_SCANCODE_SYSREQ = 154,
  KeyID_SDL_SCANCODE_CANCEL = 155,
  KeyID_SDL_SCANCODE_CLEAR = 156,
  KeyID_SDL_SCANCODE_PRIOR = 157,
  KeyID_SDL_SCANCODE_RETURN2 = 158,
  KeyID_SDL_SCANCODE_SEPARATOR = 159,
  KeyID_SDL_SCANCODE_OUT = 160,
  KeyID_SDL_SCANCODE_OPER = 161,
  KeyID_SDL_SCANCODE_CLEARAGAIN = 162,
  KeyID_SDL_SCANCODE_CRSEL = 163,
  KeyID_SDL_SCANCODE_EXSEL = 164,
  KeyID_SDL_SCANCODE_KP_00 = 176,
  KeyID_SDL_SCANCODE_KP_000 = 177,
  KeyID_SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
  KeyID_SDL_SCANCODE_DECIMALSEPARATOR = 179,
  KeyID_SDL_SCANCODE_CURRENCYUNIT = 180,
  KeyID_SDL_SCANCODE_CURRENCYSUBUNIT = 181,
  KeyID_SDL_SCANCODE_KP_LEFTPAREN = 182,
  KeyID_SDL_SCANCODE_KP_RIGHTPAREN = 183,
  KeyID_SDL_SCANCODE_KP_LEFTBRACE = 184,
  KeyID_SDL_SCANCODE_KP_RIGHTBRACE = 185,
  KeyID_SDL_SCANCODE_KP_TAB = 186,
  KeyID_SDL_SCANCODE_KP_BACKSPACE = 187,
  KeyID_SDL_SCANCODE_KP_A = 188,
  KeyID_SDL_SCANCODE_KP_B = 189,
  KeyID_SDL_SCANCODE_KP_C = 190,
  KeyID_SDL_SCANCODE_KP_D = 191,
  KeyID_SDL_SCANCODE_KP_E = 192,
  KeyID_SDL_SCANCODE_KP_F = 193,
  KeyID_SDL_SCANCODE_KP_XOR = 194,
  KeyID_SDL_SCANCODE_KP_POWER = 195,
  KeyID_SDL_SCANCODE_KP_PERCENT = 196,
  KeyID_SDL_SCANCODE_KP_LESS = 197,
  KeyID_SDL_SCANCODE_KP_GREATER = 198,
  KeyID_SDL_SCANCODE_KP_AMPERSAND = 199,
  KeyID_SDL_SCANCODE_KP_DBLAMPERSAND = 200,
  KeyID_SDL_SCANCODE_KP_VERTICALBAR = 201,
  KeyID_SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
  KeyID_SDL_SCANCODE_KP_COLON = 203,
  KeyID_SDL_SCANCODE_KP_HASH = 204,
  KeyID_SDL_SCANCODE_KP_SPACE = 205,
  KeyID_SDL_SCANCODE_KP_AT = 206,
  KeyID_SDL_SCANCODE_KP_EXCLAM = 207,
  KeyID_SDL_SCANCODE_KP_MEMSTORE = 208,
  KeyID_SDL_SCANCODE_KP_MEMRECALL = 209,
  KeyID_SDL_SCANCODE_KP_MEMCLEAR = 210,
  KeyID_SDL_SCANCODE_KP_MEMADD = 211,
  KeyID_SDL_SCANCODE_KP_MEMSUBTRACT = 212,
  KeyID_SDL_SCANCODE_KP_MEMMULTIPLY = 213,
  KeyID_SDL_SCANCODE_KP_MEMDIVIDE = 214,
  KeyID_SDL_SCANCODE_KP_PLUSMINUS = 215,
  KeyID_SDL_SCANCODE_KP_CLEAR = 216,
  KeyID_SDL_SCANCODE_KP_CLEARENTRY = 217,
  KeyID_SDL_SCANCODE_KP_BINARY = 218,
  KeyID_SDL_SCANCODE_KP_OCTAL = 219,
  KeyID_SDL_SCANCODE_KP_DECIMAL = 220,
  KeyID_SDL_SCANCODE_KP_HEXADECIMAL = 221,
  KeyID_SDL_SCANCODE_LCTRL = 224,
  KeyID_SDL_SCANCODE_LSHIFT = 225,
  KeyID_SDL_SCANCODE_LALT = 226,
  KeyID_SDL_SCANCODE_LGUI = 227,
  KeyID_SDL_SCANCODE_RCTRL = 228,
  KeyID_SDL_SCANCODE_RSHIFT = 229,
  KeyID_SDL_SCANCODE_RALT = 230,
  KeyID_SDL_SCANCODE_RGUI = 231,
  KeyID_SDL_SCANCODE_MODE = 257,
  KeyID_SDL_SCANCODE_AUDIONEXT = 258,
  KeyID_SDL_SCANCODE_AUDIOPREV = 259,
  KeyID_SDL_SCANCODE_AUDIOSTOP = 260,
  KeyID_SDL_SCANCODE_AUDIOPLAY = 261,
  KeyID_SDL_SCANCODE_AUDIOMUTE = 262,
  KeyID_SDL_SCANCODE_MEDIASELECT = 263,
  KeyID_SDL_SCANCODE_WWW = 264,
  KeyID_SDL_SCANCODE_MAIL = 265,
  KeyID_SDL_SCANCODE_CALCULATOR = 266,
  KeyID_SDL_SCANCODE_COMPUTER = 267,
  KeyID_SDL_SCANCODE_AC_SEARCH = 268,
  KeyID_SDL_SCANCODE_AC_HOME = 269,
  KeyID_SDL_SCANCODE_AC_BACK = 270,
  KeyID_SDL_SCANCODE_AC_FORWARD = 271,
  KeyID_SDL_SCANCODE_AC_STOP = 272,
  KeyID_SDL_SCANCODE_AC_REFRESH = 273,
  KeyID_SDL_SCANCODE_AC_BOOKMARKS = 274,
  KeyID_SDL_SCANCODE_BRIGHTNESSDOWN = 275,
  KeyID_SDL_SCANCODE_BRIGHTNESSUP = 276,
  KeyID_SDL_SCANCODE_DISPLAYSWITCH = 277,
  KeyID_SDL_SCANCODE_KBDILLUMTOGGLE = 278,
  KeyID_SDL_SCANCODE_KBDILLUMDOWN = 279,
  KeyID_SDL_SCANCODE_KBDILLUMUP = 280,
  KeyID_SDL_SCANCODE_EJECT = 281,
  KeyID_SDL_SCANCODE_SLEEP = 282,
  KeyID_SDL_SCANCODE_APP1 = 283,
  KeyID_SDL_SCANCODE_APP2 = 284,
  KeyID_SDL_NUM_SCANCODES = 512,
  ///< The Pause key
  KeyID_Pause = 513,
  ///< Keep last -- the total number of keyboard keys
  KeyID_KeyCount = 514
};

inline const char **EnumNamesKeyID() {
  static const char *names[] = { "SDL_SCANCODE_UNKNOWN", "", "", "", "SDL_SCANCODE_A", "SDL_SCANCODE_B", "SDL_SCANCODE_C", "SDL_SCANCODE_D", "SDL_SCANCODE_E", "SDL_SCANCODE_F", "SDL_SCANCODE_G", "SDL_SCANCODE_H", "SDL_SCANCODE_I", "SDL_SCANCODE_J", "SDL_SCANCODE_K", "SDL_SCANCODE_L", "SDL_SCANCODE_M", "SDL_SCANCODE_N", "SDL_SCANCODE_O", "SDL_SCANCODE_P", "SDL_SCANCODE_Q", "SDL_SCANCODE_R", "SDL_SCANCODE_S", "SDL_SCANCODE_T", "SDL_SCANCODE_U", "SDL_SCANCODE_V", "SDL_SCANCODE_W", "SDL_SCANCODE_X", "SDL_SCANCODE_Y", "SDL_SCANCODE_Z", "SDL_SCANCODE_1", "SDL_SCANCODE_2", "SDL_SCANCODE_3", "SDL_SCANCODE_4", "SDL_SCANCODE_5", "SDL_SCANCODE_6", "SDL_SCANCODE_7", "SDL_SCANCODE_8", "SDL_SCANCODE_9", "SDL_SCANCODE_0", "SDL_SCANCODE_RETURN", "SDL_SCANCODE_ESCAPE", "SDL_SCANCODE_BACKSPACE", "SDL_SCANCODE_TAB", "SDL_SCANCODE_SPACE", "SDL_SCANCODE_MINUS", "SDL_SCANCODE_EQUALS", "SDL_SCANCODE_LEFTBRACKET", "SDL_SCANCODE_RIGHTBRACKET", "SDL_SCANCODE_BACKSLASH", "SDL_SCANCODE_NONUSHASH", "SDL_SCANCODE_SEMICOLON", "SDL_SCANCODE_APOSTROPHE", "SDL_SCANCODE_GRAVE", "SDL_SCANCODE_COMMA", "SDL_SCANCODE_PERIOD", "SDL_SCANCODE_SLASH", "SDL_SCANCODE_CAPSLOCK", "SDL_SCANCODE_F1", "SDL_SCANCODE_F2", "SDL_SCANCODE_F3", "SDL_SCANCODE_F4", "SDL_SCANCODE_F5", "SDL_SCANCODE_F6", "SDL_SCANCODE_F7", "SDL_SCANCODE_F8", "SDL_SCANCODE_F9", "SDL_SCANCODE_F10", "SDL_SCANCODE_F11", "SDL_SCANCODE_F12", "SDL_SCANCODE_PRINTSCREEN", "SDL_SCANCODE_SCROLLLOCK", "SDL_SCANCODE_PAUSE", "SDL_SCANCODE_INSERT", "SDL_SCANCODE_HOME", "SDL_SCANCODE_PAGEUP", "SDL_SCANCODE_DELETE", "SDL_SCANCODE_END", "SDL_SCANCODE_PAGEDOWN", "SDL_SCANCODE_RIGHT", "SDL_SCANCODE_LEFT", "SDL_SCANCODE_DOWN", "SDL_SCANCODE_UP", "SDL_SCANCODE_NUMLOCKCLEAR", "SDL_SCANCODE_KP_DIVIDE", "SDL_SCANCODE_KP_MULTIPLY", "SDL_SCANCODE_KP_MINUS", "SDL_SCANCODE_KP_PLUS", "SDL_SCANCODE_KP_ENTER", "SDL_SCANCODE_KP_1", "SDL_SCANCODE_KP_2", "SDL_SCANCODE_KP_3", "SDL_SCANCODE_KP_4", "SDL_SCANCODE_KP_5", "SDL_SCANCODE_KP_6", "SDL_SCANCODE_KP_7", "SDL_SCANCODE_KP_8", "SDL_SCANCODE_KP_9", "SDL_SCANCODE_KP_0", "SDL_SCANCODE_KP_PERIOD", "SDL_SCANCODE_NONUSBACKSLASH", "SDL_SCANCODE_APPLICATION", "SDL_SCANCODE_POWER", "SDL_SCANCODE_KP_EQUALS", "SDL_SCANCODE_F13", "SDL_SCANCODE_F14", "SDL_SCANCODE_F15", "SDL_SCANCODE_F16", "SDL_SCANCODE_F17", "SDL_SCANCODE_F18", "SDL_SCANCODE_F19", "SDL_SCANCODE_F20", "SDL_SCANCODE_F21", "SDL_SCANCODE_F22", "SDL_SCANCODE_F23", "SDL_SCANCODE_F24", "SDL_SCANCODE_EXECUTE", "SDL_SCANCODE_HELP", "SDL_SCANCODE_MENU", "SDL_SCANCODE_SELECT", "SDL_SCANCODE_STOP", "SDL_SCANCODE_AGAIN", "SDL_SCANCODE_UNDO", "SDL_SCANCODE_CUT", "SDL_SCANCODE_COPY", "SDL_SCANCODE_PASTE", "SDL_SCANCODE_FIND", "SDL_SCANCODE_MUTE", "SDL_SCANCODE_VOLUMEUP", "SDL_SCANCODE_VOLUMEDOWN", "", "", "", "SDL_SCANCODE_KP_COMMA", "SDL_SCANCODE_KP_EQUALSAS400", "SDL_SCANCODE_INTERNATIONAL1", "SDL_SCANCODE_INTERNATIONAL2", "SDL_SCANCODE_INTERNATIONAL3", "SDL_SCANCODE_INTERNATIONAL4", "SDL_SCANCODE_INTERNATIONAL5", "SDL_SCANCODE_INTERNATIONAL6", "SDL_SCANCODE_INTERNATIONAL7", "SDL_SCANCODE_INTERNATIONAL8", "SDL_SCANCODE_INTERNATIONAL9", "SDL_SCANCODE_LANG1", "SDL_SCANCODE_LANG2", "SDL_SCANCODE_LANG3", "SDL_SCANCODE_LANG4", "SDL_SCANCODE_LANG5", "SDL_SCANCODE_LANG6", "SDL_SCANCODE_LANG7", "SDL_SCANCODE_LANG8", "SDL_SCANCODE_LANG9", "SDL_SCANCODE_ALTERASE", "SDL_SCANCODE_SYSREQ", "SDL_SCANCODE_CANCEL", "SDL_SCANCODE_CLEAR", "SDL_SCANCODE_PRIOR", "SDL_SCANCODE_RETURN2", "SDL_SCANCODE_SEPARATOR", "SDL_SCANCODE_OUT", "SDL_SCANCODE_OPER", "SDL_SCANCODE_CLEARAGAIN", "SDL_SCANCODE_CRSEL", "SDL_SCANCODE_EXSEL", "", "", "", "", "", "", "", "", "", "", "", "SDL_SCANCODE_KP_00", "SDL_SCANCODE_KP_000", "SDL_SCANCODE_THOUSANDSSEPARATOR", "SDL_SCANCODE_DECIMALSEPARATOR", "SDL_SCANCODE_CURRENCYUNIT", "SDL_SCANCODE_CURRENCYSUBUNIT", "SDL_SCANCODE_KP_LEFTPAREN", "SDL_SCANCODE_KP_RIGHTPAREN", "SDL_SCANCODE_KP_LEFTBRACE", "SDL_SCANCODE_KP_RIGHTBRACE", "SDL_SCANCODE_KP_TAB", "SDL_SCANCODE_KP_BACKSPACE", "SDL_SCANCODE_KP_A", "SDL_SCANCODE_KP_B", "SDL_SCANCODE_KP_C", "SDL_SCANCODE_KP_D", "SDL_SCANCODE_KP_E", "SDL_SCANCODE_KP_F", "SDL_SCANCODE_KP_XOR", "SDL_SCANCODE_KP_POWER", "SDL_SCANCODE_KP_PERCENT", "SDL_SCANCODE_KP_LESS", "SDL_SCANCODE_KP_GREATER", "SDL_SCANCODE_KP_AMPERSAND", "SDL_SCANCODE_KP_DBLAMPERSAND", "SDL_SCANCODE_KP_VERTICALBAR", "SDL_SCANCODE_KP_DBLVERTICALBAR", "SDL_SCANCODE_KP_COLON", "SDL_SCANCODE_KP_HASH", "SDL_SCANCODE_KP_SPACE", "SDL_SCANCODE_KP_AT", "SDL_SCANCODE_KP_EXCLAM", "SDL_SCANCODE_KP_MEMSTORE", "SDL_SCANCODE_KP_MEMRECALL", "SDL_SCANCODE_KP_MEMCLEAR", "SDL_SCANCODE_KP_MEMADD", "SDL_SCANCODE_KP_MEMSUBTRACT", "SDL_SCANCODE_KP_MEMMULTIPLY", "SDL_SCANCODE_KP_MEMDIVIDE", "SDL_SCANCODE_KP_PLUSMINUS", "SDL_SCANCODE_KP_CLEAR", "SDL_SCANCODE_KP_CLEARENTRY", "SDL_SCANCODE_KP_BINARY", "SDL_SCANCODE_KP_OCTAL", "SDL_SCANCODE_KP_DECIMAL", "SDL_SCANCODE_KP_HEXADECIMAL", "", "", "SDL_SCANCODE_LCTRL", "SDL_SCANCODE_LSHIFT", "SDL_SCANCODE_LALT", "SDL_SCANCODE_LGUI", "SDL_SCANCODE_RCTRL", "SDL_SCANCODE_RSHIFT", "SDL_SCANCODE_RALT", "SDL_SCANCODE_RGUI", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "SDL_SCANCODE_MODE", "SDL_SCANCODE_AUDIONEXT", "SDL_SCANCODE_AUDIOPREV", "SDL_SCANCODE_AUDIOSTOP", "SDL_SCANCODE_AUDIOPLAY", "SDL_SCANCODE_AUDIOMUTE", "SDL_SCANCODE_MEDIASELECT", "SDL_SCANCODE_WWW", "SDL_SCANCODE_MAIL", "SDL_SCANCODE_CALCULATOR", "SDL_SCANCODE_COMPUTER", "SDL_SCANCODE_AC_SEARCH", "SDL_SCANCODE_AC_HOME", "SDL_SCANCODE_AC_BACK", "SDL_SCANCODE_AC_FORWARD", "SDL_SCANCODE_AC_STOP", "SDL_SCANCODE_AC_REFRESH", "SDL_SCANCODE_AC_BOOKMARKS", "SDL_SCANCODE_BRIGHTNESSDOWN", "SDL_SCANCODE_BRIGHTNESSUP", "SDL_SCANCODE_DISPLAYSWITCH", "SDL_SCANCODE_KBDILLUMTOGGLE", "SDL_SCANCODE_KBDILLUMDOWN", "SDL_SCANCODE_KBDILLUMUP", "SDL_SCANCODE_EJECT", "SDL_SCANCODE_SLEEP", "SDL_SCANCODE_APP1", "SDL_SCANCODE_APP2", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "SDL_NUM_SCANCODES", "Pause", "KeyCount", nullptr };
  return names;
}

inline const char *EnumNameKeyID(KeyID e) { return EnumNamesKeyID()[static_cast<int>(e)]; }

enum ActionType {
  ActionType_None = 0,
  ///< move forward
  ActionType_Forward = 1,
  ///< move ForwardLeft
  ActionType_ForwardLeft = 2,
  ///< move ForwardRight
  ActionType_ForwardRight = 3,
  ///< move backward
  ActionType_Backward = 4,
  ///< move BackwardLeft
  ActionType_BackwardLeft = 5,
  ///< move BackwardRight
  ActionType_BackwardRight = 6,
  ActionType_TurnLeft = 7,
  ActionType_TurnRight = 8,
  ActionType_StrafeLeft = 9,
  ActionType_StrafeRight = 10,
  ActionType_Jump = 11,
  ActionType_Run = 12,
  ActionType_Walk = 13,
  ActionType_NextTarget = 14,
  ActionType_PrevTarget = 15,
  ActionType_Punch1 = 16,
  ActionType_Kick1 = 17,
  ///rotate Entity
  ActionType_ObjRotate = 18,
  ///Camera
  ActionType_ZoomIn = 19,
  ActionType_ZoomOut = 20,
  ///< Rotate Camera
  ActionType_CamRotate = 21,
  ActionType_PointSelectStart = 22,
  ActionType_PointSelectEnd = 23,
  ActionType_PointMoved = 24,
  ActionType_Spell1 = 25,
  ActionType_Spell2 = 26,
  ActionType_Spell3 = 27,
  ActionType_Action1 = 28,
  ActionType_Action2 = 29,
  ActionType_NavUp = 30,
  ActionType_NavDown = 31,
  ActionType_NavLeft = 32,
  ActionType_NavRight = 33,
  ActionType_NavSelect = 34,
  ActionType_NavEnter = 35,
  ActionType_TextEntered = 36,
  ActionType_KeyPressed = 37,
  ActionType_KeyDown = 38,
  ActionType_Shoot = 39,
  ActionType_Resized = 40,
  ActionType_Quit = 41
};

inline const char **EnumNamesActionType() {
  static const char *names[] = { "None", "Forward", "ForwardLeft", "ForwardRight", "Backward", "BackwardLeft", "BackwardRight", "TurnLeft", "TurnRight", "StrafeLeft", "StrafeRight", "Jump", "Run", "Walk", "NextTarget", "PrevTarget", "Punch1", "Kick1", "ObjRotate", "ZoomIn", "ZoomOut", "CamRotate", "PointSelectStart", "PointSelectEnd", "PointMoved", "Spell1", "Spell2", "Spell3", "Action1", "Action2", "NavUp", "NavDown", "NavLeft", "NavRight", "NavSelect", "NavEnter", "TextEntered", "KeyPressed", "KeyDown", "Shoot", "Resized", "Quit", nullptr };
  return names;
}

inline const char *EnumNameActionType(ActionType e) { return EnumNamesActionType()[static_cast<int>(e)]; }

enum DeviceType {
  DeviceType_DT_unknown = 0,
  DeviceType_DT_KeyMouse = 1,
  DeviceType_DT_Joy = 2,
  DeviceType_DT_Gamepad = 3,
  DeviceType_DT_count = 4
};

inline const char **EnumNamesDeviceType() {
  static const char *names[] = { "DT_unknown", "DT_KeyMouse", "DT_Joy", "DT_Gamepad", "DT_count", nullptr };
  return names;
}

inline const char *EnumNameDeviceType(DeviceType e) { return EnumNamesDeviceType()[static_cast<int>(e)]; }

enum ActionOperator {
  ActionOperator_Or = 0,
  ActionOperator_And = 1
};

inline const char **EnumNamesActionOperator() {
  static const char *names[] = { "Or", "And", nullptr };
  return names;
}

inline const char *EnumNameActionOperator(ActionOperator e) { return EnumNamesActionOperator()[static_cast<int>(e)]; }

enum MouseBottonID {
  MouseBottonID_NONE = 0,
  MouseBottonID_MBID_0 = 1,
  MouseBottonID_MBID_1 = 2,
  MouseBottonID_MBID_2 = 3,
  MouseBottonID_MBID_3 = 4,
  MouseBottonID_MBID_4 = 5,
  MouseBottonID_MBID_5 = 6,
  MouseBottonID_MBID_6 = 7,
  MouseBottonID_MBID_7 = 8,
  MouseBottonID_MBID_8 = 9,
  MouseBottonID_MBID_9 = 10
};

inline const char **EnumNamesMouseBottonID() {
  static const char *names[] = { "NONE", "MBID_0", "MBID_1", "MBID_2", "MBID_3", "MBID_4", "MBID_5", "MBID_6", "MBID_7", "MBID_8", "MBID_9", nullptr };
  return names;
}

inline const char *EnumNameMouseBottonID(MouseBottonID e) { return EnumNamesMouseBottonID()[static_cast<int>(e)]; }

enum MouseWheelEvent {
  MouseWheelEvent_NONE = 0,
  MouseWheelEvent_MW_UP = 1,
  MouseWheelEvent_MW_DOWN = 2,
  MouseWheelEvent_MW_LEFT = 3,
  MouseWheelEvent_MW_RIGHT = 4
};

inline const char **EnumNamesMouseWheelEvent() {
  static const char *names[] = { "NONE", "MW_UP", "MW_DOWN", "MW_LEFT", "MW_RIGHT", nullptr };
  return names;
}

inline const char *EnumNameMouseWheelEvent(MouseWheelEvent e) { return EnumNamesMouseWheelEvent()[static_cast<int>(e)]; }

enum EventType {
  ///< Repeated input (e.g. a key that is held down).
  EventType_Hold = 0,
  ///< Press events that occur only once (e.g. key pressed).
  EventType_PressOnce = 1,
  ///< Release events that occur only once (e.g. key released).
  EventType_ReleaseOnce = 2
};

inline const char **EnumNamesEventType() {
  static const char *names[] = { "Hold", "PressOnce", "ReleaseOnce", nullptr };
  return names;
}

inline const char *EnumNameEventType(EventType e) { return EnumNamesEventType()[static_cast<int>(e)]; }

struct Event FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  EventType eventType() const { return static_cast<EventType>(GetField<int16_t>(4, 0)); }
  ActionOperator actionOperator() const { return static_cast<ActionOperator>(GetField<uint16_t>(6, 0)); }
  KeyID kCode() const { return static_cast<KeyID>(GetField<int16_t>(8, 0)); }
  MouseBottonID mouseBtn() const { return static_cast<MouseBottonID>(GetField<int16_t>(10, 0)); }
  MouseWheelEvent mWheel() const { return static_cast<MouseWheelEvent>(GetField<int16_t>(12, 0)); }
  uint16_t joyAxis() const { return GetField<uint16_t>(14, 0); }
  int16_t joyBtn() const { return GetField<int16_t>(16, -1); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, 4 /* eventType */) &&
           VerifyField<uint16_t>(verifier, 6 /* actionOperator */) &&
           VerifyField<int16_t>(verifier, 8 /* kCode */) &&
           VerifyField<int16_t>(verifier, 10 /* mouseBtn */) &&
           VerifyField<int16_t>(verifier, 12 /* mWheel */) &&
           VerifyField<uint16_t>(verifier, 14 /* joyAxis */) &&
           VerifyField<int16_t>(verifier, 16 /* joyBtn */) &&
           verifier.EndTable();
  }
};

struct EventBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_eventType(EventType eventType) { fbb_.AddElement<int16_t>(4, static_cast<int16_t>(eventType), 0); }
  void add_actionOperator(ActionOperator actionOperator) { fbb_.AddElement<uint16_t>(6, static_cast<uint16_t>(actionOperator), 0); }
  void add_kCode(KeyID kCode) { fbb_.AddElement<int16_t>(8, static_cast<int16_t>(kCode), 0); }
  void add_mouseBtn(MouseBottonID mouseBtn) { fbb_.AddElement<int16_t>(10, static_cast<int16_t>(mouseBtn), 0); }
  void add_mWheel(MouseWheelEvent mWheel) { fbb_.AddElement<int16_t>(12, static_cast<int16_t>(mWheel), 0); }
  void add_joyAxis(uint16_t joyAxis) { fbb_.AddElement<uint16_t>(14, joyAxis, 0); }
  void add_joyBtn(int16_t joyBtn) { fbb_.AddElement<int16_t>(16, joyBtn, -1); }
  EventBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  EventBuilder &operator=(const EventBuilder &);
  flatbuffers::Offset<Event> Finish() {
    auto o = flatbuffers::Offset<Event>(fbb_.EndTable(start_, 7));
    return o;
  }
};

inline flatbuffers::Offset<Event> CreateEvent(flatbuffers::FlatBufferBuilder &_fbb,
   EventType eventType = EventType_Hold,
   ActionOperator actionOperator = ActionOperator_Or,
   KeyID kCode = KeyID_SDL_SCANCODE_UNKNOWN,
   MouseBottonID mouseBtn = MouseBottonID_NONE,
   MouseWheelEvent mWheel = MouseWheelEvent_NONE,
   uint16_t joyAxis = 0,
   int16_t joyBtn = -1) {
  EventBuilder builder_(_fbb);
  builder_.add_joyBtn(joyBtn);
  builder_.add_joyAxis(joyAxis);
  builder_.add_mWheel(mWheel);
  builder_.add_mouseBtn(mouseBtn);
  builder_.add_kCode(kCode);
  builder_.add_actionOperator(actionOperator);
  builder_.add_eventType(eventType);
  return builder_.Finish();
}

struct Action FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  ActionType actionType() const { return static_cast<ActionType>(GetField<uint16_t>(4, 0)); }
  const flatbuffers::Vector<flatbuffers::Offset<Event>> *events() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Event>> *>(6); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* actionType */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* events */) &&
           verifier.Verify(events()) &&
           verifier.VerifyVectorOfTables(events()) &&
           verifier.EndTable();
  }
};

struct ActionBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_actionType(ActionType actionType) { fbb_.AddElement<uint16_t>(4, static_cast<uint16_t>(actionType), 0); }
  void add_events(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Event>>> events) { fbb_.AddOffset(6, events); }
  ActionBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ActionBuilder &operator=(const ActionBuilder &);
  flatbuffers::Offset<Action> Finish() {
    auto o = flatbuffers::Offset<Action>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<Action> CreateAction(flatbuffers::FlatBufferBuilder &_fbb,
   ActionType actionType = ActionType_None,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Event>>> events = 0) {
  ActionBuilder builder_(_fbb);
  builder_.add_events(events);
  builder_.add_actionType(actionType);
  return builder_.Finish();
}

struct ControllerMap FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  DeviceType type() const { return static_cast<DeviceType>(GetField<uint16_t>(4, 0)); }
  const flatbuffers::Vector<flatbuffers::Offset<Action>> *actionMap() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Action>> *>(6); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* type */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* actionMap */) &&
           verifier.Verify(actionMap()) &&
           verifier.VerifyVectorOfTables(actionMap()) &&
           verifier.EndTable();
  }
};

struct ControllerMapBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(DeviceType type) { fbb_.AddElement<uint16_t>(4, static_cast<uint16_t>(type), 0); }
  void add_actionMap(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Action>>> actionMap) { fbb_.AddOffset(6, actionMap); }
  ControllerMapBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ControllerMapBuilder &operator=(const ControllerMapBuilder &);
  flatbuffers::Offset<ControllerMap> Finish() {
    auto o = flatbuffers::Offset<ControllerMap>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<ControllerMap> CreateControllerMap(flatbuffers::FlatBufferBuilder &_fbb,
   DeviceType type = DeviceType_DT_unknown,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Action>>> actionMap = 0) {
  ControllerMapBuilder builder_(_fbb);
  builder_.add_actionMap(actionMap);
  builder_.add_type(type);
  return builder_.Finish();
}

struct ControllerList FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::Vector<flatbuffers::Offset<ControllerMap>> *ctrlList() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<ControllerMap>> *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* ctrlList */) &&
           verifier.Verify(ctrlList()) &&
           verifier.VerifyVectorOfTables(ctrlList()) &&
           verifier.EndTable();
  }
};

struct ControllerListBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_ctrlList(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ControllerMap>>> ctrlList) { fbb_.AddOffset(4, ctrlList); }
  ControllerListBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ControllerListBuilder &operator=(const ControllerListBuilder &);
  flatbuffers::Offset<ControllerList> Finish() {
    auto o = flatbuffers::Offset<ControllerList>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<ControllerList> CreateControllerList(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ControllerMap>>> ctrlList = 0) {
  ControllerListBuilder builder_(_fbb);
  builder_.add_ctrlList(ctrlList);
  return builder_.Finish();
}

inline const ControllerSettings::ControllerList *GetControllerList(const void *buf) { return flatbuffers::GetRoot<ControllerSettings::ControllerList>(buf); }

inline bool VerifyControllerListBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<ControllerSettings::ControllerList>(); }

inline void FinishControllerListBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<ControllerSettings::ControllerList> root) { fbb.Finish(root); }

}  // namespace ControllerSettings

#endif  // FLATBUFFERS_GENERATED_CONTROLLERS_CONTROLLERSETTINGS_H_
