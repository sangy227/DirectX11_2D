#include "yasecondCameraStopLine_Script.h"

namespace ya {
	secondCameraStopLine_Script::secondCameraStopLine_Script()
		: Script()
	{
	}
	secondCameraStopLine_Script::~secondCameraStopLine_Script()
	{
	}
	void secondCameraStopLine_Script::Initalize()
	{
	}
	void secondCameraStopLine_Script::Update()
	{
	}
	void secondCameraStopLine_Script::FixedUpdate()
	{
	}
	void secondCameraStopLine_Script::Render()
	{
	}
	void secondCameraStopLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mGameObject->StopMove();
	}
	void secondCameraStopLine_Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void secondCameraStopLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void secondCameraStopLine_Script::Start()
	{
	}
	void secondCameraStopLine_Script::Action()
	{
	}
	void secondCameraStopLine_Script::End()
	{
	}
}