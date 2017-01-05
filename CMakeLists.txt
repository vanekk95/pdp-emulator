project(pdpemu)
cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW) # relative pathes given to link_directories

find_package (Qt5Widgets)
find_package (Threads)
find_package (Qt5Sql) 

LIST (APPEND FLAGS_COMMON -m64)

set(SRC_DIR "gui")

list (APPEND DIR_LIST
		cpu
		decode
		emulation
)

foreach (DIR ${DIR_LIST})
	aux_source_directory ("${DIR}" EMULATOR_SOURCES)
endforeach (DIR)	

list (APPEND PdpemuLib_src 
		${SRC_DIR}/process.cpp
		${SRC_DIR}/tablemodel.cpp
		${SRC_DIR}/bitmapwidget.cpp
		${SRC_DIR}/widget.cpp		
		${SRC_DIR}/styleddelegate.cpp
	)

list (APPEND PdpemuLib_hdr 
		${SRC_DIR}/process.h
		${SRC_DIR}/tablemodel.h
		${SRC_DIR}/bitmapwidget.h
		${SRC_DIR}/widget.h		
		${SRC_DIR}/formain.h
		${SRC_DIR}/styleddelegate.h
	)

list (APPEND PdpemuLib_ui 
		${SRC_DIR}/widget.ui
	)

list (APPEND PdpemuBin_src 
		main.cpp
	)


qt5_wrap_cpp(PdpemuLib_hdr_moc ${PdpemuLib_hdr})
qt5_wrap_ui (PdpemuLib_ui_moc  ${PdpemuLib_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})
include_directories (${SRC_DIR})
include_directories (${DIR_LIST})			

add_library (PdpemuLib SHARED 
    ${PdpemuLib_src}
    ${PdpemuLib_hdr_moc}
    ${PdpemuLib_ui_moc}
)

add_library (EMULATOR_LIB SHARED
	${EMULATOR_SOURCES}
)

target_link_libraries (PdpemuLib Qt5::Widgets)
target_link_libraries (PdpemuLib Qt5::Sql)

add_executable(pdpemu ${PdpemuBin_src})

target_link_libraries (pdpemu PdpemuLib)
target_link_libraries (pdpemu ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (pdpemu EMULATOR_LIB)







