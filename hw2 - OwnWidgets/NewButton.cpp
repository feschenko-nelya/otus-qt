#include "NewButton.h"
#include <QPaintEvent>
#include <QPainter>
#include <QGradient>
#include <QDebug>

const QColor NewButton::LIGHT_COLOR = QColor("#FFFF00");
const QColor NewButton::DARK_COLOR = QColor("#00FF00");

NewButton::NewButton(QWidget *parent, const QString &text)
          : QWidget{parent},
            _text(text)
{
    setFixedSize(100, 50);
    setMouseTracking(true);
}

void NewButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QColor textColor = QColor("#FFFFFF");
    if (_isPressed)
    {
        painter.fillRect(rect(), DARK_COLOR);
        textColor = LIGHT_COLOR;
    }
    else if (_isHovered)
    {
        painter.fillRect(rect(), LIGHT_COLOR);
        textColor = DARK_COLOR;
    }
    else
    {
        QLinearGradient grd(QPoint(0, 0), rect().bottomRight());
        grd.setColorAt(0, LIGHT_COLOR);
        grd.setColorAt(1, DARK_COLOR);

        QBrush brush(grd);
        painter.fillRect(rect(), brush);
    }

    QPen pen(textColor);
    painter.setPen(pen);
    QFont font;
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(rect(), _text, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}

void NewButton::mousePressEvent(QMouseEvent *event)
{
    _isPressed = true;
    repaint();
    event->accept();
}

void NewButton::mouseReleaseEvent(QMouseEvent *event)
{
    _isPressed = false;
    repaint();
    emit signalClicked();

    event->accept();
}

void NewButton::leaveEvent(QEvent *event)
{
    _isHovered = false;
    repaint();

    event->accept();
}

void NewButton::enterEvent(QEvent *event)
{
    _isHovered = true;
    repaint();

    event->accept();
}
