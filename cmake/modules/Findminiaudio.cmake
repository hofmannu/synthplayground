include(FetchContent)

FetchContent_Declare(
    miniaudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
    GIT_TAG 0.11.18
)

FetchContent_GetProperties(miniaudio)
if (NOT miniaudio_POPULATED)
    FetchContent_Populate(miniaudio)
endif()

set(miniaudio_FOUND TRUE)
set(miniaudio_INCLUDE_DIR ${miniaudio_SOURCE_DIR})