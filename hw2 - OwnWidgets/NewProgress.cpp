#include "NewProgress.h"
#include <QPainter>

NewProgress::NewProgress(QWidget *parent)
            : QWidget{parent}
{
    setMinimumSize(100, 25);
}

void NewProgress::incStep()
{
    if (_step < _steps)
    {
        ++_step;
        repaint();
    }
}

void NewProgress::reset()
{
    _step = 0;
}

bool NewProgress::isFinished() const
{
    return _step >= _steps;
}

void NewProgress::setColor(const QColor &color)
{
    _color = color;
    repaint();
}

void NewProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QRect mainRect = rect();
    mainRect.adjust(0, 0, -1, -1);
    QPen penBorder(QColor("#FFFFFF"));
    penBorder.setJoinStyle(Qt::RoundJoin);
    penBorder.setCapStyle(Qt::RoundCap);
    painter.setPen(penBorder);
    painter.drawRect(mainRect);

    const int dPix = _dPerc * (width() - 2) / 100;
    const int dStep = _dPerc * _steps / 100;

    QPoint start(2, rect().bottom() - 1);
    QPoint end(dPix, 2);

    QPen penLine(_color);
    penLine.setWidth(2);
    painter.setPen(penLine);

    for (int i = 1; i < _step; i += dStep)
    {
        painter.drawLine(start, end);
        int lastY = start.y();
        start = end;
        end = QPoint(end.x() + dPix, lastY);
    }
}
