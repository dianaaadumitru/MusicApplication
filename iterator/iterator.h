#pragma once
#include "../dynamic_vector/array.h"
#include "../domain/domain.h"

class Iterator
{
private:
    DynamicVector<Tutorial> tutorials;
    int current;

public:
    Iterator();

    Tutorial get_current_tutorial();

    void open();

    void next();

    void add(const Tutorial t);

    void iterator_empty();

    void update_likes(int pos);

    DynamicVector<Tutorial> get_tutorials_iter() {return tutorials; }

    int get_current() {return current; }


};
