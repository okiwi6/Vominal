cmake_minimum_required(VERSION 3.0.0)
project(curse_test VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")


# echo(${SFML_INCLUDE_DIR})
# include_directories(${SFML_INCLUDE_DIR})

set(SFML_DIR "/opt/vcpkg/installed/x64-linux/share/sfml")
find_package(SFML 2.5 COMPONENTS system audio network REQUIRED)

set(SOURCE
    src/window/terminal_window.cpp
    src/ui/layout.cpp
    src/primitives/primitives.cpp
    src/ui/SelectableStringList.cpp
    src/audio/Recorder.cpp
    src/audio/OutputStream.cpp
    src/audio/SoundManager.cpp
)


add_executable(curse_test src/main.cpp ${SOURCE})
add_executable(audio_test src/audiotest.cpp ${SOURCE})

target_link_libraries(audio_test PRIVATE sfml-system sfml-audio -lncurses)
target_link_libraries(curse_test PRIVATE sfml-system sfml-audio -lncurses)

# 