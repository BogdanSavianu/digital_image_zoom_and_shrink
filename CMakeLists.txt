cmake_minimum_required(VERSION 3.28)
project(Project)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Project main.cpp
        src/interpolation/resizer/Resizer.cpp
        src/interpolation/resizer/Resizer.h
        src/interpolation/nearest_neighbor/NearestNeighbor.ipp
        src/interpolation/nearest_neighbor/NearestNeighbor.h
        src/tests/RunTests.ipp
        src/tests/RunTests.h
        src/interpolation/bilinear/Bilinear.ipp
        src/interpolation/bilinear/Bilinear.h
        src/interpolation/bicubic/Bicubic.ipp
        src/interpolation/bicubic/Bicubic.h
        src/interpolation/utils/utils.ipp
        src/interpolation/curvature/Curvature.ipp
        src/interpolation/curvature/Curvature.h
        src/tests/benchmark/utils/OperationsCounter.cpp
        src/tests/benchmark/utils/OperationUtility.ipp
        src/tests/benchmark/utils/OperationsCounter.h
        src/tests/benchmark/utils/OperationUtility.h
        src/tests/benchmark/utils/OperationsCounter.cpp
        src/tests/benchmark/utils/OperationUtility.ipp
        src/tests/benchmark/utils/OperationsCounter.h
        src/tests/benchmark/utils/OperationUtility.h
        )

target_link_libraries(Project ${OpenCV_LIBS})
