import QtQuick
import QtCharts
import QmlKfunctionEditor

ChartView {
    id: root

    property string kfunction: "sin(x)"
    property alias xRangeStart: axisX.min
    property alias xRangeFinish: axisX.max
    property alias yRangeStart: axisY.min
    property alias yRangeFinish: axisY.max
    property double dpi: 2

    property kfunction kfunctionWrapper

    function resetGraph() {
        series.clear()
        let pointsCount = width / 50 * dpi
        let step = (xRangeFinish - xRangeStart) / pointsCount
        for (let x = xRangeStart; x < xRangeFinish; x += step) {
            series.append(x, kfunctionWrapper.run(x))
        }
    }

    onKfunctionChanged: {
        kfunctionWrapper.set_function(kfunction)
        resetGraph()
    }
    onXRangeStartChanged: resetGraph()
    onXRangeFinishChanged: resetGraph()
    onDpiChanged: resetGraph()

    legend.visible: false
    animationOptions: ChartView.AllAnimations
    theme: ChartView.ChartThemeBrownSand

    ValuesAxis {
        id: axisX
    }

    ValuesAxis {
        id: axisY
    }

    LineSeries {
        id: series
        axisX: axisX
        axisY: axisY
    }
}
