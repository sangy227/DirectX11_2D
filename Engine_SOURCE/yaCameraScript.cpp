#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	CameraScript::CameraScript()
		: Script()
		, mCameraState(eCameraState::IDLE_LE)
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initalize()
	{
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		{
			//카메라 기본 무빙
			if (Input::GetKeyState(eKeyCode::L) == eKeyState::PRESSED)
			{
				pos += 10.0f * tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::J) == eKeyState::PRESSED)
			{
				pos += 10.0f * -tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
			{
				pos += 10.0f * tr->Foward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::U) == eKeyState::PRESSED)
			{
				pos += 10.0f * -tr->Foward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::I) == eKeyState::PRESSED)
			{
				pos += 10.0f * tr->Up() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::K) == eKeyState::PRESSED)
			{
				pos += 10.0f * -tr->Up() * Time::DeltaTime();
			}
		}

		if(mCameraState == eCameraState::SMALL_SHAKE)
			pos = CameraWeakShakeeffect(pos);

		if (mCameraState == eCameraState::BIG_SHAKE)
			pos = CameraStrongShakeeffect(pos);

		if (mCameraState == eCameraState::IDLE) {
			pos = Vector3(1.0f, 1.0f, -3.0f); // 여기서 계속 카메라 트랜스폼 갱신중
			//pos += (4.0f * -tr->Foward());
			mCameraState = eCameraState::IDLE_LE;
		}
			



		if (Input::GetKey(eKeyCode::Q))
		{
			//pos = CameraWeakShakeeffect(pos);
			mCameraState = eCameraState::SMALL_SHAKE;
		}
		if (Input::GetKeyUp(eKeyCode::Q))
		{
			//pos = Vector3::One;
			//pos += (4.0f * -tr->Foward());
			mCameraState = eCameraState::IDLE;
		}
		if (Input::GetKey(eKeyCode::W))
		{
			pos = CameraStrongShakeeffect(pos);
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			mCameraState = eCameraState::IDLE;
		}

		

		tr->SetPosition(pos);
	}
	void CameraScript::Render()
	{
	}


	Vector3 CameraScript::CameraWeakShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.002f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;
	}
	Vector3 CameraScript::CameraStrongShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.01f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;
	}
}