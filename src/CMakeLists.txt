file(GLOB_RECURSE audio_visualizer_sources "./*.cpp")

add_executable(audio_visualizer ${audio_visualizer_sources})

# include_directories("/usr/include")
include_directories("/usr/local/include" "/usr/include" "/usr/include/eigen3")

link_directories("/usr/local/lib")

target_link_libraries(audio_visualizer
	"visualizer"
	"GLU" "glfw" "X11" "Xrandr" "pthread" "dl" "Xinerama" "Xcursor"
	"essentia" "fftw3f" "chromaprint" "avcodec" "avutil" "tag" "avformat" "yaml" "samplerate" "avresample"
	"moviemaker-cpp"
	)
