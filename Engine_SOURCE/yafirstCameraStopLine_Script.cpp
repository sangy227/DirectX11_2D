#include "yafirstCameraStopLine_Script.h"

namespace ya {
	firstCameraStopLine_Script::firstCameraStopLine_Script()
		: Script()
	{
	}
	firstCameraStopLine_Script::~firstCameraStopLine_Script()
	{
	}
	void firstCameraStopLine_Script::Initalize()
	{
	}
	void firstCameraStopLine_Script::Update()
	{
	}
	void firstCameraStopLine_Script::FixedUpdate()
	{
	}
	void firstCameraStopLine_Script::Render()
	{
	}
	void firstCameraStopLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mGameObject->StopMove();
	}
	void firstCameraStopLine_Script::OnCollisionStay(Collider2D* collider)
	{
		//mGameObject->Move();
	}
	void firstCameraStopLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}
	void firstCameraStopLine_Script::Start()
	{
	}
	void firstCameraStopLine_Script::Action()
	{
	}
	void firstCameraStopLine_Script::End()
	{
	}
}