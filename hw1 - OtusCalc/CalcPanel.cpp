#include "CalcPanel.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include "BaseCalcButton.h"
#include "CalcController.h"

CalcPanel::CalcPanel(QWidget *parent)
          : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(5);

    auto textField = new QLineEdit();
    textField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    textField->setReadOnly(true);

    CalcController *calcController = new CalcController(this);
    connect(calcController, SIGNAL(signalPrint(const QString &)), textField, SLOT(setText(const QString &)));

    auto captions = {CalcActionName::name_7, CalcActionName::name_8, CalcActionName::name_9, CalcActionName::name_R, CalcActionName::name_C,
                     CalcActionName::name_4, CalcActionName::name_5, CalcActionName::name_6, CalcActionName::name_Pls, CalcActionName::name_Mns,
                     CalcActionName::name_1, CalcActionName::name_2, CalcActionName::name_3, CalcActionName::name_Mlt, CalcActionName::name_Div,
                     CalcActionName::name_0, CalcActionName::name_Dot, CalcActionName::name_Neg, CalcActionName::name_Dummy, CalcActionName::name_Res};

    auto buttons = new QGridLayout();
    buttons->setSpacing(2);

    const size_t max_cols = 5;
    size_t row = 0;
    for (size_t i = 0; i < captions.size(); ++i)
    {
        auto but = new BaseCalcButton(this, *std::next(captions.begin(), i));
        connect(but, SIGNAL(signalAction(CalcActionType, CalcActionName)),
                calcController, SLOT(slotOnCalcAction(CalcActionType, CalcActionName)));

        buttons->addWidget(but, row, i - row * max_cols);

        if ((i > 0) && ((i+1) % max_cols == 0))
        {
            ++row;
        }
    }

    mainLayout->addWidget(textField);
    mainLayout->addLayout(buttons);

    setLayout(mainLayout);
}
