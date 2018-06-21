cmake_minimum_required(VERSION 3.4.1)

# 添加头文件路径（相对于本文件路径）同路径下 include文件夹
include_directories(src/main/cpp/include)

# 设置ffmpeg库所在路径的变量
set(FF ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})
# 添加一个标签库
add_library(avcodec SHARED IMPORTED)
# 设置参数
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FF}/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FF}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FF}/libavutil.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FF}/libswscale.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FF}/libswresample.so)

add_library( native-lib SHARED

             src/main/cpp/native-lib.cpp
              src/main/cpp/FFmpeg.cpp
              src/main/cpp/JavaMethod.cpp
              src/main/cpp/Audio.cpp)

# 链接avcodec到native-lib库中，否则在native-lib.cpp中调用函数会报链接无效
target_link_libraries( # Specifies the target library.
                       native-lib
                        android
                        avcodec avformat avutil swscale swresample
                       # Links the target library to the log library
                       # included in the NDK.
                       log )