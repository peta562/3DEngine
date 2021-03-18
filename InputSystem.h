#pragma once
#include "InputListener.h"
#include <map>
#include "MousePoint.h"


class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
public:
	static InputSystem* get();
private:
	std::map<InputListener*, InputListener*> listener_map;
	unsigned char keys_state[256] = {};
	unsigned char old_keys_state[256] = {};
	Point old_mouse_pos;
	bool first_time = true;
};

