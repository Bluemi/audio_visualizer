#include "AudioVisualizer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <visualizer/shape/shape_type.hpp>
#include <visualizer/shape/shape_heap.hpp>
#include <visualizer/shaders/shaders.hpp>
#include <visualizer/misc/timer.hpp>
#include <visualizer/controller/events.hpp>

#include "entity/creation/Creation.hpp"
#include "entity/EntityIterator.hpp"
#include "entity/EntityBuffer.hpp"
#include "entity/queries/Query.hpp"
#include "entity/Movable.hpp"
#include "entity/movement/Circle.hpp"
#include "entity/movement/RandomAcceleration.hpp"
#include "entity/movement/SimpleDrag.hpp"
#include "entity/movement/SimpleColorDrag.hpp"
#include "entity/movement/StdColor.hpp"
#include "entity/movement/RandomColor.hpp"
#include "misc/lodepng.h"

constexpr float DEFAULT_SPEED = 60.f;
constexpr unsigned int NUM_LETTER_GROUPS = 10;
constexpr double OFFSCREEN_FRAME_INTERVAL = 1.0 / 60.0;

AudioVisualizer::AudioVisualizer()
	: _event_index(0)
{}

void AudioVisualizer::setup_objects(EntityBuffer* entity_buffer, visualizer::ShapeHeap& shape_heap) {
	/*
	ShapeGenerator shape_gen(&shape_heap, visualizer::CubeSpecification(), 1.f);
	VectorGenerator pos_gen = VectorGenerator().with_stddev(glm::vec3(5.f, 0.5f, 5.f));
	VectorGenerator size_gen = VectorGenerator(glm::vec3(0.15f, 0.15f, 0.15f)).with_stddev(glm::vec3(0.01f));
	VectorGenerator speed_gen = VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));

	for (unsigned int i = 0; i < NUM_LETTER_GROUPS; i++) {
		std::string letter_group_name = "letter" + std::to_string(i);
		Creation letter_creation = Creation(shape_gen, "")
			.with_quantity(200)
			.with_position(pos_gen)
			.with_size(size_gen)
			.with_velocity(speed_gen);
		entity_buffer->insert(letter_creation.create());
	}
	*/

	/*
	Creation creation = Creation(shape_gen, "main1")
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	
	entity_buffer->insert(creation.create());
	*/

	/*
	Creation valence_arousal_debug_creation = Creation(&shape_heap, visualizer::SphereSpecification(2), "debug")
		.with_quantity(6)
		.with_size(glm::vec3(0.1f, 0.1f, 0.1f))
		.with_color(glm::vec3(0.4, 0.4, 0.4))
		.with_tag("va_debug");

	entity_buffer->insert(valence_arousal_debug_creation.create());
	*/
}

void play_song(const std::string& audio_path) {
	std::string system_command = "cvlc \"" + audio_path + "\" --play-and-exit &>/dev/null &";
	if (system(system_command.c_str()) != 0) {
		std::cerr << "vlc terminated with non zero exit code " << std::endl;
	}
}

void AudioVisualizer::run(const InformationContainer& information_container, const std::string& audio_filename, bool interactive) {
	visualizer::init();

	int window_width = 1920;
	int window_height = 1080;

	visualizer::Camera camera(glm::vec3(-195.f, 0.f, 100.f), 0.f, 0.f);
	visualizer::Controller controller;

	visualizer::ShapeHeap shape_heap;

	EntityBuffer entity_buffer;

	GLFWwindow* window = visualizer::create_window(window_width, window_height);
	if (window == NULL) {
		std::cerr << "failed to create window" << std::endl;
		return;
	}

	visualizer::events::init(window);

	visualizer::events::register_resize_callback([&window_width, &window_height](int ww, int wh){ window_width=ww; window_height = wh; glViewport(0, 0, window_width, window_height); });
	if (interactive) {
		visualizer::events::register_mouse_callback([&controller](double x, double y) { controller.mouse_callback(x, y); });
	}

	std::optional<visualizer::ShaderProgram> opt_shader_program = visualizer::ShaderProgram::from_code(visualizer::Shaders::vertex_shader(), visualizer::Shaders::fragment_shader());
	if (!opt_shader_program) {
		std::cerr << "Failed to create shader program" << std::endl;
		return;
	}

	visualizer::ShaderProgram shader_program = *opt_shader_program;

	setup_handlers(&entity_buffer, shape_heap);
	setup_objects(&entity_buffer, shape_heap);

	if (interactive) {
		play_song(audio_filename);
	}

	visualizer::Timer timer;

	unsigned int tick_counter = 0;

	double current_time = 0.0;
	while (!visualizer::should_close(window)) {
		if (interactive) {
			current_time = visualizer::Timer::get_global_time();
		} else {
			current_time += OFFSCREEN_FRAME_INTERVAL;
		}
		unsigned int frame_counter = static_cast<int>((current_time * 44100.0) / 1024.0);
		set_handler_frame_counter(frame_counter);

		EventList current_events = get_current_events(information_container.get_event_list(), current_time);

		_compositor.update(&entity_buffer, _handlers, information_container, current_events, frame_counter);

		handle_events(current_events, information_container.get_pool());

		// tick
		double speed = timer.restart() * DEFAULT_SPEED;
		controller.process_user_input(window, &camera);
		if (interactive) {
			camera.tick(speed);
			// std::cout << camera.get_position().x << ", " << camera.get_position().z << std::endl;
		}

		for (Movable& m : EntityIterator::iter(&entity_buffer)) {
			m.tick(OFFSCREEN_FRAME_INTERVAL * DEFAULT_SPEED);
		}

		// render
		visualizer::clear_window();
		shader_program.use();
		shader_program.set_4fv("view", camera.get_look_at());
		glm::mat4 projection = glm::perspective(
			glm::radians(45.0f),
			window_width/static_cast<float>(window_height),
			0.1f, 600.f
		);
		shader_program.set_4fv("projection", projection);

		for (Movable& m : EntityIterator::iter(&entity_buffer)) {
			m.render(shader_program);
		}

		if (!interactive) {
			take_screenshot(window, tick_counter, window_width, window_height);
			tick_counter++;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (interactive) {
		if (system("pkill vlc") != 0) {
			std::cerr << "failed to kill vlc" << std::endl;
		}
	}

	shape_heap.close();

	visualizer::close();
}

void AudioVisualizer::take_screenshot(GLFWwindow* window, unsigned int tick_counter, int screen_width, int screen_height) {
	if (tick_counter == 0) {
		return;
	}
	std::vector<std::uint8_t> source_buffer(screen_width*screen_height*4, 0);

    /* Store pixels into tga.pic */
    glReadPixels(0, 0, screen_width, screen_height, GL_RGBA, GL_UNSIGNED_BYTE, source_buffer.data());

    /* Store "Capture_%04lu.tga" + tick_counter into captureName, increase frame count */
	char capture_name[256];
    sprintf(capture_name, "video/capture/Capture_%06u.png", tick_counter);

	std::vector<std::uint8_t> file_buffer;
	lodepng::encode(file_buffer, source_buffer, screen_width, screen_height);
	lodepng::save_file(file_buffer, capture_name);
}

void AudioVisualizer::add_handlers(const HandlerList& handler_list) {
	_handlers.insert(_handlers.end(), handler_list.cbegin(), handler_list.cend());
}

void AudioVisualizer::handle_events(const EventList& event_list, const essentia::Pool& pool) {
	for (Handler& h: _handlers) {
		for (const Event& event : event_list) {
			std::visit([&event](auto& handler) { std::visit(handler, event.get_event()); }, h);
		}

		std::visit([&pool](auto& handler) { handler.update(pool); }, h);
	}
}

void AudioVisualizer::setup_handlers(EntityBuffer* entity_buffer, visualizer::ShapeHeap& shape_heap) {
	for (Handler& h : _handlers) {
		std::visit([entity_buffer, &shape_heap](auto& handler) { handler.entity_buffer = entity_buffer; handler.init(shape_heap); }, h);
	}
}

void AudioVisualizer::set_handler_frame_counter(unsigned int frame_counter) {
	for (Handler& h : _handlers) {
		std::visit([frame_counter](auto& handler) { handler.frame_counter = frame_counter; }, h);
	}
}

EventList AudioVisualizer::get_current_events(const EventList& event_list, double current_time) {
	EventList el;
	for (unsigned int i = _event_index; i < event_list.size(); i++) {
		if (event_list[i].get_time() < current_time) {
			el.push_back(event_list[i]);
			_event_index = i+1;
		} else break;
	}

	return el;
}
