import QtQuick
import QtCharts 2.15
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        // Calculated in C++ and transfers results to QML
        ChartView {
            id: chart
            legend.visible: false

            Layout.fillHeight: true
            Layout.fillWidth: true
            animationOptions: ChartView.AllAnimations


            theme: ChartView.ChartThemeBrownSand

            Component.onCompleted: {
                kfunctionDataModelMapper.series = series
            }

            ValuesAxis {
                id: axisX
                min: xRangeFrom.value
                max: xRangeTo.value
            }

            ValuesAxis {
                id: axisY
                min: yRangeFrom.value
                max: yRangeTo.value
            }


            LineSeries {
                id: series
                axisX: axisX
                axisY: axisY
            }
        }

        RowLayout {
            Label {
                text: "x from"
            }

            SpinBox {
                id: xRangeFrom
                value: -10
                from: -500
                to: 1000
                live: true

                editable: true
                onValueChanged: {
                    kfunctionDataModelMapper.model.setRangeStart(value)
                }
            }

            Label {
                text: "x to"
            }

            SpinBox {
                id: xRangeTo
                value: 10
                from: -500
                to: 1000
                editable: true
                live: true

                onValueChanged: {
                    kfunctionDataModelMapper.model.setRangeFinish(value)
                }
            }

            Label {
                text: "y from"
            }

            SpinBox {
                id: yRangeFrom
                value: -10
                from: -50000
                to: 500000
                editable: true
                live: true
            }

            Label {
                text: "y to"
            }

            SpinBox {
                id: yRangeTo
                value: 10
                from: -50000
                to: 500000
                editable: true
                live: true
            }

            Label {
                text: "dpi"
            }

            SpinBox {
                id: dpi
                editable: true
                value: 2
                from: 1
                to: 10
                live: true

                onValueChanged: {
                    let points = chart.width / 50 * value
                    kfunctionDataModelMapper.model.setPointsCount(points)
                }
            }

            Item { Layout.fillWidth: true }
        }

        RowLayout {

            TextField {
                id: functionText
                text: "sin(x)"
                placeholderText: "Input function"
                Layout.fillWidth: true

                onTextChanged: {
                    kfunctionDataModelMapper.model.setFunction(functionText.text)
                }
            }

            Button {
                text: "apply"
                onClicked: kfunctionDataModelMapper.model.setFunction(functionText.text)
            }

        }

        /// Calculated in QML only -- the editor
        KFunctionQmlEditor {
            id: editor

            xRangeStart: 0
            xRangeFinish: 1000
            yRangeStart: 0
            yRangeFinish: 1000
            dpi: 3

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
