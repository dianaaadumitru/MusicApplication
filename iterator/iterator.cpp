#include "iterator.h"

Iterator::Iterator() {
    this->current = 0;
}

Tutorial Iterator::get_current_tutorial()
///returns the current tutorial
///if we got to the end of the list, we restart it
{
    if (this->current == this->tutorials.getSize())
        this->current = 0;

    return this->tutorials[this->current];
}

void Iterator::open()
///opens the current tutorial
{
    if (this->tutorials.getSize() == 0)
        return;
    this->current = 0;
    Tutorial t = this->get_current_tutorial();
    t.open_link();
}

void Iterator::next()
///opens the next tutorial
{
    if (this->tutorials.getSize() == 0)
        return;
    this->current++;
    Tutorial t = this->get_current_tutorial();
    t.open_link();
}

void Iterator::add(const Tutorial t)
///adds a tutorial to the dynamic vector
{
    this->tutorials.add(t);
}

void Iterator::iterator_empty()
///empties the iterator
{
    while (this->tutorials.getSize() != 0)
        this->tutorials.delete_elem(0);
}

void Iterator::update_likes(int pos) {
    this->tutorials[pos].like();
}