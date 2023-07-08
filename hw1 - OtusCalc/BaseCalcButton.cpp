#include "BaseCalcButton.h"
#include <QDebug>

BaseCalcButton::BaseCalcButton(QWidget *parent, CalcActionName name)
               :QPushButton(parent),
                _name(name)
{
    setText(getCaption());
    setToolTip(getTooltip());
    connect(this, SIGNAL(clicked(bool)), this, SLOT(slotOnClicked(bool)));
}

void BaseCalcButton::slotOnClicked(bool checked)
{
    Q_UNUSED(checked)
    emit signalAction(getActionType(), _name);
}

QString BaseCalcButton::getTooltip() const
{
    switch (_name)
    {
    case CalcActionName::name_C:
        return QString("Clear All");
    case CalcActionName::name_R:
        return QString("Remove last");
    case CalcActionName::name_Neg:
        return QString("Invert sign");
    default:
        return QString();
    }
}

QString BaseCalcButton::getCaption() const
{
    switch (_name)
    {
    case CalcActionName::name_0:
    case CalcActionName::name_1:
    case CalcActionName::name_2:
    case CalcActionName::name_3:
    case CalcActionName::name_4:
    case CalcActionName::name_5:
    case CalcActionName::name_6:
    case CalcActionName::name_7:
    case CalcActionName::name_8:
    case CalcActionName::name_9:
    case CalcActionName::name_Dot:
    case CalcActionName::name_C:
    case CalcActionName::name_R:
    case CalcActionName::name_Mlt:
    case CalcActionName::name_Div:
    case CalcActionName::name_Pls:
    case CalcActionName::name_Mns:
    case CalcActionName::name_Res:
        return QString(std::underlying_type<CalcActionName>::type(_name));
    case CalcActionName::name_Neg:
        return QString("+/-");
    default:
        qDebug() << QStringLiteral("Undefined operation type for '%1'.").arg(static_cast<char>(_name));
        break;
    }

    return QString();
}

CalcActionType BaseCalcButton::getActionType() const
{
    switch (_name)
    {
    case CalcActionName::name_0:
    case CalcActionName::name_1:
    case CalcActionName::name_2:
    case CalcActionName::name_3:
    case CalcActionName::name_4:
    case CalcActionName::name_5:
    case CalcActionName::name_6:
    case CalcActionName::name_7:
    case CalcActionName::name_8:
    case CalcActionName::name_9:
        return CalcActionType::action_Text;

    case CalcActionName::name_C:
    case CalcActionName::name_R:
    case CalcActionName::name_Mlt:
    case CalcActionName::name_Div:
    case CalcActionName::name_Pls:
    case CalcActionName::name_Mns:
    case CalcActionName::name_Res:
    case CalcActionName::name_Neg:
    case CalcActionName::name_Dot:
        return CalcActionType::action_Operation;

    default:
        qDebug() << QStringLiteral("Undefined operation type for '%1'.").arg(static_cast<char>(_name));
        break;
    }

    return CalcActionType::action_Undefined;
}
