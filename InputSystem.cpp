#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (first_time)
	{
		old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		first_time = false;
	}
	if (current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y) 
	{
		//mouse move event
		std::map<InputListener*, InputListener*>::iterator it = listener_map.begin();

		while (it != listener_map.end())
		{
			it->second->onMouseMove(Point(current_mouse_pos.x - old_mouse_pos.x, current_mouse_pos.y - old_mouse_pos.y));
			++it;
		}
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);


	if (::GetKeyboardState(keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (keys_state[i] & 0x80) // key is down
			{
				std::map<InputListener*, InputListener*>::iterator it = listener_map.begin();

				while (it != listener_map.end())
				{
					if (i == VK_LBUTTON)
					{
						if (keys_state[i] != old_keys_state[i])
						{
							it->second->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
					}

					else if (i == VK_RBUTTON)
					{
						if (keys_state[i] != old_keys_state[i])
						{
							it->second->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
					}
					else
					{
						it->second->onKeyDown(i);
					}
					
					++it;
				}
			}
			else // key is up
			{
				if (keys_state[i] != old_keys_state[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = listener_map.begin();

					while (it != listener_map.end())
					{
						if (i == VK_LBUTTON)
						{
							it->second->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else if (i == VK_RBUTTON)
						{
							it->second->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else
						{
							it->second->onKeyUp(i);
						}
						
						++it;
					}
				}
			}
		}
	}

	//store current keys state to old keys state
	memcpy(old_keys_state, keys_state, sizeof(unsigned char) * 256);
}

void InputSystem::addListener(InputListener* listener)
{
	listener_map.insert(std::make_pair<InputListener*, InputListener*>
		(std::forward< InputListener*>(listener), std::forward< InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = listener_map.find(listener);

	if (it != listener_map.end())
	{
		listener_map.erase(it);
	}
}

InputSystem* InputSystem::get()
{
	static InputSystem inputSystem;
	return &inputSystem;
}
