#include <QWidget>
#include "../service/service.h"
#include "tutorialModel.h"
#include "NumericFilterProxyModel.h"
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class gui2; }
QT_END_NAMESPACE

class gui2 : public QWidget {
Q_OBJECT

public:
    explicit gui2(Service *s, QWidget *parent = Q_NULLPTR);

    ~gui2() override;

private:
    Ui::gui2 *ui;
    Service *s;
    tutorialModel* watchlistModel;
    tutorialModel* model;
    NumericFilterProxyModel* viewsFilter;
    Iterator iterator;
    QShortcut *undoShortcut, *redoShortcut;

    void connectSignalAndSlots();
    void populateList();
    void addTutorial();
    void removeTutorial();
    void configureIterator();
    void updateTutorial();
    void removeFromWatchlist();
    void next();
    void viewWatchlist();
    void addToWatchlist();
    int getSelectedIndex();
    int getSelectedIndexUser();
    Tutorial getSelectedTutorial();
    void updateTutorialAdmin();
    void selectTutorial();
    void undo();
    void redo();
};

