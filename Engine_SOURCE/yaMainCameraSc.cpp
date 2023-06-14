#include "yaMainCameraSc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
namespace ya {
	MainCameraSc::MainCameraSc()
		: Script()
		, mCameraState(eCameraState::IDLE_LE)
		, mMaincameraState(eMainCameraState::IDLE)
	{
	}
	MainCameraSc::~MainCameraSc()
	{
	}
	void MainCameraSc::Initalize()
	{
	}
	void MainCameraSc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		{
			//카메라 기본 무빙
			if (Input::GetKeyState(eKeyCode::L) == eKeyState::PRESSED)
			{
				pos += 50.0f * tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::J) == eKeyState::PRESSED)
			{
				pos += 50.0f * -tr->Right() * Time::DeltaTime();
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

		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::DOWN)
		{
			if (mMaincameraState == eMainCameraState::IDLE)
				mMaincameraState = eMainCameraState::MOVE;
			else if(mMaincameraState == eMainCameraState::MOVE)
				mMaincameraState = eMainCameraState::IDLE;
		}

		if (mMaincameraState == eMainCameraState::MOVE)
		{
			pos += 10.0f * tr->Right() * Time::DeltaTime();
		}
		


		tr->SetPosition(pos);
	}
	void MainCameraSc::Render()
	{
	}
	Vector3 MainCameraSc::CameraWeakShakeeffect(Vector3 pos)
	{
		return Vector3();
	}
	Vector3 MainCameraSc::CameraStrongShakeeffect(Vector3 pos)
	{
		return Vector3();
	}
}