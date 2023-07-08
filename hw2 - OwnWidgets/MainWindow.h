#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NewProgress.h"
#include "NewCheckbox.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    NewProgress *_progress = nullptr;
    QTimer *_timer = nullptr;

private slots:
    void slotButtonClicked();
    void slotCheckChanged(NewState state);

};
#endif // MAINWINDOW_H
