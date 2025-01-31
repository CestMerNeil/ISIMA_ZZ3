#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include "GridWidget.hpp"
#include <QPainterPath>

class MainWindow : public QMainWindow
{
public:
    MainWindow()
    {
        gridWidget = new GridWidget;
        setCentralWidget(gridWidget);

        createToolBar();
        setWindowTitle("A* Pathfinding with Qt");
        resize(800, 800);
    }

private:
    GridWidget *gridWidget;

    void createToolBar()
    {
        QToolBar *toolBar = addToolBar("Tools");

        QAction *startAction = new QAction("Set Start (S)", this);
        QAction *endAction = new QAction("Set End (E)", this);
        QAction *obstacleAction = new QAction("Toggle Obstacle (Click)", this);
        QAction *refreshAction = new QAction("Refresh Path (R)", this);

        connect(startAction, &QAction::triggered, [this]()
                { gridWidget->editMode = GridWidget::EditMode::Start; });
        connect(endAction, &QAction::triggered, [this]()
                { gridWidget->editMode = GridWidget::EditMode::End; });
        connect(obstacleAction, &QAction::triggered, [this]()
                { gridWidget->editMode = GridWidget::EditMode::Obstacle; });
        connect(refreshAction, &QAction::triggered, [this]()
                { gridWidget->findPath(); });

        toolBar->addAction(startAction);
        toolBar->addAction(endAction);
        toolBar->addAction(obstacleAction);
        toolBar->addAction(refreshAction);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}