file(GLOB_RECURSE audio_visualizer_sources "./*.cpp")

add_executable(audio_visualizer ${audio_visualizer_sources})

# include_directories("/usr/include")
include_directories("/usr/local/include")

target_link_libraries(audio_visualizer
	"visualizer"
	"GLU" "glfw3" "X11" "Xxf86vm" "Xrandr" "pthread" "Xi" "dl" "Xinerama" "Xcursor"
	"essentia" "fftw3f" "chromaprint" "avcodec" "avutil" "tag" "avformat" "avresample" "yaml" "samplerate"
	)
