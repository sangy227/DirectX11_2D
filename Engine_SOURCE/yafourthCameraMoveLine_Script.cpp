#include "yafourthCameraMoveLine_Script.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaGameObject.h"

namespace ya {
	fourthCameraMoveLine_Script::fourthCameraMoveLine_Script()
		: Script()
		, mState(eMainCameraState::IDLE)
	{
	}
	fourthCameraMoveLine_Script::~fourthCameraMoveLine_Script()
	{
	}
	void fourthCameraMoveLine_Script::Initalize()
	{
	}
	void fourthCameraMoveLine_Script::Update()
	{
		Transform* cameratr = mGameObject->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();

		if (mState == eMainCameraState::MOVE) {
			camerapos += 5.0f * cameratr->Right() * Time::DeltaTime();
			cameratr->SetPosition(camerapos);
		}
	}
	void fourthCameraMoveLine_Script::FixedUpdate()
	{
	}
	void fourthCameraMoveLine_Script::Render()
	{
	}
	void fourthCameraMoveLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mState = eMainCameraState::MOVE;

	}
	void fourthCameraMoveLine_Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void fourthCameraMoveLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void fourthCameraMoveLine_Script::Start()
	{
	}
	void fourthCameraMoveLine_Script::Action()
	{
	}
	void fourthCameraMoveLine_Script::End()
	{
	}
}