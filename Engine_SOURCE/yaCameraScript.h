#pragma once
#include "yaScript.h"


namespace ya
{
	class CameraScript : public Script
	{
	public:
		enum class camerastate {
			IDLE,
			SMALL_SHAKE,
			BIG_SHAKE,
			END
		};

		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		Vector3 CameraWeakShakeeffect(Vector3 pos);
		Vector3 CameraStrongShakeeffect(Vector3 pos);
		float RandomRange(float min, float max)
		{
			return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
		}

		camerastate GetCamereState() { return mState; }
		void SetCamereState(camerastate mstate) { mState = mstate; }

	private:

	public:
		camerastate mState;
	};
}
