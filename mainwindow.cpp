#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<int> sequence;
int currentStep = 0;
bool playerTurn = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50);} QPushButton:pressed {background-color: rgb(235,120,120);}"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void generateSequence(int length) {
    for (int i = 0; i < length; ++i) {
        sequence.append(rand() % 4); // Assuming 4 colors: 0, 1, 2, 3
    }
}

void displaySequence() {
    playerTurn = false;
    for (int i = 0; i < sequence.size(); ++i) {
        // Add delay and show each color in sequence
    }
    playerTurn = true; // After sequence displayed, enable player turn
}

void onButtonPressed(int color) {
    if (!playerTurn) return;

    if (color == sequence[currentStep]) {
        currentStep++;
        if (currentStep == sequence.size()) {
            // Player completed the sequence
            currentStep = 0;
            // Generate next sequence step and display
        }
    } else {
        // Game over logic
    }
}
