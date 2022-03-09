//
// Created by diana on 5/29/2021.
//

#include "ActionUpdate.h"

void ActionUpdate::executeUndo() {
    this->repo->update_tutorial_gui(newTutorial.get_presenter(),newTutorial.get_title(), std::to_string(newTutorial.get_duration().getMinutes()), std::to_string(newTutorial.get_duration().getSeconds()), std::to_string(newTutorial.get_no_of_likes()), newTutorial.get_link(),
                                    tutorial.get_presenter(),tutorial.get_title(), std::to_string(tutorial.get_duration().getMinutes()), std::to_string(tutorial.get_duration().getSeconds()), std::to_string(tutorial.get_no_of_likes()), tutorial.get_link());
}

void ActionUpdate::executeRedo() {
    this->repo->update_tutorial_gui(tutorial.get_presenter(),tutorial.get_title(), std::to_string(tutorial.get_duration().getMinutes()), std::to_string(tutorial.get_duration().getSeconds()), std::to_string(tutorial.get_no_of_likes()), tutorial.get_link(),
            newTutorial.get_presenter(),newTutorial.get_title(), std::to_string(newTutorial.get_duration().getMinutes()), std::to_string(newTutorial.get_duration().getSeconds()), std::to_string(newTutorial.get_no_of_likes()), newTutorial.get_link());
}

ActionUpdate::~ActionUpdate() {

}
