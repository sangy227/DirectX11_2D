#include "yaPlayScene.h"
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

namespace ya
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{
		//키코드 목록
		//이동 방향키
		//공격 ZXCV
		//스킬 ASDF

		//카메라이동 UIOJKL
		//카메라 쉐이크 QW

		//씬 넘기기 N
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		
		
		int a = 0;



		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		/*if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}*/
		

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		{ // Light1
			/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));*/
		} 

		{ // Light2
			/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));*/
			//Light* lightComp = directionalLight->AddComponent<Light>();
			//lightComp->SetType(eLightType::Point);
			//lightComp->SetRadius(10.0f);
			//lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{
			//paint shader
			std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
			//L"SmileTexture"
			std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
			paintShader->SetTarget(paintTex);
			paintShader->OnExcute();
		}

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		Transform* cameratr = cameraObj->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();
		camerapos += (4.0f * -cameratr->Foward());
		cameratr->SetPosition(camerapos);

		//PlaySceenBG ->배경화면 부분
		//3개의 레이어로 구상함
		{
			{
				//playBgLeyer01
				GameObject* playBGObj_01 = object::Instantiate<GameObject>(eLayerType::BackGround);
				playBGObj_01->SetName(L"PlayBG01");
				Transform* playBGTr_01 = playBGObj_01->GetComponent<Transform>();
				playBGTr_01->SetPosition(Vector3(1.0f, 1.0f, 5.1f));
				playBGTr_01->SetScale(Vector3(20.0f, 10.0f, 1.0f));

				Light* playBGComp_01 = playBGObj_01->AddComponent<Light>();
				playBGComp_01->SetType(eLightType::Directional);
				playBGComp_01->SetDiffuse(Vector4(2.0f, 2.0f, 2.0f, 1.0f));
				//playBGComp_01->SetAmbient(Vector4(2.0f, 2.0f, 2.0f, 1.0f));

				SpriteRenderer* playsr_01 = playBGObj_01->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> playmesh_01 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> playBGmaterial_01 = Resources::Find<Material>(L"playBGMaterial01");
				playsr_01->SetMaterial(playBGmaterial_01);
				playsr_01->SetMesh(playmesh_01);
			}
			{
				//playBgLeyer02
				GameObject* playBGObj_02 = object::Instantiate<GameObject>(eLayerType::BackGround);
				playBGObj_02->SetName(L"PlayBG02");
				Transform* playBGTr_02 = playBGObj_02->GetComponent<Transform>();
				playBGTr_02->SetPosition(Vector3(1.0f, 3.5f, 3.9f));
				playBGTr_02->SetScale(Vector3(16.0f, 3.15f, 1.0f));

				/*Light* playBGComp_02 = playBGObj_02->AddComponent<Light>();
				playBGComp_02->SetType(eLightType::Directional);
				playBGComp_02->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.0f));*/

				SpriteRenderer* playsr_02 = playBGObj_02->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> playmesh_02 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> playtBGmaterial_02 = Resources::Find<Material>(L"playBGMaterial02");
				playsr_02->SetMaterial(playtBGmaterial_02);
				playsr_02->SetMesh(playmesh_02);
			}
			{
				//playBgLeyer03
				GameObject* playBGObj_03 = object::Instantiate<GameObject>(eLayerType::BackGround);
				playBGObj_03->SetName(L"PlayBG03");

				Transform* playBGTr_03 = playBGObj_03->GetComponent<Transform>();
				playBGTr_03->SetPosition(Vector3(1.0f, -2.0f, 3.9f));
				playBGTr_03->SetScale(Vector3(16.0f, 3.14f, 1.0f));

				/*Light* playBGComp_03 = playBGObj_03->AddComponent<Light>();
				playBGComp_03->SetType(eLightType::Directional);
				playBGComp_03->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.0f));*/

				SpriteRenderer* playsr_03 = playBGObj_03->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> playmesh_03 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> PlayBGmaterial_03 = Resources::Find<Material>(L"playBGMaterial03");
				playsr_03->SetMaterial(PlayBGmaterial_03);
				playsr_03->SetMesh(playmesh_03);
			}
		}

		//Game_Main_Player
		{
			gameplayer = object::Instantiate<Player>(eLayerType::Player);
			gameplayer->SetName(L"GamePlayer");
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			gameplayer_tr->SetPosition(Vector3(-0.7f, -0.5f, 4.0f));
			gameplayer_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
			
			/*Light* gameplayer_light = gameplayer->AddComponent<Light>();
			gameplayer_light->SetType(eLightType::Directional);
			gameplayer_light->SetDiffuse(Vector4(1.0f, 0.7f, 0.7f, 1.0f));*/

			Rigidbody* gameplayer_rigid = gameplayer->AddComponent<Rigidbody>();

			//실행되는거 확인완료
			//Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			//gameplayer_col->SetType(eColliderType::Rect);
			//gameplayer_col->SetSize(Vector2(0.12f, 0.11f));
			
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
			
			
			gameplayer_animator->Create(L"Idle", player_idle, Vector2(0.0f, 0.0f), Vector2(59.0f, 52.0f), Vector2::Zero, 7,4,26, 0.08f);
			gameplayer_animator->Create(L"attack", player_attack, Vector2(0.0f, 0.0f), Vector2(166.0f, 54.0f), Vector2(0.03f, 0.0f), 4,6,24, 0.04f);
			gameplayer_animator->Create(L"attack2", player_attack2, Vector2(0.0f, 0.0f), Vector2(143.0f, 52.0f), Vector2(0.03f, 0.0f), 5,5,25, 0.04f);
			gameplayer_animator->Create(L"run01", player_run01, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(0.03f, 0.0f), 4, 1, 4, 0.05f);
			gameplayer_animator->Create(L"run", player_run02, Vector2(0.0f, 0.0f), Vector2(62.0f, 53.0f), Vector2(0.03f, -0.0f), 5, 3, 14, 0.05f);
			gameplayer_animator->Create(L"dash", player_dash, Vector2(0.0f, 0.0f), Vector2(181.0f, 46.0f), Vector2(-0.18f, -0.0f), 2, 8, 12, 0.05f);
			gameplayer_animator->Create(L"jump", player_jump, Vector2(0.0f, 0.0f), Vector2(60.0f, 57.0f), Vector2(0.00f, 0.0f), 4, 4, 14, 0.05f);
			
			gameplayer_animator->Create(L"skill_hammer", player_skill_hammer, Vector2(0.0f, 0.0f), Vector2(275.0f, 119.0f), Vector2(0.03f,-0.015f), 5, 12, 57, 0.04f);
			gameplayer_animator->Create(L"skill_Painwheel", player_skill_Painwheel, Vector2(0.0f, 0.0f), Vector2(190.0f, 85.0f), Vector2(0.03f,-0.015f), 5, 11, 54, 0.04f);
			gameplayer_animator->Create(L"skill_Spear", player_skill_Spear, Vector2(0.0f, 0.0f), Vector2(272.0f, 71.0f), Vector2(0.03f, 0.0f), 4, 9, 34, 0.04f);
			gameplayer_animator->Create(L"skill_Whirlwind", player_skill_Whirlwind, Vector2(0.0f, 0.0f), Vector2(128.0f, 60.0f), Vector2(-0.03f, 0.0f), 4, 8, 31, 0.04f);
			
			gameplayer_animator->Play(L"Idle", true);
#pragma endregion
			
			SpriteRenderer* gameplayer_sr = gameplayer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			gameplayer_sr->SetMesh(gameplayer_mesh);
			gameplayer_sr->SetMaterial(gameplayer_mateiral);

			gameplayer->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(gameplayer);

		}

		
		//Boss_Wanda
		{
			Monster* wanda_obj = object::Instantiate<Monster>(eLayerType::Monster);
			wanda_obj->SetName(L"Boss_Wanda");

			Transform* wanda_tr = wanda_obj->GetComponent<Transform>();
			wanda_tr->SetPosition(Vector3(2.5f, 0.1f, 5.0f));
			wanda_tr->SetScale(Vector3(13.0f, 13.3f, 1.0f));
			wanda_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));

			/*Light* lightComp = wanda_obj->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.1f));*/

			Animator* BossWanda_Animator = wanda_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> wanda_idle = Resources::Load<Texture>(L"wanda", L"Boss\\T_Boss_Wanda_S1_Idle.png");
			std::shared_ptr<Texture> wanda_aoe_middle = Resources::Load<Texture>(L"wanda_aoe", L"Boss\\T_Boss_Wanda_S1_AoE_Middle.png");
			std::shared_ptr<Texture> wanda_chain = Resources::Load<Texture>(L"wanda_chain", L"Boss\\T_Boss_Wanda_S1_Chain.png");

			BossWanda_Animator->Create(L"wanda_idle", wanda_idle, Vector2(0.0f, 0.0f), Vector2(96.0f, 106.0f), Vector2::Zero, 4, 4, 13, 0.10f);
			BossWanda_Animator->Create(L"wanda_aoe_middle", wanda_aoe_middle, Vector2(0.0f, 0.0f), Vector2(130.0f, 167.0f), Vector2(0.0f, -0.03f), 6, 6, 36, 0.10f);
			BossWanda_Animator->Create(L"wanda_chain", wanda_chain, Vector2(0.0f, 0.0f), Vector2(285.0f, 98.0f), Vector2(0.0f, -0.03f), 5, 5, 25, 0.10f , 3);

			BossWanda_Animator->Play(L"wanda_aoe_middle", true);


			SpriteRenderer* wanda_sr = wanda_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> wanda_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> wanda_mt = Resources::Find<Material>(L"SpriteMaterial");
			wanda_sr->SetMesh(wanda_mesh);
			wanda_sr->SetMaterial(wanda_mt);
			wanda_obj->AddComponent<BossWandaScript>();
			object::DontDestroyOnLoad(wanda_obj);
		}


		//SMILE RECT
		{
		//	Player* obj = object::Instantiate<Player>(eLayerType::Player);
		//	obj->SetName(L"tochlight");
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(5.3f, 1.0f, 3.2f));
		//	tr->SetScale(Vector3(0.5f, 1.5f, 1.0f));
		//
		//	
		//	Light* lightComp = obj->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Point); //포인트여야지 주변 밝게 할수있음
		//	lightComp->SetRadius(1.0f);
		//	lightComp->SetDiffuse(Vector4(0.0f, 0.0f, 3.0f, 1.0f));
		//
		//	SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
		//	mr->SetMaterial(mateiral);
		//	std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		//	mr->SetMesh(mesh);
		//	object::DontDestroyOnLoad(obj);
		}
		
		
	}

	void PlayScene::OnExit()
	{

	}

}
