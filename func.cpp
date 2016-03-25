#include "func.h"

Func::Func()
{
    msg.setWindowIcon(QIcon(":/main.png"));
    msg.setWindowTitle("Оповещение");
}

Func::Func(QWidget *objMainWindow, QWebView *webView, QListWidget *widgetAlbum, QListWidget *widgetGroup,
           QStringList *listAlbum, QStringList *listGroup, QString *sendText,
           QStatusBar *statusBar, bool *loadFin, QProgressBar *progressBar, QLabel *labelPause,
           QString wayToFolder, bool *withPauseBeforePaste)
{
    this->objMainWindow = objMainWindow;
    this->widgetAlbum = widgetAlbum;
    this->widgetGroup = widgetGroup;
    this->statusBar = statusBar;
    this->listAlbum = listAlbum;
    this->listGroup = listGroup;
    this->loadFin = loadFin;
    this->sendText = sendText;
    this->webView = webView;
    this->progressBar = progressBar;
    this->labelPause = labelPause;
    this->wayToFolder = wayToFolder;
    this->withPauseBeforePaste = withPauseBeforePaste;
    msg.setWindowIcon(QIcon(":/main.png"));
    msg.setWindowTitle("Оповещение");
    xCorectPos = 15;
    yCorectPos = 15;
    char* filename2 = "../temp.png";
    char* filename3 = "../tempCaptha.png";
    templ = cvLoadImage(filename2,1);
    templCaptha = cvLoadImage(filename3,1);
}


Func::~Func()
{

}

void Func::test(){
    for(int i=0;i<999;i++){
        if(!pauseSend){
            //qDebug() << i;
            mySleep(50);
        }else{
            i--;
            mySleep(100);
        }
    }
}


void Func::loadFile(QWidget *objMainWindow, QStringList &list, QStatusBar *bar){
    list.clear();
    QString fileName=QFileDialog::getOpenFileName(objMainWindow, "OpenFile", "D:\\", "Text Files (*.txt);;");
    if(fileName.isEmpty()){
        bar->showMessage("Ошибка загрузки. Код ошибки: 1", 10000);
        return;
    }
    QFile file( fileName );
    file.open( QIODevice::ReadOnly );
    if(!file.isOpen()){
        bar->showMessage("Ошибка загрузки. Код ошибки: 2", 10000);
        return;
    }
    QTextStream stream(&file);
    for(int i=0; !stream.atEnd(); i++){
        list.append( stream.readLine());
    }
    file.close();
}

void Func::saveFile(QWidget *objMainWindow, QStringList &list, QStatusBar *bar){
    QString fileName=QFileDialog::getSaveFileName(objMainWindow, "SaveFile", "D:\\", "Text Files (*.txt);;");
    if(fileName.isEmpty()){
        bar->showMessage("Ошибка сохранения. Код ошибки: 1", 10000);
        return;
    }
    QFile file( fileName );
    file.open( QIODevice::WriteOnly );
    if(!file.isOpen()){
        bar->showMessage("Ошибка сохранения. Код ошибки: 2", 10000);
        return;
    }
    QTextStream stream(&file);
    for(int i=0; i < list.size(); i++){
        stream << list.at(i) << endl;
    }
    file.close();
}

void Func::autoLoadFile(){
    QFile file( "../album.txt" );
    file.open( QIODevice::ReadOnly );
    if(!file.isOpen()){
        statusBar->showMessage("Ошибка загрузки. Код ошибки: 3", 10000);
    }else{
        QTextStream stream(&file);
        for(int i=0; !stream.atEnd(); i++){
            listAlbum->append( stream.readLine());
        }
        file.close();
    }
    QFile file1( "../group.txt" );
    file1.open( QIODevice::ReadOnly );
    if(!file1.isOpen()){
        statusBar->showMessage("Ошибка загрузки. Код ошибки: 4", 10000);
        return;
    }
    QTextStream stream1(&file1);
    for(int i=0; !stream1.atEnd(); i++){
        listGroup->append( stream1  .readLine());
    }
    file1.close();
}

void Func::showList(QListWidget *widget, QStringList &list){
    widget->clear();
    for(int i = 0; i < list.size(); i++){
        widget->addItem(list.at(i));
    }
}

bool Func::searchEnter(){
    doSnapShot();
    // имя картинки задаётся первым параметром
    IplImage* image = 0;

    IplImage *res = 0;

    char* filename = "\\src.png";
    qDebug()  << filename;

    assert( templ != 0 );
    qDebug() << templ;

    // получаем картинку
    image = cvLoadImage(filename,1);
    qDebug() << image;
    assert( image != 0 );

    qDebug() << "1";
    res = cvCreateImageHeader(cvSize( ((image->width) - (templ->width) + 1), ((image->height) - (templ->height) + 1)), IPL_DEPTH_32F, 1);
    qDebug() << "2";
    cvCreateData(res);
    qDebug() <<"3";
    res = cvCreateImage( cvSize( ((image->width) - (templ->width) + 1), ((image->height) - (templ->height) + 1)), IPL_DEPTH_32F, 1 );

    // сравнение изображения с шаблоном
    cvMatchTemplate(image, templ, res, CV_TM_SQDIFF_NORMED);
    qDebug() <<"4";

    double    minval, maxval;
    CvPoint    minloc, maxloc;
    cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);
    xPosCursor = minloc.x;
    yPosCursor = minloc.y;

    if(minval > 0.002){
        qDebug() << "Не нашел";
        statusBar->showMessage("Поле ввода не найдено", 5000);
        cvReleaseImage( &image );
        cvReleaseImage( &res );
        return false;
    } else{
        qDebug() << "Нашел";
        statusBar->showMessage("Поле ввода найдено", 5000);
    }

    // освобождаем ресурсы
    cvReleaseImage( &image );
    cvReleaseImage( &res );
    //cvDestroyAllWindows();
    return true;
}

void Func::useArrow(){
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
    keybd_event(VK_DOWN, 0, 0 ,0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP,0);
    mySleep(5);
}

void Func::usePaste(){
    QString temp;
    for(int i = 0; i < listAlbum->size(); i++){
        temp.append(listAlbum->at(i)+"\n");
    }
    setBuffer(temp);
    mySleep(50);
    keybd_event(VK_CONTROL, 0, 0 ,0);
    keybd_event(0x56, 0, 0 ,0);
    keybd_event(0x56, 0, KEYEVENTF_KEYUP ,0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
    for(int i = 0; i < listAlbum->size() + 1; i++){
        mySleep(400);
        keybd_event(VK_SPACE, 0, 0 ,0);
        keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP,0);
    }
    mySleep(400);
    keybd_event(VK_CONTROL, 0, 0 ,0);
    keybd_event(0x41, 0, 0 ,0);
    keybd_event(0x41, 0, KEYEVENTF_KEYUP ,0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
    mySleep(100);

    keybd_event(VK_BACK, 0, 0 ,0);
    keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP ,0);

    if((*sendText) == ""){

    }else{
        setBuffer(*sendText);
        mySleep(100);
        keybd_event(VK_CONTROL, 0, 0 ,0);
        keybd_event(0x56, 0, 0 ,0);
        keybd_event(0x56, 0, KEYEVENTF_KEYUP ,0);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);

    }
    mySleep(200);
    keybd_event(VK_CONTROL, 0, 0 ,0);
    keybd_event(VK_RETURN, 0, 0 ,0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP,0);
    mySleep(500);//Удалить для скорости ///////////////////////////////////////////////////////////////////

}

void Func::setBuffer(QString buf){
    const char* output = buf.toLocal8Bit().constData();
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

bool Func::searchCaptha()
{
    doSnapShot();
    qDebug() << "Поиск капча";
    IplImage* image = 0;

    IplImage *res = 0;

    char* filename = "\\src.png";
    qDebug()  << filename;



    // получаем картинку
    image = cvLoadImage(filename,1);
    qDebug() << image;

    assert( image != 0 );


    qDebug() << "1капча";
    res = cvCreateImageHeader(cvSize( ((image->width) - (templCaptha->width) + 1), ((image->height) - (templCaptha->height) + 1)), IPL_DEPTH_32F, 1);
    qDebug() << "2капча";
    cvCreateData(res);
    qDebug() <<"3капча";
    res = cvCreateImage( cvSize( ((image->width) - (templCaptha->width) + 1), ((image->height) - (templCaptha->height) + 1)), IPL_DEPTH_32F, 1 );

    cvMatchTemplate(image, templCaptha, res, CV_TM_SQDIFF_NORMED);
    qDebug() <<"4капча";

    double    minval, maxval;
    CvPoint    minloc, maxloc;
    cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);
    xPosCursor = minloc.x;
    yPosCursor = minloc.y;

    if(minval > 0.002){
        qDebug() << "Не нашел капча";
        statusBar->showMessage("Поле ввода не найдено", 5000);
        cvReleaseImage( &image );
        cvReleaseImage( &res );
        return false;
    } else{
        qDebug() << "Нашел капча";
        statusBar->showMessage("Поле ввода найдено", 5000);
    }

    cvReleaseImage( &image );
    cvReleaseImage( &res );
    return true;
}

bool Func::getPauseSend() const
{
    return pauseSend;
}

void Func::setPauseSend(bool value)
{
    pauseSend = value;
}

void Func::setCorectPos(int x, int y)
{
    this->xCorectPos = x;
    this->yCorectPos = y;
    qDebug() << "Corect pos" << this->xCorectPos << " " << this->yCorectPos;
}


void Func::startSender(){
    qDebug() << this->wayToFolder;
    progressBar->setMaximum(listGroup->size());
    progressBar->setMinimum(0);
    for(int i = 0, timesArrow = 0, timesFin = 0; i < listGroup->size(); i++, timesArrow = 0, timesFin = 0){
        //qDebug() << listGroup->at(i);
        while(pauseSend)mySleep(200);
        while(!(*loadFin)){
            mySleep(200);
            if(timesFin > 20){
                timesFin = 0;
                *loadFin = true;
                break;
            }
            timesFin++;
        }
        *loadFin = false;
        mySleep(100);
        while(pauseSend)mySleep(200);
        webView->setUrl(listGroup->at(i));
        mySleep(500);
        while(!(*loadFin)){
            if(timesFin > 20){
                timesFin = 0;
                *loadFin = true;
                break;
            }
            mySleep(200);
            timesFin++;
        }
        while(pauseSend)mySleep(200);
        mySleep(200);
        useArrow();
        mySleep(200);
        while(!searchEnter() && timesArrow < 6){
            useArrow();
            mySleep(200);
            timesArrow++;
            while(pauseSend)mySleep(200);
        }
        if(timesArrow == 6)continue;
        mySleep(150);
        while(pauseSend)mySleep(200);
        SetCursorPos(xPosCursor + xCorectPos, yPosCursor + yCorectPos);
        mySleep(250);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
        mySleep(200);
        if(*withPauseBeforePaste)mySleep(2000);
        while(pauseSend)mySleep(200);
        usePaste();
        if( i > listGroup->size()/2){
            mySleep(500);
            if(searchCaptha()){
                Beep(500, 300);
                Beep(600, 500);
                mySleep(820);// задержка мелодии т.е. спим 
                Beep(600, 300);
                Beep(500, 500);
                mySleep(820);// задержка мелодии т.е. спим 
                Beep(670, 210);
                Beep(600, 210);
                Beep(670, 210);
                Beep(600, 210);
                Beep(670, 210);
                Beep(600, 210);
                Beep(670, 210);
                Beep(600, 210);
                Beep(670, 210);
                Beep(750, 550);
                pauseSend = true;
                while(pauseSend)mySleep(200);
            }
        }
        progressBar->setValue(progressBar->value() + 1);

    }
    progressBar->setValue(progressBar->value() + 1);
    statusBar->showMessage("Рассылка закончена", 10000);
    msg.setText("Рассылка окончена");
    msg.exec();

}

void Func::mySleep(int time){
    QTimer::singleShot(time, &wait, SLOT(quit()));
    wait.exec();
}

void Func::doSnapShot(){
    qDebug() << "enter doSnapShot";
    QPixmap okno = QPixmap::grabWindow(QApplication::desktop()->winId());
    QFile file("\\src.png");
    file.open(QIODevice::WriteOnly);
    okno.save(&file, "PNG");
    mySleep(20);
    file.close();
    qDebug() << "out doSnapShot";
}
