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
#include "yaGrandPaScript.h"
#include "yaRedQueenScript.h"
#include "yaSculptorScript.h"
#include "yafirstCameraMoveLine_Script.h"
#include "yaevent_Line_Sc.h"
#include "yafirstCameraStopLine_Script.h"
#include "yasecondCameraMoveLine_Script.h"
#include "yaevent_Line2_Sc.h"
#include "yasecondCameraStopLine_Script.h"
#include "yathirdCameraMoveLine_Script.h"
#include "yaevent_Line3_Sc.h"
#include "yathirdCameraStopLine_Script.h"
#include "yafourthCameraMoveLine_Script.h"
#include "yaevent_Line4_Sc.h"
#include "yafourthCameraStopLine_Script.h"
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
namespace ya {
	MainScene::MainScene()
		: Scene(eSceneType::Main)
	{
		//키보드 목록
		//ENTER 카메라 무브및 멈춤
		//UIOJKL 카메라 이동
		// QW 카메라 진동
		//E 할배 키목록
		//T 조각가할배 키 목록
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
		cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->RegisterCameraInRenderer();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		MainCameraSc* bcs = cameraObj->AddComponent<MainCameraSc>();
		mainCamera = cameraComp;

		Transform* cameratr = cameraObj->GetComponent<Transform>();
		cameratr->SetPosition(Vector3(1.0f, 1.0f, -3.0f));
		AudioListener* player_lis = cameraObj->AddComponent<AudioListener>(); //여기랑

		

#pragma region Audio 
		//여기
		std::shared_ptr<AudioClip> myAudioClip = Resources::Load<AudioClip>(L"BGMmain", L"Moonscars Exterior Music.wav");
		myAudioClip->SetVolume(1.0f);

		//Audio Object
		audio_obj = object::Instantiate<GameObject>(eLayerType::UI);
		Transform* audio_tr = audio_obj->GetComponent<Transform>();
		Vector3 pos = cameratr->GetPosition();
		pos += 10 * cameratr->Foward();
		audio_tr->SetPosition(pos);

		audio = audio_obj->AddComponent<AudioSource>();
		audio->SetClip(myAudioClip);
		audio->Play();

		
		


		
#pragma endregion



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

				//Moonscars Exterior Music


			}
		}

		//Game_Main_Player = 플레이어
		{
			gameplayer = object::Instantiate<Player>(eLayerType::Player);
			gameplayer->SetName(L"GamePlayer");

			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			gameplayer_tr->SetPosition(Vector3(-5.0f, -1.55f, 5.0f));
			gameplayer_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));


			Light* gameplayer_light = gameplayer->AddComponent<Light>();
			gameplayer_light->SetType(eLightType::Directional);
			gameplayer_light->SetDiffuse(Vector4(0.2f, 0.2f, 0.2f, 0.0f));

			Rigidbody* gameplayer_rigid = gameplayer->AddComponent<Rigidbody>();

			//실행되는거 확인완료
			Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			gameplayer_col->SetType(eColliderType::Rect);
			gameplayer_col->SetSize(Vector2(0.03f, 0.11f));
			gameplayer_col->SetCenter(Vector2(0.2f, 0.0f));

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

			//어택 콜라이더 오브젝트
			GameObject* mAttack_obj = object::Instantiate<GameObject>(eLayerType::Player_Attack_Object);
			mAttack_obj->SetName(L"Hammer_Attack_Hit_Check");

			PlayerScMainScene* camsc = gameplayer->AddComponent<PlayerScMainScene>();
			camsc->setMainCameraSc(bcs);
			camsc->setGameObject(cameraObj);
			camsc->setAttack_obj(mAttack_obj);

			
		
		

		}
#pragma region 할배 몬스터
		//할배 몬스터
		
		Monster* grandpa_obj = object::Instantiate<Monster>(eLayerType::Monster);
		grandpa_obj->SetName(L"Grandpa");

		Transform* grandpa_tr = grandpa_obj->GetComponent<Transform>();
		grandpa_tr->SetPosition(Vector3(17.5f, -1.0f, 5.0f));
		grandpa_tr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
		{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			Vector3 firsttr = grandpa_tr->GetPosition();
			Vector3 secondtr = gameplayer_tr->GetPosition();
			if (firsttr.x - secondtr.x > 0.0f)
				grandpa_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
			else
				grandpa_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		}

		/*Light* lightComp = wanda_obj->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.1f));*/

		Collider2D* grandpa_col = grandpa_obj->AddComponent<Collider2D>();
		grandpa_col->SetType(eColliderType::Rect);
		grandpa_col->SetSize(Vector2(0.07f, 0.11f));
		grandpa_col->SetCenter(Vector2(0.3f, 0.0f));
		grandpa_col->IsTriiger();


		Animator* grandpa_Animator = grandpa_obj->AddComponent<Animator>();
		std::shared_ptr<Texture> grandpa_idle = Resources::Load<Texture>(L"grandpa", L"GrandPa\\T_NPC_FirstOne_Idle.png");
		std::shared_ptr<Texture> grandpa_attack = Resources::Load<Texture>(L"grandpa_attack", L"GrandPa\\T_NPC_FirstOne_Heal.png");
		std::shared_ptr<Texture> grandpa_die = Resources::Load<Texture>(L"grandpa_die", L"GrandPa\\T_NPC_FirstOne_Death.png");


		grandpa_Animator->Create(L"grandpa_idle", grandpa_idle, Vector2(0.0f, 0.0f), Vector2(36.0f, 69.0f), Vector2(-0.07f, 0.05f), 4, 2, 8, 0.13f);
		grandpa_Animator->Create(L"grandpa_attack_1", grandpa_attack, Vector2(0.0f, 0.0f), Vector2(55.0f, 83.0f), Vector2::Zero, 6, 3, 10, 0.13f);
		grandpa_Animator->Create(L"grandpa_attack_2", grandpa_attack, Vector2(165.0f, 83.0f), Vector2(55.0f, 83.0f), Vector2::Zero, 3, 1, 3, 0.13f);
		grandpa_Animator->Create(L"grandpa_attack_3", grandpa_attack, Vector2(0.0f, 166.0f), Vector2(55.0f, 83.0f), Vector2::Zero, 6, 1, 6, 0.13f);
		grandpa_Animator->Create(L"grandpa_die", grandpa_die, Vector2(0.0f, 0.0f), Vector2(86.0f, 69.0f), Vector2(0.055f, 0.015f), 3, 6, 17, 0.15f);


		grandpa_Animator->Play(L"grandpa_idle", true);

		SpriteRenderer* grandpa_sr = grandpa_obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> grandpa_mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> grandpa_mt = Resources::Find<Material>(L"SpriteMaterial");
		grandpa_sr->SetMesh(grandpa_mesh);
		grandpa_sr->SetMaterial(grandpa_mt);

		GrandPaScript* grandpaSc = grandpa_obj->AddComponent<GrandPaScript>();
		grandpaSc->setmGameObject(gameplayer);
		//object::DontDestroyOnLoad(wanda_obj);
#pragma endregion

		//빨간 의자
		{
			GameObject* chair_obj = object::Instantiate<GameObject>(eLayerType::BackGround);
			chair_obj->SetName(L"chair");

			Transform* chair_tr = chair_obj->GetComponent<Transform>();
			chair_tr->SetPosition(Vector3(34.0f, -1.0f, 5.01f));
			chair_tr->SetScale(Vector3(1.0f, 2.0f, 1.0f));

			SpriteRenderer* chair_sr = chair_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> chair_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> chair_material = Resources::Find<Material>(L"chairMaterial");
			chair_sr->SetMaterial(chair_material);
			chair_sr->SetMesh(chair_mesh);
		}

		//빨간 의자 앉아있는 여자
		{
			Monster* redqueen_obj = object::Instantiate<Monster>(eLayerType::Monster);
			redqueen_obj->SetName(L"redqueen");

			Transform* redqueen_tr = redqueen_obj->GetComponent<Transform>();
			redqueen_tr->SetPosition(Vector3(34.0f, -1.0f, 5.0f));
			redqueen_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
			{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
				Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
				Vector3 firsttr = redqueen_tr->GetPosition();
				Vector3 secondtr = gameplayer_tr->GetPosition();
				if (firsttr.x - secondtr.x > 0.0f)
					redqueen_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
				else
					redqueen_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}


			Collider2D* redqueen_col = redqueen_obj->AddComponent<Collider2D>();
			redqueen_col->SetType(eColliderType::Rect);
			redqueen_col->SetSize(Vector2(0.35f, 0.2f));
			redqueen_col->SetCenter(Vector2(0.7f, 0.0f));


			Animator* redqueen_Animator = redqueen_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> redqueen_idle = Resources::Load<Texture>(L"redqueen", L"RedQueen\\T_NPC_Yadwiga_Idle.png");



			redqueen_Animator->Create(L"redqueen_idle", redqueen_idle, Vector2(0.0f, 0.0f), Vector2(99.0f, 72.0f), Vector2(0.0f, 0.0f), 5, 11, 55, 0.10f);



			redqueen_Animator->Play(L"redqueen_idle", true);


			SpriteRenderer* redqueen_sr = redqueen_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> redqueen_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> redqueen_mt = Resources::Find<Material>(L"SpriteMaterial");
			redqueen_sr->SetMesh(redqueen_mesh);
			redqueen_sr->SetMaterial(redqueen_mt);
			RedQueenScript* redqueenSc = redqueen_obj->AddComponent<RedQueenScript>();
			redqueenSc->setmGameObject(gameplayer);
			//object::DontDestroyOnLoad(wanda_obj);
		}

		//빨간 여자 옆에 고양이
		{
			Monster* cat_obj = object::Instantiate<Monster>(eLayerType::Monster);
			cat_obj->SetName(L"cat");

			Transform* cat_tr = cat_obj->GetComponent<Transform>();
			cat_tr->SetPosition(Vector3(36.f, -1.7f, 5.0f));
			cat_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
			{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
				Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
				Vector3 firsttr = cat_tr->GetPosition();
				Vector3 secondtr = gameplayer_tr->GetPosition();
				if (firsttr.x - secondtr.x > 0.0f)
					cat_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
				else
					cat_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}

			Animator* cat_Animator = cat_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> cat_idle = Resources::Load<Texture>(L"cat", L"npc_etalag_idle.png");

			cat_Animator->Create(L"cat_idle", cat_idle, Vector2(0.0f, 0.0f), Vector2(97.f, 43.f), Vector2(0.0f, 0.0f), 5, 6, 23, 0.10f);

			cat_Animator->Play(L"cat_idle", true);


			SpriteRenderer* cat_sr = cat_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> cat_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> cat_mt = Resources::Find<Material>(L"SpriteMaterial");
			cat_sr->SetMesh(cat_mesh);
			cat_sr->SetMaterial(cat_mt);
		}

#pragma region 조각가 보스
		//날아다니는 할배 == 조각가보스
		Monster* sculptor_obj = object::Instantiate<Monster>(eLayerType::Monster);
		sculptor_obj->SetName(L"sculptor");

		Transform* sculptor_tr = sculptor_obj->GetComponent<Transform>();
		sculptor_tr->SetPosition(Vector3(51.5f, -0.7f, 5.0f));
		sculptor_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
		{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			Vector3 firsttr = sculptor_tr->GetPosition();
			Vector3 secondtr = gameplayer_tr->GetPosition();
			if (firsttr.x - secondtr.x > 0.0f)
				sculptor_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
			else
				sculptor_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		}

		Collider2D* sculptor_col = sculptor_obj->AddComponent<Collider2D>();
		sculptor_col->SetType(eColliderType::Rect);
		sculptor_col->SetSize(Vector2(0.1f, 0.25f));
		sculptor_col->SetCenter(Vector2(0.0f, 0.0f));



		Animator* sculptor_Animator = sculptor_obj->AddComponent<Animator>();
		std::shared_ptr<Texture> sculptor_idle = Resources::Load<Texture>(L"sculptor", L"BossSculptor\\T_BossSculptor_Idle.png");
		std::shared_ptr<Texture> sculptor_attack = Resources::Load<Texture>(L"sculptor_attack", L"BossSculptor\\T_BossSculptor_Cast.png");
		std::shared_ptr<Texture> sculptor_die = Resources::Load<Texture>(L"sculptor_die", L"BossSculptor\\T_BossSculptor_DeathBody.png");


		sculptor_Animator->Create(L"sculptor_idle", sculptor_idle, Vector2(0.0f, 0.0f), Vector2(194.0f, 139.0f), Vector2(0.0f, 0.0f), 3, 4, 12, 0.12f);
		sculptor_Animator->Create(L"sculptor_attack", sculptor_attack, Vector2(0.0f, 0.0f), Vector2(202.0f, 189.0f), Vector2(0.0f, 0.0f), 3, 5, 13, 0.12f);
		sculptor_Animator->Create(L"sculptor_die", sculptor_die, Vector2(0.0f, 0.0f), Vector2(102.0f, 135.0f), Vector2(0.0f, 0.0f), 7, 5, 35, 0.10f);


		sculptor_Animator->Play(L"sculptor_idle", true);


		SpriteRenderer* sculptor_sr = sculptor_obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> sculptor_mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> sculptor_mt = Resources::Find<Material>(L"SpriteMaterial");
		sculptor_sr->SetMesh(sculptor_mesh);
		sculptor_sr->SetMaterial(sculptor_mt);
		SculptorScript* SculptorSc = sculptor_obj->AddComponent<SculptorScript>();
		SculptorSc->setmGameObject(gameplayer);
			
#pragma endregion


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
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
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
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
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
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
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
			UI_SpellRect_ani->Create(L"UI_Spell", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
			UI_SpellRect_ani->Create(L"UI_Spell2", UI_Spell, Vector2(0.0f, 0.0f), Vector2(99.0f, 151.0f), Vector2::Zero, 5, 5, 24, 0.05f);
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

		//GrandPa HP




#pragma endregion
		

#pragma region 이벤트 콜라이더 설정 모음
		//이벤트 수직 선
		GameObject* event_line = object::Instantiate<GameObject>(eLayerType::EventObjectLine);
		event_line->SetName(L"event_Line");

		Transform* event_Line_tr = event_line->GetComponent<Transform>();
		event_Line_tr->SetPosition(Vector3(7.51f, 1.0f, 5.0f));


		Collider2D* event_Line_col = event_line->AddComponent<Collider2D>();
		event_Line_col->SetType(eColliderType::Rect);
		event_Line_col->SetSize(Vector2(0.01f, 7.f));
		event_Line_col->SetCenter(Vector2(0.7f, 0.0f));

		event_Line_Sc* event_line_Sc = event_line->AddComponent<event_Line_Sc>();
		//event_line_Sc->setmGameObject(cameraObj);

		//첫번째카메라 무빙하기위한 콜라이더
		GameObject* firstCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		firstCameraMoveLine->SetName(L"firstCameraMoveLine");

		Transform* firstCameraMoveLine_tr = firstCameraMoveLine->GetComponent<Transform>();
		firstCameraMoveLine_tr->SetPosition(Vector3(7.5f, 1.0f, 5.0f));

		Collider2D* firstCameraMoveLine_col = firstCameraMoveLine->AddComponent<Collider2D>();
		firstCameraMoveLine_col->SetType(eColliderType::Rect);
		firstCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		firstCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		firstCameraMoveLine_Script* firstCameraMoveLineSc = firstCameraMoveLine->AddComponent<firstCameraMoveLine_Script>();
		firstCameraMoveLineSc->setmGameObject(cameraObj);


		//첫번째카메라 멈추기 위한 콜라이더
		GameObject* firstCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop);
		firstCameraStopLine->SetName(L"firstCameraStopLine");

		Transform* firstCameraStopLine_tr = firstCameraStopLine->GetComponent<Transform>();
		firstCameraStopLine_tr->SetPosition(Vector3(23.5f, 1.0f, 5.0f));

		Collider2D* firstCameraStopLine_col = firstCameraStopLine->AddComponent<Collider2D>();
		firstCameraStopLine_col->SetType(eColliderType::Rect);
		firstCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		firstCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		firstCameraStopLine_Script* firstCameraStopLineSc = firstCameraStopLine->AddComponent<firstCameraStopLine_Script>();
		firstCameraStopLineSc->SetCamera_Sc(firstCameraMoveLineSc);
		firstCameraStopLineSc->SetGrandPa_Sc(grandpaSc);





		//두번째 이벤트 수직 선
		GameObject* event_line2 = object::Instantiate<GameObject>(eLayerType::EventObjectLine);
		event_line2->SetName(L"event_Line2");

		Transform* event_Line_tr2 = event_line2->GetComponent<Transform>();
		event_Line_tr2->SetPosition(Vector3(23.6f, 1.0f, 5.0f));

		Collider2D* event_Line_col2 = event_line2->AddComponent<Collider2D>();
		event_Line_col2->SetType(eColliderType::Rect);
		event_Line_col2->SetSize(Vector2(0.01f, 7.f));
		event_Line_col2->SetCenter(Vector2(0.7f, 0.0f));

		event_Line2_Sc* event_line_Sc2 = event_line2->AddComponent<event_Line2_Sc>();


		//두번째카메라 무빙하기위한 콜라이더
		GameObject* secondCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		secondCameraMoveLine->SetName(L"secondCameraMoveLine");

		Transform* secondCameraMoveLine_tr = secondCameraMoveLine->GetComponent<Transform>();
		secondCameraMoveLine_tr->SetPosition(Vector3(23.7f, 1.0f, 5.0f));

		Collider2D* secondCameraMoveLine_col = secondCameraMoveLine->AddComponent<Collider2D>();
		secondCameraMoveLine_col->SetType(eColliderType::Rect);
		secondCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		secondCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		secondCameraMoveLine_Script* secondCameraMoveLineSc = secondCameraMoveLine->AddComponent<secondCameraMoveLine_Script>();
		secondCameraMoveLineSc->setmGameObject(cameraObj);


		//두번째카메라 멈추기 위한 콜라이더
		GameObject* secondCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop);
		secondCameraStopLine->SetName(L"secondCameraStopLine");

		Transform* secondCameraStopLine_tr = secondCameraStopLine->GetComponent<Transform>();
		secondCameraStopLine_tr->SetPosition(Vector3(40.5f, 1.0f, 5.0f));

		Collider2D* secondCameraStopLine_col = secondCameraStopLine->AddComponent<Collider2D>();
		secondCameraStopLine_col->SetType(eColliderType::Rect);
		secondCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		secondCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		secondCameraStopLine_Script* secondCameraStopLineSc = secondCameraStopLine->AddComponent<secondCameraStopLine_Script>();
		secondCameraStopLineSc->SetCamera_Sc(secondCameraMoveLineSc);



		//세번째 이벤트 수직 선
		GameObject* event_line3 = object::Instantiate<GameObject>(eLayerType::EventObjectLine2);
		event_line3->SetName(L"event_Line3");

		Transform* event_Line_tr3 = event_line3->GetComponent<Transform>();
		event_Line_tr3->SetPosition(Vector3(40.6f, 1.0f, 5.0f));

		Collider2D* event_Line_col3 = event_line3->AddComponent<Collider2D>();
		event_Line_col3->SetType(eColliderType::Rect);
		event_Line_col3->SetSize(Vector2(0.01f, 7.f));
		event_Line_col3->SetCenter(Vector2(0.7f, 0.0f));

		event_Line3_Sc* event_line_Sc3 = event_line3->AddComponent<event_Line3_Sc>();


		//세번째카메라 무빙하기위한 콜라이더
		GameObject* thirdCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		thirdCameraMoveLine->SetName(L"thirdCameraMoveLine");

		Transform* thirdCameraMoveLine_tr = thirdCameraMoveLine->GetComponent<Transform>();
		thirdCameraMoveLine_tr->SetPosition(Vector3(40.7f, 1.0f, 5.0f));

		Collider2D* thirdCameraMoveLine_col = thirdCameraMoveLine->AddComponent<Collider2D>();
		thirdCameraMoveLine_col->SetType(eColliderType::Rect);
		thirdCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		thirdCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		thirdCameraMoveLine_Script* thirdCameraMoveLineSc = thirdCameraMoveLine->AddComponent<thirdCameraMoveLine_Script>();
		thirdCameraMoveLineSc->setmGameObject(cameraObj);


		//세번째카메라 멈추기 위한 콜라이더
		GameObject* thirdCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop2);
		thirdCameraStopLine->SetName(L"thirdCameraStopLine");

		Transform* thirdCameraStopLine_tr = thirdCameraStopLine->GetComponent<Transform>();
		thirdCameraStopLine_tr->SetPosition(Vector3(58.0f, 1.0f, 5.0f));

		Collider2D* thirdCameraStopLine_col = thirdCameraStopLine->AddComponent<Collider2D>();
		thirdCameraStopLine_col->SetType(eColliderType::Rect);
		thirdCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		thirdCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		thirdCameraStopLine_Script* thirdCameraStopLineSc = thirdCameraStopLine->AddComponent<thirdCameraStopLine_Script>();
		thirdCameraStopLineSc->SetCamera_Sc(thirdCameraMoveLineSc);
		thirdCameraStopLineSc->SetSculptorScript(SculptorSc);

		
		//네번째 이벤트 수직 선
		GameObject* event_line4 = object::Instantiate<GameObject>(eLayerType::EventObjectLine);
		event_line4->SetName(L"event_line4");

		Transform* event_Line_tr4 = event_line4->GetComponent<Transform>();
		event_Line_tr4->SetPosition(Vector3(58.1f, 1.0f, 5.0f));

		Collider2D* event_Line_col4 = event_line4->AddComponent<Collider2D>();
		event_Line_col4->SetType(eColliderType::Rect);
		event_Line_col4->SetSize(Vector2(0.01f, 7.f));
		event_Line_col4->SetCenter(Vector2(0.7f, 0.0f));

		yaevent_Line4_Sc* event_line_Sc4 = event_line4->AddComponent<yaevent_Line4_Sc>();


		//네번째카메라 무빙하기위한 콜라이더
		GameObject* fourthCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		fourthCameraMoveLine->SetName(L"fourthCameraMoveLine");

		Transform* fourthCameraMoveLine_tr = fourthCameraMoveLine->GetComponent<Transform>();
		fourthCameraMoveLine_tr->SetPosition(Vector3(58.2f, 1.0f, 5.0f));

		Collider2D* fourthCameraMoveLine_col = fourthCameraMoveLine->AddComponent<Collider2D>();
		fourthCameraMoveLine_col->SetType(eColliderType::Rect);
		fourthCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		fourthCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		fourthCameraMoveLine_Script* fourthCameraMoveLineSc = fourthCameraMoveLine->AddComponent<fourthCameraMoveLine_Script>();
		fourthCameraMoveLineSc->setmGameObject(cameraObj);


		//네번째카메라 멈추기 위한 콜라이더
		GameObject* fourthCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop);
		fourthCameraStopLine->SetName(L"fourthCameraStopLine");

		Transform* fourthCameraStopLine_tr = fourthCameraStopLine->GetComponent<Transform>();
		fourthCameraStopLine_tr->SetPosition(Vector3(74.0f, 1.0f, 5.0f));

		Collider2D* fourthCameraStopLine_col = fourthCameraStopLine->AddComponent<Collider2D>();
		fourthCameraStopLine_col->SetType(eColliderType::Rect);
		fourthCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		fourthCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		fourthCameraStopLine_Script* fourthCameraStopLineSc = fourthCameraStopLine->AddComponent<fourthCameraStopLine_Script>();
		fourthCameraStopLineSc->SetCamera_Sc(fourthCameraMoveLineSc);
		
		
		
		
		
#pragma endregion



		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player_Attack_Object, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Attack_Object, eLayerType::Player, true);





		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectStart, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectLine, true);
		CollisionManager::CollisionLayerCheck(eLayerType::EventObjectStop, eLayerType::EventObjectLine, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectLine2, true);
		CollisionManager::CollisionLayerCheck(eLayerType::EventObjectStop2, eLayerType::EventObjectLine2, true);



	}
	void MainScene::OnExit()
	{
		audio->Stop();
		gameplayer->Death();
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, false);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectStart, false);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectLine, false);
		CollisionManager::CollisionLayerCheck(eLayerType::EventObjectStop, eLayerType::EventObjectLine, false);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectLine2, false);
		CollisionManager::CollisionLayerCheck(eLayerType::EventObjectStop2, eLayerType::EventObjectLine2, false);

	}
}
