
#ifndef XENGINE_HPP
#define XENGINE_HPP

//Componentsytem comparison
//https://tilemapkit.com/2015/10/entity-component-systems-compared-benchmarked-entityx-anax-artemis/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <XEDebugger.hpp>

#include <XESystem.hpp>
#include <XESystem/Entityx/entityx.h>
#include <XENetwork.hpp>
#include <XESystem/Logging.hpp> // add here for winsock conflict from XENetwork!

#include <Ogre/OgreMain/include/OgreVector3.h>

#include <XEAudio.hpp>
#include <XERenderer.hpp>
#include <XEEffect.hpp>
#include <XEUI.hpp>
#include <XEScripts.hpp>
#include <XEPhysics.hpp>
#include <XEController.hpp>
#include <XEAnimation.hpp>


#include <XEngine/Systems/RenderBodySystem.hpp>
#include <XEngine/Components/SpawnPoint.hpp>
#include <XEngine/Systems/EntityRenderSystem.hpp>
#include <XEngine/Systems/FreeLookCameraSystem.hpp>
//#include <XEngine/Systems/ControllerSystem.hpp>
#include <XEngine/Systems/AnimationSystem.hpp>
#include <XEngine/Components/CameraFree.hpp>
#include <XEngine/Components/CameraFix.hpp>
#include <XEngine/Components/Controller.hpp>
#include <XEngine/Components/ScreenComponent.hpp>
#include <XEngine/Components/NetId.hpp>
#include <XEngine/Components/AnimationComponent.hpp>
//#include <XEngine/Components/Light.hpp>

#include <XEngine/Components/PhysicsComponents.hpp>
#include <XEngine/Components/SpawnPoint.hpp>

#include <XERenderer/CameraRenderable.hpp>
#include <XEngine/Systems/PhysicsSystem.hpp>

#include <XEngine/Controller/UI/UI_Console.hpp>
#include <XEngine/Controller/UI/UIFrameStatState.hpp>

#include <XEngine/Scene.hpp>

#include <XEInput.hpp>

#include <XEngine/XENetObserver.hpp>

#include <XEState.h>
#include <XEDAL.h>
#include <XERenderer/GraphicsManager.hpp>

#include <XERenderer/OgreSceneManager.hpp>

#include <iostream>

#include <stack>
#include <string>
#include <memory>
#include <thread>
#include <mutex>


namespace XE
{
	//all namespaces should be callable with XE::
	using namespace thor;
	//	using namespace sf; math conflict
	using namespace Ogre;
	//using namespace sfn;
	using namespace XFBType;

	struct StateData;

	class XEngine
	{
	public:
		///Ctor
		XEngine(const std::string& ressFile, const std::string& title, bool isEditor = false);
		~XEngine();

		void setScene(std::unique_ptr<Scene> scene);
		void run(std::unique_ptr< XEState > state);
		void setNextState(std::unique_ptr<XEState> state);


		void nextState();
		void lastState();

		void update();
		void draw();

		XEState* getCurrentState() {
			return m_states.top().get(); }

		inline bool running() {  
			return m_running; }

		void quit();

		template < typename T >
		std::unique_ptr< T > build(XEngine& engine, bool replace = true);

		inline bool isInitialized() {
			return m_initialized;
		}

		inline IDAL& getIDAL() {
			return mIDAL;
		}
		inline LuaEngine& getLua() {
			return _lua;
		}
		inline GraphicsManager& getGraphicsManager() {
			return mGraphicsManager;
		}
		inline NetworkManager& getNetworkManager() {
			return m_NetworkManager;
		}
		OgreSceneManager& getOgreSceneManager() {
			return m_OgreSceneManager;
		}
		SoundManager& getSoundMgr() {
			return _soundMgr;
		};
		Scene& getScene() {
			return *m_scene.get();
		}


	protected:


	private:

		void initResourceSystem();

		void registerObject(sol::state& lua);

		sf::Clock m_clock;
		// the stack of states
		std::stack< std::unique_ptr< XEState > > m_states;
		bool m_resume;
		std::string m_ressFile;
		bool m_running;
		bool m_initialized;

		//initialization order!
		LuaEngine			_lua;
		GraphicsManager   mGraphicsManager;
		OgreSceneManager m_OgreSceneManager;

		IDAL				mIDAL;
		std::unique_ptr<Scene>	m_scene;

		NetworkManager		m_NetworkManager;
		SoundManager		_soundMgr;

		std::mutex			mControllerMutex;// protects mControllerThread
		std::thread			mControllerThread;
	};

	template < typename T >
	std::unique_ptr< T > XEngine::build(XEngine& engine, bool replace)
	{
		return std::move(std::unique_ptr< T >(new T(engine, replace)));
	}
}
#endif 