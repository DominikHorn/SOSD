include(FetchContent)

set(EXOTIC_HASHING_LIBRARY exotic-hashing)
FetchContent_Declare(
  ${EXOTIC_HASHING_LIBRARY}
  GIT_REPOSITORY https://github.com/DominikHorn/exotic-hashing.git
  GIT_TAG 3bd992b
  )
FetchContent_MakeAvailable(${EXOTIC_HASHING_LIBRARY})
