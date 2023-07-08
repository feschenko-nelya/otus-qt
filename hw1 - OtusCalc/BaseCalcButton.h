#ifndef BASECALCBUTTON_H
#define BASECALCBUTTON_H

#include <QPushButton>

enum class CalcActionType
{
    action_Text,
    action_Operation,
    action_Undefined,
};

enum class CalcActionName: char
{
    name_0 = '0',
    name_1 = '1',
    name_2 = '2',
    name_3 = '3',
    name_4 = '4',
    name_5 = '5',
    name_6 = '6',
    name_7 = '7',
    name_8 = '8',
    name_9 = '9',
    name_C = 'C', /// clear all
    name_R = 'R', /// remove last
    name_Mlt = '*',
    name_Div = '\\',
    name_Pls = '+',
    name_Mns = '-',
    name_Dot = '.',
    name_Neg = 'n', /// make negative/positive
    name_Res = '=',
    name_Dummy = ' ',
//    name_Dec = 'd',
};

class BaseCalcButton : public QPushButton
{
    Q_OBJECT
public:
    explicit BaseCalcButton(QWidget *parent, CalcActionName name);

private:
    CalcActionName _name;

    CalcActionType getActionType() const;
    QString getCaption() const;
    QString getTooltip() const;

private slots:
    void slotOnClicked(bool checked = false);

signals:
    void signalAction(CalcActionType, CalcActionName);

};

#endif // BASECALCBUTTON_H
