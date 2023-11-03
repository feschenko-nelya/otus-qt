import QtQuick 2.6
import Sailfish.Silica 1.0

Dialog {
    property string headerText;
    property string noteText;
    property string dateText;

    function getCurDate() {
        var today = new Date();

        var dd = ("0" + today.getDate()).slice(-2);
        var MM = ("0" + (today.getMonth() + 1)).slice(-2);
        var yyyy = today.getFullYear();

        var HH = ("0" + today.getHours()).slice(-2);
        var mm = ("0" + today.getMinutes()).slice(-2);
        var ss = ("0" + today.getSeconds()).slice(-2);

        return dd + '.' + MM + '.' + yyyy + ' ' + HH + ':' + mm + ':' + ss;
    }

    function updateCanAccept() {
        if (!canAccept && (headerField.text.length > 0) && (noteArea.text.length > 0))
        {
            canAccept = true;
        }
        else if ((headerField.text.length == 0) || (noteArea.text.length == 0))
        {
            canAccept = false;
        }

    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            bottomPadding: Theme.paddingLarge

            DialogHeader {
                acceptText: qsTr("Сохранить")
                cancelText: qsTr("Отменить")
            }

            Text {
                id: dateLabel
                text: dateText == "" ? getCurDate() : dateText
                horizontalAlignment: Text.AlignRight
                width: parent.width
                color: Theme.secondaryColor
            }

            TextField {
                id: headerField
                label: "Заголовок"
                labelVisible: false
                onTextChanged: updateCanAccept()

                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: noteArea.focus = true

                text: headerText
            }

            Item {
                id: headSeparator
                width: parent.width
                height: Theme.paddingMedium
            }

            TextArea {
                id: noteArea
                label: "Текст"
                labelVisible: false
                onTextChanged: updateCanAccept()

                text: noteText

            }
        }

        VerticalScrollDecorator { }
    }

    onAccepted: {
        dateText = dateLabel.text
        headerText = headerField.text
        noteText = noteArea.text
    }

    Component.onCompleted: {
        updateCanAccept();
    }
}
