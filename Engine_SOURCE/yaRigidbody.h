#pragma once
#include "yaComponent.h"

namespace ya {
	
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }



	private:
		//���� �������� �̿��� �̵��� �߰�
		float mMass;
		float mFriction;

		Vector2 mForce;
		Vector2 mVelocity;
		Vector2 mAccelation;

		//�߷��� �̿��� ����
		Vector2 mGravity;
		bool mbGround;
		Vector2 mLimitVelocity;
	};
}