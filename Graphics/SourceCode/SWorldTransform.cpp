#include "SWorldTransform.h"

SWorldTransform::SWorldTransform()
{
}

SWorldTransform::~SWorldTransform()
{
}

void SWorldTransform::SetPosition(float x, float y, float z)
{
	m_Position = Vector3f(x, y, z);
}

void SWorldTransform::SetScale(float scale)
{
	m_Scale = scale;
}

void SWorldTransform::SetRotation(float x, float y, float z)
{
	m_Rotation = Vector3f(x, y, z);
}

void SWorldTransform::Rotate(float x, float y, float z)
{
	m_Rotation.x += x;
	m_Rotation.y += y;
	m_Rotation.z += z;
}

Matrix4f SWorldTransform::GetMatrix()
{
	Matrix4f scale;
	scale.InitScaleTransform(m_Scale, m_Scale, m_Scale);

	Matrix4f rotation;
	rotation.InitRotateTransform(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	Matrix4f translation;
	translation.InitTranslationTransform(m_Position);

	Matrix4f worldTransformation = translation * rotation * scale;
	return worldTransformation;
}