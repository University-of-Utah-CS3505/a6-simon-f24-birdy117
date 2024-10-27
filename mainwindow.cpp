#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QTimer"

/*
 * Aaron Perez CS3505
 * A6: Qt Simon Game
 *
 * This cpp file is contains the model aspect of the Simon game. And deals with all the logic
 * needed to make the game run.
 */

QVector<int> sequence;
int currentStep = 0;
int score = 0;
bool playerTurn = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked); // Connect signal to slot
    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::redButtonClicked); // Connect signal to slot
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::blueButtonClicked); // Connect signal to slot
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50);} QPushButton:pressed {background-color: rgb(235,120,120);}"));
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(50,50,100);} QPushButton:pressed {background-color: rgb(120,120,235);}"));
    ui->gameOverLabel->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButtonClicked() {
    startGame();
}

void MainWindow::startGame() {
    // Code to start the game
    ui->startButton->setDisabled(true);
    ui->gameOverLabel->hide();
    sequence.clear();
    addToSequence(); // Example: Generate the first step in the sequence
    displaySequence();   // Example: Display the sequence to the player
}

void MainWindow::endGame() {
    disableButtons();
    currentStep = 0;
    ui->gameOverLabel->show();
    ui->startButton->setDisabled(false);
}

void MainWindow::addToSequence() {
        sequence.append(rand() % 2); // Assuming 2 colors: 0, 1
}

void MainWindow::displaySequence() {
    playerTurn = false;
    disableButtons();
    for (int i = 0; i < sequence.size(); ++i) {
        QTimer::singleShot(2000, this, [this, i]() {
            if (sequence[i] == 0) {
                redButtonFlash();
            } else if (sequence[i] == 1) {
                blueButtonFlash();
            }
        });
    }
    playerTurn = true; // After sequence displayed, enable player turn
    enableButtons();

}

void MainWindow::onButtonPressed(int color) {
    if (!playerTurn) return;

    if (color == sequence[currentStep]) {
        currentStep++;
        if (currentStep == sequence.size()) {
            // Player completed the sequence
            currentStep = 0;
            score++;
            // Generate next sequence step and display
            addToSequence();
            displaySequence();
        }
    } else {
        // Game over logic
        endGame();
    }
}

void MainWindow::redButtonClicked()
{
    onButtonPressed(0); // Assuming 0 represents red
}

void MainWindow::blueButtonClicked()
{
    onButtonPressed(1); // Assuming 1 represents blue
}

void MainWindow::redButtonFlash(){
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(235,120,120);}"));
    QTimer::singleShot(1000, this, [this]() {
        ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50);}"));
    });
}

void MainWindow::blueButtonFlash(){
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(120,120,235);}"));
    QTimer::singleShot(1000, this, [this]() {
        ui->blueButton->setStyleSheet("QPushButton {background-color: rgb(50,50,100);}");
    });

}

void MainWindow::enableButtons(){
    ui->blueButton->setDisabled(false);
    ui->redButton->setDisabled(false);
}

void MainWindow::disableButtons(){
    ui->blueButton->setDisabled(true);
    ui->redButton->setDisabled(true);
}
