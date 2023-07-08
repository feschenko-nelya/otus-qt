#ifndef NEWPROGRESS_H
#define NEWPROGRESS_H

#include <QWidget>

class NewProgress : public QWidget
{
    Q_OBJECT
public:
    explicit NewProgress(QWidget *parent = nullptr);

    void incStep();
    void reset();
    bool isFinished() const;
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int _step = 0;
    int _steps = 100;
    QColor _color = QColor("#FFFFFF");
    const int _dPerc = 5;

signals:

};

#endif // NEWPROGRESS_H
