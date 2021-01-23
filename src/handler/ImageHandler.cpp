#include "ImageHandler.hpp"

#include <iostream>

#include "../event/ImageEvent.hpp"
#include "misc/lodepng.h"

constexpr float MAX_MAGNITUDE = 0.04f;
constexpr float BRIGHTNESS_THRESHOLD = 400.f;

ImageHandler::ImageHandler(const std::vector<std::string>& image_paths) : _image_paths(image_paths), _current_image(-1) {}

std::vector<glm::vec3> image_to_points(const std::vector<unsigned char>& image, unsigned int width, unsigned int height) {
	std::vector<glm::vec3> points;

	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			unsigned int brightness = 0;
			for (unsigned rgb_counter = 0; rgb_counter < 3; rgb_counter++) {
				brightness += image[rgb_counter + 4*(x + y*width)];
			}
			if (brightness > BRIGHTNESS_THRESHOLD) {
				points.push_back(glm::vec3(0.f, static_cast<float>(height-y-1), static_cast<float>(x)));
			}
		}
	}

	return points;
}

void ImageHandler::init(visualizer::ShapeHeap& shape_heap) {
	// load images
	for (const std::string& path : _image_paths) {
		std::vector<unsigned char> image;
		unsigned int width;
		unsigned int height;
		unsigned int error = lodepng::decode(image, width, height, path.c_str());
		if (error) {
			std::cerr << "ERROR: failed to decode image \"" << path << "\": " << lodepng_error_text(error) << std::endl;
			_images.push_back(std::vector<glm::vec3>());
			continue;
		}
		_images.push_back(image_to_points(image, width, height));
	}
}

void ImageHandler::update(const essentia::Pool& pool) {
	if (_current_image != -1) {
		for (std::string group : groups) {
			auto movables = entity_buffer->find(group);
			if (movables != entity_buffer->end()) {
				for (Movable& movable : movables->second) {
					apply_force(&movable);
				}
			} else {
				std::cerr << "ERROR: Could not find group \"" << group << "\" but required by ImageHandler movement" << std::endl;
			}
		}
	}
}

void ImageHandler::operator()(const ImageEvent& image_event) {
	if (image_event.image_id >= static_cast<int>(_images.size())) {
		std::cerr << "ERROR: Got image id that is out of range\n id: " << image_event.image_id << "\nnum images: " << _images.size() << std::endl;
		return;
	}
	_current_image = image_event.image_id;
}

void ImageHandler::apply_force(Movable* movable) {
	unsigned int pixel_id = (movable->get_id()+5032)*4034 % _images[_current_image].size();
	glm::vec3 target_point = _images[_current_image][pixel_id];
	target_point *= 0.14f;
	target_point += glm::vec3(0.f, -40.f, 50.f);

	glm::vec3 dir = target_point - movable->get_position();
	glm::vec3 update = dir - movable->get_velocity();

	if (glm::length(update) > MAX_MAGNITUDE) {
		update *= MAX_MAGNITUDE / glm::length(update);
	}

	movable->update_acceleration(update);
}
