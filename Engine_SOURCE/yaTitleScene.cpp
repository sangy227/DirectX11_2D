#include "yaTitleScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaCollider2D.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"

namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		//Particle
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			obj->AddComponent<ParticleSystem>();
		}

		////paint shader
		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		////L"SmileTexture"
		//std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		//paintShader->SetTarget(paintTex);
		//paintShader->OnExcute();
		

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		
		//renderer::cameras[0] = cameraComp;

		//TitleSceen
		{
			GameObject* titleBGObj = object::Instantiate<GameObject>(eLayerType::BackGround);
			titleBGObj->SetName(L"TitleBG");
			Transform* titleBGTr = titleBGObj->GetComponent<Transform>();
			titleBGTr->SetPosition(Vector3(0.99f, 1.0f, 1.7f));
			titleBGTr->SetScale(Vector3(1.5f, 0.88f, 1.0f));

			Light* bglightComp = titleBGObj->AddComponent<Light>();
			bglightComp->SetType(eLightType::Directional);
			bglightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			SpriteRenderer* titlesr = titleBGObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> titleBGmaterial = Resources::Find<Material>(L"TitleBGMaterial");
			titlesr->SetMaterial(titleBGmaterial);
			titlesr->SetMesh(mesh);
		}

		{
			GameObject* titleLogoObj = object::Instantiate<GameObject>(eLayerType::BackGround);
			titleLogoObj->SetName(L"TitleLogo");
			Transform* titleLogoTr = titleLogoObj->GetComponent<Transform>();
			titleLogoTr->SetPosition(Vector3(1.02f, 1.28f, 1.7f));
			titleLogoTr->SetScale(Vector3(0.68f, 0.12f, 1.0f));

			Light* logolightComp = titleLogoObj->AddComponent<Light>();
			logolightComp->SetType(eLightType::Directional);
			logolightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			SpriteRenderer* logosr = titleLogoObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> logomesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> titleLogomaterial = Resources::Find<Material>(L"TitleLogoMaterial");
			logosr->SetMaterial(titleLogomaterial);
			logosr->SetMesh(logomesh);
		}

		






		

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Main);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}
