#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<tins/tins.h>
#include<iostream>
#include<cstring>

using namespace Tins;


bool MainWindow::callback(const PDU &pdu) {


    const IP &ip = pdu.rfind_pdu<IP>(); // Find the IP layer
    const TCP &tcp = pdu.rfind_pdu<TCP>(); // Find the TCP layer

    std::cout << ip.src_addr() << ':' << tcp.sport() << " -> "
              << ip.dst_addr() << ':' << tcp.dport() << std::endl;
    return true;
}


bool MainWindow::callbackdest(const PDU &pdu)
{

    const IP ip = pdu.rfind_pdu<IP>(); // non-const works as well
    int proto = (int)ip.protocol();



 //  MainWindow *m= new MainWindow();
  // m->nothing("asd");

    std::cout << "Destination address: " << ip.dst_addr() <<" Protocol: "<<proto<< std::endl;
    // Just one packet please
    return true;

}


bool MainWindow::callbackport(const PDU &pdu)
{


    const TCP tcp = pdu.rfind_pdu<TCP>();
    //const RawPDU pdu1 = pdu.rfind_pdu<RawPDU>();
    const IP ip = pdu.rfind_pdu<IP>(); // non-const works as well
    int proto = (int)ip.protocol();
    std::cout << "Destination address: " << ip.dst_addr() <<" Protocol: "<<proto<<" Src port:"<<tcp.sport()<<" Dest port:"<<tcp.dport()<< std::endl;


    return true;

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString s=ui->ipadd->text();
    std::string ss= s.toStdString();

    Sniffer sniffer("wlan0", Sniffer::PROMISC);

    if(ui->radioButton->isChecked()){
        sniffer.set_filter("dst port 21");
        sniffer.sniff_loop(callbackport);
    }

    if(ui->radioButton_2->isChecked()){
        sniffer.set_filter("udp and dst port 53");
        sniffer.sniff_loop(callback);
    }

    if(ui->radioButton_3->isChecked()){
       std::string filter="ip dst ";
       strcat((char *)filter.data(),ss.data());
       std::cout<<filter;

       sniffer.set_filter(filter);
       sniffer.sniff_loop(callbackdest);
    }


}

void MainWindow::on_pushButton_pressed()
{
ui->packetdata->appendPlainText("Sniffing Has Started");
ui->packetdata->appendHtml("<br/><h1> Check Terminal");
}

void MainWindow::nothing(char *s){
    std::cout<<"ada.asd.das.sdas.d";
    ui->packetdata->appendPlainText("HEYYYYYYY");
}
