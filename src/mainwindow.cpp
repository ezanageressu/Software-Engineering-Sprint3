#include <iostream>
#include <QTimer>
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "intelligence.h"
#include "intelligence.cpp"

/* Start: Initialization */

/// Mainwindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /// Label is set to display as soon as the MainWindow class is constructed
    ui->setupUi(this);
    disableComponents();

    /// Timer initialization
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(intelligenceRunner()));
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
    ui->priceofWood->setAlignment(Qt::AlignCenter);
    ui->priceofGraphite->setText("$ "+QString::number(Production::priceofGraphite));
    ui->priceofGraphite->setAlignment(Qt::AlignCenter);
    ui->priceofApmUpgrade->setText(QString::number(Pencil::apmUpgradePrice) + " IQ");
    ui->priceofApmUpgrade->setAlignment(Qt::AlignCenter);

    ui->wallet->setText("$ " + QString::number(Wallet::balance));

    ui->pencilPrice->setText("$ " + QString::number(Pencil::priceofPencil));
    ui->publicDemand->setText(QString::number(Pencil::rateofPencil));
    ui->numberofApm->setText(QString::number(Pencil::numberofApm));
    ui->priceofApm->setText("$ " + QString::number(Pencil::priceofApm));
    ui->priceofApm->setAlignment(Qt::AlignCenter);
    ui->rateofApm->setText(QString::number(Pencil::rateofApm) + " pencils/sec");
    ui->totalinventory->setText(QString::number(Pencil::totalnumberofPencil));
    ui->intelligence->setText(QString::number(Intelligence::intelligenceBalance));
    ui->marketingLevel->setText(QString::number(Pencil::marketing));
    ui->pricetoUnlockMarketing->setText(QString::number(100) + " IQ");
    ui->pricetoUnlockMarketing->setAlignment(Qt::AlignCenter);
    ui->priceofMarketingUpgrade->setText("$ "+QString::number(Pencil::marketingUpgradePrice));
    ui->priceofMarketingUpgrade->setAlignment(Qt::AlignCenter);

    QTimer *timer = new QTimer(this);
    timer->start();
    checkbuttons();
}

void MainWindow::intelligenceRunner(){
    if(!Intelligence::intelligenceIsActive){
        if(Pencil::activateIntelligence()){
            ui->intelligence->setVisible(true);
            ui->intelligenceLabel->setVisible(true);
            ui->upgradeApm->setVisible(true);
            ui->priceofApmUpgrade->setVisible(true);
            ui->unlockMarketing->setVisible(true);
            ui->pricetoUnlockMarketing->setVisible(true);
            return;
        }
        else{
            return;
        }
    }
    Intelligence::increaseIntelligence();
}

//! Function to check which buttons need to be disabled. */
/* setEnabled(0) = disable button, setEnabled(1) = enable button */
void MainWindow::checkbuttons(){
    if(Intelligence::intelligenceIsActive){
        if (apmCheck()){
            ui->upgradeApm->setEnabled(1);
        }
        else{
            ui->upgradeApm->setEnabled(0);
        }

        if (!ui->upgradeMarketing->isVisible() &&
                Intelligence::intelligenceBalance>=100){
            ui->unlockMarketing->setEnabled(1);
        }
        else{
            ui->unlockMarketing->setEnabled(0);
        }

        if(ui->upgradeMarketing->isVisible() &&
                Wallet::balance>=Pencil::marketingUpgradePrice){
            ui->upgradeMarketing->setEnabled(1);
        }
        else{
            ui->upgradeMarketing->setEnabled(0);
        }
    }

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

void MainWindow::on_upgradeApm_clicked(){
    Pencil::upgradeApm();
    ui->upgradeApm->setVisible(false);
    ui->priceofApmUpgrade->setVisible(false);
    checkbuttons();
}


void MainWindow::on_unlockMarketing_clicked()
{
    ui->unlockMarketing->setVisible(false);
    ui->pricetoUnlockMarketing->setVisible(false);
    ui->marketingLabel->setVisible(true);
    ui->marketingLevel->setVisible(true);
    ui->upgradeMarketing->setVisible(true);
    ui->priceofMarketingUpgrade->setVisible(true);
}

void MainWindow::on_upgradeMarketing_clicked()
{
    Pencil::upgradeMarketing();
}

/* End: Buttons and their functionalities */

bool MainWindow::apmCheck(){
    if(ui->upgradeApm->isVisible()){
        if(Intelligence::intelligenceBalance>=Pencil::apmUpgradePrice){
            return true;
        }
        return false;
    }

    else if(Pencil::totalnumberofPencil>=Pencil::pencilsForUpgrade){
        ui->upgradeApm->setVisible(true);
        ui->priceofApmUpgrade->setVisible(true);
        return apmCheck();
    }
    else{
        return false;
    }
}

bool MainWindow::marketingCheck(){
    if(!ui->upgradeMarketing->isVisible()){
        return true;
    }
    return false;
}

void MainWindow::disableComponents(){
    ui->intelligence->setVisible(false);
    ui->intelligenceLabel->setVisible(false);
    ui->upgradeApm->setVisible(false);
    ui->priceofApmUpgrade->setVisible(false);
    ui->unlockMarketing->setVisible(false);
    ui->pricetoUnlockMarketing->setVisible(false);
    ui->upgradeMarketing->setVisible(false);
    ui->priceofMarketingUpgrade->setVisible(false);
    ui->marketingLabel->setVisible(false);
    ui->marketingLevel->setVisible(false);
}
