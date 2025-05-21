#pragma once

#include <Windows.h>
#include <bitset>
#include <assert.h>

namespace CommonUtilities
{

	class InputManager
	{

		public:
			InputManager();

			inline bool IsKeyDown(const int aKeyCode) const;
			inline bool IsKeyUp(const int aKeyCode) const;
			inline bool IsKeyPressed(const int aKeyCode) const;

			bool IsMousePresent() const;
			POINT GetMouseMovement() const;
			POINT GetMousePosition() const;

			void SetMousePosition(POINT& aMousePosition);
	
			inline bool IsMouseButtonDown(const int aKeyCode) const;
			inline bool IsMouseButtonUp(const int aKeyCode) const;
			inline bool IsMouseButtonPressed(const int aKeyCode) const;

			inline int GetScrollWheel() const;

			void CaptureMouse(const HWND& aWindow);
			void ReleaseMouse();
			inline const bool IsMouseCaptured() const;

			bool UpdateEvents(UINT aMsg, WPARAM aWParam, LPARAM aLParam); 
			void Update();

		private:
			std::bitset<256> myUnsetKey;
			std::bitset<256> myCurrentKey;
			std::bitset<256> myLastKey;
			
			POINT myUnsetMousePosition;
			POINT myCurrentMousePosition;
			POINT myLastMousePosition;
			
			int myUnsetZwheelScroll;
			int myCurrentZWheelScroll;
			int myLastZWheelScroll;

			bool myMouseIsCaptured;
	};

	inline bool InputManager::IsKeyDown(const int aKeyCode) const
	{
		assert(aKeyCode > 0 && L"Index need to be above 0");
		return myLastKey.test(aKeyCode) == false && myCurrentKey.test(aKeyCode);
	}

	inline bool InputManager::IsKeyUp(const int aKeyCode) const
	{
		assert(aKeyCode > 0 && L"Index need to be above 0");
		return myCurrentKey.test(aKeyCode) == false && myLastKey.test(aKeyCode);
	}

	inline bool InputManager::IsKeyPressed(const int aKeyCode) const
	{
		assert(aKeyCode > 0 && L"Index need to be above 0");
		return myCurrentKey.test(aKeyCode) && myLastKey.test(aKeyCode);
	}

	inline int InputManager::GetScrollWheel() const
	{
		return myCurrentZWheelScroll;
	}

	inline bool InputManager::IsMouseButtonDown(const int aKeyCode) const
	{
		assert((aKeyCode >= VK_LBUTTON && aKeyCode <= VK_XBUTTON2) && L"Key code is not a mouse key");
		assert(aKeyCode != VK_CANCEL && L"Key code is not a mouse key");
		return myLastKey.test(aKeyCode) == false && myCurrentKey.test(aKeyCode);
	}

	inline bool InputManager::IsMouseButtonUp(const int aKeyCode) const
	{
		assert((aKeyCode >= VK_LBUTTON && aKeyCode <= VK_XBUTTON2) && L"Key code is not a mouse key");
		assert(aKeyCode != VK_CANCEL && L"Key code is not a mouse key");
		return myCurrentKey.test(aKeyCode) == false && myLastKey.test(aKeyCode);;
	}

	inline bool InputManager::IsMouseButtonPressed(const int aKeyCode) const
	{
		assert((aKeyCode >= VK_LBUTTON && aKeyCode <= VK_XBUTTON2) && L"Key code is not a mouse key");
		assert(aKeyCode != VK_CANCEL && L"Key code is not a mouse key");
		return myCurrentKey.test(aKeyCode) && myLastKey.test(aKeyCode);
	}

	inline const bool InputManager::IsMouseCaptured() const
	{
		return myMouseIsCaptured;
	}
	
}