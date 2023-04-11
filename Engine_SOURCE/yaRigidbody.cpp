#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaGameObject.h"

namespace ya {
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.5f)
		, mFriction(0.5f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 1000.f;
		mbGround = true;
		mGravity = Vector2(0.0f, 800.0f);
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initalize()
	{
	}
	void Rigidbody::Update()
	{
	}
	void Rigidbody::FixedUpdate()
	{
		//�̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot =  Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}




		// �ִ� �ӵ� ����
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = ya::math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		////������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// �ӵ��� �ݴ� �������� �������� ����
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

		//	// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		// �ӵ��� 0 �� �����.
		//		mVelocity = Vector2(0.f, 0.f);
		//	}
		//	else
		//	{
		//		// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
		//		mVelocity += friction;
		//	}
		//}

		//�ӵ��� �°� �̵���Ų��
		Transform* rigidbody2 = GetOwner()->GetComponent<Transform>();
		Vector3 pos = rigidbody2->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		rigidbody2->SetPosition(pos);
	}
	void Rigidbody::Render()
	{
	}
	void Rigidbody::AddForce(Vector2 force)
	{
	}
}