#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "qobjectdefs.h"
#include "./Buttons/BaseCalcButton.h"

class CalcController : public QObject
{
    Q_OBJECT
public:
    CalcController(QObject *parent);

private:
    double _value = 0;
    QString _printedValue;
    bool _isInitValue = true;
    CalcActionName _lastActionName;

    void doText(CalcActionName name);
    void doOperation(CalcActionName name);

public slots:
    void slotOnCalcAction(CalcActionType type, CalcActionName name);

signals:
    void signalPrint(const QString &text);
    void signalMake();
    void signalResult();
};

#endif // CALCCONTROLLER_H
