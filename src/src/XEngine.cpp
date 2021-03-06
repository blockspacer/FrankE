#include <XEngine.hpp>

#include <XEDAL/PhysFS/PhysFSWrapper.h>
#include <XEDAL/PhysFS/PhysFSArchive.h>
#include <XEPhysics/Physics/gkDynamicsWorld.h>


#include <algorithm>

//INITIALIZE_EASYLOGGINGPP

void ControllerThread(XE::XEngine* engine)
{
	//return;
	while (engine->running() || !engine->isInitialized())
	{

		if (engine->isInitialized())
		{
			// let the state update the game
			//todo	engine->lastState()->update();
		//	engine->getCtrlMgr().update(); //update Controller

			//update physics 
			//	engine->getScene().getDynamicsWorld()->step(evt.timeSinceLastFrame);
		}

		//	engine->renderUpdate();

		//if (engine->getCtrlMgr().getController(0))
		//	engine->getCtrlMgr().update(); //update Controller
	}
}

namespace XE
{
	class ViewManager2
	{
	public:
		ViewManager2(XEngine* test);

	};

	XEngine::XEngine() :
		m_initialized(false)
		, m_resume(false)
		, m_running(true)
		//	mControllerThread(ControllerThread, this),
		, mGraphicsManager(this)
		, m_clock()
		, m_NetworkManager()
		, _lua(*this)
		, _soundMgr()
		, m_OgreSceneManager(mGraphicsManager)
		, m_mtFrameLimiter()
	{		
		//plog::init(plog::debug, "HelloLog.txt"); // Step2: initialize the logger.
		//el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level ,tid: %thread msg: %msg");

		PhysFS::init(""); // init PhysFS system
	}

	XEngine::~XEngine()
	{

	}

	void XEngine::init()
	{
		LOG(plog::info) << "XEngine():init";


		//singlethreaded renderer	engine->getGraphicsManager().updateRenderer();
		//		engine->getGraphicsManager().updateRenderer();
		//controller->getControllerView().getCameraController().getOgreCamera();
		//texturemanager initialized in createrenderwindow!!!
		//renderwindow is create from current rendersystem!
		//Step 1 - RenderWindow
		mGraphicsManager.createRenderWindow(settings.windowTitle);// controller->getCameraController().getOgreCamera().__OgreCameraPtr);

		 //Step 1 Hlms
		//needs initialized root and renderwindow from rendersytem for vaomanager
		mGraphicsManager.registerHlms();

		//Step 2 Init Resourcesystem - needs hlms
		m_scene->loadRendererResources();

		//Step 3 atlas
		//	mGraphicsManager.getGUIRenderer().loadAtlas("UI/TestAtlas.fbbin"); // ("XEngine", "General"); //texturemanager initialized in createrenderwindow!!!

		//Step 4 scene
		m_OgreSceneManager.create();

		registerObject(_lua.state);
		m_NetworkManager.registerObject(_lua.state);
		
		m_IDAL->open();


		//m_DebugDrawer = std::unique_ptr<DebugDrawer>(new DebugDrawer(*m_scene.get(), 1));
	}

	void XEngine::registerObject(sol::state& lua)
	{
		lua.new_usertype<Entity>("Entity"
			//methods
			//, "onTick", &AIEvents::onTick

			//properties
			, "bodyComponent", sol::property(&Entity::getComponent<BodyComponent>)
			, "physicsComponent", sol::property(&Entity::getComponent<PhysicsComponent>)
			, "animationComponent", sol::property(&Entity::getComponent<AnimationComponent>)
			);

		auto overloaded = sol::overload(
			sol::resolve<void(const Ogre::Vector3&)>(&BodyComponent::setPosition),
			sol::resolve<void(Ogre::Real x, Ogre::Real y, Ogre::Real z)>(&BodyComponent::setPosition));


		lua.new_usertype<BodyComponent>("BodyComponent"
			//methods
			, "getPosition", &BodyComponent::getPosition
			, "getOrientation", &BodyComponent::getOrientation
			, "setPosition", overloaded
			, "setTargetPosition", &BodyComponent::setTargetPosition

			//properties
			, "hasTargetPosition", sol::property(&BodyComponent::hasTargetPosition)
			);


		lua.new_usertype<AnimationComponent>("AnimationComponent"
			//methods
			, "getParameter", &AnimationComponent::getParameter
			
			//properties
			);

		lua.new_usertype<ParameterNode>("ParameterNode"
			//methods
			, "setValue", &ParameterNode::setValue
			);

		lua.new_usertype<IPhysicsObject>("PhysicsObject"
			//methods
	//		, "rotate", &IPhysicsObject::rotate 
			, "setOrientation", &IPhysicsObject::setOrientation
	//		, "setTransformState", &IPhysicsObject::setTransformState
			, "setPosition", &IPhysicsObject::setPosition
			, "suspend", &IPhysicsObject::suspend
			//properties
			//, "hasTargetPosition", sol::property(&BodyComponent::hasTargetPosition)
			);

		lua.new_usertype<PhysicsComponent>("PhysicsComponent"
			//methods
			, "get", &PhysicsComponent::get
			);
		
		lua.new_usertype<CameraFreeComponent>("CameraFreeComponent"
			//methods
			, "getCameraNode", &CameraFreeComponent::getCameraNode
			, "rotate", &CameraFreeComponent::rotate
			);

		lua.new_usertype<XEngine>("XEngine",

			//properties
			"graphicsMgr", sol::property(&XEngine::getGraphicsManager),
			"networkMgr", sol::property(&XEngine::getNetworkManager),
			"ogreSceneMgr", sol::property(&XEngine::getOgreSceneManager),
			"soundMgr", sol::property(&XEngine::getSoundMgr),
			"scene", sol::property(&XEngine::getScene),
			"dal", sol::property(&XEngine::getDAL),
			"lua", sol::property(&XEngine::getLua),
			"isInitialized", sol::property(&XEngine::isInitialized),

			//functions
			"quit", &XEngine::quit,
			//"run", &XEngine::run  unique_ptr ! parameter
			"nextState", &XEngine::nextState,
			"lastState", &XEngine::lastState
		);

		auto stateView = lua.set("XEngine", this); //set object instance
	}

	void XEngine::quit()
	{
		m_running = false;
	}

	void XEngine::destroy()
	{
		for (entityx::Entity entity : m_scene->entities.entities_for_debugging()) {

			entity.destroy();
		}
	}
	
	void XEngine::setScene(std::unique_ptr<Scene> scene)
	{
		m_scene = std::move(scene);
	}

	void XEngine::setDAL(std::unique_ptr<IDAL> idal)
	{
		m_IDAL = std::move(idal);
	}

	void XEngine::setNextState(std::unique_ptr<XEState> state)
	{
		m_states.top()->m_next = std::move(state);
	}

	void XEngine::run(std::unique_ptr<XEState> state)
	{
		m_running = true;
		m_initialized = true;

		m_states.push(std::move(state));

	}

	void XEngine::nextState()
	{
		if (m_resume)
		{
			// cleanup the current state
			if (!m_states.empty())
			{
				m_states.pop();
			}

			// resume previous state
			if (!m_states.empty())
			{
				m_states.top()->resume();
			}

			m_resume = false;
		}

		// there needs to be a state
		if (!m_states.empty())
		{
			std::unique_ptr<XEState> temp = m_states.top()->next();

			// only change states if there's a next one existing
			if (temp != nullptr)
			{
				// replace the running state
				if (temp->isReplacing())
					m_states.pop();
				// pause the running state
				else
					m_states.top()->pause();

				m_states.push(std::move(temp));
			}
		}
	}

	void XEngine::lastState()
	{
		m_resume = true;
	}


	void XEngine::update()
	{
		//bool test = false;
		//if (test)
		//{
		//	mGraphicsManager.getIntoRendererQueue().push([this]() {
		//		//saving 
		//	DataStreamPtr shaderCacheFileout = mGraphicsManager.getRoot()->createFileStream("F:/Projekte/coop/XGame/data/MyCache.cache", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
		//	GpuProgramManager::getSingleton().saveMicrocodeCache(shaderCacheFileout);
		//
		//	std::ifstream f(tmpShaderCacheFolder.c_str()); // http://www.ogre3d.org/forums/viewtopic.php?f=25&t=88919&p=530493#p530493
		//if (f.good())
		//{
		//		//loading
		//		//GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true); //Make sure it's enabled.
		//		//DataStreamPtr shaderCacheFile = mGraphicsManager.getRoot()->openFileStream("F:/Projekte/coop/XGame/data/MyCache.cache");
		//		//GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);
		//	});
		//}

		//sf::Time elapsed1 = m_clock.getElapsedTime();
	

		elapsedTimeMainThread = m_clock.restart();


		m_mtFrameLimiter.ApplyFrameLimit(elapsedTimeMainThread,50);

		
		sf::Uint64 time = elapsedTimeMainThread.asMicroseconds();

		double timeSinceLast = time / 1000000.0;
		timeSinceLast = std::min(1.0, timeSinceLast); //Prevent from going haywire.

				
		m_scene->update(timeSinceLast);

		m_states.top()->update(timeSinceLast);

#ifndef UseRenderThread
		mGraphicsManager.updateRenderer();  // only in singlethread mode! -> else it's  the job of the graphicsmanager!
#else
		mGraphicsManager._isRenderThreadFinished = false;
#endif

		mGraphicsManager.getFromRendererQueue().TriggerAllHandler();

		//bool cap = true;limi


		////If we want to cap the frame rate
		//if ((cap == true) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND))
		//{
		//	//Sleep the remaining frame time
		//	SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		//}

		//	XE::WindowEventUtilities::messagePump(); //dont use it or .net wrapper crash!
	}

	void XEngine::draw()
	{
		// let the state draw the screen
		m_states.top()->draw();
	}


}