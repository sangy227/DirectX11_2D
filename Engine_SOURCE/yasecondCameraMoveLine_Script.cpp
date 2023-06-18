#include "yasecondCameraMoveLine_Script.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaGameObject.h"

namespace ya {
	secondCameraMoveLine_Script::secondCameraMoveLine_Script()
		: Script()
		, mState(eMainCameraState::IDLE)
	{
	}
	secondCameraMoveLine_Script::~secondCameraMoveLine_Script()
	{
	}
	void secondCameraMoveLine_Script::Initalize()
	{
	}
	void secondCameraMoveLine_Script::Update()
	{
		Transform* cameratr = mGameObject->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();

		if (mState == eMainCameraState::MOVE) {
			camerapos += 5.0f * cameratr->Right() * Time::DeltaTime();
			cameratr->SetPosition(camerapos);
		}
	}
	void secondCameraMoveLine_Script::FixedUpdate()
	{
	}
	void secondCameraMoveLine_Script::Render()
	{
	}
	void secondCameraMoveLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mState = eMainCameraState::MOVE;

	}
	void secondCameraMoveLine_Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void secondCameraMoveLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void secondCameraMoveLine_Script::Start()
	{
	}
	void secondCameraMoveLine_Script::Action()
	{
	}
	void secondCameraMoveLine_Script::End()
	{
	}
}