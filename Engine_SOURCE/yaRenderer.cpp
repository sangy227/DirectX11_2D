#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"
#include "yaPaintShader.h"

namespace ya::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	StructedBuffer* lightsBuffer = nullptr;



	void LoadMesh()
	{
#pragma region POINT MESH
		Vertex v = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"PointMesh", pointMesh);
		pointMesh->CreateVertexBuffer(&v, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
#pragma endregion

#pragma region RECT MESH
		//Rect
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion

#pragma region DEBUG RECTMESH
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion

#pragma region CIRCLE MESH
		// Circle Mesh
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;
		
		
		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}
		indexes.clear();
		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		// Crate Mesh
		std::shared_ptr<Mesh> cirlceMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", cirlceMesh);
		cirlceMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		cirlceMesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
	}

	void SetUpState()
	{
#pragma region Input layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddressOf());

#pragma endregion
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;


		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());


#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		
		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
		
#pragma endregion
#pragma region Blend State
		//None
		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadBuffer()
	{
#pragma region CONSTANT BUFFER
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));
#pragma endregion
#pragma region STRUCTED BUFFER
		//Structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::None, nullptr);
#pragma endregion
	}

	void LoadShader()
	{
		// Default
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", shader);

		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		spriteShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);

		// Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);

		// Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);

		// PaintShader
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");

		Resources::Insert<PaintShader>(L"PaintShader", paintShader);

		// Particle Shader
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

		Resources::Insert<Shader>(L"ParticleShader", particleShader);

	}

	void LoadTexture()
	{
#pragma region STATIC TEXTURE
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Smile.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"CartoonSmoke", L"particle\\CartoonSmoke.png");
#pragma endregion

#pragma region DYNAMIC TEXTURE
		//Create //paintTexture 실험용
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE
			| D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);
#pragma endregion

#pragma region USER TEXTURE
		//TitleScene
		//Resources::Load<Texture>(L"TitleBG", L"T_MainMenu_Background.png");
		Resources::Load<Texture>(L"TitleBG", L"bg.png");
		Resources::Load<Texture>(L"TitleLogo", L"T_MainMenu_Title_Moonscars.png");

		//PlayScene
		Resources::Load<Texture>(L"PlayBG_Leyer01", L"PlayBG01.png");
		Resources::Load<Texture>(L"PlayBG_Leyer02", L"PlayBG02.png");
		Resources::Load<Texture>(L"PlayBG_Leyer03", L"PlayBG03.png");

		//MainScene
		Resources::Load<Texture>(L"MainBG_Leyer01", L"MainBG01.png");
		Resources::Load<Texture>(L"MainBG_Leyer02", L"MainBG02.png");
		Resources::Load<Texture>(L"RedQuene_Chair", L"T_NPC_Yadviga_throne_normal.png");

		//UI
		Resources::Load<Texture>(L"Bar_BG", L"UI\\T_UI_HEALT_BAR_BG.png");
		Resources::Load<Texture>(L"Bar_HEALTH", L"UI\\T_UI_HEALTH_BAR.png");
		Resources::Load<Texture>(L"Hammer_icon", L"UI\\T_Icon_Weapon_Hammer_small.png");
		Resources::Load<Texture>(L"Painwheel_icon", L"UI\\T_Icon_Weapon_Painwheel_small.png");
		Resources::Load<Texture>(L"Spear_icon", L"UI\\T_Icon_Weapon_Spear_small.png");
		Resources::Load<Texture>(L"Whirlwind_icon", L"UI\\T_Icon_Weapon_Sword_small.png");
		Resources::Load<Texture>(L"Bar_Boss_BG", L"UI\\T_UI_HealthBar_Boss_Background.png");
		Resources::Load<Texture>(L"Bar_Boss_HEALTH", L"UI\\T_UI_HEALTH_BAR_HURT.png");



#pragma endregion

	}

	void LoadMaterial()
	{
		//TitleSceen
		{
			std::shared_ptr <Texture> titleBGTexture = Resources::Find<Texture>(L"TitleBG");
			std::shared_ptr<Shader> titleBGShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> titleBGMaterial = std::make_shared<Material>();
			titleBGMaterial->SetRenderingMode(eRenderingMode::Transparent);
			titleBGMaterial->SetTexture(eTextureSlot::T0, titleBGTexture);
			titleBGMaterial->SetShader(titleBGShader);
			Resources::Insert<Material>(L"TitleBGMaterial", titleBGMaterial);

			std::shared_ptr <Texture> titleLogoTexture = Resources::Find<Texture>(L"TitleLogo");
			std::shared_ptr<Shader> titleLogoShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> titleLogoMaterial = std::make_shared<Material>();
			titleLogoMaterial->SetRenderingMode(eRenderingMode::Transparent);
			titleLogoMaterial->SetTexture(eTextureSlot::T0, titleLogoTexture);
			titleLogoMaterial->SetShader(titleLogoShader);
			Resources::Insert<Material>(L"TitleLogoMaterial", titleLogoMaterial);
		}

		//PlaySceen
		{
			//PlayBG
			{
				std::shared_ptr <Texture>  playBGTexture01 = Resources::Find<Texture>(L"PlayBG_Leyer01");
				std::shared_ptr<Shader> playBGShader01 = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> playBGMaterial01 = std::make_shared<Material>();
				playBGMaterial01->SetRenderingMode(eRenderingMode::Transparent);
				playBGMaterial01->SetTexture(eTextureSlot::T0, playBGTexture01);
				playBGMaterial01->SetShader(playBGShader01);
				Resources::Insert<Material>(L"playBGMaterial01", playBGMaterial01);

				std::shared_ptr <Texture>  playBGTexture02 = Resources::Find<Texture>(L"PlayBG_Leyer02");
				std::shared_ptr<Shader> playBGShader02 = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> playBGMaterial02 = std::make_shared<Material>();
				playBGMaterial02->SetRenderingMode(eRenderingMode::Transparent);
				playBGMaterial02->SetTexture(eTextureSlot::T0, playBGTexture02);
				playBGMaterial02->SetShader(playBGShader02);
				Resources::Insert<Material>(L"playBGMaterial02", playBGMaterial02);

				std::shared_ptr <Texture>  playBGTexture03 = Resources::Find<Texture>(L"PlayBG_Leyer03");
				std::shared_ptr<Shader> playBGShader03 = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> playBGMaterial03 = std::make_shared<Material>();
				playBGMaterial03->SetRenderingMode(eRenderingMode::Transparent);
				playBGMaterial03->SetTexture(eTextureSlot::T0, playBGTexture03);
				playBGMaterial03->SetShader(playBGShader03);
				Resources::Insert<Material>(L"playBGMaterial03", playBGMaterial03);
			}
		}

		//MainScene
		{
			std::shared_ptr <Texture>  mainBGTexture01 = Resources::Find<Texture>(L"MainBG_Leyer01");
			std::shared_ptr<Shader> mainBGShader01 = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> mainBGMaterial01 = std::make_shared<Material>();
			mainBGMaterial01->SetRenderingMode(eRenderingMode::Transparent);
			mainBGMaterial01->SetTexture(eTextureSlot::T0, mainBGTexture01);
			mainBGMaterial01->SetShader(mainBGShader01);
			Resources::Insert<Material>(L"mainBGMaterial01", mainBGMaterial01);

			std::shared_ptr <Texture>  mainBGTexture02 = Resources::Find<Texture>(L"MainBG_Leyer02");
			std::shared_ptr<Shader> mainBGShader02 = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> mainBGMaterial02 = std::make_shared<Material>();
			mainBGMaterial02->SetRenderingMode(eRenderingMode::Transparent);
			mainBGMaterial02->SetTexture(eTextureSlot::T0, mainBGTexture02);
			mainBGMaterial02->SetShader(mainBGShader02);
			Resources::Insert<Material>(L"mainBGMaterial02", mainBGMaterial02);

			std::shared_ptr <Texture>  chairTexture = Resources::Find<Texture>(L"RedQuene_Chair");
			std::shared_ptr<Shader> chairShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> chairMaterial = std::make_shared<Material>();
			chairMaterial->SetRenderingMode(eRenderingMode::Transparent);
			chairMaterial->SetTexture(eTextureSlot::T0, chairTexture);
			chairMaterial->SetShader(chairShader);
			Resources::Insert<Material>(L"chairMaterial", chairMaterial);
		}


		//UI
		{
			std::shared_ptr <Texture> BarBGTexture = Resources::Find<Texture>(L"Bar_BG");
			std::shared_ptr<Shader> BarBGShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> BarBGMaterial = std::make_shared<Material>();
			BarBGMaterial->SetRenderingMode(eRenderingMode::Transparent);
			BarBGMaterial->SetTexture(eTextureSlot::T0, BarBGTexture);
			BarBGMaterial->SetShader(BarBGShader);
			Resources::Insert<Material>(L"BarBGMaterial", BarBGMaterial);

			std::shared_ptr <Texture> BarHEALTHTexture = Resources::Find<Texture>(L"Bar_HEALTH");
			std::shared_ptr<Shader> BarHEALTHShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> BarHEALTHMaterial = std::make_shared<Material>();
			BarHEALTHMaterial->SetRenderingMode(eRenderingMode::Transparent);
			BarHEALTHMaterial->SetTexture(eTextureSlot::T0, BarHEALTHTexture);
			BarHEALTHMaterial->SetShader(BarHEALTHShader);
			Resources::Insert<Material>(L"BarHEALTHMaterial", BarHEALTHMaterial);

			{
				std::shared_ptr <Texture> Hammer_iconTexture = Resources::Find<Texture>(L"Hammer_icon");
				std::shared_ptr<Shader> Hammer_iconShader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> Hammer_iconMaterial = std::make_shared<Material>();
				Hammer_iconMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Hammer_iconMaterial->SetTexture(eTextureSlot::T0, Hammer_iconTexture);
				Hammer_iconMaterial->SetShader(Hammer_iconShader);
				Resources::Insert<Material>(L"Hammer_iconMaterial", Hammer_iconMaterial);
			}

			{
				std::shared_ptr <Texture> Painwheel_iconTexture = Resources::Find<Texture>(L"Painwheel_icon");
				std::shared_ptr<Shader> Painwheel_iconShader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> Painwheel_iconMaterial = std::make_shared<Material>();
				Painwheel_iconMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Painwheel_iconMaterial->SetTexture(eTextureSlot::T0, Painwheel_iconTexture);
				Painwheel_iconMaterial->SetShader(Painwheel_iconShader);
				Resources::Insert<Material>(L"Painwheel_iconMaterial", Painwheel_iconMaterial);
			}

			{
				std::shared_ptr <Texture> Spear_iconTexture = Resources::Find<Texture>(L"Spear_icon");
				std::shared_ptr<Shader> Spear_iconShader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> Spear_iconMaterial = std::make_shared<Material>();
				Spear_iconMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Spear_iconMaterial->SetTexture(eTextureSlot::T0, Spear_iconTexture);
				Spear_iconMaterial->SetShader(Spear_iconShader);
				Resources::Insert<Material>(L"Spear_iconMaterial", Spear_iconMaterial);
			}

			{
				std::shared_ptr <Texture> Whirlwind_iconTexture = Resources::Find<Texture>(L"Whirlwind_icon");
				std::shared_ptr<Shader> Whirlwind_iconShader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> Whirlwind_iconMaterial = std::make_shared<Material>();
				Whirlwind_iconMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Whirlwind_iconMaterial->SetTexture(eTextureSlot::T0, Whirlwind_iconTexture);
				Whirlwind_iconMaterial->SetShader(Whirlwind_iconShader);
				Resources::Insert<Material>(L"Whirlwind_iconMaterial", Whirlwind_iconMaterial);
			}
		}



		//-----------------------------------------------------------------------------
		// Default //현재 토치라이트 이미지로 쓰이는중
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"SmileTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>(); 
		material->SetShader(shader);
		material->SetTexture(eTextureSlot::T0, texture);
		Resources::Insert<Material>(L"RectMaterial", material);

		// default2 // paintRextur 실험용
		std::shared_ptr <Texture> texture2 = Resources::Find<Texture>(L"PaintTexture");
		std::shared_ptr<Shader> shader2 = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material2 = std::make_shared<Material>();
		material2->SetShader(shader2);
		material2->SetTexture(eTextureSlot::T0, texture2);
		Resources::Insert<Material>(L"RectMaterial2", material2);

		// Sprite
		std::shared_ptr <Texture> spriteTexture= Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(eTextureSlot::T0, spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

		// UI
		std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);

		// Grid
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);

		// Debug
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

		// particle
		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		Resources::Insert<Material>(L"ParticleMaterial", particleMaterial);
	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i]; 
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void Render()
	{
		BindLights();

		//std::vector<Camera*> cameras[(UINT)eSceneType::End];
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->SetData(lights.data(), lights.size());
		lightsBuffer->Bind(eShaderStage::VS, 13);
		lightsBuffer->Bind(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLight = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
}