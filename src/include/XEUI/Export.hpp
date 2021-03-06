////////////////////////////////////////////////////////////

#ifndef XEUI_EXPORT_HPP
#define XEUI_EXPORT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>


////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(XEUI_EXPORTS)

#define XEUI_API SFML_API_EXPORT

#else

#define XEUI_API SFML_API_IMPORT

#endif


#endif // XEUI_EXPORT_HPP
