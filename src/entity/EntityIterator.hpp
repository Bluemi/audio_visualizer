#ifndef __ENTITYITERATOR_CLASS__
#define __ENTITYITERATOR_CLASS__

#include "EntityBuffer.hpp"

class EntityIterator;

class EntityIterable {
	public:
		EntityIterable(EntityBuffer* entity_buffer) : _entity_buffer(entity_buffer) {}

		EntityIterator begin();
		EntityIterator end();
	private:
		EntityBuffer* _entity_buffer;

};

class EntityIterator {
	public:
		EntityIterator(const EntityBuffer::iterator& map_iterator, const std::vector<Movable>::iterator& vektor_iterator);

		static EntityIterator begin(EntityBuffer& entity_buffer);
		static EntityIterator end(EntityBuffer& entity_buffer);

		static EntityIterable iter(EntityBuffer* entity_buffer);

		void operator++();
		void operator++(int);

		bool operator==(const EntityIterator& other) const;
		bool operator!=(const EntityIterator& other) const;

		Movable* operator->();
		Movable& operator*();
	private:
		EntityBuffer::iterator _map_iterator;
		std::vector<Movable>::iterator _vektor_iterator;
};

#endif
