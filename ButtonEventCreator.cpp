#include "ButtonEventCreator.hpp"

ButtonEventCreator::ButtonEventCreator()
{
	for (size_t buttonNumber = (int)ButtonsEnum::First; buttonNumber < (int)ButtonsEnum::Size; buttonNumber++)
	{
		oldButtons[buttonNumber] = false;
		newButtons[buttonNumber] = false;
	}
}

std::vector<ButtonsEnum> ButtonEventCreator::GenerateEvents(blit::ButtonState buttons)
{
	setOldButtons();

	setNewButtons(buttons);

	return createPressedEvents();
}

void ButtonEventCreator::setOldButtons()
{
	for (size_t buttonNumber = (int)ButtonsEnum::First; buttonNumber < (int)ButtonsEnum::Size; buttonNumber++)
		oldButtons[buttonNumber] = newButtons[buttonNumber];
}

void ButtonEventCreator::setNewButtons(blit::ButtonState buttons)
{
	newButtons[(int)ButtonsEnum::Up] = buttons & blit::Button::DPAD_UP;
	newButtons[(int)ButtonsEnum::Down] = buttons & blit::Button::DPAD_DOWN;
	newButtons[(int)ButtonsEnum::Left] = buttons & blit::Button::DPAD_LEFT;
	newButtons[(int)ButtonsEnum::Right] = buttons & blit::Button::DPAD_RIGHT;
}

std::vector<ButtonsEnum> ButtonEventCreator::createPressedEvents()
{
	std::vector<ButtonsEnum> events;

	for (size_t buttonNumber = (int)ButtonsEnum::First; buttonNumber < (int)ButtonsEnum::Size; buttonNumber++)
		if (newButtons[buttonNumber] && !oldButtons[buttonNumber])
			events.push_back((ButtonsEnum)buttonNumber);

	return events;
}