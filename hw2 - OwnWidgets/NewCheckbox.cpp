#include "NewCheckbox.h"
#include <QPainter>
#include <QMouseEvent>

NewCheckbox::NewCheckbox(QWidget *parent)
            : QWidget{parent}
{
    setFixedSize(25, 25);
}

void NewCheckbox::setState(NewState state)
{
    _state = state;
    repaint();

    emit signalStateChanged(_state);
}

NewState NewCheckbox::getState() const
{
    return _state;
}

void NewCheckbox::mouseReleaseEvent(QMouseEvent *event)
{
    if (_state == NewState::state_Checked)
    {
        _state = NewState::state_Unchecked;
    }
    else if (_state == NewState::state_Unchecked)
    {
        _state = NewState::state_Tristate;
    }
    else if (_state == NewState::state_Tristate)
    {
        _state = NewState::state_Checked;
    }

    emit signalStateChanged(_state);
    repaint();

    event->accept();
}

void NewCheckbox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QRect newRect = rect();
    newRect.adjust(1, 1, -1, -1);

    QPen pen(QColor("#00FF00"));
    pen.setWidth(2);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawEllipse(newRect);

    if (_state == NewState::state_Checked)
    {
        newRect.adjust(3, 3, -4, -4);
        painter.setBrush(QBrush(QColor("#FFFF00")));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(newRect);
    }
    else if (_state == NewState::state_Tristate)
    {
        newRect.adjust(3, 3, -4, -4);
        painter.setBrush(QBrush(QColor("#FFFFFF"), Qt::Dense2Pattern));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(newRect);
    }
}
