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
import QtQuick.LocalStorage 2.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    function getDbHandle()
    {
        try {
            var db = LocalStorage.openDatabaseSync("notes_db", "1.0", "", 1000000);
            db.transaction(function(tx){
                tx.executeSql("CREATE TABLE IF NOT EXISTS notes(id INTEGER PRIMARY KEY AUTOINCREMENT,
                              header TEXT, note TEXT, date TEXT)");
            });

            return db;
        }
        catch (err) {
            console.log("Error of db table creating: " + err)
            return -1;
        }
    }

    readonly property var appDb: getDbHandle()

    SilicaListView {
        id: notesList
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Simple notes")
        }

        PullDownMenu {
            MenuItem {
                text: "Добавить"
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/NoteDialog.qml"))
                    dialog.accepted.connect(function() {
                        try {
                            var db = appDb;
                            db.transaction(function(tx) {
                                tx.executeSql("insert into NOTES(DATE, HEADER, NOTE) values(?, ?, ?)",
                                              [dialog.dateText, dialog.headerText, dialog.noteText]);
                            });
                            notesModel.insert(0,
                                              {noteDate: dialog.dateText,
                                               noteHeader: dialog.headerText,
                                               noteText: dialog.noteText});
                        }
                        catch (err) {
                            console.log('Db insert error: ' + err)
                        }
                    });
                }
            }
        }

        model: ListModel { id: notesModel }

        delegate: ListItem {
            contentHeight: Theme.itemSizeMedium
            Column {
                anchors {
                    top: parent.top
                    left: parent.left
                    leftMargin: Theme.horizontalPageMargin
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                    bottom: parent.bottom
                }

                Row {
                    id: headerRow
                    width: parent.width
                    Label {
                        width: parent.width * 0.5
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignTop

                        text: noteHeader
                    }
                    Text {
                        width: parent.width * 0.5
                        horizontalAlignment: Text.AlignRight
                        color: Theme.secondaryColor
                        font.pixelSize: Theme.fontSizeTiny

                        text: noteDate + '\n'
                    }
                }
                Text {
                    height: parent.height - headerRow.height
                    width: parent.width
                    elide: Text.ElideRight
                    wrapMode: Text.WrapAnywhere
                    font.pixelSize: Theme.fontSizeTiny

                    text: noteText
                }
            }

            menu: ContextMenu {
                MenuItem {
                    text: "Редактировать"
                    onClicked: {
                        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/NoteDialog.qml"),
                                                    {"headerText": noteHeader,
                                                     "noteText": noteText,
                                                     "dateText": noteDate})
                        dialog.accepted.connect(function() {

                            try {
                                appDb.transaction(function(tx) {
                                        tx.executeSql("update NOTES set DATE = ?, HEADER = ?, NOTE = ? where ID = ? ",
                                                      [dialog.dateText, dialog.headerText, dialog.noteText, noteId]);
                                });
                                noteHeader = dialog.headerText
                                noteText = dialog.noteText
                                noteDate = dialog.dateText
                            }
                            catch (err) {
                                console.log("Update note error: " + err);
                            }
                        });
                    }
                }
                MenuItem {
                    text: "Удалить"
                    onClicked: {
                        try {
                            appDb.transaction(function(tx) {
                                    tx.executeSql("delete from NOTES where ID = ? ",
                                                  [noteId]);
                            });
                            notesModel.remove(index)
                        }
                        catch (err) {
                            console.log("Delete note error: " + err);
                        }
                    }
                }
            }
        }

        VerticalScrollDecorator { }

        Component.onCompleted: {
            try {
                var db = appDb;
                db.transaction(function(tx){
                    var rows = tx.executeSql("select ID, HEADER, NOTE, DATE from NOTES order by ID desc");

                    for (var i = 0; i < rows.rows.length; i++)
                    {
                        notesModel.append({noteId: rows.rows.item(i).id,
                                           noteHeader: rows.rows.item(i).header,
                                           noteText: rows.rows.item(i).note,
                                           noteDate: rows.rows.item(i).date})
                    }
                })
            }
            catch (err) {
                console.log("Error of db table creating: " + err)
            }
        }
    }
}
