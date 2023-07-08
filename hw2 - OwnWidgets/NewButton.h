#ifndef NEWBUTTON_H
#define NEWBUTTON_H

#include <QWidget>

class NewButton : public QWidget
{
    Q_OBJECT
public:
    explicit NewButton(QWidget *parent, const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEvent *event) override;

private:
    QString _text;
    bool _isPressed = false;
    bool _isHovered = false;
    static const QColor LIGHT_COLOR;
    static const QColor DARK_COLOR;

signals:
    void signalClicked();
};

#endif // NEWBUTTON_H
