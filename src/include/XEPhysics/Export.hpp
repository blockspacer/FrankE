////////////////////////////////////////////////////////////

#ifndef XEPHYSICS_EXPORT_HPP
#define XEPHYSICS_EXPORT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>


////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(XEPHYSICS_EXPORTS)

#define XEPHYSICS_API SFML_API_EXPORT

#else

#define XEPHYSICS_API SFML_API_IMPORT

#endif


#endif // XEPHYSICS_EXPORT_HPP
