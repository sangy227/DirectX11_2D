#pragma once
#include "yaScene.h"
#include "yaAudioSource.h"
namespace ya
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		AudioSource* audio;
		GameObject* audio_obj;
		AudioSource* P_audio;
	};
}