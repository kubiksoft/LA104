cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0025 NEW)
project(LA140_emulator)

set(CMAKE_SUPPRESS_REGENERATION true)
set (CMAKE_CXX_STANDARD 17)

# call "brew install sdl2"

if (ARM)
include_directories("../../os_platform/common/include")
endif()

if (DESKTOP)           	
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#include_directories("include/")
include_directories("../../os_platform/common/include")

file(GLOB main_src 
    "../../os_platform/mac_sdl/source/sdlmain.cpp"
    "../../os_platform/mac_sdl/source/sdlhal.h"
    "../../os_platform/common/include/library.h"
)

file(GLOB bios_src
    "../../os_platform/common/source/bios/*.cpp"
    "../../os_platform/common/source/bios/*.h"
)

file(GLOB framework_src
    "../../os_platform/common/source/framework/*.cpp"
    "../../os_platform/common/source/framework/*.h"
)

endif()

if (ARM)
file(GLOB main_src 
    "../../os_host/source/framework/Wnd.cpp"
)

file(GLOB linker_script
    "../../apps/test41_alchemy/app.lds"
)
endif()

file(GLOB application_src
    "../../apps/test41_alchemy/source/*.cpp"
    "../../apps/test41_alchemy/source/*.h"
)

file(GLOB application_devices_src
    "../../apps/test41_alchemy/source/devices/*.cpp"
    "../../apps/test41_alchemy/source/devices/*.h"
)

file(GLOB application_codecs_src
    "../../apps/test41_alchemy/source/codecs/*.cpp"
    "../../apps/test41_alchemy/source/codecs/*.h"
)

file(GLOB application_layouts_src
    "../../apps/test41_alchemy/source/layouts/*.cpp"
    "../../apps/test41_alchemy/source/layouts/*.h"
)

file(GLOB application_layouts_file_src
    "../../apps/test41_alchemy/source/layouts/file/*.cpp"
    "../../apps/test41_alchemy/source/layouts/file/*.h"
)

file(GLOB application_layouts_meas_src
    "../../apps/test41_alchemy/source/layouts/meas/*.cpp"
    "../../apps/test41_alchemy/source/layouts/meas/*.h"
)

file(GLOB application_layouts_modem_src
    "../../apps/test41_alchemy/source/layouts/modem/*.cpp"
    "../../apps/test41_alchemy/source/layouts/modem/*.h"
)

file(GLOB application_utils_src
    "../../apps/test41_alchemy/source/utils/*.cpp"
    "../../apps/test41_alchemy/source/utils/*.h"
)

file(GLOB application_controls_src
    "../../apps/test41_alchemy/source/controls/*.cpp"
    "../../apps/test41_alchemy/source/controls/*.h"
)

if (DESKTOP)           	

#file(GLOB application_sdl
#    "../os_platform/mac_sdl/sdlmain.cpp"
#    "../os_platform/mac_sdl/sdlhal.h"
#)

source_group("platform\\main" FILES ${main_src})
source_group("platform\\bios" FILES ${bios_src})
source_group("platform\\framework" FILES ${framework_src})
#source_group("source\\gui" FILES ${gui_src})
endif()

source_group("application" FILES ${application_src})
source_group("application\\devices" FILES ${application_devices_src})
source_group("application\\codecs" FILES ${application_codecs_src})
source_group("application\\layouts" FILES ${application_layouts_src})
source_group("application\\layouts\\file" FILES ${application_layouts_file_src})
source_group("application\\layouts\\meas" FILES ${application_layouts_meas_src})
source_group("application\\layouts\\modem" FILES ${application_layouts_modem_src})
source_group("application\\utils" FILES ${application_utils_src})
source_group("application\\controls" FILES ${application_controls_src})
source_group("include" FILES "../../os_platform/common/include")

file(GLOB application_exec
  ${main_src} ${bios_src} ${framework_src} 
  ${gui_src} ${application_src} ${application_devices_src} ${application_codecs_src} 
  ${application_layouts_src} ${application_utils_src} ${application_controls_src} 
  ${application_layouts_file_src} ${application_layouts_meas_src} ${application_layouts_modem_src}
)

add_executable(application ${application_exec})

add_definitions(-DEMULATED)

if (ARM)
target_link_libraries(application m)
target_link_libraries(application bios)
set_target_properties(application PROPERTIES LINK_DEPENDS ${linker_script})
set_target_properties(application PROPERTIES LINK_FLAGS "-T ${linker_script}")
endif()

target_link_libraries(application ${SDL2_LIBRARIES})

install(TARGETS application DESTINATION bin)