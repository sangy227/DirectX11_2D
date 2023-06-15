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
#include "yaPlayerScMainScene.h"
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


		//Game_Main_Player
		{
			gameplayer = object::Instantiate<Player>(eLayerType::Player);
			gameplayer->SetName(L"GamePlayer");
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			gameplayer_tr->SetPosition(Vector3(-5.0f, -1.55f, 5.0f));
			gameplayer_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

			Light* gameplayer_light = gameplayer->AddComponent<Light>();
			gameplayer_light->SetType(eLightType::Directional);
			gameplayer_light->SetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 0.0f));

			Rigidbody* gameplayer_rigid = gameplayer->AddComponent<Rigidbody>();

			//실행되는거 확인완료
			Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			gameplayer_col->SetType(eColliderType::Rect);
			gameplayer_col->SetSize(Vector2(0.12f, 0.11f));

#pragma region Animator
			Animator* gameplayer_animator = gameplayer->AddComponent<Animator>();
			std::shared_ptr<Texture> player_idle = Resources::Load<Texture>(L"player", L"Player\\T_BossIrma_Idle_Final.png");
			std::shared_ptr<Texture> player_attack = Resources::Load<Texture>(L"player_attack", L"Player\\T_BossIrma_Attacks.png");
			std::shared_ptr<Texture> player_attack2 = Resources::Load<Texture>(L"player_attack2", L"Player\\T_BossIrma_Attacks2.png"); //흰색 플레이어 공격 안씀
			std::shared_ptr<Texture> player_run01 = Resources::Load<Texture>(L"player_run01", L"Player\\T_BossIrma_idle_to_run.png"); // 아이들 투 런 인데 안씀
			std::shared_ptr<Texture> player_run02 = Resources::Load<Texture>(L"player_run02", L"Player\\T_BossIrma_Run_Final.png");
			std::shared_ptr<Texture> player_dash = Resources::Load<Texture>(L"player_Dash", L"Player\\T_BossIrma_Dash.png");
			std::shared_ptr<Texture> player_jump = Resources::Load<Texture>(L"player_jump", L"Player\\T_Player_Jump.png");

			std::shared_ptr<Texture> player_skill_hammer = Resources::Load<Texture>(L"player_skill_1", L"Player\\T_BossIrma_Hammer_Final.png");
			std::shared_ptr<Texture> player_skill_Painwheel = Resources::Load<Texture>(L"player_skill_2", L"Player\\T_BossIrma_Painwheel_Final.png");
			std::shared_ptr<Texture> player_skill_Spear = Resources::Load<Texture>(L"player_skill_3", L"Player\\T_Player_Spear_Body.png");
			std::shared_ptr<Texture> player_skill_Whirlwind = Resources::Load<Texture>(L"player_skill_4", L"Player\\T_Player_Whirlwind_Body.png");


			gameplayer_animator->Create(L"Idle", player_idle, Vector2(0.0f, 0.0f), Vector2(59.0f, 52.0f), Vector2::Zero, 7, 4, 26, 0.08f);
			gameplayer_animator->Create(L"attack", player_attack, Vector2(0.0f, 0.0f), Vector2(166.0f, 54.0f), Vector2(0.03f, 0.0f), 4, 6, 24, 0.04f);
			gameplayer_animator->Create(L"attack2", player_attack2, Vector2(0.0f, 0.0f), Vector2(143.0f, 52.0f), Vector2(0.03f, 0.0f), 5, 5, 25, 0.04f);
			gameplayer_animator->Create(L"run01", player_run01, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(0.03f, 0.0f), 4, 1, 4, 0.05f);
			gameplayer_animator->Create(L"run", player_run02, Vector2(0.0f, 0.0f), Vector2(62.0f, 53.0f), Vector2(0.03f, -0.0f), 5, 3, 14, 0.05f);
			gameplayer_animator->Create(L"dash", player_dash, Vector2(0.0f, 0.0f), Vector2(181.0f, 46.0f), Vector2(-0.18f, -0.0f), 2, 8, 12, 0.05f);
			gameplayer_animator->Create(L"jump", player_jump, Vector2(0.0f, 0.0f), Vector2(60.0f, 57.0f), Vector2(0.00f, 0.0f), 4, 4, 14, 0.05f);

			gameplayer_animator->Create(L"skill_hammer", player_skill_hammer, Vector2(0.0f, 0.0f), Vector2(275.0f, 119.0f), Vector2(0.03f, -0.015f), 5, 12, 57, 0.04f);
			gameplayer_animator->Create(L"skill_Painwheel", player_skill_Painwheel, Vector2(0.0f, 0.0f), Vector2(190.0f, 85.0f), Vector2(0.03f, -0.015f), 5, 11, 54, 0.04f);
			gameplayer_animator->Create(L"skill_Spear", player_skill_Spear, Vector2(0.0f, 0.0f), Vector2(272.0f, 71.0f), Vector2(0.03f, 0.0f), 4, 9, 34, 0.04f);
			gameplayer_animator->Create(L"skill_Whirlwind", player_skill_Whirlwind, Vector2(0.0f, 0.0f), Vector2(128.0f, 60.0f), Vector2(-0.03f, 0.0f), 4, 8, 31, 0.04f);

			gameplayer_animator->Play(L"Idle", true);
#pragma endregion

			SpriteRenderer* gameplayer_sr = gameplayer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			gameplayer_sr->SetMesh(gameplayer_mesh);
			gameplayer_sr->SetMaterial(gameplayer_mateiral);


			PlayerScMainScene* camsc = gameplayer->AddComponent<PlayerScMainScene>();
			camsc->setCameraScript(bcs);
			//gameplayer->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(gameplayer);

		}




		////할배 몬스터
		//{
		//	Monster* wanda_obj = object::Instantiate<Monster>(eLayerType::Monster);
		//	wanda_obj->SetName(L"Boss_Wanda");

		//	Transform* wanda_tr = wanda_obj->GetComponent<Transform>();
		//	wanda_tr->SetPosition(Vector3(2.5f, -0.1f, 5.0f));
		//	wanda_tr->SetScale(Vector3(13.0f, 13.0f, 1.0f));
		//	{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
		//		Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
		//		Vector3 firsttr = wanda_tr->GetPosition();
		//		Vector3 secondtr = gameplayer_tr->GetPosition();
		//		if (firsttr.x - secondtr.x > 0.0f)
		//			wanda_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
		//		else
		//			wanda_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		//	}

		//	/*Light* lightComp = wanda_obj->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Directional);
		//	lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.1f));*/

		//	Animator* BossWanda_Animator = wanda_obj->AddComponent<Animator>();
		//	//std::shared_ptr<Texture> wanda_idle = Resources::Load<Texture>(L"wanda", L"Boss\\T_Boss_Wanda_S1_Idle.png");
		//	

		//	//BossWanda_Animator->Create(L"wanda_idle", wanda_idle, Vector2(0.0f, 0.0f), Vector2(96.0f, 106.0f), Vector2::Zero, 4, 4, 13, 0.10f);
		//	

		//	BossWanda_Animator->Play(L"wanda_idle", true);


		//	SpriteRenderer* wanda_sr = wanda_obj->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Mesh> wanda_mesh = Resources::Find<Mesh>(L"RectMesh");
		//	std::shared_ptr<Material> wanda_mt = Resources::Find<Material>(L"SpriteMaterial");
		//	wanda_sr->SetMesh(wanda_mesh);
		//	wanda_sr->SetMaterial(wanda_mt);
		//	BossWandaScript* wandaSc = wanda_obj->AddComponent<BossWandaScript>(); //바꿔야딤
		//	wandaSc->setPlayerObject(gameplayer);
		//	//object::DontDestroyOnLoad(wanda_obj);
		//}




	}
	void MainScene::OnExit()
	{
	}
}