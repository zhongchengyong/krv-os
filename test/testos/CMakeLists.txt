file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testos ${SRCS})

TARGET_LINK_LIBRARIES(testos
        libgtest
        libgmock
        )

add_test(NAME testos
        COMMAND testos)
