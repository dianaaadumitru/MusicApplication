#include "ActionAdd.h"

void ActionAdd::executeUndo() {
    this->repo->remove_tutorial(this->tutorial.get_presenter(), this->tutorial.get_title());
}

void ActionAdd::executeRedo() {
    this->repo->add_tutorial(tutorial);
}

ActionAdd::~ActionAdd() {

}
