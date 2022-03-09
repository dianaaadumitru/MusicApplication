#include "Action.h"

class ActionAdd : public Action{
private:
    Repo *repo;
    Tutorial tutorial;

public:
    ActionAdd(Repo *repo, Tutorial t) : repo{repo}, tutorial{t}, Action() {};
    void executeUndo() override;
    void executeRedo() override;
    ~ActionAdd() override;
};

