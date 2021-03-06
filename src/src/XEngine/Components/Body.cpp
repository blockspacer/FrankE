#include <XEngine/Components/Body.hpp>

#include <ThirdParty/plog/Log.h>

namespace XE
{
	BodyComponent::BodyComponent()
		: m_bodyDirection(0, 0, 0)
		, m_bodyGoalDirection(1, 0, 0, 0)
		, m_parent(nullptr)
		, mYawFixed(true)
		, mYawFixedAxis(Ogre::Vector3::UNIT_Y)
		,mPosition(0,0,0),
		 _isDirty(true)	
		, isSelected(false)
		,_isNetIDDirty(true)
		,mOrientation(1,0,0,0),
		mScale(1,1,1),
		mDerivedPosition(0,0,0),
		mDerivedOrientation(1,0,0,0),
		mDerivedScale(1,1,1),
		mDerivedTransform(),
		mInheritOrientation(true),
		mInheritScale(true)
		, m_hasTargetPosition(false)
#ifdef CompileEditor
		, _t_nodeScaleStart(Ogre::Vector3::ZERO)
#endif
	{
	}

	BodyComponent::BodyComponent(const XFBType::BodyComponent* transform)
		:
		m_bodyDirection(0, 0, 0)
		, m_bodyGoalDirection(1, 0, 0, 0)
		, mYawFixed(true)
		, mYawFixedAxis(Ogre::Vector3::UNIT_Y)
		,mPosition(0, 0, 0),
		mOrientation(1, 0, 0, 0),
		mScale(1, 1, 1),
		mDerivedPosition(0, 0, 0),
		mDerivedOrientation(1, 0, 0, 0),
		mDerivedScale(1, 1, 1),
		mDerivedTransform(),
		mInheritOrientation(true),
		mInheritScale(true)
		,_isDirty(true)
		, isSelected(false)
		, _isNetIDDirty(true)
		, m_parent(nullptr)
		, m_hasTargetPosition(false)
	{
		setPosition(transform->position()->x(), transform->position()->y(), transform->position()->z());

		setScale(transform->scale()->x(), transform->scale()->y(), transform->scale()->z());

		setOrientation(Ogre::Quaternion::IDENTITY);
		pitch(Ogre::Degree(transform->rotation()->x() * -1));
		yaw(Ogre::Degree(transform->rotation()->y() * -1));
		roll(Ogre::Degree(transform->rotation()->z() * -1));

	//	setOrientation(transform->rotation()->w(), transform->rotation()->x(), transform->rotation()->y(), transform->rotation()->z());
	}

	BodyComponent::~BodyComponent()
	{

	}

	const Ogre::Vector3& BodyComponent::getTargetDirection() {
		return m_targetDirection;
	}
	void BodyComponent::setTargetDirection(const Ogre::Vector3& direction) {
		m_targetDirection = direction;
	}
	 Ogre::Real BodyComponent::getTargetDistance() {
		return m_targetDistance;
	}
	void BodyComponent::setTargetDistance(Ogre::Real distance) {
		m_targetDistance = distance;
	}
	const Ogre::Vector3& BodyComponent::getTargetPosition() {
		return m_targetPosition;
	}

	const Ogre::Matrix4& BodyComponent::GetWorldTransform() const
	{
		//m00 * scale.x
		//chunkBase[1] = _mm_mul_ps(chunkBase[1], scaleChunkBase[1]);   //m01 * scale.y
		//chunkBase[2] = _mm_mul_ps(chunkBase[2], scaleChunkBase[2]);   //m02 * scale.z
		//chunkBase[3] = posChunkBase[0];                                //m03 * pos.x

		//chunkBase[4] = _mm_mul_ps(chunkBase[4], scaleChunkBase[0]);   //m10 * scale.x
		//chunkBase[5] = _mm_mul_ps(chunkBase[5], scaleChunkBase[1]);   //m11 * scale.y
		//chunkBase[6] = _mm_mul_ps(chunkBase[6], scaleChunkBase[2]);   //m12 * scale.z
		//chunkBase[7] = posChunkBase[1];                                //m13 * pos.y0

		//chunkBase[8] = _mm_mul_ps(chunkBase[8], scaleChunkBase[0]);   //m20 * scale.x
		//chunkBase[9] = _mm_mul_ps(chunkBase[9], scaleChunkBase[1]);   //m21 * scale.y
		//chunkBase[10] = _mm_mul_ps(chunkBase[10], scaleChunkBase[2]);   //m22 * scale.z
		//chunkBase[11] = posChunkBase[2];                                //m23 * pos.z

	//	Ogre::Matrix4();
		Ogre::Matrix3 kRot;
		mOrientation.ToRotationMatrix(kRot);
			
		const Ogre::Matrix3 kRotScaled( kRot[0][0] * mScale.x, kRot[0][1] * mScale.y, kRot[0][2] * mScale.z
								, kRot[1][0] * mScale.x, kRot[1][1] * mScale.y, kRot[1][2] * mScale.z
								, kRot[2][0] * mScale.x, kRot[2][1] * mScale.y, kRot[2][2] * mScale.z);


		auto debug = Ogre::Matrix4(  kRotScaled[0][0], kRotScaled[0][1], kRotScaled[0][2],
						mPosition.x, kRotScaled[1][0], kRotScaled[1][1], kRotScaled[1][2],
						mPosition.y, kRotScaled[2][0], kRotScaled[2][1], kRotScaled[2][2],
						mPosition.z, 0, 0, 0, 1.0);
			//, mPosition,		
		//	mOrientation, mScale
		
	//	LOG(plog::info) << "body-trans:" << debug;

		return debug;
	}
	
	void BodyComponent::setTargetPosition(const Ogre::Vector3& targetPosition) {
		
		setHasTargetPosition(true);

		m_targetPosition = targetPosition;
		
		m_targetDirection = m_targetPosition - getPosition();
		m_targetDistance = m_targetDirection.normalise();

		Ogre::Vector3 mDirection = getTargetPosition() - getPosition();
		Ogre::Vector3 src = getOrientation() * Ogre::Vector3::UNIT_Z;
		src.y = 0;
		mDirection.y = 0;
		Ogre::Real mDistance = mDirection.normalise();
		Ogre::Quaternion quat = src.getRotationTo(mDirection);
		rotate(quat);
	}

	bool BodyComponent::hasTargetPosition() {
		return m_hasTargetPosition;
	}

	void BodyComponent::setHasTargetPosition(bool hasTargetPosition) {
		m_hasTargetPosition = hasTargetPosition;
	}


	void BodyComponent::isDirty(bool isDirty)
	{
		_isDirty = isDirty;

		if(isDirty)
			_isNetIDDirty = true; //only set to false in serversystem!

		for each (auto& child in m_children)
		{
			child->isDirty(_isDirty);
		}
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setFixedYawAxis(bool useFixed, const Ogre::Vector3& fixedAxis)
	{
		mYawFixed = useFixed;
		mYawFixedAxis = fixedAxis;
	}

	//-----------------------------------------------------------------------
	void BodyComponent::yaw(const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		if (mYawFixed)
		{
			rotate(mYawFixedAxis, angle, relativeTo);
		}
		else
		{
			rotate(Ogre::Vector3::UNIT_Y, angle, relativeTo);
		}

	}
	//-----------------------------------------------------------------------
	void BodyComponent::setDirection(Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo,
		const Ogre::Vector3& localDirectionVector)
	{
		setDirection(Ogre::Vector3(x, y, z), relativeTo, localDirectionVector);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setDirection(const Ogre::Vector3& vec, TransformSpace relativeTo,
		const Ogre::Vector3& localDirectionVector)
	{
		// Do nothing if given a zero vector
		if (vec == Ogre::Vector3::ZERO) return;

		_updateFromParent();

		// The direction we want the local direction point to
		Ogre::Vector3 targetDir = vec.normalisedCopy();

		const bool inheritOrientation = mInheritOrientation;

		// Transform target direction to world space
		switch (relativeTo)
		{
		case TS_PARENT:
			if (inheritOrientation)
			{
				if (m_parent)
				{
					targetDir = m_parent->_getDerivedOrientation() * targetDir;
				}
			}
			break;
		case TS_LOCAL:
			targetDir = _getDerivedOrientation() * targetDir;
			break;
		case TS_WORLD:
			// default orientation
			break;
		}

		// Calculate target orientation relative to world space
		Ogre::Quaternion targetOrientation;
		if (mYawFixed)
		{
			// Calculate the quaternion for rotate local Z to target direction
			Ogre::Vector3 xVec = mYawFixedAxis.crossProduct(targetDir);
			xVec.normalise();
			Ogre::Vector3 yVec = targetDir.crossProduct(xVec);
			yVec.normalise();
			Ogre::Quaternion unitZToTarget = Ogre::Quaternion(xVec, yVec, targetDir);

			if (localDirectionVector == Ogre::Vector3::NEGATIVE_UNIT_Z)
			{
				// Specail case for avoid calculate 180 degree turn
				targetOrientation =
					Ogre::Quaternion(-unitZToTarget.y, -unitZToTarget.z, unitZToTarget.w, unitZToTarget.x);
			}
			else
			{
				// Calculate the quaternion for rotate local direction to target direction
				Ogre::Quaternion localToUnitZ = localDirectionVector.getRotationTo(Ogre::Vector3::UNIT_Z);
				targetOrientation = unitZToTarget * localToUnitZ;
			}
		}
		else
		{
			const Ogre::Quaternion& currentOrient = _getDerivedOrientation();

			// Get current local direction relative to world space
			Ogre::Vector3 currentDir = currentOrient * localDirectionVector;

			if ((currentDir + targetDir).squaredLength() < 0.00005f)
			{
				// Oops, a 180 degree turn (infinite possible rotation axes)
				// Default to yaw i.e. use current UP
				targetOrientation =
					Ogre::Quaternion(-currentOrient.y, -currentOrient.z, currentOrient.w, currentOrient.x);
			}
			else
			{
				// Derive shortest arc to new direction
				Ogre::Quaternion rotQuat = currentDir.getRotationTo(targetDir);
				targetOrientation = rotQuat * currentOrient;
			}
		}

		// Set target orientation, transformed to parent space
		if (m_parent && inheritOrientation)
			setOrientation(m_parent->_getDerivedOrientation().UnitInverse() * targetOrientation);
		else
			setOrientation(targetOrientation);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::lookAt(const Ogre::Vector3& targetPoint, TransformSpace relativeTo,
		const Ogre::Vector3& localDirectionVector)
	{
		// Calculate ourself origin relative to the given transform space
		Ogre::Vector3 origin;
		switch (relativeTo)
		{
		default:    // Just in case
		case TS_WORLD:
			origin = _getDerivedPosition();
			break;
		case TS_PARENT:
			origin = mPosition; // ->getAsOgre::Vector3(origin, mIndex);
			break;
		case TS_LOCAL:
			origin = Ogre::Vector3::ZERO;
			break;
		}

		setDirection(targetPoint - origin, relativeTo, localDirectionVector);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::_updateFromParent(void)
	{
		if (m_parent)
			m_parent->_updateFromParent();

		updateFromParentImpl();
	}
	//-----------------------------------------------------------------------
	void BodyComponent::updateFromParentImpl(void)
	{
		if (!isDirty())
			return;

		if (!m_parent)
		{
			mDerivedPosition = mPosition;
			mDerivedOrientation = mOrientation;
			mDerivedScale = mScale;
		}
		else
		{
			// Scale own position by parent scale, NB just combine
			// as equivalent axes, no shearing
			mDerivedScale = m_parent->mDerivedScale * (mScale);

			// Combine orientation with that of parent
			mDerivedOrientation = m_parent->mDerivedOrientation * (mOrientation);

			// Change position vector based on parent's orientation & scale
			mDerivedPosition = m_parent->mDerivedOrientation * (m_parent->mDerivedScale * (mPosition));

			// Add altered position vector to parents
			mDerivedPosition += m_parent->mDerivedPosition;

		}
	
		isDirty(false);
	}

	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::getOrientation() const
	{
		return mOrientation;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setOrientation(Ogre::Quaternion q)
	{
		assert(!q.isNaN() && "Invalid orientation supplied as parameter");
		q.normalise();
		mOrientation = q;

		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setOrientation(Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		setOrientation(Ogre::Quaternion(w, x, y, z));
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setPosition(const Ogre::Vector3& pos)
	{
		assert(!pos.isNaN() && "Invalid vector supplied as parameter");
		mPosition = pos;

		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		setPosition(Ogre::Vector3(x, y, z));
	}
	//-----------------------------------------------------------------------
	const Ogre::Vector3& BodyComponent::getPosition(void) const
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------
	Ogre::Matrix3& BodyComponent::getLocalAxes(void) const
	{
		Ogre::Matrix3 retVal;
		mOrientation.ToRotationMatrix(retVal);

		/* Equivalent code (easier to visualize):
		axisX = q.xAxis();
		axisY = q.yAxis();
		axisZ = q.zAxis();

		return Matrix3(axisX.x, axisY.x, axisZ.x,
		axisX.y, axisY.y, axisZ.y,
		axisX.z, axisY.z, axisZ.z);*/

		return retVal;
	}

	//-----------------------------------------------------------------------
	void BodyComponent::translate(const Ogre::Vector3& d, TransformSpace relativeTo)
	{
		switch (relativeTo)
		{
		case TS_LOCAL:
			// position is relative to parent so transform downwards
			mPosition += mOrientation * d;
			break;
		case TS_WORLD:
			// position is relative to parent so transform upwards
			if (m_parent)
			{
				mPosition += (m_parent->_getDerivedOrientation().Inverse() * d) / m_parent->_getDerivedScale();
			}
			else
			{
				mPosition += d;
			}
			break;
		case TS_PARENT:
			mPosition += d;
			break;
		}		

		isDirty(true);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::translate(Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo)
	{
		Ogre::Vector3 v(x, y, z);
		translate(v, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::translate(const Ogre::Matrix3& axes, const Ogre::Vector3& move, TransformSpace relativeTo)
	{
		Ogre::Vector3 derived = axes * move;
		translate(derived, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::translate(const Ogre::Matrix3& axes, Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo)
	{
		Ogre::Vector3 d(x, y, z);
		translate(axes, d, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::roll(const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		rotate(Ogre::Vector3::UNIT_Z, angle, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::pitch(const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		rotate(Ogre::Vector3::UNIT_X, angle, relativeTo);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		Ogre::Quaternion q;
		q.FromAngleAxis(angle, axis);
		rotate(q, relativeTo);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::rotate(const Ogre::Quaternion& q, TransformSpace relativeTo)
	{
		// Normalise quaternion to avoid drift
		Ogre::Quaternion qnorm = q;
		qnorm.normalise();

		switch (relativeTo)
		{
		case TS_PARENT:
			// Rotations are normally relative to local axes, transform up
			mOrientation = qnorm * mOrientation;
			break;
		case TS_WORLD:
			// Rotations are normally relative to local axes, transform up
			mOrientation = mOrientation * _getDerivedOrientation().Inverse()
				* qnorm * _getDerivedOrientation();
			break;
		case TS_LOCAL:
			// Note the order of the mult, i.e. q comes after
			mOrientation = mOrientation * qnorm;
			break;
		}	

		isDirty(true);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::_setDerivedPosition(const Ogre::Vector3& pos)
	{
		//find where the node would end up in parent's local space
		if (m_parent)
			setPosition(m_parent->convertWorldToLocalPosition(pos));
	}
	//-----------------------------------------------------------------------
	void BodyComponent::_setDerivedOrientation(const Ogre::Quaternion& q)
	{
		//find where the node would end up in parent's local space
		if (m_parent)
			setOrientation(m_parent->convertWorldToLocalOrientation(q));
	}

	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::_getDerivedOrientation(void) const
	{
		
		return mDerivedOrientation;
	}
	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::_getDerivedOrientationUpdated(void)
	{
		_updateFromParent();
		return mDerivedOrientation;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedPosition(void) const
	{
		
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedPositionUpdated(void)
	{
		_updateFromParent();
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedScale(void) const
	{
		
		return mDerivedScale;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedScaleUpdated(void)
	{
		_updateFromParent();
		return mDerivedScale;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::convertWorldToLocalPosition(const Ogre::Vector3 &worldPos)
	{
		return mDerivedOrientation.Inverse() * (worldPos - (mDerivedPosition)) / (mDerivedScale);
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::convertLocalToWorldPosition(const Ogre::Vector3 &localPos)
	{
		return ((mDerivedOrientation)* (localPos * (mDerivedScale)) ) + (mDerivedPosition);
	}

	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::convertWorldToLocalOrientation(const Ogre::Quaternion &worldOrientation)
	{
		return mDerivedOrientation.Inverse() * worldOrientation;
	}
	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::convertLocalToWorldOrientation(const Ogre::Quaternion &localOrientation)
	{

		return mDerivedOrientation * localOrientation;
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setScale(const Ogre::Vector3& inScale)
	{
		assert(!inScale.isNaN() && "Invalid vector supplied as parameter");
		mScale = inScale;	

		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		setScale(Ogre::Vector3(x, y, z));
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::getScale(void) const
	{
		return mScale;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setInheritOrientation(bool inherit)
	{
		mInheritOrientation = inherit;
		
	}
	//-----------------------------------------------------------------------
	bool BodyComponent::getInheritOrientation(void) const
	{
		return mInheritOrientation;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setInheritScale(bool inherit)
	{
		mInheritScale = inherit;
		
	}
	//-----------------------------------------------------------------------
	bool BodyComponent::getInheritScale(void) const
	{
		return mInheritScale;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::scale(const Ogre::Vector3& inScale)
	{
		mScale *= inScale;
		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::scale(Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		scale(Ogre::Vector3(x, y, z));
	}
}