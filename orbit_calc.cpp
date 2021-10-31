#include "orbit_calc.h"
#include "ui_orbit_calc.h"

double calcVal = 0;
bool multTrigger = false;
bool divTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Orbit_calc::Orbit_calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Orbit_calc)
{
    ui->setupUi(this);
    ui->Display->setReadOnly(true); // prevents the digits from being editable


    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10]; // array to hold buttons

//    mathButtons = {
//        ui->Button_add,
//        ui->Button_sub,
//        ui->Button_div,
//        ui->Button_mult
//    };

    for(int i = 1; i < 10; ++i) {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Orbit_calc::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed())); // connecting buttons to slot
    }

    // connections to individual buttons
    connect((ui->Button_point), SIGNAL(released()), this, SLOT(pointPressed()));
    connect((ui->Button_clear), SIGNAL(released()), this, SLOT(displayClear())); // connecting AC button to displayClear
    connect((ui->Button0), SIGNAL(released()), this, SLOT(zeroPressed()));
    connect((ui->Button_equal), SIGNAL(released()), this, SLOT(equalPressed()));

//    for(QPushButton button : mathButtons) {
//        connect(button, SIGNAL(released()), this, SLOT(mathPressed()));
//    }

    connect((ui->Button_add), SIGNAL(released()), this, SLOT(mathPressed()));
    connect((ui->Button_sub), SIGNAL(released()), this, SLOT(mathPressed()));
    connect((ui->Button_mult), SIGNAL(released()), this, SLOT(mathPressed()));
    connect((ui->Button_div), SIGNAL(released()), this, SLOT(mathPressed()));

    connect((ui->Button_mem_set), SIGNAL(released()), this, SLOT(memSetPressed()));
    connect((ui->Button_mem_clear), SIGNAL(released()), this, SLOT(memClsPressed()));
    connect((ui->Button_mem_rec), SIGNAL(released()), this, SLOT(memRecPressed()));
}

Orbit_calc::~Orbit_calc()
{
    delete ui;
}

void Orbit_calc::clearMath() {
    addTrigger = false;
    subTrigger = false;
    divTrigger = false;
    multTrigger = false;
}

void Orbit_calc::numPressed() {

    QPushButton *button = (QPushButton *)sender(); // getting the sender object i.e (button pressed).
    QString butVal{button->text()};
    QString disVal{ui->Display->text()};

    if((disVal == "0") | (disVal == "")) {
        ui->Display->setText(butVal);
    }
    else {
        QString newVal = ui->Display->text();
        newVal += butVal;
        double dblVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblVal, 'g', 16)); // set exponential to start at 16 digits
    }
}

void Orbit_calc::zeroPressed() {
    QString disVal{ui->Display->text()};
    disVal += "0";
    ui->Display->setText(disVal);
}


void Orbit_calc::pointPressed() {

    QString disVal = ui->Display->text();

    if((disVal == "") | ((disVal.toDouble()) == 0.0)) {
        ui->Display->setText("0.");
    }
    else {
        disVal += ".";
        ui->Display->setText(disVal);
    }

}

void Orbit_calc::mathPressed() {
    /*/addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;*/

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        if(addTrigger && heldVal != 0.0) {
            heldVal += (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(subTrigger && heldVal != 0.0) {
            heldVal -= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(divTrigger && heldVal != 0.0) {
            heldVal /= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(multTrigger && heldVal != 0.0) {
            heldVal *= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else {
            Orbit_calc::heldVal = (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        divTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        if(addTrigger && heldVal != 0.0) {
            heldVal += (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(subTrigger && heldVal != 0.0) {
            heldVal -= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(divTrigger && heldVal != 0.0) {
            heldVal /= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(multTrigger && heldVal != 0.0) {
            heldVal *= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else {
            Orbit_calc::heldVal = (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        addTrigger = true;
    }
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        if((ui->Display->text() == "0") | (ui->Display->text() == "0.0")) {
            ui->Display->setText("-");
        }
        else if(addTrigger && heldVal != 0.0) {
            heldVal += (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(subTrigger && heldVal != 0.0) {
            heldVal -= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(divTrigger && heldVal != 0.0) {
            heldVal /= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(multTrigger && heldVal != 0.0) {
            heldVal *= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else {
            Orbit_calc::heldVal = (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        subTrigger = true;
    }
    else {
        if(addTrigger && heldVal != 0.0) {
            heldVal += (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(subTrigger && heldVal != 0.0) {
            heldVal -= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(divTrigger && heldVal != 0.0) {
            heldVal /= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else if(multTrigger && heldVal != 0.0) {
            heldVal *= (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        else {
            Orbit_calc::heldVal = (ui->Display->text().toDouble());
            ui->Display->setText("");
            clearMath();
        }
        multTrigger = true;
    }
}

void Orbit_calc::equalPressed() {

    Orbit_calc::solution = 0.0;
    QString disVal = ui->Display->text();
    double dblVal = disVal.toDouble();

    if(addTrigger || subTrigger || divTrigger || multTrigger) {
        if(addTrigger) {
            solution = Orbit_calc::heldVal + dblVal;
        }
        else if(subTrigger) {
            solution = Orbit_calc::heldVal - dblVal;
        }
        else if(divTrigger) {
            try {
                solution = Orbit_calc::heldVal / dblVal;
            }
            catch(const QString e) {
                ui->Display->setText("ERROR : DIVISION WITH ZERO");
            }
        }
        else if(multTrigger) {
            solution = Orbit_calc::heldVal * dblVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Orbit_calc::memSetPressed() {
    QString disVal = ui->Display->text();
    Orbit_calc::memory = disVal;
    ui->statusBar->showMessage("M+");
}

void Orbit_calc::memClsPressed() {
    Orbit_calc::memory = "";
    ui->statusBar->showMessage("");
}

void Orbit_calc::memRecPressed() {
    if(Orbit_calc::memory != "") {
        ui->Display->setText(Orbit_calc::memory);
        ui->statusBar->showMessage("M >>");
    }
    else {
        ui->statusBar->showMessage("M!");
    }
}

void Orbit_calc::displayClear() {
    ui->Display->setText("");
    heldVal = 0.0;
    solution = 0.0;
}









