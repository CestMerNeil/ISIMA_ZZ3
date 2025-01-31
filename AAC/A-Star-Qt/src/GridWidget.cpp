// src/GridWidget.cpp
#include <QPainterPath> // 确保在文件最开头添加
#include "GridWidget.hpp"
#include <QPainter>
#include <QMouseEvent>

GridWidget::GridWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(CELL_SIZE * gridSize, CELL_SIZE * gridSize);
    initializeGrid();
}

void GridWidget::initializeGrid()
{
    grid = std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
}

void GridWidget::setGridSize(int size)
{
    gridSize = size;
    setFixedSize(CELL_SIZE * gridSize, CELL_SIZE * gridSize);
    initializeGrid();
    update();
}

void GridWidget::findPath()
{
    path = pathfinder.findPath(grid, start, goal);
    update();
}

void GridWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制网格
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            QRect cell(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            painter.fillRect(cell, grid[i][j] ? Qt::black : Qt::white);
            painter.drawRect(cell);
        }
    }

    // 绘制起点终点
    painter.setBrush(Qt::green);
    painter.drawEllipse(start.y * CELL_SIZE + CELL_SIZE / 4,
                        start.x * CELL_SIZE + CELL_SIZE / 4,
                        CELL_SIZE / 2, CELL_SIZE / 2);

    painter.setBrush(Qt::red);
    painter.drawEllipse(goal.y * CELL_SIZE + CELL_SIZE / 4,
                        goal.x * CELL_SIZE + CELL_SIZE / 4,
                        CELL_SIZE / 2, CELL_SIZE / 2);

    // 绘制路径
    if (!path.empty())
    {
        QPen pathPen(Qt::blue, 2);
        painter.setPen(pathPen);

        QPainterPath pathLine;
        pathLine.moveTo(path[0].y * CELL_SIZE + CELL_SIZE / 2,
                        path[0].x * CELL_SIZE + CELL_SIZE / 2);

        for (const auto &node : path)
        {
            pathLine.lineTo(node.y * CELL_SIZE + CELL_SIZE / 2,
                            node.x * CELL_SIZE + CELL_SIZE / 2);
        }
        painter.drawPath(pathLine);
    }
}

void GridWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint gridPos = gridPosFromMouse(event->pos());
    if (gridPos.x() >= 0 && gridPos.y() >= 0)
    {
        updateGrid(gridPos.x(), gridPos.y());
        findPath();
    }
}

QPoint GridWidget::gridPosFromMouse(const QPoint &pos) const
{
    int x = pos.y() / CELL_SIZE;
    int y = pos.x() / CELL_SIZE;
    return (x >= 0 && x < gridSize && y >= 0 && y < gridSize)
               ? QPoint(x, y)
               : QPoint(-1, -1);
}

void GridWidget::updateGrid(int x, int y)
{
    switch (editMode)
    {
    case EditMode::Start:
        if (grid[x][y] == 0)
            start = {x, y};
        break;
    case EditMode::End:
        if (grid[x][y] == 0)
            goal = {x, y};
        break;
    case EditMode::Obstacle:
        grid[x][y] = grid[x][y] ? 0 : 1;
        break;
    }
}