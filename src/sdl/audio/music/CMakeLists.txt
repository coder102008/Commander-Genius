
include_directories(${SDL_INCLUDE_DIR})


add_library(sdl_extensions_audio_music CIMFPlayer.cpp CIMFPlayer.h
                                       CMusic.cpp CMusic.h
                                       CMusicPlayer.cpp CMusicPlayer.h
                                       COGGPlayer.cpp COGGPlayer.h)

                                     
# TODO: Does not work with MacOS. Where is the pkgconfig or cmake script
IF(OGG)
  if(WIN32)
    TARGET_LINK_LIBRARIES(sdl_extensions_audio_music vorbisfile vorbis ogg)
  else(WIN32)
    TARGET_LINK_LIBRARIES(sdl_extensions_audio_music vorbis vorbisfile)
  endif(WIN32)
ENDIF(OGG)
                                     
IF(TREMOR)
  TARGET_LINK_LIBRARIES(sdl_extensions_audio_music vorbisidec)
ENDIF(TREMOR)




if(USE_SDL2)
    LINK_DIRECTORIES(${SDL_MIXER_LIBRARY_DIRS})
    target_link_libraries(sdl_extensions_audio_music
                          ${SDL_MIXER_LIBRARY})
else(USE_SDL2)
    LINK_DIRECTORIES(${SDL2_MIXER_LIBRARY_DIRS})
    target_link_libraries(sdl_extensions_audio_music
                          ${SDL2_MIXER_LIBRARY})
endif(USE_SDL2)

