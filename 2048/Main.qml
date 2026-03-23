import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    id: root
    width: 500
    height: 600
    visible: true
    title: "2048"

    // ── Conteneur principal et couleur de fond ────────────────
    Rectangle {
        anchors.fill: parent
        color: "#faf8ef"
        focus: true // C'est ce Rectangle qui écoute le clavier !

        // ── Capture des touches du clavier ───────────────────────
        Keys.onPressed: function(event) {
            if (gameOverlay.visible) return

            switch(event.key) {
                case Qt.Key_Left:  game.move("left");  break
                case Qt.Key_Right: game.move("right"); break
                case Qt.Key_Up:    game.move("up");    break
                case Qt.Key_Down:  game.move("down");  break
            }
        }

        // ── Connexion aux signaux C++ ────────────────────────────
        Connections {
            target: game
            function onGameWon()  { overlayText.text = "Victoire !"; gameOverlay.visible = true }
            function onGameLost() { overlayText.text = "Perdu !";         gameOverlay.visible = true }
        }

        // ── Titre et score ───────────────────────────────────────
        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
            spacing: 8

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "2048"
                font.pixelSize: 48
                font.bold: true
                color: "#776e65"
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Score : " + game.score
                font.pixelSize: 22
                color: "#776e65"
            }

            // ── Bouton Rejouer ───────────────────────────────────
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 120
                height: 40
                radius: 0
                color: "#8f7a66"

                Text {
                    anchors.centerIn: parent
                    text: "Rejouer"
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        game.restart()
                        gameOverlay.visible = false
                    }
                }
            }
        }

        // ── Grille ───────────────────────────────────────────────
        Rectangle {
            id: boardRect
            width: 420
            height: 420
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 40
            color: "#bbada0"
            radius: 0

            Grid {
                anchors.centerIn: parent
                columns: 4
                spacing: 10

                Repeater {
                    model: game.board

                    Rectangle {
                        width: 95
                        height: 95
                        radius: 0
                        color: tileColor(modelData)

                        function tileColor(value) {
                            switch(value) {
                                case 0:    return "#cdc1b4"
                                case 2:    return "#eee4da"
                                case 4:    return "#ede0c8"
                                case 8:    return "#f2b179"
                                case 16:   return "#f59563"
                                case 32:   return "#f67c5f"
                                case 64:   return "#f65e3b"
                                case 128:  return "#edcf72"
                                case 256:  return "#edcc61"
                                case 512:  return "#edc850"
                                case 1024: return "#edc53f"
                                case 2048: return "#edc22e"
                                default:   return "#3c3a32"
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData === 0 ? "" : modelData
                            font.pixelSize: modelData >= 1000 ? 22 : 28
                            font.bold: true
                            color: modelData <= 4 ? "#776e65" : "#f9f6f2"
                        }
                    }
                }
            }
        }

        // ── Overlay Game Over / Victoire ─────────────────────────
        Rectangle {
            id: gameOverlay
            visible: false
            anchors.fill: boardRect
            color: "#000000aa"  // noir semi-transparent
            radius: 0

            Column {
                anchors.centerIn: parent
                spacing: 16

                Text {
                    id: overlayText
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: ""
                    font.pixelSize: 28
                    font.bold: true
                    color: "white"
                }

                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 120
                    height: 40
                    radius: 0
                    color: "#8f7a66"

                    Text {
                        anchors.centerIn: parent
                        text: "Rejouer"
                        color: "white"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            game.restart()
                            gameOverlay.visible = false
                        }
                    }
                }
            }
        }

    } // <-- Fin du Rectangle principal
}
