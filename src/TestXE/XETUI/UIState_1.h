#pragma once

#include <XEngine.hpp>

#include <XEUI/UIState.hpp>

namespace XET {
	struct TestControllerComponent;
}

class UIState_1 : public XE::UIState
{

public:
	UIState_1(const XE::Uint16& id, entityx::Entity entity, bool replace);
	~UIState_1();

	void pause();
	void resume();

	void draw();

	bool running() { return m_running; }
	void quit() { m_running = false; }

	void create(const char* fbdata);
	void reload(const char* fbdata);

	void update(float delta);

	void ButtonClick();
	void MouseEnter();
	void Btn_QuitClick();

protected:

	XE::ScreenComponent*		m_screen;
	XET::TestControllerComponent*	m_controller;

	bool m_running;
	bool m_resume;

private:
	//initialization order!
	XE::Button::Ptr m_btnTest;
	XE::CheckButton::Ptr m_checkBoxTest;
	XE::Image::Ptr m_imageTest;
	XE::Box::Ptr  m_Box;
	XE::Alignment::Ptr  m_alignment;
	XE::ProgressBar::Ptr m_progressbar;
	XE::Entry::Ptr m_entry;
	XE::UIWindow::Ptr m_window;
	XE::Button::Ptr m_btnQuit;
};