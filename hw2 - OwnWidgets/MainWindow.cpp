#include "MainWindow.h"
#include "NewButton.h"
#include <QLayout>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
           : QMainWindow(parent)
{
    auto centralWidget = new QWidget(this);
    setMinimumSize(500, 100);

    auto layout = new QVBoxLayout();

    auto hLayout = new QHBoxLayout();

    auto but = new NewButton(this, "PUSH");
    connect(but, SIGNAL(signalClicked()), this, SLOT(slotButtonClicked()));

    auto newCheck = new NewCheckbox(this);
    connect(newCheck, SIGNAL(signalStateChanged(NewState)), this, SLOT(slotCheckChanged(NewState)));

    hLayout->addWidget(but);
    hLayout->addStretch();
    hLayout->addWidget(newCheck);

    _progress = new NewProgress();
    _progress->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addLayout(hLayout);
    layout->addWidget(_progress);
    layout->addStretch();
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    _timer = new QTimer(this);
    _timer->setInterval(100);
    _timer->callOnTimeout([=]()
    {
        _progress->incStep();
        if (_progress->isFinished())
        {
            _timer->stop();
        }
    });
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotButtonClicked()
{
    if (!_timer->isActive())
    {
        _progress->reset();
        _timer->start();
    }
    else
    {
        _timer->stop();
    }
}

void MainWindow::slotCheckChanged(NewState state)
{
    switch (state)
    {
    case NewState::state_Unchecked:
        _progress->setColor(QColor("#FFFFFF"));
        break;
    case NewState::state_Checked:
        _progress->setColor(QColor("#FFFF00"));
        break;
    case NewState::state_Tristate:
        _progress->setColor(QColor("#00FF00"));
        break;
    default:
        break;
    }
}
