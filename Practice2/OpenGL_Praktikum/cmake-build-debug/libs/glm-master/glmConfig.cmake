set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "C:/Users/pablo b/CLionProjects/VisualComputing/Practice2/OpenGL_Praktikum/libs/glm-master")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
