#add source
file(GLOB_RECURSE SglToolkit_SRC "*.cpp")
add_library(${LIB_NAME} STATIC ${SglToolkit_SRC})

#target
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
#my glad.h is stored here
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../include)
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME "SglToolkit")