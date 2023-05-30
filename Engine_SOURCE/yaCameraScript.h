#pragma once
#include "yaScript.h"


namespace ya
{
	class CameraScript : public Script
	{
	public:
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

		eCameraState GetCamereState() { return mCameraState; }
		void SetCamereState(eCameraState mstate) { mCameraState = mstate; }

		void SetCameraState_Small_Shake() { mCameraState = eCameraState::SMALL_SHAKE; }
		void SetCameraState_Big_Shake() { mCameraState = eCameraState::BIG_SHAKE; }
		void SetCameraState_Idle() { mCameraState = eCameraState::IDLE; }

	private:

	public:
		eCameraState mCameraState;
	};
}
