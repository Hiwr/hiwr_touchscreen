cmake_minimum_required(VERSION 2.8.3)
project(hiwr_touchscreen)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  rospack
  hyve_msg
)


catkin_package(
  CATKIN_DEPENDS roscpp std_msgs rospack hyve_msg
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++0x -pthread") 

add_executable(hiwr_touchscreen src/hiwr_touchscreen.cpp)
target_link_libraries(hiwr_touchscreen ${catkin_LIBRARIES} ts)

