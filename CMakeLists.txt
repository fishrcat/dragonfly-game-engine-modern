cmake_minimum_required(VERSION 3.24)
project(dragonfly_course LANGUAGES CXX)

add_subdirectory(dragonfly)
# TODO: Re-enable saucer shoot builds when dragonfly library is re-implemented.
# The current `saucer_shoot/.saucer_shoot` executable was built with the complete library example and is playable.
# add_subdirectory(saucer_shoot)
