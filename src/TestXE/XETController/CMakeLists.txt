
# XETController

# --------------------------- Common Files for Testproject ----------------
set(TESTCOMMONROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETCommon)

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETUI)

set(XETCommon_SOURCES
    ${TESTCOMMONROOT}/TestPostProcess.cpp
	${TESTCOMMONROOT}/TestScene.cpp
    ${TESTCOMMONROOT}/TestControllerSystem.cpp
    ${TESTCOMMONROOT}/Controllers_generated.h
    ${TESTCOMMONROOT}/Netmsg_generated.h
	${TESTCOMMONROOT}/TestDAL.cpp
	${TESTCOMMONROOT}/TestController.cpp	
	${TESTCOMMONROOT}/EditorControllerSystem.cpp
   #	${SRCROOT}/GUI.h
)
source_group("src\\common" FILES ${XETCommon_SOURCES})

# all header files
set(XETCommon_HEADER
    ${TESTCOMMONROOT}/TestController.hpp
    ${TESTCOMMONROOT}/TestScene.hpp
	${TESTCOMMONROOT}/TestPostProcess.hpp
	${TESTCOMMONROOT}/TestDAL.hpp
	${TESTCOMMONROOT}/TestControllerSystem.hpp
	${TESTCOMMONROOT}/EditorControllerSystem.hpp
)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include\\common" FILES ${XETCommon_HEADER})

# --------------------------- End Common Files for Testproject ----------------

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TestXE/XETController)

# all source files
set(XETController_SOURCES
    ${SRCROOT}/main.cpp
	${SRCROOT}/ControllerState.cpp
)
source_group("src" FILES ${XETController_SOURCES})

# all header files
set(XETController_HEADER
	${SRCROOT}/ControllerState.hpp
#	${SRCROOT}/TestScene.h
)

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XETController_HEADER})

# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
#add_executable (XETController ${XETController_SOURCES} ${XETController_HEADER})


# Properties->Linker->Controller->Additional Dependencies
#target_link_libraries (XETController XEngine)

##
# find libraries
 #       find_sfml_dependency(PHYSFS_LIBRARY "physfs" "physfs")
      



# Adds logic to INSTALL.vcproj to copy math.dll to destination directory
#install (TARGETS XETController
#         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

# find OpenGL and GLU
#find_package(physfs REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIR})

  
#find_sfml_dependency(SNDFILE_LIBRARY "libsndfile" physfs)

######set(ADDITIONAL_LIBRARIES XEGraphics ${PHYSFSFILE_LIBRARY}) #${SNDFILE_LIBRARY}) #${OPENGL_LIBRARIES})

# define the opengl target
sfml_add_example(XETController GUI_APP
                 SOURCES ${XETController_SOURCES} ${XETController_HEADER} ${XETCommon_HEADER} ${XETCommon_SOURCES}
                 DEPENDS XEngine ${XEngine_EXT_LIBS} )


#if (WIN32) # win32 is not the build platform! its just the windows identifier
#	message(STATUS  "FMOD WIN32 not supported") 
	#  set (dllSrc  ${PROJECT_SOURCE_DIR}/extlibs/bin/x86/test.dll)
#else() 
	set (dllSrc	${PROJECT_SOURCE_DIR}/extlibs/bin/x64/fmodL64.dll)
#endif()

message(STATUS  "FMOD source dll: " ${dllSrc})

#http://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
add_custom_command(TARGET XETController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${dllSrc}
        $<TARGET_FILE_DIR:XETController>)
# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
#set_property(TARGET XETController PROPERTY FOLDER "Tests")

