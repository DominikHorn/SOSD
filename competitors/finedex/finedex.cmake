include(FetchContent)
set(FINEDEX_LIBRARY finedex-sosd)
FetchContent_Declare(
  ${FINEDEX_LIBRARY}
  GIT_REPOSITORY https://github.com/DominikHorn/FINEdex-sosd.git
  GIT_TAG 3afdb86
  )
FetchContent_MakeAvailable(${FINEDEX_LIBRARY})