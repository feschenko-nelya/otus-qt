#ifndef NEWCHECKBOX_H
#define NEWCHECKBOX_H

#include <QWidget>

enum class NewState {
    state_Checked,
    state_Unchecked,
    state_Tristate,
};

class NewCheckbox : public QWidget
{
    Q_OBJECT
public:
    explicit NewCheckbox(QWidget *parent = nullptr);

    void setState(NewState state);
    NewState getState() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    NewState _state = NewState::state_Unchecked;

signals:
    void signalStateChanged(NewState);
};

#endif // NEWCHECKBOX_H
