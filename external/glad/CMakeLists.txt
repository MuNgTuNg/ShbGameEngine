add_library( glad
        include/glad/glad.h
        include/KHR/khrplatform.h
        glad.c
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}include)

