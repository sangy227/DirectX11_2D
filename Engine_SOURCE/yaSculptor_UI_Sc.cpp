#include "yaSculptor_UI_Sc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimation.h"
#include "yaTexture.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSculptorScript.h"

namespace ya {
	Sculptor_UI_Sc::Sculptor_UI_Sc()
		: Script()
		, index(0)
		, mTimer(0)
	{
	}
	Sculptor_UI_Sc::~Sculptor_UI_Sc()
	{
	}
	void Sculptor_UI_Sc::Initalize()
	{
	}
	void Sculptor_UI_Sc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if (index >= 0) {
			//GrandPaScript* sc = mGameObject->GetComponent<GrandPaScript>(); 
			//index = Pa_Sc->GetGrandPa_Hp();
			tr->SetScale(Vector3(index, 0.08f, 0));
		}

		if (index <= 0) {
			//GrandPaScript* sc = mGameObject->GetComponent<GrandPaScript>();
			//sc->DieDieDie();
			//GetOwner()->Death();
		}
	}
	void Sculptor_UI_Sc::Render()
	{
	}
	void Sculptor_UI_Sc::OnCollisionEnter(Collider2D* collider)
	{
	}
	void Sculptor_UI_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void Sculptor_UI_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void Sculptor_UI_Sc::Start()
	{
	}
	void Sculptor_UI_Sc::Action()
	{
	}
	void Sculptor_UI_Sc::End()
	{
	}
}