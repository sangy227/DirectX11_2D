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
				pos += 30.0f * tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::J) == eKeyState::PRESSED)
			{
				pos += 30.0f * -tr->Right() * Time::DeltaTime();
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

		//카메라 흔들기 부분
		{
			if (mCameraState == eCameraState::SMALL_SHAKE)
				pos = CameraWeakShakeeffect(pos);

			if (mCameraState == eCameraState::BIG_SHAKE)
				pos = CameraStrongShakeeffect(pos);

			if (mCameraState == eCameraState::IDLE) {
				//pos = Vector3(1.0f, 1.0f, -3.0f); // 여기서 계속 카메라 트랜스폼 갱신중
				pos.y = 1.0f;
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
		}


		//카메라 오른쪽 으로 무빙
		{
			if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::DOWN)
			{
				if (mMaincameraState == eMainCameraState::IDLE)
					mMaincameraState = eMainCameraState::MOVE;
				else if (mMaincameraState == eMainCameraState::MOVE)
					mMaincameraState = eMainCameraState::IDLE;
			}

			if (mMaincameraState == eMainCameraState::MOVE)
			{
				pos += 10.0f * tr->Right() * Time::DeltaTime();
			}
		}


		tr->SetPosition(pos);
	}
	void MainCameraSc::Render()
	{
	}
	Vector3 MainCameraSc::CameraWeakShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.004f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;
	}
	Vector3 MainCameraSc::CameraStrongShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.01f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;
	}
}