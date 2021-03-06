#pragma once

#include <XEUI/Bin.hpp>

#include <SFML/System/String.hpp>
#include <memory>


namespace XE {

	class WRectangle;
	class WCaption;
	class Image;

	/** Pushbutton.
	*/
	class Button : public Bin {
	public:
		typedef std::shared_ptr<Button> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Button> PtrConst; //!< Shared pointer.

														/** Create button.
														* @param label Label.
														* @return Button.
														*/
		static Ptr Create(WLayer& parentLayer, const sf::String& label = L"", Uint16 fontId = 14);

		virtual ~Button();

		const std::string& GetName() const override;

		/** Set label.
		* @param label Label.
		*/
		void SetLabel(const sf::String& label);

		/** Get label.
		* @return Label.
		*/
		const sf::String& GetLabel() const;

		/** Set Image of the button.
		* @param image Image of the button.
		*/
		void SetImage(std::shared_ptr<Image> image);
	

		void SetImageName(const std::string& imageName);

		/** Get contained Image.
		* @return Contained Image.
		*/
		std::shared_ptr<const Image> GetImage() const;

		/** Clear Image of the button.
		*/
		void ClearImage();

	protected:
		/** Ctor.
		*/
		Button(WLayer& parentLayer, Uint16 fontId);// = default;

		void draw() override;
		//sf::Vector2f CalculateRequisition() override;

		//bool HandleAdd(Widget::Ptr child) override;

		//void HandleSizeChange() override;

		void HandleStateChange(State old_state) override;

		void HandleMouseButtonEvent(bool press, int x, int y) override;

		WRectangle* m_rectangle;
		WCaption* m_wcaption;

		std::string m_imageName;

	private:
		void HandleMouseEnter(int x, int y) override;
		void HandleMouseLeave(int x, int y) override;
	//	void AllocateChild();

		//sf::String m_label;

	};

}