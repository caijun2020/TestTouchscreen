/**********************************************************************
PACKAGE:        UI
FILE:           PaintWidget.cpp
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Paint Widget
**********************************************************************/

#include "PaintWidget.h"
#include "ui_PaintWidget.h"

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintWidget),
    screenHSize(1024),
    screenVSize(768),
    reverseCoordinateFlag(false)
{
    ui->setupUi(this);

    m_renderArea = new RenderArea(ui->label_painter);

    // Init UI
    initUI();
}

PaintWidget::~PaintWidget()
{
    delete ui;
    delete m_renderArea;
}

void PaintWidget::setXYRange(int32_t xMax, int32_t yMax)
{
    screenHSize = xMax;
    screenVSize = yMax;
    m_renderArea->setXYRange(xMax, yMax);
}

void PaintWidget::updateCoordinate(int x, int y, int z)
{
    if(reverseCoordinateFlag)
    {
        x = abs(screenHSize - x);
        y = abs(screenVSize - y);
    }

    ui->lcdNumber_X->display(x);
    ui->lcdNumber_Y->display(y);

    m_renderArea->updateTouchPoint(x, y);

    if(0 == z)
    {
        ui->label_pressStatus->setText(tr("No Press"));
        m_renderArea->onceTouchDone();
    }
    else
    {
        ui->label_pressStatus->setText(tr("Pressing"));
    }
}


void PaintWidget::on_pushButton_clearScreen_clicked()
{
    m_renderArea->eraseDisplay();
}

void PaintWidget::on_checkBox_reverse_clicked(bool checked)
{
    reverseCoordinateFlag = checked;
}

void PaintWidget::initUI()
{
    ui->checkBox_reverse->setChecked(reverseCoordinateFlag);
}
