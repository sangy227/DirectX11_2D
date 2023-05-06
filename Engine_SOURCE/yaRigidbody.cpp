#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaGameObject.h"

namespace ya {
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(100.0f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 1000.f;
		mbGround = true;
		mGravity = Vector2(0.0f, 110.0f);
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initalize()
	{
	}

	void Rigidbody::Update()
	{

		mAccelation = Vector2(mForce.x / mMass, mForce.y / mMass);

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += Vector2(mAccelation.x * Time::DeltaTime(), mAccelation.y * Time::DeltaTime());

		if (mbGround)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = (gravity.x * mVelocity.x) + (gravity.y * mVelocity.y);
			mVelocity -= Vector2(gravity.x * dot, gravity.y * dot);
		}
		else
		{
			// ���߿� ���� ��
			mVelocity -= Vector2(mGravity.x * Time::DeltaTime(), mGravity.y * Time::DeltaTime());
		}

		// �ִ� �ӵ� ����
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = ((mVelocity.x * gravity.x) + (mVelocity.y * gravity.y));
		gravity *= dot;

		Vector2 sideVelocity = Vector2(mVelocity.x - gravity.x, mVelocity.y - gravity.y);
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
		mVelocity = Vector2(gravity.x + sideVelocity.x, gravity.y + sideVelocity.y);

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		if (!(mVelocity == Vector2::Zero))
		{
			// �ӵ��� �ݴ� �������� �������� ����
			Vector2 friction = -mVelocity;
			friction.Normalize();
			friction *= mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = Vector2(0.0f, 0.0f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity += friction;
			}
		}

		// �ӵ��� �°� ��ü�� �̵���Ų��.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//pos = Vector3(pos.x + mVelocity.x * Time::DeltaTime(), pos.y + mVelocity.y * Time::DeltaTime(), 1.0f);

		//tr->SetPosition(pos);
		//mForce.x = 0;
		//mForce.y = 0;
	}

	void Rigidbody::FixedUpdate()
	{
	}

	void Rigidbody::Render()
	{

	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}