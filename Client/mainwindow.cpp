#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textclient.h"
#include <QMessageBox>
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    connect(ui->txtEditor, SIGNAL(textChanged()),
            this, SLOT(data_changed()));

    ui->txtEditor->setEnabled(false);
    ui->bDisconncet->setEnabled(false);

    connect(ui->bDisconncet, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::assignWebClient(TextClient *ncl) {
    cl = ncl;
    connect(cl, SIGNAL(got_new_data()), this, SLOT(data_received()));
}

void MainWindow::on_bConnect_clicked(){

    int connect_res = cl->sconnect();
    if (connect_res) {
        QMessageBox::critical(NULL, QString("Connection error"),
                              QString("Error code: " + QString::number(connect_res)));
    }
    else {
        ui->bConnect->setEnabled(false);
        ui->bDisconncet->setEnabled(true);
        ui->txtEditor->setEnabled(true);
    }
}

void MainWindow::data_changed() {
    QPlainTextEdit *source = (QPlainTextEdit*)sender();
    if (source->document()->isModified()) {
        cl->sendData(source->toPlainText());
    }
}
void MainWindow::data_received() {

    TextClient* client = (TextClient*)sender();

    char* data = client->getBuf();

    string line(data);

    int pos = ui->txtEditor->textCursor().positionInBlock();
    int line_num = ui->txtEditor->textCursor().blockNumber();

    ui->txtEditor->setPlainText(QString::fromStdString(line));

    QTextCursor cursor = ui->txtEditor->textCursor();
    cursor.setPosition(0);
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line_num + 1);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos);

    ui->txtEditor->setTextCursor(cursor);
}
