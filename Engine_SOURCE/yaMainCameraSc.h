
#pragma once
#include "yaScript.h"


namespace ya
{
	class MainCameraSc : public Script
	{
	public:
		
		MainCameraSc();
		~MainCameraSc();

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

		void SetMainCameraState_Idle() { mMaincameraState = eMainCameraState::IDLE; }
		void SetMainCameraState_Move() { mMaincameraState = eMainCameraState::MOVE; }
		

	private:

	public:
		eCameraState mCameraState;
		eMainCameraState mMaincameraState;
	};
}