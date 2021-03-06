#include <XEScripts/LUAEngine.h>

#include <Ogre/OgreMain/include/OgreVector3.h>
#include <XEScripts/LUA/LuaVector3.hpp>
#include <XEDAL/PhysFS/PhysFsStream.hpp>
#include <ThirdParty/sfml/include/sfml/System/Vector2.hpp>

namespace XE {

	LuaEngine::LuaEngine(XEngine& engine)
		: m_engine(engine)
		, state()
	{
		state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);

		state.new_usertype< Ogre::Vector3>("Vector3",

			// 3 constructors
			//sol::constructors<sol::types<>, sol::types<int>, sol::types<int, int>>(),
			sol::constructors<sol::types<>, sol::types<float, float, float>>(),

			// typical member function that returns a variable

			"x", &Ogre::Vector3::x,
			// typical member function
			"y", &Ogre::Vector3::y,
			"z", &Ogre::Vector3::z

			// gets or set the value using member variable syntax
			//"hp", sol::property(&player::get_hp, &player::set_hp),

			//// read and write variable
			//"speed", &player::speed,
			//// can only read from, not write to
			//"bullets", sol::readonly(&player::bullets)
			);

		state.new_usertype< Ogre::Quaternion>("Quaternion",

			// 3 constructors
			//sol::constructors<sol::types<>, sol::types<int>, sol::types<int, int>>(),
			sol::constructors<sol::types<>, sol::types<float, float, float, float>>(),

			// typical member function that returns a variable

			"w", &Ogre::Quaternion::w,
			"x", &Ogre::Quaternion::x,
			// typical member function
			"y", &Ogre::Quaternion::y,
			"z", &Ogre::Quaternion::z

			// gets or set the value using member variable syntax
			//"hp", sol::property(&player::get_hp, &player::set_hp),

			//// read and write variable
			//"speed", &player::speed,
			//// can only read from, not write to
			//"bullets", sol::readonly(&player::bullets)
			);

		state.new_usertype<sf::Vector2f>("Vector2f",

			// 3 constructors
			//sol::constructors<sol::types<>, sol::types<int>, sol::types<int, int>>(),
			sol::constructors<sol::types<>, sol::types<float, float>>(),

			// typical member function that returns a variable

			"x", &sf::Vector2f::x,
			// typical member function
			"y", &sf::Vector2f::y

			// gets or set the value using member variable syntax
			//"hp", sol::property(&player::get_hp, &player::set_hp),

			//// read and write variable
			//"speed", &player::speed,
			//// can only read from, not write to
			//"bullets", sol::readonly(&player::bullets)
			);
	}

	//void LuaEngine::init()
	//{
	//	sol::state state;
	//					 
	//	// open some common libraries
	//	state.open_libraries(sol::lib::base, sol::lib::package);

	//	Ogre::Vector3 foo(2,2,2);

	//	LuaVector3::regClass(state);
	//	LuaVector3::regObj(state, foo);

	//	// load file without execute
	//	sol::load_result script1 = state.load_file("F:\\Projekte\\coop\\XGame\\data\\lua\\test.lua");
	//	script1.call();
	//	//script1(); //execute
	//}

	void LuaEngine::executeScript(const std::string& filepath)
	{
		auto result = loadFile( filepath);
		result(); //execute
	}

	void LuaEngine::reloadScript(const std::string& filepath)
	{
		//FIXME
		auto result = loadFile(filepath);
		result(); //execute
	}

	void LuaEngine::removeScript(const std::string& filepath)
	{
		//todo
	}

	sol::load_result LuaEngine::loadFile(const std::string& filename)
	{
		XE::PhysFsStream wonderfullStream;
		if (wonderfullStream.open(filename.c_str()))
		{
			// Make sure that the stream's reading position is at the beginning
			wonderfullStream.seek(0);

			std::vector<char> buffer(wonderfullStream.getSize());
			if (wonderfullStream.read(buffer.data(), wonderfullStream.getSize()))
			{
				return state.load_buffer(&buffer[0], wonderfullStream.getSize(), filename.c_str());
			}
		}
		return 0;
	}

} // ns XE