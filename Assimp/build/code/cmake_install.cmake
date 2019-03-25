# Install script for directory: E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/Debug/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/Release/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/MinSizeRel/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/RelWithDebInfo/assimp-vc140-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/Debug/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/Release/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/MinSizeRel/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/RelWithDebInfo/assimp-vc140-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/anim.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/ai_assert.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/camera.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/color4.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/color4.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/../include/assimp/config.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/defs.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Defines.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/cfileio.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/light.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/material.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/material.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/matrix3x3.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/matrix3x3.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/matrix4x4.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/matrix4x4.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/mesh.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/postprocess.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/quaternion.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/quaternion.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/scene.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/metadata.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/texture.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/types.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/vector2.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/vector2.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/vector3.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/vector3.inl"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/version.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/cimport.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/importerdesc.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Importer.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/DefaultLogger.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/ProgressHandler.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/IOStream.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/IOSystem.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Logger.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/LogStream.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/NullLogger.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/cexport.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Exporter.hpp"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/DefaultIOStream.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/DefaultIOSystem.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/SceneCombiner.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Compiler/pushpack1.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Compiler/poppack1.h"
    "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/Debug/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/Projects/C++/SKNI_KOD_OGL_TEMPLATE/Assimp/build/code/RelWithDebInfo/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

