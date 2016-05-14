#ifndef __IDALOBJECT_HPP__
#define __IDALOBJECT_HPP__

#include <XESystem/SystemConfig.hpp>

namespace XE {

	class IDALObject
	{
	public:
		virtual void create(XE::Uint16 id, char* fbData = nullptr) = 0;
		virtual void reload(char* fbData = nullptr) = 0;
	};

} // ns XE

#endif // __IDALOBJECT_HPP__