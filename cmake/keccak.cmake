INCLUDE(FetchContent)
FETCHCONTENT_DECLARE(
        Keccak
        GIT_REPOSITORY https://github.com/herculas/Keccak
        GIT_TAG main
)

FETCHCONTENT_MAKEAVAILABLE(Keccak)