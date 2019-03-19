#include <iostream>
#include <QTimer>
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pencil.h"
#include "production.h"
#include "wallet.h"

/* Start: Initialization */

/// Mainwindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /// Label is set to display as soon as the MainWindow class is constructed
    ui->setupUi(this);
    /// Timer initialization
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(runner()));
    connect(timer, SIGNAL(timeout()), this, SLOT(seller()));
    connect(timer, SIGNAL(timeout()), this, SLOT(apm2Seller()));
    timer->start(1000);
    ///This timer is used for calculating prices of graphite and wood every 5 sec.
    QTimer *timer5s = new QTimer(this);
    connect(timer5s, SIGNAL(timeout()), this, SLOT(calculatePrices()));
    timer5s->start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* End: Initialization */

/* Start: Functions running every second */

///Function to calculate prices of graphite and wood every 5 second
void MainWindow::calculatePrices(){

  Production::calculatePrices();
  QTimer *timer5s = new QTimer(this);
  timer5s->start();
}
/// Function that updates ui labels every second
void MainWindow::runner()
{
    checkbuttons();
    ui->inventory->setText(QString::number(Pencil::numberofPencil));
    ui->wood->setText(QString::number(Production::numberofWood));
    ui->graphite->setText(QString::number(Production::numberofGraphite));
    ui->priceofWood->setText("$ " + QString::number( Production::priceofWood));
    ui->priceofGraphite->setText("$ "+QString::number(Production::priceofGraphite));

    ui->wallet->setText("$ " + QString::number(Wallet::balance));

    ui->pencilPrice->setText("$ " + QString::number(Pencil::priceofPencil));
    ui->publicDemand->setText(QString::number(Pencil::rateofPencil));
    ui->numberofApm->setText(QString::number(Pencil::numberofApm));
    ui->priceofApm->setText("$ " + QString::number(Pencil::priceofApm));
    ui->rateofApm->setText(QString::number(Pencil::rateofApm) + " pencils/min");
    ui->totalinventory->setText(QString::number(Pencil::totalnumberofPencil));

    QTimer *timer = new QTimer(this);
    timer->start();
    checkbuttons();
}

//! Function to check which buttons need to be disabled. */
/* setEnabled(0) = disable button, setEnabled(1) = enable button */
void MainWindow::checkbuttons(){

  if (Wallet::balance < Production::priceofGraphite){
    ui->buyGraphite->setEnabled(0);
  }else{
    ui->buyGraphite->setEnabled(1);
  }

  if (Wallet::balance < Production::priceofWood){
    ui->buyWood->setEnabled(0);
  }else{
    ui->buyWood->setEnabled(1);
  }

  if (Wallet::balance < Pencil::priceofApm){
    ui->buyApm->setEnabled(0);
  }else{
    ui->buyApm->setEnabled(1);
  }

  ///Prevent the user from setting the price lower than 0
  if (Pencil::priceofPencil <= 0.1){
    ui->decreasePencil->setEnabled(0);
  }else{
    ui->decreasePencil->setEnabled(1);
  }
}

/*! Function to sell pencils continuously every second */
void MainWindow::seller()
{
    Pencil::sell();
    QTimer *timer = new QTimer(this);
    timer->start();
}

/*Function to produce pencils continuously every second */
void MainWindow::apm2Seller()
{
    Pencil::apm2000();
    QTimer *timer = new QTimer(this);
    timer->start();
}

/* End : Functions running every second */

/* Start: Buttons and their functionalities */

void MainWindow::on_buyWood_clicked()
{
    Production::buyWood();
    checkbuttons();
}

void MainWindow::on_buyGraphite_clicked()
{
    Production::buyGraphite();
    checkbuttons();
}

void MainWindow::on_makePencil_clicked()
{
    Pencil::producePencil();
}

void MainWindow::on_increasePencil_clicked()
{
    Pencil::increasePrice();
    Pencil::newRate();
}

void MainWindow::on_decreasePencil_clicked()
{
    Pencil::decreasePrice();
    Pencil::newRate();
}

void MainWindow::on_buyApm_clicked(){
  Pencil::buyApm();
  checkbuttons();
}

/* End: Buttons and their functionalities */
