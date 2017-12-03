#pragma once

#include <XESystem/SystemConfig.hpp>
#include <XERenderer/Editor/IEditorUIState.hpp>
#include <Ogre/OgreMain/include/OgreString.h>
#include <Ogre/OgreMain/include/OgreVector3.h>

#include <memory>

namespace XE {

	struct EditorComponent
	{
	public:
		Uint32 id;
		std::string name;

		void UpdateTransform(Ogre::Matrix4 delta);
	};

	struct DisplayInformation
	{
	public:
		Ogre::String name;
	};

	struct DisplayBody : public DisplayInformation {
	public:
		Ogre::Vector3 position;
	};

	struct EntityDebug
	{
	public:
		XE::Int32 id;

		//display data
		std::unique_ptr<DisplayInformation> displayInformation;
	};


	class Scene;
	class GraphicsManager;

	class SceneViewerUIState : public IEditorUIState {

	public:
		SceneViewerUIState(const GraphicsManager& graphicsMgr, const Scene& scene);

		void render();

		std::vector<std::unique_ptr<EntityDebug>> _t_displayedEntities;

	private:
		const GraphicsManager& m_graphicsMgr;
		const Scene& m_scene;
	};
}