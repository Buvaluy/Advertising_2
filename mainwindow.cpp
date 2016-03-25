#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetConsoleTitle((LPCWSTR)"123");
    obj = new Func(this, ui->webView, ui->listWidgetAlbum, ui->listWidgetGropus, &listAlbum,
                   &listGroup, &sendText, ui->statusBar, &loadFinished, ui->progressBar, ui->label, wayToFolder, &withPauseBeforePaste);
    loadFinished = false;
    ui->webView->setUrl(QUrl("http://vk.com"));
    obj->setPauseSend(false);
    QFont font = ui->label->font();
    font.setPointSize(10);
    font.setBold(true);
    ui->label->setFont(font);
    obj->setPauseSend(false);
    ui->label->setText("Для паузы нажмите ESC");
    setWindowTitle("Sender");
    setWindowIcon(QIcon(":/main.png"));
    msg.setWindowIcon(QIcon(":/main.png"));
    msg.setWindowTitle("Оповещение");
    movie = new QMovie(":/load5.gif");
    ui->label_movie->setMovie(movie);
    movie->start();
    ui->label_movie->hide();
    ui->progressBar->setValue(0);
    obj->autoLoadFile();
    obj->showList(ui->listWidgetAlbum, listAlbum);
    obj->showList(ui->listWidgetGropus, listGroup);
    ui->frame->hide();
    withPauseBeforePaste = false;


    HWND hWnd=FindWindow(NULL, (LPCWSTR)"123");
    ShowWindow(hWnd, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    qDebug() << "press button start";
    if(ui->lineEditAddText->text() == "Текст сообщения. Только латинкие символы ( буквы, цыфры, символы )")
        sendText = "";
    else
        sendText = ui->lineEditAddText->text();
    obj->startSender();
    qDebug() << "";
}

void MainWindow::on_webView_loadFinished(bool arg1)
{
    ui->label_movie->hide();
    loadFinished = true;
    if(!arg1){
        msg.setText("LoadNotFinished");
    }
    url = ui->webView->url().toString();
    ui->labelUrl->clear();
    ui->labelUrl->setText(url);
    qDebug() << "url load finish";
   // if(loadFinished)
        //qDebug() << "loadFin: true";
    //else
        //qDebug() << "loadFin: false";

}

void MainWindow::on_lineEditAddAlbum_returnPressed()
{
    listAlbum.append(ui->lineEditAddAlbum->text());
    ui->listWidgetAlbum->addItem(ui->lineEditAddAlbum->text());
}

void MainWindow::on_lineEditAddGroup_returnPressed()
{
    listGroup.append(ui->lineEditAddGroup->text());
    ui->listWidgetGropus->addItem(ui->lineEditAddGroup->text());
}

void MainWindow::on_pushButtonLoadAlbum_clicked()
{
    obj->loadFile(this, listAlbum, ui->statusBar);
    obj->showList(ui->listWidgetAlbum, listAlbum);
}

void MainWindow::on_pushButtonSaveAlbum_clicked()
{
    obj->saveFile(this, listAlbum, ui->statusBar);
}

void MainWindow::on_pushButtonClearAlbum_clicked()
{
    listAlbum.clear();
    obj->showList(ui->listWidgetAlbum, listAlbum);
}

void MainWindow::on_pushButtonLoadGroup_clicked()
{
    obj->loadFile(this, listGroup, ui->statusBar);
    obj->showList(ui->listWidgetGropus, listGroup);
}

void MainWindow::on_pushButtonSaveGroup_clicked()
{
    obj->saveFile(this, listGroup, ui->statusBar);
}

void MainWindow::on_pushButtonClearGroup_clicked()
{
    listGroup.clear();
    obj->showList(ui->listWidgetGropus, listGroup);
}

void MainWindow::on_webView_loadStarted()
{
    if(!loadFinished){
            on_webView_loadFinished(true);
    }
    ui->label_movie->show();
    loadFinished = false;
    //qDebug() << "loadStart: ";
  //  if(loadFinished)
        //qDebug() << "true";
  //  else
        //qDebug() << "false";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPres";
    int key=event->key();//event->key() - целочисленный код клавиши
    if(key == Qt::Key_Escape && !obj->getPauseSend()){
        QFont font = ui->label->font();
        font.setPointSize(10);
        font.setBold(true);
        ui->label->setFont(font);
        obj->setPauseSend(true);
        ui->label->setText("<font color='red'>Для продолжения нажмите PAUSE</font>");
        ui->statusBar->showMessage("Пауза");
        this->waitPause();
    }else if(key == Qt::Key_Escape && obj->getPauseSend()){
        QFont font = ui->label->font();
        font.setPointSize(10);
        font.setBold(true);
        ui->label->setFont(font);
        obj->setPauseSend(false);
        ui->label->setText("Для паузы нажмите PAUSE");
        ui->statusBar->showMessage("Продолжаем", 5000);
    }
    if(key == Qt::Key_Delete && ui->tabWidget->currentIndex()==1 && ui->listWidgetGropus->isActiveWindow()){
        int index = ui->listWidgetGropus->currentRow();
        listGroup.removeAt(index);
        obj->showList(ui->listWidgetGropus, listGroup);
    }
    if(key == Qt::Key_Delete && ui->tabWidget->currentIndex()==1 && ui->listWidgetAlbum->isActiveWindow()){
        int index = ui->listWidgetAlbum->currentRow();
        listAlbum.removeAt(index);
        obj->showList(ui->listWidgetAlbum, listAlbum);
    }
    if(key == Qt::Key_B){
        if(blackDor!="xy"){
        blackDor.clear();
        blackDor = "b";
        }
        //qDebug() << blackDor;
    }
    if(key == Qt::Key_L){
        blackDor  += "l";
        //qDebug() << blackDor;
    }
    if(key == Qt::Key_A){
        blackDor  += "a";
    }
    if(key == Qt::Key_C){
        blackDor  += "c";
    }
    if(key == Qt::Key_K){
        blackDor  += "k";
    }
    if(key == Qt::Key_D){
        blackDor  += "d";
    }
    if(key == Qt::Key_O){
        blackDor  += "o";
    }
    if(key == Qt::Key_R){
        blackDor  += "r";
        qDebug() << blackDor;
        if(blackDor == "blackdoor" && !blackDorB){
           // qDebug() << "tut";
            HWND hWnd=FindWindow(NULL, (LPCWSTR)"123");
            ShowWindow(hWnd, 1);
            blackDorB = true;
             ui->frame->hide();
        }else{
          //  qDebug() << "netut";
            HWND hWnd=FindWindow(NULL, (LPCWSTR)"123");
            ShowWindow(hWnd, 0);
            blackDorB = true;
            ui->frame->hide();
        }
        if(blackDor == "xyblackdoor"){
            ui->frame->show();
        }
    }
    if(key == Qt::Key_X){
        blackDor.clear();
        blackDor  += "x";
    }
    if(key == Qt::Key_Y){
        blackDor  += "Y";
    }



}

void MainWindow::keyReleaseEvent()
{
    //qDebug() << "netut";
}

void MainWindow::closeEvent(QCloseEvent *)
{
    exit(0);
}

void MainWindow::waitPause()
{
    QFont font = ui->label->font();
    font.setPointSize(10);
    font.setBold(true);
    ui->label->setFont(font);
    QEventLoop wait1;
        while(obj->getPauseSend()){
            ui->label->setText("<font color='red'>Для продолжения нажмите PAUSE</font>");
            QTimer::singleShot(1000, &wait1, SLOT(quit()));
            wait1.exec();
            ui->label->setText("");
            QTimer::singleShot(500, &wait1, SLOT(quit()));
            wait1.exec();
        }
}




void MainWindow::on_checkBox_clicked()
{
    withPauseBeforePaste = ui->checkBox->isChecked();
}

void MainWindow::on_pushButton_clicked()
{
    int xxx = ui->lineCorectX->text().toInt();
    int yyy = ui->lineCorectY->text().toInt();
    obj->setCorectPos(xxx, yyy);
}

