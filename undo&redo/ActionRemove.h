#include "Action.h"

class ActionRemove : public Action{
private:
    Repo *repo;
    Tutorial tutorial;

public:
    ActionRemove(Repo *repo, Tutorial t) : repo{repo}, tutorial{t}, Action() {};
    void executeUndo() override;
    void executeRedo() override;
    ~ActionRemove() override;
};