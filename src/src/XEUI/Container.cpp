#include <XEUI/Container.hpp>

//#include <iostream>

namespace XE {

	void Container::Add(Widget::Ptr widget) {
		if (IsChild(widget))
			return;

		m_children.push_back(widget);

		widget->SetParent(shared_from_this());
	}

	void Container::Remove(Widget::Ptr widget) {
		WidgetsList::iterator iter(std::find(m_children.begin(), m_children.end(), widget));

		if (iter != m_children.end()) {
			m_children.erase(iter);
			widget->SetParent(Widget::Ptr());
		}
	}

	void Container::HandleUpdate(float seconds) {
		Widget::HandleUpdate(seconds);

		for (const auto& child : m_children) {
			child->Update(seconds);
		}
	}

	void Container::HandleNavEvent(NavAction navAction) {
		Widget::HandleNavEvent(navAction);

		for (const auto& child : m_children) {
			child->HandleNavEvent(navAction);
		}
	}
	
	void Container::AddEntry(Widget::Ptr widget) {
		if (IsChild(widget))
			return;

		m_entries.push_back(widget);

		widget->SetParent(shared_from_this());
	}

	void Container::RemoveEntry(Widget::Ptr widget) {
		WidgetsList::iterator iter(std::find(m_entries.begin(), m_entries.end(), widget));

		if (iter != m_entries.end()) {
			m_entries.erase(iter);
			widget->SetParent(Widget::Ptr());
		}
	}

	void Container::RemoveAll() {
		while (!m_children.empty()) {
			auto widget = m_children.back();

			m_children.pop_back();
			widget->SetParent(Widget::Ptr());
		}
	}

	bool Container::IsChild(Widget::Ptr widget) const {
		return std::find(m_children.begin(), m_children.end(), widget) != m_children.end();
	}

	const Container::WidgetsList& Container::GetChildren() const {
		return m_children;
	}

	void Container::Refresh() {
		for (const auto& child : m_children) {
			child->Refresh();
		}

		Widget::Refresh();
	}

	void Container::onPointMoved(const float& x, const float& y) {
		
	//	std::cout << "-container->onPointMoved " << x << ",childs:" << m_children.size() << std::endl;
	//	if(m_children.size() > 0)
	//		std::cout << "-container->onPointMoved " << x << ",child[0]:" << m_children[0]->GetName() << std::endl;

		if (!HandleEvent())
			return;

		
		// Pass event to children.
		//dont use an iterator here! it's possible widget deletion happens while iterating here
		for (int index = 0; index < static_cast<int>(m_children.size()); ++index) {
			Widget::Ptr child(m_children[static_cast<std::size_t>(index)]);
			//for (const auto& child : m_children) {
			
	//		std::cout << "---child->onPointMoved " << x << std::endl;
			
			child->onPointMoved(x, y);
		}

		// Process event for own widget.
		Widget::onPointMoved(x, y);
	}

	void Container::onPointDown(const float& x, const float& y) {
		if (!HandleEvent())
			return;
		// Pass event to children.
		//dont use an iterator here! it's possible widget deletion happens while iterating here
		for (int index = 0; index < static_cast<int>(m_children.size()); ++index) {
			Widget::Ptr child(m_children[static_cast<std::size_t>(index)]);
			//for (const auto& child : m_children) {
			child->onPointDown(x, y);
		}

		// Process event for own widget.
		Widget::onPointDown(x, y);
	}

	void Container::onPointUp(const float& x, const float& y) {
		if (!HandleEvent())
			return;

		// Pass event to children.
		//dont use an iterator here! it's possible widget deletion happens while iterating here
		for (int index = 0; index < static_cast<int>(m_children.size()); ++index) {
			Widget::Ptr child(m_children[static_cast<std::size_t>(index)]);
			//for (const auto& child : m_children) {
			child->onPointUp(x, y);
		}

		// Process event for own widget.
		Widget::onPointUp(x, y);
	}

	void Container::onKeyEvent(const  SDL_KeyboardEvent& key) {
		if (!HandleEvent())
			return;

		// Pass event to children.
		//dont use an iterator here! it's possible widget deletion happens while iterating here
		for (int index = 0; index < static_cast<int>(m_children.size()); ++index) {
			Widget::Ptr child(m_children[static_cast<std::size_t>(index)]);
			//for (const auto& child : m_children) {
			child->onKeyEvent(key);
		}

		// Process event for own widget.
		Widget::HandleKeyEvent(key, key.type == SDL_KEYDOWN ? true : false);
	}

	bool Container::HandleEvent() {
	
		
		// Ignore event when widget is not visible.
		//if (!IsGloballyVisible()) {
		
		//	std::cout << "-Container->HandleEvent " << IsGloballyVisible() << std::endl;
			
			return true;
		//}
	//	std::cout << "-Container->HandleEvent, OK "  << std::endl;

		// Create a copy of the event and transform mouse coordinates to local
		// coordinates if event is a mouse event.
		/*sf::Event local_event(event);

		if (local_event.type == sf::Event::MouseMoved) {
			local_event.mouseMove.x -= static_cast<int>(getPosition().x);
			local_event.mouseMove.y -= static_cast<int>(getPosition().y);
		}

		if (
			local_event.type == sf::Event::MouseButtonPressed ||
			local_event.type == sf::Event::MouseButtonReleased
			) {
			local_event.mouseButton.x -= static_cast<int>(getPosition().x);
			local_event.mouseButton.y -= static_cast<int>(getPosition().y);
		}*/
	}

	void Container::HandleChildInvalidate(Widget::PtrConst child) const {
		auto parent = GetParent();

		if (parent) {
			parent->HandleChildInvalidate(child);
		}
	}

	void Container::HandleGlobalVisibilityChange() {
		Widget::HandleGlobalVisibilityChange();

		for (const auto& child : m_children) {
			child->HandleGlobalVisibilityChange();
		}
	}
}