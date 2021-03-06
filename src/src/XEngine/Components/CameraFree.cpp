#include <XEngine/Components/CameraFree.hpp>

#include <XEngine/Components/Body.hpp>
#include <XERenderer/CameraRenderable.hpp>

namespace XE
{
	CameraFreeComponent::CameraFreeComponent(CameraRenderable& cameraRenderable, BodyComponent& bodyComponent)
		: _cameraRenderable(cameraRenderable)
		, m_SpeedModifier(false)
		, mTopSpeed(150)
		, mFastMove(false)
		, _isDirty(false)
		, _cameraBodyNode(bodyComponent)
		, m_CameraYaw(0)
		, m_CameraPitch(0)
		, m_freezed(false)
	{
		//_cameraRenderable.setAutoTracking(false);
		_cameraBodyNode.setFixedYawAxis(true);
	}

	CameraFreeComponent::~CameraFreeComponent()
	{
	}

	void CameraFreeComponent::IsDirty(bool isDirty) {
		_isDirty = isDirty;
		_cameraBodyNode.isDirty(false);
	}

	bool CameraFreeComponent::IsDirty() {
		return _cameraBodyNode.isDirty() || _isDirty ? true : false;
	}

	void CameraFreeComponent::rotate(float x, float y)
	{
		if (m_freezed)
			return;

		m_CameraYaw += x;
		m_CameraPitch += y;

		_isDirty = true;
	}
}