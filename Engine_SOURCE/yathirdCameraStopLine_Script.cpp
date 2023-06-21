#include "yathirdCameraStopLine_Script.h"

namespace ya
{
	thirdCameraStopLine_Script::thirdCameraStopLine_Script()
		: Script()
	{
	}
	thirdCameraStopLine_Script::~thirdCameraStopLine_Script()
	{
	}
	void thirdCameraStopLine_Script::Initalize()
	{
	}
	void thirdCameraStopLine_Script::Update()
	{
	}
	void thirdCameraStopLine_Script::FixedUpdate()
	{
	}
	void thirdCameraStopLine_Script::Render()
	{
	}
	void thirdCameraStopLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mSculptorScript->Attack_Start();
		mGameObject->StopMove();
	}
	void thirdCameraStopLine_Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void thirdCameraStopLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void thirdCameraStopLine_Script::Start()
	{
	}
	void thirdCameraStopLine_Script::Action()
	{
	}
	void thirdCameraStopLine_Script::End()
	{
	}
}
