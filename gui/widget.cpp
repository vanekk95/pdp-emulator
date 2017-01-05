#include "widget.h"
#include "ui_widget.h"
#include "formain.h"
#include <QTableWidget>

Widget::Widget(QWidget *parent, Arg *arg) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    while (!arg->sharedMem->isFull);
    sharedMem = arg->sharedMem;
    callList = arg->callList;

    tableModel = new TableModel();
    tableModel->setSharedMem(sharedMem);
    ui->tableCommand->setModel(tableModel);
    ui->tableCommand->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableCommand->resizeColumnsToContents();
    ui->tableCommand->setItemDelegate(new StyledDelegate(this, sharedMem->asmCommand));

    ui->bitmap->setMatrix(sharedMem->vidio_memory);

    connect(ui->buttonRun,      SIGNAL(clicked()), this, SLOT(slotButtonRun()));
    connect(ui->buttonStop,     SIGNAL(clicked()), this, SLOT(slotButtonStop()));
    connect(ui->buttonStep,     SIGNAL(clicked()), this, SLOT(slotButtonStep()));
    connect(ui->buttonContinue, SIGNAL(clicked()), this, SLOT(slotButtonContinue()));
    connect(ui->buttonReset,    SIGNAL(clicked()), this, SLOT(slotButtonReset()));
    connect(ui->tableCommand,   SIGNAL(doubleClicked(QModelIndex)), this,
            SLOT(userClicked(QModelIndex)));

    ui->buttonContinue->setEnabled(false);
    ui->buttonStep->setEnabled(false);
    ui->buttonStop->setEnabled(false);
    ui->buttonReset->setEnabled(false);

    timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()) , this, SLOT(slotUpdateRegister()));
    timer->start();

}

void Widget::userClicked(QModelIndex index) {
    tableModel->headerDoubleClick(index);
    ui->tableCommand->reset();
    int address = sharedMem->asmCommand[index.row()].address;
    callList->setBreakPointForAddress = address;

    tableModel->setData(index, QBrush(Qt::red), Qt::BackgroundRole);
}

void Widget::slotUpdateRegister() {
    char strtmp[100];
    sprintf(strtmp, "0x%x", sharedMem->registers[0]);
    ui->val_R_0->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[1]);
    ui->val_R_1->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[2]);
    ui->val_R_2->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[3]);
    ui->val_R_3->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[4]);
    ui->val_R_4->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[5]);
    ui->val_R_5->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[6]);
    ui->val_R_6->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[7]);
    ui->val_R_7->setText(strtmp);

    sprintf(strtmp, "x%x", *sharedMem->flags);
    ui->val_flags->setText(strtmp);
}

void Widget::setEnableButton(State state) {
    switch (state) {
    case StateInit:
        ui->buttonRun->setEnabled(true);
        ui->buttonContinue->setEnabled(false);
        ui->buttonStep->setEnabled(false);
        ui->buttonStop->setEnabled(false);
        ui->buttonReset->setEnabled(false);
        break;
    case StateRun:
        ui->buttonRun->setEnabled(false);
        ui->buttonContinue->setEnabled(false);
        ui->buttonStep->setEnabled(false);
        ui->buttonStop->setEnabled(true);
        ui->buttonReset->setEnabled(true);
        break;
    case StateStop:
        ui->buttonRun->setEnabled(false);
        ui->buttonContinue->setEnabled(true);
        ui->buttonStep->setEnabled(true);
        ui->buttonStop->setEnabled(false);
        ui->buttonReset->setEnabled(true);
        break;
    }
}

void Widget::slotButtonRun() {
    callList->doRun = 1;
    setEnableButton(StateRun);
}

void Widget::slotButtonStop() {
    callList->doStopReset = 1;
    setEnableButton(StateStop);
}

void Widget::slotButtonReset() {
    callList->doStopReset = 1;
    setEnableButton(StateInit);
}

void Widget::slotButtonContinue() {
    callList->doRun = 1;
    setEnableButton(StateRun);
}

void Widget::slotButtonStep() {
    callList->doStep = 1;
    setEnableButton(StateStop);
}

Widget::~Widget()
{
    delete ui;
}
