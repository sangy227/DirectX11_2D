#include "yathirdCameraMoveLine_Script.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaGameObject.h"

namespace ya {
	thirdCameraMoveLine_Script::thirdCameraMoveLine_Script()
		: Script()
		, mState(eMainCameraState::IDLE)
	{
	}
	thirdCameraMoveLine_Script::~thirdCameraMoveLine_Script()
	{
	}
	void thirdCameraMoveLine_Script::Initalize()
	{
	}
	void thirdCameraMoveLine_Script::Update()
	{
		Transform* cameratr = mGameObject->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();

		if (mState == eMainCameraState::MOVE) {
			camerapos += 5.0f * cameratr->Right() * Time::DeltaTime();
			cameratr->SetPosition(camerapos);
		}
	}
	void thirdCameraMoveLine_Script::FixedUpdate()
	{
	}
	void thirdCameraMoveLine_Script::Render()
	{
	}
	void thirdCameraMoveLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mState = eMainCameraState::MOVE;
	}
	void thirdCameraMoveLine_Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void thirdCameraMoveLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void thirdCameraMoveLine_Script::Start()
	{
	}
	void thirdCameraMoveLine_Script::Action()
	{
	}
	void thirdCameraMoveLine_Script::End()
	{
	}
}