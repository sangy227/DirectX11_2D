#pragma once
#include "yaScene.h"
#include "yaAudioSource.h"
namespace ya
{
	class MainScene : public Scene
	{
	public:
		MainScene();
		virtual ~MainScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* cameraObj;
		AudioSource* audio[100];
		GameObject* audio_obj[100];
	};
}