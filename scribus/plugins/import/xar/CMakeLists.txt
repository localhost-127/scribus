include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/scribus
)

set(IMPORTXAR_PLUGIN_MOC_CLASSES
#	qtiocompressor.h
	importxar.h
	importxarplugin.h
)

set(IMPORTXAR_PLUGIN_SOURCES
#	qtiocompressor.cpp
	importxar.cpp
	importxarplugin.cpp
)

set(SCRIBUS_IMPORTXAR_PLUGIN "importxar")

QT5_WRAP_CPP(IMPORTXAR_PLUGIN_MOC_SOURCES ${IMPORTXAR_PLUGIN_MOC_CLASSES})

add_library(${SCRIBUS_IMPORTXAR_PLUGIN} MODULE ${IMPORTXAR_PLUGIN_SOURCES} ${IMPORTXAR_PLUGIN_MOC_SOURCES})

target_link_libraries(${SCRIBUS_IMPORTXAR_PLUGIN} ${PLUGIN_LIBRARIES})

if(WANT_PCH)
	target_precompile_headers(${SCRIBUS_IMPORTXAR_PLUGIN} PRIVATE "../../plugins_pch.h")
endif()

install(TARGETS ${SCRIBUS_IMPORTXAR_PLUGIN}
	LIBRARY
	DESTINATION ${PLUGINDIR}
	PERMISSIONS ${PLUGIN_PERMISSIONS}
)

add_dependencies(${SCRIBUS_IMPORTXAR_PLUGIN} ${EXE_NAME})
