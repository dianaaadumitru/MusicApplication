//
// Created by diana on 5/29/2021.
//

#include "ActionRemove.h"

void ActionRemove::executeUndo() {
    this->repo->add_tutorial(tutorial);
}

void ActionRemove::executeRedo() {
    this->repo->remove_tutorial(tutorial.get_presenter(), tutorial.get_title());
}

ActionRemove::~ActionRemove() {

}
