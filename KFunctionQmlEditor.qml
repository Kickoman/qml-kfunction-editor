import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QmlKfunctionEditor

Item {
    id: root
    property alias value: chart.kfunction
    property alias xRangeStart: chart.xRangeStart
    property alias xRangeFinish: chart.xRangeFinish
    property alias yRangeStart: chart.yRangeStart
    property alias yRangeFinish: chart.yRangeFinish
    property alias dpi: chart.dpi

    ColumnLayout {
        anchors.fill: parent
        KFunctionQmlView {
            id: chart
            Layout.fillHeight: true
            Layout.fillWidth: true
            kfunction: functionValue.text
        }

        RowLayout {
            TextField {
                id: functionValue
                Layout.fillWidth: true
                placeholderText: "Function like sin(x)*2"
            }
            Button {
                id: showButton
                text: "G"
                onClicked: chart.visible = !chart.visible
            }
        }
    }
}
