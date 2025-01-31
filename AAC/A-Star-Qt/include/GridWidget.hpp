#pragma once
#include <QWidget>
#include <vector>
#include "A_Star.hpp"

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(QWidget *parent = nullptr);

    enum class EditMode
    {
        Start,
        End,
        Obstacle
    };

    void setGridSize(int size);
    void findPath();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public:
    const int CELL_SIZE = 40;
    int gridSize = 16;
    std::vector<std::vector<int>> grid;
    Node start{0, 0};
    Node goal{15, 15};
    std::vector<Node> path;
    EditMode editMode = EditMode::Obstacle;
    AStar pathfinder;

    void initializeGrid();
    QPoint gridPosFromMouse(const QPoint &pos) const;
    void updateGrid(int x, int y);
};