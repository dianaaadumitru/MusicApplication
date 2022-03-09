#include "Action.h"

class ActionUpdate : public Action{
private:
    Repo *repo;
    Tutorial tutorial, newTutorial;

public:
    ActionUpdate(Repo *repo, Tutorial t, Tutorial newt) : repo{repo}, tutorial{t}, newTutorial{newt}, Action() {};
    void executeUndo() override;
    void executeRedo() override;
    ~ActionUpdate() override;
};