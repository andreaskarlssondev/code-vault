#pragma once

namespace CommonUtilities
{
	class Timer
	{
		public:
			Timer();
			Timer(const Timer& aTimer) = delete;
			Timer& operator=(const Timer& aTimer) = delete;

			void Update();

			inline float GetDeltaTime() const { return myDeltaTime; }
			double GetTotalTime() const;

		private:
			double myStartTime;
			double myPrevTime;
			float myDeltaTime;

	};
}
