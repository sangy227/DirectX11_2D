#include "yaMainScene.h"
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
#include "yaSkillEffect.h"
#include "yaSkillEffectScript.h"
#include "yaTime.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"
#include "yaBossWandaScript.h"
#include "yaRigidbody.h"
#include "yaMainCameraSc.h"

namespace ya {
	MainScene::MainScene()
		: Scene(eSceneType::Main)
	{
		//키보드 목록
		//ENTER 카메라 무브및 멈춤
		//UIOJKL 카메라 이동
 	}
	MainScene::~MainScene()
	{
	}
	void MainScene::Initalize()
	{
		Scene::Initalize();
	}
	void MainScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void MainScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void MainScene::Render()
	{
		Scene::Render();
	}
	void MainScene::OnEnter()
	{

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		MainCameraSc* bcs = cameraObj->AddComponent<MainCameraSc>();
		mainCamera = cameraComp;

		Transform* cameratr = cameraObj->GetComponent<Transform>();

		cameratr->SetPosition(Vector3(1.0f, 1.0f, -3.0f));

		//MainSceenBG ->배경화면 부분
		//2개의 레이어로 구상
		{
			{
				//mainBgLeyer01
				GameObject* mainBGObj_01 = object::Instantiate<GameObject>(eLayerType::BackGround);
				mainBGObj_01->SetName(L"MainBG01");
				Transform* mainBGTr_01 = mainBGObj_01->GetComponent<Transform>();
				mainBGTr_01->SetPosition(Vector3(34.0f, 1.0f, 6.0f));
				mainBGTr_01->SetScale(Vector3(85.0f, 10.5f, 1.0f));

				Light* mainBGComp_01 = mainBGObj_01->AddComponent<Light>();
				mainBGComp_01->SetType(eLightType::Directional);
				mainBGComp_01->SetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 1.0f));
				//mainBGComp_01->SetAmbient(Vector4(2.0f, 2.0f, 2.0f, 1.0f));

				SpriteRenderer* mainsr_01 = mainBGObj_01->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> mainmesh_01 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> mainBGmaterial_01 = Resources::Find<Material>(L"mainBGMaterial01");
				mainsr_01->SetMaterial(mainBGmaterial_01);
				mainsr_01->SetMesh(mainmesh_01);
			}
			{
				//mainBgLeyer02
				GameObject* mainBGObj_02 = object::Instantiate<GameObject>(eLayerType::BackGround);
				mainBGObj_02->SetName(L"PlayBG02");
				Transform* mainBGTr_02 = mainBGObj_02->GetComponent<Transform>();
				mainBGTr_02->SetPosition(Vector3(30.0f, -2.0f, 4.0f));
				mainBGTr_02->SetScale(Vector3(110.0f, 2.55f, 1.0f));

				Light* mainBGComp_02 = mainBGObj_02->AddComponent<Light>();
				mainBGComp_02->SetType(eLightType::Directional);
				mainBGComp_02->SetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 0.0f));

				SpriteRenderer* mainsr_02 = mainBGObj_02->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> mainmesh_02 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> maintBGmaterial_02 = Resources::Find<Material>(L"mainBGMaterial02");
				mainsr_02->SetMaterial(maintBGmaterial_02);
				mainsr_02->SetMesh(mainmesh_02);
			}
		}




	}
	void MainScene::OnExit()
	{
	}
}