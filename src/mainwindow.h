#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "intelligence.h"

/**
 * \brief Getting MainWondow class from Ui namespace
 *
 */

namespace Ui {
    class MainWindow;
}
/*
 * \brief class MainWindow extending from QMainWindow
 * uses Q_OBJECT macro defined in QMainWindow header
 *
 */

class MainWindow : public QMainWindow, public Pencil
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_makePencil_clicked();
    void runner();
    void seller();
    void apm2Seller();
    void intelligenceRunner();
    void calculatePrices();
    void checkbuttons();
    bool apmCheck();
    bool marketingCheck();
    void disableComponents();

    void on_buyWood_clicked();
    void on_buyGraphite_clicked();
    void on_buyApm_clicked();
    void on_increasePencil_clicked();
    void on_decreasePencil_clicked();
    void on_upgradeApm_clicked();
    void on_unlockMarketing_clicked();
    void on_upgradeMarketing_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
