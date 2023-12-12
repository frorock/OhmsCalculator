#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>
#include <QMainWindow>
#include<QTabWidget>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_CalculOhms, SIGNAL(clicked()), this, SLOT(CalculOhms()));
    connect(ui->pushButton_CalculCost, SIGNAL(clicked()), this, SLOT(CalculCost()));
    connect(ui->pushButton_CalculDistance, SIGNAL(clicked()), this, SLOT(CalculDistCov()));
    connect(ui->pushButton_CalculAcc, SIGNAL(clicked()), this, SLOT(CalculAcc()));
    connect(ui->pushButton_CalculRot, SIGNAL(clicked()), this, SLOT(CalculKinRot()));
    connect(ui->pushButton_CalculLin, SIGNAL(clicked()), this, SLOT(CalculKinLin()));
    connect(ui->pushButton_CalculAcceleration, SIGNAL(clicked()), this, SLOT(CalculAccel()));

    connect(ui->pushButton_ClearOhms, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_ClearCost, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_ClearVel1, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_ClearVel2, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_ClearKin1, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_ClearKin2, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_ClearAcc, SIGNAL(clicked()), this, SLOT(clearAll()));

}

double MainWindow::convert(double value, ConversionType type)
{
    int index;

    switch (type) {
        case volts:
            index = ui->comboBox_Volt->currentIndex();
            break;
        case ohms:
            index = ui->comboBox_Ohms->currentIndex();
            break;
        case watts:
            index = ui->comboBox_Power->currentIndex();
            break;
        case current:
            index = ui->comboBox_Current->currentIndex();
        break;
        case distance:
            index = ui->comboBox_Distance->currentIndex();
        break;
        case time:
            index = ui->comboBox_Time->currentIndex();
        break;
        case final_Velocity:
            index = ui->comboBox_Final_Velocity->currentIndex();
        break;
        case PowerC:
            index = ui->comboBox_PowerC->currentIndex();
        break;
        case kg:
        index = ui->comboBox_mass->currentIndex();
                break;
            default:
                return value;



    }
    if (type == PowerC)
    {
         switch (index)
         {
             case 0: // W
                 return value / 1000.0; // Convertir en kW
             case 1: // MW
                 return value * 1000.0; // Convertir en kW
             case 2: // KW
                 return value;
             case 3: // mW
                 return value / 1000000.0; // Convertir en kW
             default:
                 return value;
         }
     }
    else if (type == time)
    {
        switch (index) {
            case 0: // s
                return value;
            case 1: // min
                return value * 60.0;
            case 2: // h
                return value * 3600.0;
            default:
                return value;
    }   }
    else if (type == distance)
    {
        switch (index) {
            case 0: // s
                return value;
            case 1: // min
                return value * 1000000.0;
            case 2: // h
                return value / 1000000.0;
            default:
                return value;
    }   }

    else
    {
        switch (index)
        {
        case 0: // V, Ohms, W, A
            return value;
        case 1: // KV, KOhms, KW, KA
            return value * 1000.0;
        case 2: // mV, MOhms, mW, mA
            if (type == ohms) {
                return value * 1000000.0;
            } else {
                return value / 1000.0;
            }
        case 3: // MV, MOhms, MW, MA
            return value * 1000000.0;
        default:
            return value;
         }
    }
}

double MainWindow::convertToDate(double value)
{
    int index = ui->comboBox_date->currentIndex();
       switch (index) {
           case 0: // Days
               return value * 24.0 * 30.0 / 24.0; // Convertir les jours en heures et diviser par 24 pour obtenir les heures par jour
           case 1: // Week
               return value * 24.0 * 7.0 * 30.0 / (24.0 * 7.0) ; // Convertir les semaines en heures par jour et diviser par 24 * 7 pour obtenir les heures par jour
           case 2: // Month
               return value * 24.0 * 30.0 / (24.0 * 30.0); // Convertir les mois en heures par jour
           default:
               return value;
    }
}

void MainWindow::CalculOhms()
{
    Volt = convert(ui->spinBox_Voltage->value(), volts);
    Ohms = convert(ui->spinBox_Ohms->value(), ohms);
    Power = convert(ui->spinBox_Power->value(), watts);
    Current = convert(ui->spinBox_Current->value(), current);


    if (Volt != NULL && Current != 0)
    {
        Ohms = Volt/Current;
        Power = Volt*Current;

        ui->spinBox_Ohms->setValue(Ohms);
        ui->spinBox_Power->setValue(Power);
    }
    else if (Volt != 0 && Ohms != 0)
    {
        Current = Volt/Ohms;
        Power = Volt*Current;

        ui->spinBox_Current->setValue(Current);
        ui->spinBox_Power->setValue(Power);
    }
    else if (Volt != 0 && Power != 0)
    {
        Current = Power/Volt;
        Ohms = Volt/Current;

        ui->spinBox_Current->setValue(Current);
        ui->spinBox_Ohms->setValue(Ohms);
    }
    else if (Current != 0 && Ohms != 0)
    {
        Volt = Ohms*Current;
        Power = Volt*Current;

        ui->spinBox_Voltage->setValue(Volt);
        ui->spinBox_Power->setValue(Power);
    }
    else if (Current != 0 && Power != 0)
    {
        Volt = Power/Current;
        Ohms = Volt*Current;

        ui->spinBox_Ohms->setValue(Ohms);
        ui->spinBox_Voltage->setValue(Volt);
    }
    else if (Ohms != 0 && Power != 0)
    {
        Current = sqrt(Power/Ohms);
        Volt = Ohms*Current;

        ui->spinBox_Current->setValue(Current);
        ui->spinBox_Power->setValue(Power);
    }
    else
    {

    }



}

void MainWindow::CalculCost()
{
    TpsUsage = convertToDate(ui->doubleSpinBox_Date->value());
    PowerCons = convert(ui->doubleSpinBox_PowerC->value(), PowerC);
    Rate = ui->lineEdit_Price->text().toDouble(); // Prix de l'énergie en $/kWh

    // Calcul de la consommation d'énergie en kilowattheures (kWh)
    Energie = PowerCons * TpsUsage;
    // Calcul du coût en dollars
    Cost = Energie * Rate;

    QString powerText = "Power Consumed = " + QString::number(Energie) + " (kWh per month)";
       QString costText = "Cost = " + QString::number(Cost) + " ($ per month)";

       QMessageBox messageBox;
       messageBox.setWindowTitle("Results");
       messageBox.setText(powerText + "\n" + costText);
       messageBox.exec();

}

void MainWindow::CalculDistCov()
{
    int index = ui->comboBox_Type->currentIndex();

        Distance = convert(ui->doubleSpinBox_Distance->value(), distance); // Donne la distance en mètre
        Time = convert(ui->doubleSpinBox_Time->value(), time); // Donne le temps en seconde
        Initial_Velocity = convert(ui->doubleSpinBox_Distance->value(), distance);

        QMessageBox messageBox;
        messageBox.setWindowTitle("Results");

        switch (index) {
            case 0: // Calculer Velocity
            {
                ui->label_distcov->setText("v = d / t");
                Initial_Velocity = Distance / Time; // DOnne la velocité en m/s
                messageBox.setText("Initial Velocity: " + QString::number(Initial_Velocity) + " m/s");
                break;
            }
            case 1: // Calculer Time
            {
                ui->label_distcov->setText("t = d / v");
                Time = Distance / Initial_Velocity;
                messageBox.setText("Time: " + QString::number(Time) + " s");
                break;
            }
            case 2: // Calculer Distance
            {
                ui->label_distcov->setText("d = v * t");
                Distance = Initial_Velocity * Time;
                messageBox.setText("Distance: " + QString::number(Distance) + " m");
                break;
            }
            default:
                return;
        }

        messageBox.exec();
    }

void MainWindow::CalculAcc()
{
    int index = ui->comboBox_Type_2->currentIndex();

        Distance = convert(ui->doubleSpinBox_Distance->value(), distance); // Donne la distance en mètre
        Time = convert(ui->doubleSpinBox_Time2->value(), time); // Donne le temps en seconde
        Acc = ui->doubleSpinBox_Acc->value(); // Donne le temps en seconde
        Initial_Velocity = convert(ui->doubleSpinBox_Final_Velocity->value(), final_Velocity);
        Final_Velocity = convert(ui->doubleSpinBox_Final_Velocity->value(), final_Velocity);



        QMessageBox messageBox;
        messageBox.setWindowTitle("Results");

        switch (index) {
            case 0: // Calculer Initial Velocity
            {
                ui->label_distcov->setText("vi = vf−a*t");
                Initial_Velocity = Final_Velocity - Acc * Time; // DOnne la velocité en m/s
                messageBox.setText("Initial Velocity: " + QString::number(Initial_Velocity) + " m/s");
                break;
            }
            case 1: // Calculer Time
            {
                ui->label_distcov->setText("t = (*f-vi)/a");
                Time = (Final_Velocity * Initial_Velocity) / Acc;
                messageBox.setText("Time: " + QString::number(Time) + " s");
                break;
            }
            case 2: // Calculer Acceleration
            {
                ui->label_distcov->setText("a = (vf-vi)/t");
                Final_Velocity = Initial_Velocity + Acc * Time;
                Acc = (Final_Velocity - Initial_Velocity) / Time;
                messageBox.setText("Distance: " + QString::number(Acc) + " m");
                break;
            }
            case 3: // Calculer Final Velocity
            {
                ui->label_distcov->setText("v*f = vi+a*t");
                Final_Velocity = Initial_Velocity + Acc * Time;
                messageBox.setText("Distance: " + QString::number(Final_Velocity) + " m");
                break;
            }
                default:
                    return;
            }

        messageBox.exec();
    }

void MainWindow::CalculKinRot()
{
    Moment_Inert = ui->doubleSpinBox_inertia->value(); // Donne la valeur du moment d'inertie en kg.m^2
    Kinetic = ui->doubleSpinBox_Kinetic->value(); // Donne la valeur de l'énergie cinétique en J
    Angular_Vel = ui->doubleSpinBox_angularvel->value(); // Donne la vitesse angulaire en rad/s

    QMessageBox messageBox;
    messageBox.setWindowTitle("Results");

    if (ui->checkBox_KineticEnRot->isChecked()) {
         Kinetic = 0.5 * Moment_Inert * Angular_Vel * Angular_Vel; // Calcul de l'énergie cinétique (KE = 0.5 * I * ω^2)
         messageBox.setText("Kinetic Energie: " + QString::number(Kinetic) + " J");
         ui->checkBox_MomOfInRot->setChecked(false);

     }


    else if (ui->checkBox_MomOfInRot->isChecked())
    {
        Moment_Inert = 2 * Kinetic / (Angular_Vel * Angular_Vel); // Calcul du moment d'inertie (I = 2 * KE / ω^2)
        messageBox.setText("Moment of Inertia: " + QString::number(Moment_Inert) + " kg*m²");
        ui->checkBox_KineticEnRot->setChecked(false);

    }
    messageBox.exec();

}

void MainWindow::CalculKinLin()
{
     Mass = convert(ui->doubleSpinBox_mass->value(), kg);
     Velocity = ui->doubleSpinBox_velo->value();
     Kinetic = ui->doubleSpinBox_kine->value();

     QMessageBox messageBox;
     messageBox.setWindowTitle("Results");


    if (ui->checkBox_KineticEnL->isChecked())
    {
        Kinetic = 0.5 * Mass * Velocity * Velocity;
        messageBox.setText("Kinetic Energie: " + QString::number(Kinetic) + " J");
        ui->checkBox_MassL->setChecked(false);
        ui->checkBox_VelocityL->setChecked(false);


    }
    else if (ui->checkBox_MassL->isChecked())
    {
        Mass = (2 * Kinetic) / (Velocity * Velocity);
        messageBox.setText("Mass: " + QString::number(Mass) + " kg");
        ui->checkBox_KineticEnL->setChecked(false);
        ui->checkBox_VelocityL->setChecked(false);


    }
    else if (ui->checkBox_VelocityL->isChecked())
    {
        Velocity = sqrt((2 * Kinetic) / Mass);
        messageBox.setText("Velocity: " + QString::number(Velocity) + " m/s");
        ui->checkBox_MassL->setChecked(false);
        ui->checkBox_KineticEnL->setChecked(false);


    }

    messageBox.exec();
}

void MainWindow::CalculAccel()
{
     Time = convert(ui->doubleSpinBox_T->value(), time);
     Final_Speed = ui->doubleSpinBox_finSpeed->value();
     Initial_Speed = ui->doubleSpinBox_inSpeed->value();
     Acc = ui->doubleSpinBox_Accele->value();


     QMessageBox messageBox;
     messageBox.setWindowTitle("Results");


    if (ui->checkBox_Acce->isChecked())
    {
        Acc = (Final_Speed - Initial_Speed) / Time;
        messageBox.setText("Acceleration: " + QString::number(Acc) + " m/s");
        ui->checkBox_FinalSpeedA->setChecked(false);
        ui->checkBox_InSpeedA->setChecked(false);
        ui->checkBox_TimeA->setChecked(false);


    }
    else if (ui->checkBox_InSpeedA->isChecked())
    {
        Initial_Speed = Final_Speed - (Acc * Time);
        messageBox.setText("Initial Speed: " + QString::number(Initial_Speed) + " m/s");
        ui->checkBox_FinalSpeedA->setChecked(false);
        ui->checkBox_TimeA->setChecked(false);
        ui->checkBox_Acce->setChecked(false);


    }
    else if (ui->checkBox_FinalSpeedA->isChecked())
    {
        Final_Speed = Initial_Speed + (Acc * Time);
        messageBox.setText("Final Speed: " + QString::number(Final_Speed) + " m/s");
        ui->checkBox_TimeA->setChecked(false);
        ui->checkBox_InSpeedA->setChecked(false);
        ui->checkBox_Acce->setChecked(false);
    }
    else if (ui->checkBox_TimeA->isChecked())
    {
        Time = (Final_Speed - Initial_Speed) / Acc;
        messageBox.setText("Time: " + QString::number(Time) + " s");
        ui->checkBox_FinalSpeedA->setChecked(false);
        ui->checkBox_InSpeedA->setChecked(false);
        ui->checkBox_Acce->setChecked(false);

    }

    messageBox.exec();
}

void MainWindow::clearAll()
{
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
       for (QLineEdit* lineEdit : lineEdits) {
           lineEdit->clear();
       }

       QList<QDoubleSpinBox*> doubleSpinBoxes = findChildren<QDoubleSpinBox*>();
       for (QDoubleSpinBox* doubleSpinBox : doubleSpinBoxes) {
           doubleSpinBox->setValue(0.0);
       }
}

MainWindow::~MainWindow()
{
    delete ui;
}

