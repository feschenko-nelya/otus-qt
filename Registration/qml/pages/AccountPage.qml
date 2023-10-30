import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    id: page

    PageHeader {
        id: pageHeader
        title: qsTr("Карточка")
    }

    Column {
        spacing: 5

        Label {
            text: "Фамилия"

        }
        TextField {
            id: surname
            label: "Фамилия"
            width: page.width * 0.5
        }

        Label {
            text: "Имя"
        }
        TextField {
            id: name
            placeholderText: "Имя"
            width: page.width * 0.5
        }

        Label {
            text: "Отчество"
        }
        TextField {
            id: fatherName
            placeholderText: "Отчество"
            width: page.width * 0.5
        }

        Label {
            text: "e-mail"
        }

        TextField {
            id: email
            placeholderText: "abcd@efg.hi"
            validator: RegExpValidator { regExp: /^[A-Z0-9._%+-]+@[A-Z0-9-]+.+.[A-Z]{2,4}$/i }
            width: page.width * 0.8
        }

        Label {
            text: "Интерес"
        }

        ComboBox {
            id: topics
            readonly property string freeTopic: "free"

            menu: ContextMenu {

                MenuItem {
                    text: "ИТ"
                }
                MenuItem {
                    text: "маркетинг"
                }
                MenuItem {
                    text: "образование"
                }
                MenuItem {
                    text: "экономика"
                }
                MenuItem {
                    text: "жизнь"
                }
                MenuItem {
                    objectName: topics.freeTopic
                    text: "другая"
                }
            }

          onCurrentItemChanged: {
              if (currentItem.objectName == freeTopic)
              {
                  topics.visible = false;
                  freeTopicValue.visible = true;
              }
          }
        }

        TextField {
            id: freeTopicValue
            visible: false
            onTextChanged: {
                if (text.length == 0)
                {
                    topics.currentIndex = 0;
                    visible = false;
                    topics.visible = true;
                }
            }
        }

        TextSwitch {
            text: checked ? "Да" : "Нет"
            description: "Согласие на обработку данных"
        }
        IconTextSwitch {
            icon.source: Qt.resolvedUrl("../icons/mailing.png")
            text: checked ? "Да" : "Нет"
            description: "Согласие на рассылку"
        }

        anchors {
            top: pageHeader.bottom
            topMargin: Theme.vertivalPageMargin
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
    }

}
