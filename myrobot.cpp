// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend.resize(9);
    DataToSend[0] = static_cast<char>(0xFF);
    DataToSend[1] = 0x07;

    // left
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;

    // right
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;

    // char
    DataToSend[6] = 0x0;

    short mycrcsend = Crc16(DataToSend, 6);
    DataToSend[7] = static_cast<char>(mycrcsend);
    DataToSend[8] = static_cast<char>(mycrcsend >> 8);

    DataReceived.resize(21);
    TimerEnvoi = new QTimer();

    // connect the "tic" of the timer with our method
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}

// Connect us to the robot with TCP protocol (cf datasheet wifibot)
void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.10", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

// disconnect us from the robot : stop the timer and close the tcp socket
void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

// Listener of connection
void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

// Listener of disconnect
void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

// Setup the correct value of DataToSend with those four parameter
void MyRobot::writeData(short leftSpeed, short rightSpeed, bool leftForward, bool rightForward) {
    QByteArray local;
    local.resize(9);

    // init
    local[0] = static_cast<char>(0xFF);
    local[1] = 0x07;

    // left speed
    local[2] = static_cast<char>(leftSpeed);
    local[3] = static_cast<char>(leftSpeed >> 8);

    // right speed
    local[4] = static_cast<char>(rightSpeed);
    local[5] = static_cast<char>(rightSpeed >> 8);

    // special byte
    int tmp = 128+32; // Close loop control always ON (128 left loop / 32 right loop)
    if(leftForward) tmp += 64;
    if(rightForward) tmp += 16;
    local[6] = static_cast<char>(tmp);

    // CRC
    short crc = Crc16(local, 6);
    local[7] = static_cast<char>(crc);
    local[8] = (crc>>8);

    printData(local); // listener
    this->DataToSend.replace(0,9,local); // remplace the data contained into QByteArray by our local one
}

// Reset DataToSend to his construction value : robot idle status.
void MyRobot::resetDataToSend(){
    this->DataToSend.resize(9);
    this->DataToSend[0] = static_cast<char>(0xFF);
    this->DataToSend[1] = 0x0;
    this->DataToSend[2] = 0x0;
    this->DataToSend[3] = 0x0;
    this->DataToSend[4] = 0x0;
    this->DataToSend[5] = 0x0;
    this->DataToSend[6] = 0x0;

    short mycrcsend = Crc16(this->DataToSend, 6);
    this->DataToSend[7] = static_cast<char>(mycrcsend);
    this->DataToSend[8] = (mycrcsend >> 8);
    printData(this->DataToSend);
}

// Method just to make sure than we are sending stuff
void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

// Read the data that the robot send us (updateUI have to be written)
void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
   // struct data data = getData(DataReceived);
    qDebug() << "DataReceived : " << DataReceived;
    printData(DataReceived);
    emit updateUI(DataReceived);
    qDebug() << "dataReceived ";
}

// What's consuming the signal generated by the timer clock
void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

// CRC implementation, source code : datasheet with some light modification to work with our code/project
short MyRobot::Crc16(QByteArray Array, unsigned char Taille_max)
{
    unsigned char * Adresse_tab;
    Adresse_tab = (unsigned char *) Array.data();

    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet = 1; CptOctet < Taille_max+1; CptOctet++)
    {
        //qDebug() << "AdrTab+Cpt : " << *(Adresse_tab+CptOctet);
        Crc ^= *(Adresse_tab + CptOctet);
        for (CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(static_cast<short>(Crc));
}

// Debug tools : print onto the console the DataToSend
void MyRobot::printData(QByteArray qb){
    QDebug debug = qDebug();
    for(int i=0; i<qb.size(); i++){
        debug << static_cast<unsigned char>(qb[i]) << " ";
    }
}
