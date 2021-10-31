#ifndef ORBIT_CALC_H
#define ORBIT_CALC_H

#include <QMainWindow>
# include <QMessageBox>
# include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class Orbit_calc; }
QT_END_NAMESPACE

class Orbit_calc : public QMainWindow
{
    Q_OBJECT

public:
    Orbit_calc(QWidget *parent = nullptr);
    ~Orbit_calc();

//public:
//    std::array<QPushButton, 4> mathButtons;
//    std::array<QPushButton, 3> memButtons;
//    QPushButton mathButtons[4];
//    QPushButton memButtons[3];

private:
    Ui::Orbit_calc *ui;

private slots:
    // to handle number buttons
    void numPressed();
    void zeroPressed();
    // to handle math buttons
    void mathPressed();
    // to handle the point button
    void pointPressed();
    // to clear the display
    void displayClear();
    // equal button
    void equalPressed();
    // to handle the memory set button

    void memSetPressed();
    // to handle the memory clear button
    void memClsPressed();
    // to the memory recover button
    void memRecPressed();

private:
    void clearMath();

private:
    double heldVal = 0.0;
    double solution = 0.0;
    QString memory = "";

};
#endif // ORBIT_CALC_H
