#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	CameraScript::CameraScript()
		: Script()
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

		tr->SetPosition(pos);
	}
	void CameraScript::Render()
	{
	}
}