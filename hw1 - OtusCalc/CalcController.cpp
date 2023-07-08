#include "CalcController.h"
#include <QDebug>

CalcController::CalcController(QObject *parent)
               :QObject(parent)
{

}

void CalcController::slotOnCalcAction(CalcActionType type, CalcActionName name)
{
    switch (type)
    {
    case CalcActionType::action_Text:
        doText(name);
        emit signalPrint(_printedValue);
        break;
    case CalcActionType::action_Operation:
        doOperation(name);
        emit signalMake();
        break;
    default:
        qDebug() << QStringLiteral("Calc %1 action is undefined.").arg(static_cast<char>(name));
        break;
    }
}

void CalcController::doText(CalcActionName name)
{
    _printedValue += static_cast<char>(name);
}

void CalcController::doOperation(CalcActionName name)
{
    switch (name)
    {
    case CalcActionName::name_C:
        _value = 0;
        _printedValue.clear();
        _isInitValue = true;
        emit signalPrint(_printedValue);
        return;
    case CalcActionName::name_R:
        _printedValue = _printedValue.remove(_printedValue.length() - 1, 1);
        emit signalPrint(_printedValue);
        return;
    case CalcActionName::name_Dot:
        if (_printedValue.at(_printedValue.length() - 1) == '.')
        {
            doOperation(CalcActionName::name_R);
        }
        else if (!_printedValue.contains('.'))
        {
            _printedValue += '.';
        }
        emit signalPrint(_printedValue);
        return;
    case CalcActionName::name_Neg:
        if (_printedValue.at(0) == '-')
        {
            _printedValue = _printedValue.remove(0, 1);
        }
        else if (!_printedValue.contains('-'))
        {
            _printedValue.prepend('-');
        }
        emit signalPrint(_printedValue);
        return;
    default:
        break;
    }

    double newValue = _printedValue.toDouble();

    if (_isInitValue)
    {
        _value = newValue;
        _lastActionName = name;
        _isInitValue = false;
        _printedValue.clear();
        emit signalPrint(_printedValue);
        return;
    }

    switch (_lastActionName)
    {
    case CalcActionName::name_Pls:
        _value += newValue;
        break;
    case CalcActionName::name_Mns:
        _value -= newValue;
        break;
    case CalcActionName::name_Mlt:
        _value *= newValue;
        _printedValue.clear();
        break;
    case CalcActionName::name_Div:
        _value /= newValue;
        break;
    case CalcActionName::name_Res:
        break;
    default:
        qDebug() << QStringLiteral("Undefined action for %1.").arg(static_cast<char>(name));
        break;
    }

    emit signalPrint(QString::number(_value));

    _lastActionName = name;
    _printedValue.clear();

    if (name == CalcActionName::name_Res)
    {
        _printedValue = QString::number(_value);
        _isInitValue = true;
        _value = 0;
    }
}
