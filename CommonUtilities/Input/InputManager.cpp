#include "pch.h"
#include "InputManager.h"
#include <winuser.h>

namespace CommonUtilities
{
	InputManager::InputManager():
		myUnsetMousePosition({ 0, 0 }),
		myCurrentMousePosition({ 0, 0 }),
		myLastMousePosition({ 0, 0 }),
		myUnsetZwheelScroll(0),
		myCurrentZWheelScroll(0),
		myLastZWheelScroll(0),
		myMouseIsCaptured(false)
	{}

	bool InputManager::IsMousePresent() const
	{
		return !GetSystemMetrics(SM_CMOUSEBUTTONS);
	}

	POINT InputManager::GetMouseMovement() const
	{
		return {
			myLastMousePosition.x - myCurrentMousePosition.x,
			myLastMousePosition.y - myCurrentMousePosition.y
		};
	}

	POINT InputManager::GetMousePosition() const
	{
		return myCurrentMousePosition;
	}

	void InputManager::SetMousePosition(POINT& aMousePosition)
	{
		ClientToScreen(GetActiveWindow(), &aMousePosition);
		SetCursorPos(aMousePosition.x, aMousePosition.y);
	}

	void InputManager::CaptureMouse(const HWND& aWindow)
	{
		RECT rect;
		GetClientRect(aWindow, &rect);

		POINT topleft {
			rect.top,
			rect.left,
		};
	
		POINT bottomRight {
			rect.right,
			rect.bottom,
		};

		MapWindowPoints(aWindow, nullptr, &topleft, 1);
		MapWindowPoints(aWindow, nullptr, &bottomRight, 1);

		rect.left = topleft.x;
		rect.top = topleft.y;
		rect.right = bottomRight.x;
		rect.bottom = bottomRight.y;

		ClipCursor(&rect);
		myMouseIsCaptured = true;
	}

	void InputManager::ReleaseMouse()
	{
		ClipCursor(nullptr);
		myMouseIsCaptured = false;
	}

	bool InputManager::UpdateEvents(UINT aMsg, WPARAM aWParam, LPARAM )
	{
		switch(aMsg)
		{
			// Keyboard
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			// Mouse
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				myUnsetKey.set(aWParam);
				return true;
			}

			case WM_MBUTTONDOWN:
			{
				myUnsetKey.set(VK_MBUTTON);
				return true;
			}
			
			case WM_XBUTTONDOWN: 
			{
				if(GET_KEYSTATE_WPARAM(aWParam) == MK_XBUTTON1)
				{
					myUnsetKey.set(VK_XBUTTON1);
					return true;
				}
				if(GET_KEYSTATE_WPARAM(aWParam) == MK_XBUTTON2)
				{
					myUnsetKey.set(VK_XBUTTON2);
					return true;
				}
			}

			// Keyboard
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				myUnsetKey.reset(aWParam);
				return true;
			}

			// Mouse
			case WM_LBUTTONUP:
			{
				myUnsetKey.reset(VK_LBUTTON);
				return true;
			}
			case WM_RBUTTONUP:
			{
				myUnsetKey.reset(VK_RBUTTON);
				return true;
			}
			case WM_MBUTTONUP:
			{
				myUnsetKey.reset(VK_MBUTTON);
				return true;
			}

			case WM_XBUTTONUP:
			{
				if(GET_KEYSTATE_WPARAM(aWParam) == MK_XBUTTON1)
				{
					myUnsetKey.reset(VK_XBUTTON1);
					return true;
				}
				if(GET_KEYSTATE_WPARAM(aWParam) == MK_XBUTTON2)
				{
					myUnsetKey.reset(VK_XBUTTON2);
					return true;
				}
			}

			case WM_MOUSEMOVE:
			{
				POINT point;
				GetCursorPos(&point);
				ScreenToClient(GetActiveWindow(), &point);
				myUnsetMousePosition = point;

				return true;
			}
	
			case WM_MOUSEWHEEL:
			{
				myUnsetZwheelScroll = GET_WHEEL_DELTA_WPARAM(aWParam) / WHEEL_DELTA;
				return true;
			}
		}

		return false;
	}

	void InputManager::Update()
	{
		myLastKey = myCurrentKey;
		myCurrentKey = myUnsetKey;
		
		myLastMousePosition = myCurrentMousePosition;
		myCurrentMousePosition = myUnsetMousePosition;

		myLastZWheelScroll = myCurrentZWheelScroll;
		myCurrentZWheelScroll = myUnsetZwheelScroll;
		myUnsetZwheelScroll = 0;
	}

}


