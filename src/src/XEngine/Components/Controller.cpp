#include <XEngine/Components/Controller.hpp>


//#include <XEngine/Controller/InputCmd.hpp>

//#include <XEInput/InputConfigFile.hpp>

//#include <Thor/Input/InputNames.hpp>

#include <iostream>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"


//#include <ThirdParty/sfml/include/sfml/Window.hpp>

namespace XE
{
	ControllerComponent::ControllerComponent() 
		:m_ControllerData(0)
	{
	}

	ControllerComponent::~ControllerComponent()
	{
	//	delete m_ControllerData;
	}

	ControllerData* ControllerComponent::get() {
		return m_ControllerData;
	}

	using namespace thor;
	//using namespace sf;

	ControllerData::ControllerData(Uint16 id, XEngine& engine, SDL_Window* window, bool defaultCtrl)
		: isActive(false)
		, m_window(window)
		, mID(id)
		, engine(engine)
	{
		SDL_GetWindowSize(window,
			&_windowState.width,
			&_windowState.width);


		//_windowState.width = window->getSize().x;
		//_windowState.height = window->getSize().y;
		_windowState.isDirty = true;

		//default mouse keyboard
		if (defaultCtrl)
		{
			//std::cout << "settingActionMap!" << std::endl;

			//actionmap[InputCmd::TextEntered] = Action(Event::TextEntered);
			//actionmap[InputCmd::KeyPressed] = Action(Event::KeyPressed);

			//// Resize: Change window size (single event)
			//actionmap[InputCmd::Resized] = Action(Event::Resized);
			////actionmap[InputCmd::Quit] = Action(Event::Closed);

			////Actions festlegen
			//actionmap[InputCmd::PointSelectStart] = Action(Mouse::Left, Action::PressOnce) || Action(Mouse::Right, Action::PressOnce);
			//actionmap[InputCmd::PointSelectEnd] = Action(Mouse::Left, Action::ReleaseOnce) || Action(Mouse::Right, Action::ReleaseOnce);
			//actionmap[InputCmd::PointMoved] = Action(Event::MouseMoved);

			////actionmap[InputCmd::CamRotateStart] = Action(Mouse::Left, Action::PressOnce);
			////actionmap[InputCmd::CamRotate] = Action(Mouse::Left, Action::Hold);
			////actionmap[InputCmd::ObjRotateStart] = Action(Mouse::Right, Action::PressOnce);
			////actionmap[InputCmd::ObjRotate] = Action(Mouse::Right, Action::Hold);

			////actionmap[InputCmd::ZoomIn] = Action(Event::MouseWheelMoved);
			////actionmap[InputCmd::ZoomOut] = Action(Event::MouseWheelMoved);


			//actionmap[InputCmd::Quit] = Action(Keyboard::Escape, Action::PressOnce) || Action(Event::Closed);
			//actionmap[InputCmd::NavLeft] = Action(Keyboard::Left, Action::PressOnce);
			//actionmap[InputCmd::NavRight] = Action(Keyboard::Right, Action::PressOnce);
			//actionmap[InputCmd::NavUp] = Action(Keyboard::Up, Action::PressOnce);
			//actionmap[InputCmd::NavDown] = Action(Keyboard::Down, Action::PressOnce);
			//actionmap[InputCmd::NavEnter] = Action(Keyboard::Return, Action::PressOnce);
		}
	}


	void ControllerData::destroy()
	{

	}

	//void ControllerData::setActionMap(const std::string& ctrlFile, const std::string& schema)
	//{
	//	std::cout << "settingActionMap!" << std::endl;

	//	controller.actionmap[ControllerSettings::ActionType::ActionType_TextEntered] = XE::Action(sf::Event::TextEntered);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_KeyPressed] = XE::Action(sf::Event::KeyPressed);

	//	// Resize: Change window size (single event)
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_Resized] = XE::Action(sf::Event::Resized);
	//	//actionmap[ControllerSettings::ActionType::ActionType_Quit] = Action(Event::Closed);

	//	//Actions festlegen
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_PointSelectStart] = XE::Action(sf::Mouse::Left, XE::Action::PressOnce) || XE::Action(sf::Mouse::Right, XE::Action::PressOnce);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_PointSelectEnd] = XE::Action(sf::Mouse::Left, XE::Action::ReleaseOnce) || XE::Action(sf::Mouse::Right, XE::Action::ReleaseOnce);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_PointMoved] = XE::Action(sf::Event::MouseMoved);

	//	//actionmap[ControllerSettings::ActionType::ActionType_CamRotateStart] = Action(Mouse::Left, Action::PressOnce);
	//	//actionmap[ControllerSettings::ActionType::ActionType_CamRotate] = Action(Mouse::Left, Action::Hold);
	//	//actionmap[ControllerSettings::ActionType::ActionType_ObjRotateStart] = Action(Mouse::Right, Action::PressOnce);
	//	//actionmap[ControllerSettings::ActionType::ActionType_ObjRotate] = Action(Mouse::Right, Action::Hold);

	//	//actionmap[ControllerSettings::ActionType::ActionType_ZoomIn] = Action(Event::MouseWheelMoved);
	//	//actionmap[ControllerSettings::ActionType::ActionType_ZoomOut] = Action(Event::MouseWheelMoved);


	//	controller.actionmap[ControllerSettings::ActionType::ActionType_Quit] = XE::Action(sf::Keyboard::Escape, XE::Action::PressOnce) || XE::Action(sf::Event::Closed);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_NavLeft] = XE::Action(sf::Keyboard::Left, XE::Action::PressOnce);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_NavRight] = XE::Action(sf::Keyboard::Right, XE::Action::PressOnce);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_NavUp] = XE::Action(sf::Keyboard::Up, XE::Action::PressOnce);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_NavDown] = XE::Action(sf::Keyboard::Down, XE::Action::PressOnce);
	//	controller.actionmap[ControllerSettings::ActionType::ActionType_NavEnter] = XE::Action(sf::Keyboard::Return, XE::Action::PressOnce);
//
////		std::string schemafile;
//		std::string jsonfile;
//
//	//	flatbuffers::LoadFile("F:\\Projekte\\coop\\XGame\\data\\fb\\Controller\\Controllers.fbs", false, &schemafile);
//		flatbuffers::LoadFile("F:\\Projekte\\coop\\XGame\\data\\fb\\Controller\\Player_1.json", false, &jsonfile);
//
//
//		// parse schema first, so we can use it to parse the data after
//		flatbuffers::Parser parser;
//
//		//	const char *include_directories[] = { "samples", nullptr };
//		const char *include_directories[] = { nullptr };
//		parser.Parse(schema.c_str(), include_directories);
//		parser.Parse(jsonfile.c_str(), include_directories);
//
//		auto controllers = Controller::GetControllers(parser.builder_.GetBufferPointer());
//
//		auto controller1 = controllers->controllers()->Get(0);
//
//		//actions
//		for (auto it = controller1->actionMap()->begin(); it != controller1->actionMap()->end(); ++it)
//		{
//			int j = 0;
//			XE::Action::ActionType evtType = XE::Action::ActionType((*it)->eventType());
//
//			auto events = (*it)->events();
//			if (!events)
//				continue;
//
//
//			//events
//			for (auto itEvt = events->begin(); itEvt != events->end(); ++itEvt)
//			{
//				XE::Action action;
//
//				if ((*itEvt)->joy())
//					action = XE::Action(XE::JoystickButton(0, (*itEvt)->joyBtn()), evtType);
//				else if ((*itEvt)->kCode())
//					action = XE::Action(XE::Keyboard::Key((*itEvt)->kCode()), evtType);
//
//				else if ((*itEvt)->mouse())
//					action = XE::Action(XE::Mouse::Button((*itEvt)->mouse()), evtType);
//
//				else if ((*itEvt)->mWheel())
//					action = XE::Action(XE::Event::MouseWheelMoved);
//				else
//					continue;
//
//				if (j == 0)
//				{
//					Ctrl.actionmap[(*it)->actionType()] = action; // XE::Action(XE::JoystickButton(0, 2), evtType);
//					j++;
//				}
//				else if ((*itEvt)->actionOperator() == Controller::ActionOperator::ActionOperator_And)
//					Ctrl.actionmap[(*it)->actionType()] = Ctrl.actionmap[(*it)->actionType()] && action;
//				else //or and none .....  if ((*itEvt)->actionOperator() == Controller::ActionOperator::ActionOperator_Or)
//					Ctrl.actionmap[(*it)->actionType()] = Ctrl.actionmap[(*it)->actionType()] || action;
//			}
//		}
//
//
//
//
//
//	}

	//std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	//	std::stringstream ss(s);
	//	std::string item;
	//	while (std::getline(ss, item, delim)) {
	//		elems.push_back(item);
	//	}
	//	return elems;
	//}

	//std::vector<std::string> split(const std::string &s, char delim) {
	//	std::vector<std::string> elems;
	//	split(s, delim, elems);
	//	return elems;
	//}

	//void ControllerData::loadControllerFile()
	//{

	//	InputConfigFile cfg;

	//	//todo load from resource !!
	//	cfg.load("F:\\Projekte\\coop\\XEngine\\data\\Test\\XETController\\Controller.cfg", "=:\t", false);

	//	//---------------------------------------------------------------------------
	//	// Alle Aktionen auslesen
	//	// Aktion: z.B. Forward
	//	//---------------------------------------------------------------------------
	//	for (int actionInt = InputCmd::None; actionInt != InputCmd::Count; actionInt++)
	//	{
	//		InputCmd::MyAction action = static_cast<InputCmd::MyAction>(actionInt);

	//		std::string actionName = InputCmd::EnumStrings[action];

	//		std::stringstream controllerName;
	//		controllerName << mID;

	//		std::string actionCfg = cfg.getSetting(actionName, controllerName.str());

	//		std::cout << "Action:" << actionName;

	//		//---------------------------------------------------------------------
	//		// EventTyp
	//		// z.B. Key,Mouse etc.
	//		//---------------------------------------------------------------------

	//		std::vector<std::string> eventTypes = split(actionCfg, ',');
	//		std::queue<Action> eventsCombined; // Actions aus cfg file mit && verkn�pft
	//		for (std::vector<std::string>::iterator it = eventTypes.begin(); it != eventTypes.end(); ++it)
	//		{
	//			std::vector<std::string> actions = split(*it, '_');
	//			//std::cout << ",Events:" << actions.size();

	//			int i = 0;
	//			std::string sType;
	//			std::string sEvent;

	//			for (std::vector<std::string>::iterator it = actions.begin(); it != actions.end(); ++it)
	//			{
	//				if (i == 0) sType = *it;
	//				else if (i == 1) sEvent = *it;

	//				std::cout << (i == 0 ? "#_Type:" : "#Event:") << *it;

	//				if (i == 1) // nur die Events adden nicht die typen an sich
	//				{
	//					switch (action){
	//					case InputCmd::Forward:
	//					case InputCmd::Backward:
	//					case InputCmd::StrafeLeft:
	//					case InputCmd::StrafeRight:
	//					case InputCmd::ForwardLeft:
	//					case InputCmd::ForwardRight:
	//					case InputCmd::BackwardLeft:
	//					case InputCmd::BackwardRight:
	//					case InputCmd::TurnLeft:
	//					case InputCmd::TurnRight:
	//						if (sType.compare("Key") == 0)
	//						{
	//							eventsCombined.push(Action(toKeyboardKey(sEvent), Action::Hold));
	//							m_deviceType = DT_KeyMouse;
	//						}
	//						else if (sType.compare("Joy") == 0)
	//						{
	//							//	Joy(0).button(2)
	//							Event testEv;
	//							testEv.joystickMove.axis = toJoystickAxis(sEvent);
	//							eventsCombined.push(Action(JoystickButton(0, 2), Action::PressOnce));
	//							m_deviceType = DT_Joy;
	//						}
	//						break;
	//					default:
	//						if (sType.compare("Key") == 0)
	//							eventsCombined.push(Action(toKeyboardKey(sEvent), Action::PressOnce));
	//						else if (sType.compare("Joy") == 0)
	//							//todo joy Buttons!
	//							eventsCombined.push(Action(JoystickButton(0, 2), Action::PressOnce));
	//						else if (sType.compare("MOUSE") == 0)
	//							eventsCombined.push(Action(toMouseButton(sEvent), Action::PressOnce));

	//						break;
	//					}
	//				}
	//				i++;
	//			}


	//		}

	//		//	mActionmap[action] =  Action(Mouse::Left, Action::PressOnce);
	//		//	mActionmap[action] &&  Action(Mouse::Right, Action::PressOnce);
	//		int j = 0;
	//		while (!eventsCombined.empty())
	//		{
	//			if (j == 0)
	//				actionmap[action] = eventsCombined.front();
	//			else
	//				actionmap[action] = actionmap[action] && eventsCombined.front();

	//			eventsCombined.pop();
	//			j++;
	//		}


	//		//		mActionmap[action] = eventsCombined.back() && eventsCombined.back();


	//		//map[foo] = Action(toKeyboardKey(sEvent), Action::PressOnce);*/

	//		//map[foo] = Action(Mouse::Left, Action::PressOnce) || Action(Joy(0).button(2), Action::PressOnce);


	//		std::cout << std::endl;
	//	}
	//}


}