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
#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"
#include "yaHPBar_BG_Sc.h"
#include "yaHPBar_HEALTH_Sc.h"
#include "yaUI_SPELL_Hammer_Sc.h"
#include "yaUI_SPELL_Painwheel_Sc.h"
#include "yaUI_SPELL_Spear_Sc.h"
#include "yaUI_SPELL_Whirlwind_Sc.h"
#include "yaUI_Icon_Sc.h"

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
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		CameraScript* bcs = cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		Transform* cameratr = cameraObj->GetComponent<Transform>();
		
		cameratr->SetPosition(Vector3(1.0f,1.0f,-3.0f));

		//PlaySceenBG ->배경화면 부분
		//3개의 레이어로 구상함
		{
			{
				//playBgLeyer01
				GameObject* playBGObj_01 = object::Instantiate<GameObject>(eLayerType::BackGround);
				playBGObj_01->SetName(L"PlayBG01");
				Transform* playBGTr_01 = playBGObj_01->GetComponent<Transform>();
				playBGTr_01->SetPosition(Vector3(1.0f, 1.0f, 6.0f));
				playBGTr_01->SetScale(Vector3(20.0f, 10.0f, 1.0f));

				Light* playBGComp_01 = playBGObj_01->AddComponent<Light>();
				playBGComp_01->SetType(eLightType::Directional);
				playBGComp_01->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
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
				playBGTr_02->SetPosition(Vector3(1.0f, 3.4f, 4.0f));
				playBGTr_02->SetScale(Vector3(16.0f, 3.5f, 1.0f));

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
				playBGTr_03->SetPosition(Vector3(1.0f, -2.0f, 4.0f));
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
			gameplayer_tr->SetPosition(Vector3(-3.7f, -0.7f, 5.0f));
			gameplayer_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
			
			Light* gameplayer_light = gameplayer->AddComponent<Light>();
			gameplayer_light->SetType(eLightType::Directional);
			gameplayer_light->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			Rigidbody* gameplayer_rigid = gameplayer->AddComponent<Rigidbody>();

			//실행되는거 확인완료
			Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			gameplayer_col->SetType(eColliderType::Rect);
			gameplayer_col->SetSize(Vector2(0.03f, 0.11f));
			

			
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

			//어택 콜라이더 오브젝트
			GameObject* mAttack_obj = object::Instantiate<GameObject>(eLayerType::Player_Attack_Object);
			mAttack_obj->SetName(L"Hammer_Attack_Hit_Check");

			PlayerScript* player_sc = gameplayer->AddComponent<PlayerScript>();
			player_sc->setCameraScript(bcs);
			player_sc->setGameObject(cameraObj);
			player_sc->setAttack_obj(mAttack_obj);
			//gameplayer->AddComponent<PlayerScript>();
			//object::DontDestroyOnLoad(gameplayer);

		}
		

		
		//Boss_Wanda
		{
			Monster* wanda_obj = object::Instantiate<Monster>(eLayerType::Monster);
			wanda_obj->SetName(L"Boss_Wanda");

			Transform* wanda_tr = wanda_obj->GetComponent<Transform>();
			wanda_tr->SetPosition(Vector3(1.5f, -0.1f, 5.0f));
			wanda_tr->SetScale(Vector3(13.0f, 13.0f, 1.0f));
			{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
				Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
				Vector3 firsttr = wanda_tr->GetPosition();
				Vector3 secondtr = gameplayer_tr->GetPosition();
				if(firsttr.x - secondtr.x > 0.0f )
					wanda_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
				else
					wanda_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}

			/*Light* lightComp = wanda_obj->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.1f));*/

			Collider2D* wanda_col = wanda_obj->AddComponent<Collider2D>();
			wanda_col->SetType(eColliderType::Rect);
			wanda_col->SetSize(Vector2(0.1f, 0.25f));
			wanda_col->SetCenter(Vector2(-0.1f, 0.0f));


			Animator* BossWanda_Animator = wanda_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> wanda_idle = Resources::Load<Texture>(L"wanda", L"Boss\\T_Boss_Wanda_S1_Idle.png");
			std::shared_ptr<Texture> wanda_aoe_middle = Resources::Load<Texture>(L"wanda_aoe", L"Boss\\T_Boss_Wanda_S1_AoE_Middle.png");
			std::shared_ptr<Texture> wanda_chain = Resources::Load<Texture>(L"wanda_chain", L"Boss\\T_Boss_Wanda_S1_Chain.png"); //씀
			std::shared_ptr<Texture> wanda_s1_s2 = Resources::Load<Texture>(L"wanda_S1_S2", L"Boss\\T_Boss_Wanda_S1_S2.png");
			std::shared_ptr<Texture> wanda_s2_aoe = Resources::Load<Texture>(L"wanda_S1_AoE", L"Boss\\T_Boss_Wanda_S2_AoE.png"); // 씀
			std::shared_ptr<Texture> wanda_s2_garden = Resources::Load<Texture>(L"wanda_S2_Garden", L"Boss\\T_Boss_Wanda_S2_Garden.png"); //씀
			std::shared_ptr<Texture> wanda_s2_npc = Resources::Load<Texture>(L"wanda_S2_NPC", L"Boss\\T_Boss_Wanda_S2_NPC.png");
			std::shared_ptr<Texture> wanda_s2_npc_idle = Resources::Load<Texture>(L"wanda_S2_NPC_IDLE", L"Boss\\T_Boss_Wanda_S2_NPC_idel.png");
			std::shared_ptr<Texture> wanda_s2_skinshed = Resources::Load<Texture>(L"wanda_S2_SkinShed", L"Boss\\T_Boss_Wanda_S2_SkinShed.png");
			std::shared_ptr<Texture> wanda_s2_spin = Resources::Load<Texture>(L"wanda_S2_Spin", L"Boss\\T_Boss_Wanda_S2_Spin.png"); //씀

			BossWanda_Animator->Create(L"wanda_idle", wanda_idle, Vector2(0.0f, 0.0f), Vector2(96.0f, 106.0f), Vector2::Zero, 4, 4, 13, 0.10f);
			BossWanda_Animator->Create(L"wanda_aoe_middle", wanda_aoe_middle, Vector2(0.0f, 0.0f), Vector2(130.0f, 167.0f), Vector2(0.0f, -0.03f), 6, 6, 36, 0.10f);
			BossWanda_Animator->Create(L"wanda_chain", wanda_chain, Vector2(0.0f, 0.0f), Vector2(285.0f, 98.0f), Vector2(0.07f, -0.03f), 5, 2, 10, 0.10f , 3); //씀
			BossWanda_Animator->Create(L"wanda_chain2", wanda_chain, Vector2(0.0f, 196.0f), Vector2(285.0f, 98.0f), Vector2(0.07f, -0.03f), 5, 3, 5, 0.10f , 3); //씀
			BossWanda_Animator->Create(L"wanda_chain3", wanda_chain, Vector2(0.0f, 294.0f), Vector2(285.0f, 98.0f), Vector2(0.07f, -0.03f), 5, 5, 5, 0.10f , 3); //씀
			BossWanda_Animator->Create(L"wanda_chain4", wanda_chain, Vector2(0.0f, 392.0f), Vector2(285.0f, 98.0f), Vector2(0.07f, -0.03f), 5, 5, 5, 0.10f , 3); //씀
			BossWanda_Animator->Create(L"wanda_s1_s2", wanda_s1_s2, Vector2(0.0f, 0.0f), Vector2(119.0f, 122.0f), Vector2(0.0f, -0.03f), 6, 5, 26, 0.10f, 6);
			BossWanda_Animator->Create(L"wanda_s2_aoe", wanda_s2_aoe, Vector2(0.0f, 0.0f), Vector2(365.0f, 234.0f), Vector2(0.0f, -0.03f), 5, 5, 15, 0.10f); //씀
			BossWanda_Animator->Create(L"wanda_s2_aoe2", wanda_s2_aoe, Vector2(0.0f, 702.0f), Vector2(365.0f, 234.0f), Vector2(0.0f, -0.03f), 5, 2, 5, 0.10f); //씀
			BossWanda_Animator->Create(L"wanda_s2_aoe3", wanda_s2_aoe, Vector2(0.0f, 936.0f), Vector2(365.0f, 234.0f), Vector2(0.0f, -0.03f), 5, 1, 4, 0.10f); //씀
			BossWanda_Animator->Create(L"wanda_s2_garden", wanda_s2_garden, Vector2(0.0f, 0.0f), Vector2(181.0f, 228.0f), Vector2(0.0f, -0.01f), 6, 2, 8, 0.1f); //씀
			BossWanda_Animator->Create(L"wanda_s2_garden2", wanda_s2_garden, Vector2(362.0f, 228.0f), Vector2(181.0f, 228.0f), Vector2(0.0f, -0.01f), 4, 1, 4, 0.1f); //씀
			BossWanda_Animator->Create(L"wanda_s2_garden3", wanda_s2_garden, Vector2(0.0f, 456.0f), Vector2(181.0f, 228.0f), Vector2(0.0f, -0.01f), 6, 4, 19, 0.1f); //씀
			BossWanda_Animator->Create(L"wanda_s2_npc", wanda_s2_npc, Vector2(0.0f, 0.0f), Vector2(121.0f, 147.0f), Vector2(0.0f, -0.01f), 5, 5, 24, 0.10f);//씀
			BossWanda_Animator->Create(L"wanda_s2_npc_idle", wanda_s2_npc_idle, Vector2(0.0f, 0.0f), Vector2(48.0f, 61.0f), Vector2(0.0f, 0.1f), 1, 1, 1, 0.10f);//씀
			BossWanda_Animator->Create(L"wanda_s2_skinshed", wanda_s2_skinshed, Vector2(0.0f, 0.0f), Vector2(272.0f, 132.0f), Vector2(0.0f, -0.01f), 7, 6, 39, 0.10f); 
			BossWanda_Animator->Create(L"wanda_s2_spin", wanda_s2_spin, Vector2(0.0f, 0.0f), Vector2(391.0f, 216.0f), Vector2(0.0f, -0.03f), 6, 6, 12, 0.10f); //씀
			BossWanda_Animator->Create(L"wanda_s2_spin2", wanda_s2_spin, Vector2(0.0f, 432.0f), Vector2(391.0f, 216.0f), Vector2(0.0f, -0.03f), 6, 4, 6, 0.10f); //씀
			BossWanda_Animator->Create(L"wanda_s2_spin3", wanda_s2_spin, Vector2(0.0f, 648.0f), Vector2(391.0f, 216.0f), Vector2(0.0f, -0.03f), 6, 3, 6, 0.10f); //씀
			BossWanda_Animator->Create(L"wanda_s2_spin4", wanda_s2_spin, Vector2(0.0f, 864.0f), Vector2(391.0f, 216.0f), Vector2(0.0f, -0.03f), 6, 2, 7, 0.10f); //씀

			BossWanda_Animator->Play(L"wanda_s2_npc_idle", true);
			

			SpriteRenderer* wanda_sr = wanda_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> wanda_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> wanda_mt = Resources::Find<Material>(L"SpriteMaterial");
			wanda_sr->SetMesh(wanda_mesh);
			wanda_sr->SetMaterial(wanda_mt);
			BossWandaScript* wandaSc = wanda_obj->AddComponent<BossWandaScript>();
			wandaSc->setmGameObject(gameplayer);
			wandaSc->setCameraObject(cameraObj);

		}


#pragma region UI
		//HPBG
		{
			GameObject* HPBar_BG_obj = object::Instantiate<GameObject>(eLayerType::UI);
			HPBar_BG_obj->SetName(L"HPBar_BG_obj");

			Transform* HPBar_BG_tr = HPBar_BG_obj->GetComponent<Transform>();
			Vector3 cam_pos = cameratr->GetPosition();
			cam_pos += 6.9 * cameratr->Foward();
			cam_pos += -3.8 * cameratr->Up();
			cam_pos += -4.9 * cameratr->Right();
			HPBar_BG_tr->SetPosition(cam_pos);
			HPBar_BG_tr->SetScale(Vector3(4.f, 0.1f, 0.f));

			HPBar_BG_Sc* HpBG_Sc = HPBar_BG_obj->AddComponent<HPBar_BG_Sc>();
			HpBG_Sc->setGameObject(cameraObj);
			HpBG_Sc->setPlayerObj(gameplayer);

			SpriteRenderer* HPBar_BG_sr = HPBar_BG_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> HPBar_BG_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> HPBar_BG_material = Resources::Find<Material>(L"BarBGMaterial");
			HPBar_BG_sr->SetMaterial(HPBar_BG_material);
			HPBar_BG_sr->SetMesh(HPBar_BG_mesh);
		}

		//HPBar
		{
			GameObject* HPBar_obj = object::Instantiate<GameObject>(eLayerType::UI);
			HPBar_obj->SetName(L"HPBar_obj");

			Transform* HPBar_tr = HPBar_obj->GetComponent<Transform>();
			Vector3 cam_pos = cameratr->GetPosition();
			cam_pos += 6.8 * cameratr->Foward();
			cam_pos += -3.75 * cameratr->Up();
			cam_pos += -4.8 * cameratr->Right();
			HPBar_tr->SetPosition(cam_pos);
			HPBar_tr->SetScale(Vector3(3.8f, 0.04f, 0.f));

			HPBar_HEALTH_Sc* HpBar_Sc = HPBar_obj->AddComponent<HPBar_HEALTH_Sc>();
			HpBar_Sc->setGameObject(cameraObj);
			HpBar_Sc->setPlayerObj(gameplayer);

			SpriteRenderer* HPBar_BG_sr = HPBar_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> HPBar_BG_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> HPBar_BG_material = Resources::Find<Material>(L"BarHEALTHMaterial");
			HPBar_BG_sr->SetMaterial(HPBar_BG_material);
			HPBar_BG_sr->SetMesh(HPBar_BG_mesh);
		}

		//Skill UI Hammer
		{
			GameObject* UI_SpellRect_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_obj->SetName(L"UI_SPellRect_obj");

			Transform* UI_SpellRect_tr = UI_SpellRect_obj->GetComponent<Transform>();
			Vector3 cam_pos = cameratr->GetPosition();
			cam_pos += 6.8 * cameratr->Foward();
			cam_pos += -2.4 * cameratr->Up();
			cam_pos += -6.3 * cameratr->Right();
			UI_SpellRect_tr->SetPosition(cam_pos);
			UI_SpellRect_tr->SetScale(Vector3(8.f, 8.0f, 0.f));

			Animator* UI_SpellRect_ani = UI_SpellRect_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> UI_Spell = Resources::Load<Texture>(L"UISPELL", L"UI\\UI_SpellReady.png");
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Play(L"UI_Spell", false);

			UI_SPELL_Hammer_Sc* UI_SpellRect_Sc = UI_SpellRect_obj->AddComponent<UI_SPELL_Hammer_Sc>();
			UI_SpellRect_Sc->setGameObject(cameraObj);
			UI_SpellRect_Sc->setPosY(2.4);
			UI_SpellRect_Sc->setPosX(6.3);

			SpriteRenderer* UI_SpellRect_sr = UI_SpellRect_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"SpriteMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);

			//icon
			GameObject* UI_SpellRect_icon_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_icon_obj->SetName(L"UI_SpellRect_icon_obj");

			Transform* UI_SpellRect_icon_tr = UI_SpellRect_icon_obj->GetComponent<Transform>();
			UI_SpellRect_icon_tr->SetScale(Vector3(0.5f, 0.5f, 0.f));

			UI_Icon_Sc* UI_icon_Sc = UI_SpellRect_icon_obj->AddComponent<UI_Icon_Sc>();
			UI_icon_Sc->setGameObject(cameraObj);
			UI_icon_Sc->setPosY(3.1);
			UI_icon_Sc->setPosX(6.2);

			SpriteRenderer* UI_SpellRect_icon_sr = UI_SpellRect_icon_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_icon_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_icon_material = Resources::Find<Material>(L"Hammer_iconMaterial");
			UI_SpellRect_icon_sr->SetMaterial(UI_SpellRect_icon_material);
			UI_SpellRect_icon_sr->SetMesh(UI_SpellRect_icon_mesh);
		}

		//Skill UI PainWheel
		{
			GameObject* UI_SpellRect_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_obj->SetName(L"UI_SPellRect_obj");

			Transform* UI_SpellRect_tr = UI_SpellRect_obj->GetComponent<Transform>();
			Vector3 cam_pos = cameratr->GetPosition();
			cam_pos += 6.8 * cameratr->Foward();
			cam_pos += -2.4 * cameratr->Up();
			cam_pos += -5.3 * cameratr->Right();
			UI_SpellRect_tr->SetPosition(cam_pos);
			UI_SpellRect_tr->SetScale(Vector3(8.f, 8.0f, 0.f));

			Animator* UI_SpellRect_ani = UI_SpellRect_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> UI_Spell = Resources::Load<Texture>(L"UISPELL", L"UI\\UI_SpellReady.png");
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Play(L"UI_Spell", false);

			UI_SPELL_Painwheel_Sc* UI_SpellRect_Sc = UI_SpellRect_obj->AddComponent<UI_SPELL_Painwheel_Sc>();
			UI_SpellRect_Sc->setGameObject(cameraObj);

			SpriteRenderer* UI_SpellRect_sr = UI_SpellRect_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"SpriteMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);

			//icon
			GameObject* UI_SpellRect_icon_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_icon_obj->SetName(L"UI_SpellRect_icon_obj");

			Transform* UI_SpellRect_icon_tr = UI_SpellRect_icon_obj->GetComponent<Transform>();
			UI_SpellRect_icon_tr->SetScale(Vector3(0.5f, 0.5f, 0.f));

			UI_Icon_Sc* UI_icon_Sc = UI_SpellRect_icon_obj->AddComponent<UI_Icon_Sc>();
			UI_icon_Sc->setGameObject(cameraObj);
			UI_icon_Sc->setPosY(3.1);
			UI_icon_Sc->setPosX(5.2);

			SpriteRenderer* UI_SpellRect_icon_sr = UI_SpellRect_icon_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_icon_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_icon_material = Resources::Find<Material>(L"Painwheel_iconMaterial");
			UI_SpellRect_icon_sr->SetMaterial(UI_SpellRect_icon_material);
			UI_SpellRect_icon_sr->SetMesh(UI_SpellRect_icon_mesh);
		}

		//Skill UI Spear
		{
			GameObject* UI_SpellRect_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_obj->SetName(L"UI_SPellRect_obj");

			Transform* UI_SpellRect_tr = UI_SpellRect_obj->GetComponent<Transform>();
			Vector3 cam_pos = cameratr->GetPosition();
			cam_pos += 6.8 * cameratr->Foward();
			cam_pos += -2.4 * cameratr->Up();
			cam_pos += -4.3 * cameratr->Right();
			UI_SpellRect_tr->SetPosition(cam_pos);
			UI_SpellRect_tr->SetScale(Vector3(8.f, 8.0f, 0.f));

			Animator* UI_SpellRect_ani = UI_SpellRect_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> UI_Spell = Resources::Load<Texture>(L"UISPELL", L"UI\\UI_SpellReady.png");
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Play(L"UI_Spell", false);

			UI_SPELL_Spear_Sc* UI_SpellRect_Sc = UI_SpellRect_obj->AddComponent<UI_SPELL_Spear_Sc>();
			UI_SpellRect_Sc->setGameObject(cameraObj);

			SpriteRenderer* UI_SpellRect_sr = UI_SpellRect_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"SpriteMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);

			//icon
			GameObject* UI_SpellRect_icon_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_icon_obj->SetName(L"UI_SpellRect_icon_obj");

			Transform* UI_SpellRect_icon_tr = UI_SpellRect_icon_obj->GetComponent<Transform>();
			UI_SpellRect_icon_tr->SetScale(Vector3(0.45f, 0.45f, 0.f));

			UI_Icon_Sc* UI_icon_Sc = UI_SpellRect_icon_obj->AddComponent<UI_Icon_Sc>();
			UI_icon_Sc->setGameObject(cameraObj);
			UI_icon_Sc->setPosY(3.1);
			UI_icon_Sc->setPosX(4.25);

			SpriteRenderer* UI_SpellRect_icon_sr = UI_SpellRect_icon_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_icon_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_icon_material = Resources::Find<Material>(L"Spear_iconMaterial");
			UI_SpellRect_icon_sr->SetMaterial(UI_SpellRect_icon_material);
			UI_SpellRect_icon_sr->SetMesh(UI_SpellRect_icon_mesh);
		}

		//Skill UI Whirlwind
		{
			GameObject* UI_SpellRect_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_obj->SetName(L"UI_SPellRect_obj");

			Transform* UI_SpellRect_tr = UI_SpellRect_obj->GetComponent<Transform>();
			Vector3 cam_pos = cameratr->GetPosition();
			cam_pos += 6.8 * cameratr->Foward();
			cam_pos += -2.4 * cameratr->Up();
			cam_pos += -3.3 * cameratr->Right();
			UI_SpellRect_tr->SetPosition(cam_pos);
			UI_SpellRect_tr->SetScale(Vector3(8.f, 8.0f, 0.f));

			Animator* UI_SpellRect_ani = UI_SpellRect_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> UI_Spell = Resources::Load<Texture>(L"UISPELL", L"UI\\UI_SpellReady.png");
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.10f);
			UI_SpellRect_ani->Play(L"UI_Spell", false);

			UI_SPELL_Whirlwind_Sc* UI_SpellRect_Sc = UI_SpellRect_obj->AddComponent<UI_SPELL_Whirlwind_Sc>();
			UI_SpellRect_Sc->setGameObject(cameraObj);

			SpriteRenderer* UI_SpellRect_sr = UI_SpellRect_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"SpriteMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);

			//icon
			GameObject* UI_SpellRect_icon_obj = object::Instantiate<GameObject>(eLayerType::UI);
			UI_SpellRect_icon_obj->SetName(L"UI_SpellRect_icon_obj");

			Transform* UI_SpellRect_icon_tr = UI_SpellRect_icon_obj->GetComponent<Transform>();
			UI_SpellRect_icon_tr->SetScale(Vector3(0.45f, 0.45f, 0.f));

			UI_Icon_Sc* UI_icon_Sc = UI_SpellRect_icon_obj->AddComponent<UI_Icon_Sc>();
			UI_icon_Sc->setGameObject(cameraObj);
			UI_icon_Sc->setPosY(3.1);
			UI_icon_Sc->setPosX(3.25);




			SpriteRenderer* UI_SpellRect_icon_sr = UI_SpellRect_icon_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_icon_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_icon_material = Resources::Find<Material>(L"Whirlwind_iconMaterial");
			UI_SpellRect_icon_sr->SetMaterial(UI_SpellRect_icon_material);
			UI_SpellRect_icon_sr->SetMesh(UI_SpellRect_icon_mesh);

		}

#pragma endregion








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
		
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Attack_Object, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player_Attack_Object, eLayerType::Monster, true);
	}

	void PlayScene::OnExit()
	{
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, false);
	}

}
