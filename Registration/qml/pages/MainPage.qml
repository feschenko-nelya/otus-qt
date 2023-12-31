/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the My Aurora OS Application project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    PageHeader {
        id: pageHeader
        objectName: "pageHeader"
        title: qsTr("Регистрация")
    }

    Column {
        anchors {
            top: pageHeader.bottom
            topMargin: Theme.horizontalPageMargin
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }

        Label {
            id: loginLabel
            text: "Логин"
        }
        Label {
            id: errLogin
            color: Theme.errorColor
            font.pixelSize: Theme.fontSizeTiny
            visible: false
            wrapMode: Text.WordWrap
            width: parent.width
        }

        TextField {
            id: login
            placeholderText: "login123"
            validator: RegExpValidator { regExp: /^[a-z0-9_-]{3,16}$/ }
            onTextChanged: {
                if (errLogin.visible)
                {
                    errLogin.visible = false;
                }
            }
        }

        Label {
            text: "Номер телефона"
        }
        Label {
            id: errPhone
            color: Theme.errorColor
            font.pixelSize: Theme.fontSizeTinyBase
            visible: false
            wrapMode: Text.WordWrap
            width: parent.width
        }

        Row {
            Item {
                width: 25
                height: 10
            }

            TextInput {
                id: phone
                inputMask: "+7(000)00-00-00"
                color: focus ? Theme.highlightColor : Theme.primaryColor
                height: login.height / 2
                verticalAlignment: Text.AlignVCenter
                onTextChanged: {
                    if (errPhone.visible)
                    {
                        errPhone.visible = false;
                    }
                }
            }
        }

        Item {
            width: parent.width
            height: Theme.paddingLarge
        }

        Button {
            id: submit
            text: "Зарегистрироваться"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                var hasErrors = false;
                if (login.text.length == 0)
                {
                    errLogin.visible = true;
                    errLogin.text = "Укажите логин";
                    hasErrors = true;
                }
                else if (!login.acceptableInput)
                {
                    errLogin.visible = true;
                    errLogin.text = "Укажите правильный логин: от 3 до 16 символов, только строчные буквы, числа или знаки '_', '-'";
                    hasErrors = true;
                }

                if (phone.text.length != 15)
                {
                    errPhone.text = "Укажите номер телефона полностью";
                    errPhone.visible = true;
                    hasErrors = true;
                }

                if (!hasErrors)
                {
                    pageStack.push(Qt.resolvedUrl("AccountPage.qml"))
                }
            }
        }
    }
}
