#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void CalculOhms();
    void CalculCost();
    void CalculDistCov();
    void CalculAcc();
    void CalculKinRot();
    void CalculKinLin();
    void CalculAccel();
    void clearAll();


private:
    Ui::MainWindow *ui;

    double Volt;
    double Ohms;
    double Power;
    double Current;

    double TpsUsage;
    double PowerCons;
    double Rate;
    double Energie;
    double Cost;

    double convertToDate(double value);

    double Distance;
    double Time;
    double Initial_Velocity;
    double Final_Velocity;
    double Acc;

    double Velocity;
    double Kinetic;
    double Mass;
    double Moment_Inert;
    double Angular_Vel;

    double Final_Speed;
    double Initial_Speed;

    enum ConversionType {
        volts,
        ohms,
        watts,
        current,
        distance,
        kg,
        time,
        final_Velocity,
        PowerC
    };

    double convert(double value, ConversionType type);
};

#endif // MAINWINDOW_H
