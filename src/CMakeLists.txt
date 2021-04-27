aux_source_directory(. OS_SRC)
if(DEFINED ENV{BOOST_ROOT_1_72_0})
    message($ENV{BOOST_ROOT_1_72_0})
    file(TO_CMAKE_PATH $ENV{BOOST_ROOT_1_72_0} CMAKE_BOOST_ROOT)
    list(APPEND BOOST_ROOT "$ENV{CMAKE_BOOST_ROOT}")
    list(APPEND Boost_INCLUDE_DIRS "$ENV{CMAKE_BOOST_ROOT}/boost/include")
    list(APPEND Boost_LIB_DIRS "$ENV{CMAKE_BOOST_ROOT}/lib")
endif()
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} )
add_library(libos STATIC ${OS_SRC})

# Specify here the include directories exported by this library
target_include_directories(libos PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${OS_SRC})
