#include "Query.hpp"

#include "../Movable.hpp"

Query::Query()
{}

Query& Query::with_shape(const visualizer::ShapeType& spec) {
	_shape_types.push_back(spec);
	return *this;
}

Query& Query::with_position(const QuerySpace& space) {
	_space = space;
	return *this;
}

Query& Query::with_groups(const std::vector<std::string>& groups) {
	_groups.insert(_groups.end(), groups.cbegin(), groups.cend());
	return *this;
}

Query& Query::with_tags(const std::vector<std::string>& tags) {
	_include_tags = tags;
	return *this;
}

Query& Query::exclude_tags(const std::vector<std::string>& tags) {
	_exclude_tags = tags;
	return *this;
}

bool Query::entity_included(const Movable& movable) const {
	bool included = true;

	bool shape_included = _shape_types.size() == 0;
	for (const visualizer::ShapeType& shape_type : _shape_types) {
		if (shape_type == movable.get_shape_specification()) {
			shape_included = true;
		}
	}
	included &= shape_included;

	bool position_included = _space.is_position_included(movable.get_position());
	included &= position_included;

	bool not_tag_excluded = true;
	for (const std::string& exclude_tag : _exclude_tags) {
		for (const std::string& movable_tag : movable.get_tags()) {
			if (movable_tag == exclude_tag) {
				not_tag_excluded = false;
				break;
			}
		}
		if (!not_tag_excluded)
			break;
	}
	included &= not_tag_excluded;

	if (_include_tags.size()) {
		bool tag_included = false;

		for (const std::string& include_tag : _include_tags) {
			for (const std::string& movable_tag : movable.get_tags()) {
				if (movable_tag == include_tag) {
					tag_included = true;
					break;
				}
			}
			if (tag_included)
				break;
		}

		included &= tag_included;
	}

	return included;
}

const std::vector<std::string>& Query::get_groups() const {
	return _groups;
}
