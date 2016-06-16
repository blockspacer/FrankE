#include "TestControllerSystem.hpp"

#include <XEngine.hpp>

#include <XEngine/Controller/UI/UI_Console.hpp>
#include <XEngine/Controller/UI/UIFrameStatState.hpp>
#include <XEngine/Components/CameraFree.hpp>
#include <XEngine/Components/Controller.hpp>
#include <XEPhysics/Physics/gkRayTest.h>
#include "Controllers_generated.h"
#include <functional>

namespace XET {

	void TestControllerSystem::onQuit()
	{
		mEngine.quit();
	}

	void TestControllerSystem::setBasicInputEvents(TestControllerComponent& controller)
	{
		controller.system.connect0(ControllerSettings::ActionType_Quit, [this]() { onQuit(); });

		////Interface
		//controller.system.connect(ActionType_NavRight, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });  //std::bind(&TestControllerSystem::menuNav, std::placeholders::_1, ControllerSettings::ActionType_NavRight));
		//controller.system.connect(ActionType_NavLeft, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });
		//controller.system.connect(ActionType_NavUp, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });
		//controller.system.connect(ActionType_NavDown, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });
		//controller.system.connect(ActionType_NavEnter, [this, &controller](XE::ActionContext context) { menuNav(context, controller); });

		controller.system.connect(ControllerSettings::ActionType_Resized, [this](XE::ActionContext context) { onResized(context); });

		controller.system.connect(ControllerSettings::ActionType_KeyPressed, [this](XE::ActionContext context) { onKeyPressed(context); });
		controller.system.connect(ControllerSettings::ActionType_TextEntered, [this](XE::ActionContext context) { onTextEntered(context); });

		//mouse only events
		controller.system.connect(ControllerSettings::ActionType_PointSelectStart, [this](XE::ActionContext context) { onPointSelectStart(context); });
		controller.system.connect(ControllerSettings::ActionType_PointSelectEnd, [this](XE::ActionContext context) { onPointSelectEnd(context); });
		controller.system.connect(ControllerSettings::ActionType_PointMoved, [this](XE::ActionContext context) { onPointMoved(context); });
	}

	TestControllerSystem::TestControllerSystem(XE::XEngine& engine)
		: mEngine(engine)
		, mDecalDestroy(false)
		, _lastMousePos(0, 0)
		, _mousePressed(false)
		, moveDirection(0, 0, 0)

		, _turn_speed(0)
		, _zoom_speed(0)
	{
		//	mCamera.getCamera()->setNearClipDistance(0.7);
		//mRayScnQuery = mEngine->mScene->getSceneMgr()->createRayQuery(Ogre::Ray());
	}

	TestControllerSystem::~TestControllerSystem()
	{
	}

	void TestControllerSystem::onPointMoved(XE::ActionContext context)
	{
		// Ignore this if it happened due to a warp
		if (handleWarpMotion(context.event->motion))
			return;

		// Try to keep the mouse inside the window
		if (m_windowHasFocus)
			wrapMousePointer(context.event->motion, context.window);

		// If in relative mode, don't trigger events unless window has focus
		if (m_wantRelative && !m_windowHasFocus)
			return;

		sf::Vector2i mousePosition = sf::Vector2i(context.event->button.x, context.event->button.y);//;sf::Mouse::getPosition(*controller.m_window);

		std::cout << "onPointMoved! x:" << mousePosition.x << ",y:" << mousePosition.y << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->onPointMoved(mousePosition.x, mousePosition.y);

			if (!_mousePressed)
				continue;

			//-----------------------------------------------
			//TODO only if no Interface active!!!!
			float tx = controller->_windowState.width;
			float ty = controller->_windowState.height;

			float deltax = -context.event->motion.xrel / tx;
			float deltay = -context.event->motion.yrel / ty;

			//	std::cout << "delta! x:" << deltax << ",y:" << deltay << std::endl;

			if (entity.has_component<XE::CameraFreeComponent>())
			{
				entity.component<XE::CameraFreeComponent>()->rotate(deltax, deltay);
			}
		}
	}

	void TestControllerSystem::onKeyPressed(XE::ActionContext context)
	{
		std::cout << "onKeyPressed! " << context.event->key.keysym.scancode << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {
			screen->m_Desktop->onKeyEvent(context.event->key);
		}
	}

	void TestControllerSystem::onTextEntered(XE::ActionContext context)
	{
		std::cout << "onTextEntered! " << context.event->text.text << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {
			screen->m_Desktop->onTextEvent(context.event->text);
		}
	}

	void TestControllerSystem::onPointSelectStart(XE::ActionContext context)
	{
		std::cout << "onPointSelectStart! " << context.event->button.button << std::endl;

		setGrabMousePointer(true, context.window);
		setMouseVisible(false, context.window);

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->onPointDown(context.event->button.x, context.event->button.y);
		}

		_lastMousePos = sf::Vector2i(context.event->button.x, context.event->button.y);
		_mousePressed = true;
	}

	void TestControllerSystem::onPointSelectEnd(XE::ActionContext context)
	{
		std::cout << "onPointSelectEnd! " << context.event->button.button << std::endl;

		entityx::ComponentHandle<TestControllerComponent> controller;
		entityx::ComponentHandle<XE::ScreenComponent> screen;

		//todo !!! check all scenes for controllers or handle all controllers in a separat list?
		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller, screen)) {

			screen->m_Desktop->onPointUp(context.event->button.x, context.event->button.y);
		}

		setGrabMousePointer(false, context.window);
		setMouseVisible(true, context.window);
		_mousePressed = false;
	}

	void TestControllerSystem::onResized(XE::ActionContext context)
	{
		SDLInputHandler::onWindowEvent(context);

		sf::Vector2i size;
		SDL_GetWindowSize(context.window, &size.x, &size.y);
		mEngine.getGraphicsManager().resizeRenderWindow(size.x, size.y);

		entityx::ComponentHandle<TestControllerComponent> controller;

		for (entityx::Entity entity : mEngine.getScene().entities.entities_with_components(controller)) {

			controller->_windowState.width = size.x;
			controller->_windowState.height = size.y;
			controller->_windowState.isDirty = true;
		}

		std::cout << "Resized!   New size = (" << size.x << ", " << size.y << ")" << std::endl;
	}

	void TestControllerSystem::menuNav(XE::ActionContext context, TestControllerComponent& controller)
	{
		//switch (context.actionId)
		//{
		//case InputCmd::NavRight:

		////todo	mEngine->getUIMgr().makeNextItemOver();
		//	std::cout << "menuNav (NavRight)" << std::endl;
		//	break;
		//case InputCmd::NavLeft:

		//	//todo	mEngine->getUIMgr().makePrevItemOver();
		//	std::cout << "menuNav (NavLeft)" << std::endl;
		//	break;
		//case InputCmd::NavDown:

		//	//todo	mEngine->getUIMgr().selectOveredItem();
		//	std::cout << "menuNav (NavDown)" << std::endl;
		//	break;
		//
		//case InputCmd::NavUp:

		//		//todo	mEngine->getUIMgr().selectOveredItem();
		//		std::cout << "menuNav (NavUp)" << std::endl;
		//		break;
		//case InputCmd::NavEnter:

		//	//todo	mEngine->getUIMgr().selectOveredItem();
		//	std::cout << "menuNav (NavEnter)" << std::endl;
		//	break;
		//}

		//	MyEvent( 5 );
	}

	void TestControllerSystem::move(entityx::Entity entity)
	{
		entityx::ComponentHandle<XE::BodyComponent> body = entity.component<XE::BodyComponent>();
		entityx::ComponentHandle<TestControllerComponent> controller = entity.component<TestControllerComponent>();

		if (controller->actionmap.isActive(ControllerSettings::ActionType_StrafeLeft))
			moveDirection.x = -1.0f;//left

		if (controller->actionmap.isActive(ControllerSettings::ActionType_Forward))
			moveDirection.z = 1.0f;//forward

		if (controller->actionmap.isActive(ControllerSettings::ActionType_StrafeRight))
			moveDirection.x = 1.0f; //right

		if (controller->actionmap.isActive(ControllerSettings::ActionType_Backward))
			moveDirection.z = -1.0f;//backward

		if (controller->actionmap.isActive(ControllerSettings::ActionType_TurnLeft) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeLeft) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeRight))
		{
			if (entity.has_component<XE::BodyComponent>())
				entity.component<XE::BodyComponent>()->rotate(XE::Vector3::UNIT_Y, XE::Radian(_turn_speed));
			else // camera
				moveDirection.x = -1.0f;//left
		}
		else if (controller->actionmap.isActive(ControllerSettings::ActionType_TurnRight) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeLeft) && !controller->actionmap.isActive(ControllerSettings::ActionType_StrafeRight))
		{
			if (entity.has_component<XE::BodyComponent>())
				entity.component<XE::BodyComponent>()->rotate(XE::Vector3::UNIT_Y, XE::Radian(-_turn_speed));
			else // camera
				moveDirection.x = 1.0f; //right
		}
	}

	void TestControllerSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
	{
		entityx::ComponentHandle<TestControllerComponent> controller;

		for (entityx::Entity entity : es.entities_with_components(controller)) {

			if (controller->m_window)
				controller->actionmap.update(); //clearing events !!

			// Forward actions to callbacks: Invokes onResize() in case of Event::Resized events
			controller->actionmap.invokeCallbacks(controller->system, controller->m_window);

			move(entity);

			////only camera
			if (moveDirection != XE::Vector3::ZERO && entity.has_component<XE::CameraFreeComponent>())
			{
				entityx::ComponentHandle<XE::CameraFreeComponent> camera = entity.component<XE::CameraFreeComponent>();
				moveDirection.normalise();
				camera->getCameraNode().translate(moveDirection * 0.5);

				//	else
				//		LOG(INFO) << "camposx:" << camera->getCameraNode().getPosition().x << "camposy:" << camera->getCameraNode().getPosition().y << "camposz:" << camera->getCameraNode().getPosition().z;
			}

			moveDirection = XE::Vector3(0, 0, 0);

			if (entity.has_component<XE::ScreenComponent>())
			{
				if (controller->_windowState.isDirty)
				{
					controller->_windowState.isDirty = false;
					entity.component<XE::ScreenComponent>()->setSize(controller->_windowState.width, controller->_windowState.height);
				}

				entity.component<XE::ScreenComponent>()->mUIStateManager.update(dt);
				entity.component<XE::ScreenComponent>()->m_Desktop->Update(dt);
			}
		}
	}

} // namespace XE
