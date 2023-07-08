#include "MainWindow.h"
#include "CalcPanel.h"

MainWindow::MainWindow(QWidget *parent)
           : QMainWindow(parent)
{
    setCentralWidget(new CalcPanel(this));
}

MainWindow::~MainWindow()
{
}

