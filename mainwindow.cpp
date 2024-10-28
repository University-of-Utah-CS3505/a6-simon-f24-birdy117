#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QTimer"
#include "QSoundEffect"

/*
 * Aaron Perez CS3505
 * A6: Qt Simon Game
 * Github User: birdy117
 * https://github.com/University-of-Utah-CS3505/a6-simon-f24-birdy117
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
    , redBeep(new QSoundEffect())
    , blueBeep(new QSoundEffect())
    , roundWin(new QSoundEffect())
    , gameOver(new QSoundEffect())
{
    ui->setupUi(this);

    //connect the signals to the slots
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::redButtonClicked);
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::blueButtonClicked);

    //Decorate UI Buttons to make the UI look pretty on start up
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50); border: 2px solid black;} QPushButton:pressed {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton:hover {background-color: rgb(200,75,75); border: 2px solid black;}"));
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(50,50,100); border: 2px solid black;} QPushButton:pressed {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton::hover {background-color: rgb(100,100,200); border: 2px solid black;}"));
    ui->gameOverLabel->hide();
    ui->winLabel->hide();

    //Make sure the Progress bar is set to 0
    resetProgressBar(1);

    //Locate the sounds files for the sound effects
    redBeep->setSource(QUrl::fromLocalFile(":/sounds/redBeep.wav"));
    blueBeep->setSource(QUrl::fromLocalFile(":/sounds/blueBeep.wav"));
    roundWin->setSource(QUrl::fromLocalFile(":/sounds/roundWin.wav"));
    gameOver->setSource(QUrl::fromLocalFile(":/sounds/game_over.wav"));
}


MainWindow::~MainWindow() {
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
    resetProgressBar(1);
    addToSequence();
    displaySequence();
    ui->roundCounter->setText(QString::number(sequence.size()));
}

void MainWindow::endGame() {
    gameOver->play();
    disableButtons();
    currentStep = 0;
    ui->gameOverLabel->show();
    ui->startButton->setDisabled(false);
}

void MainWindow::addToSequence() {
        sequence.append(rand() % 2); // 2 colors: 0 for red, 1 for blue
}

void MainWindow::displaySequence() {
    //Disable user input
    playerTurn = false;
    disableButtons();

    //Show the sequence
    for (int i = 0; i < sequence.size(); ++i) {
        //As the sequence grows larger, the computer will display the sequence faster
        QTimer::singleShot((1000+(1000*i)-(50*i*sequence.size())), this, [this, i]() {
            ui->winLabel->hide();
            if (sequence[i] == 0) {
                redButtonFlash();
            } else if (sequence[i] == 1) {
                blueButtonFlash();
            }
        });
    }

    // After the sequence is displayed, enable the player's turn
    QTimer::singleShot((1000+1000*sequence.size())-(50*sequence.size()*sequence.size()), this, [this]() {
        playerTurn = true;
        enableButtons();
    });

}

void MainWindow::onButtonPressed(int color) {
    if (!playerTurn) return;

    if (color == sequence[currentStep]) {
        currentStep++;
        ui->progressBar->setValue(currentStep);
        if (currentStep == sequence.size()) {
            // Player completed the sequence
            currentStep = 0;
            score++;
            ui->winLabel->show();
            QTimer::singleShot(200, this, [this](){
                roundWin->play();
            });
            // Generate next sequence step and display
            addToSequence();
            ui->roundCounter->setText(QString::number(sequence.size()));
            displaySequence();
            QTimer::singleShot(1000, this, [this](){
                resetProgressBar(sequence.size());
            });
        }
    } else {
        // Game over logic
        endGame();
    }
}

void MainWindow::redButtonClicked() {
    onButtonPressed(0); // 0 represents red
    redBeep->play();
}

void MainWindow::blueButtonClicked() {
    onButtonPressed(1); // 1 represents blue
    blueBeep->play();
}

void MainWindow::redButtonFlash() {
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton:pressed {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton::hover {background-color: rgb(200,100,100); border: 2px solid black;}"));
    redBeep->play();
    QTimer::singleShot(520-(sequence.size()*20), this, [this](){
        ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50); border: 2px solid black;} QPushButton:pressed {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton::hover {background-color: rgb(200,100,100); border: 2px solid black;}"));
    });
}

void MainWindow::blueButtonFlash() {
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton:pressed {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton::hover {background-color: rgb(100,100,200); border: 2px solid black;}"));
    blueBeep->play();
    QTimer::singleShot(520-(sequence.size()*20), this, [this](){
        ui->blueButton->setStyleSheet("QPushButton {background-color: rgb(50,50,100); border: 2px solid black;} QPushButton:pressed {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton::hover {background-color: rgb(100,100,200); border: 2px solid black;}");
    });
}

void MainWindow::enableButtons() {
    ui->blueButton->setDisabled(false);
    ui->redButton->setDisabled(false);
}

void MainWindow::disableButtons() {
    ui->blueButton->setDisabled(true);
    ui->redButton->setDisabled(true);
}

void MainWindow::resetProgressBar(int MaxValue) {
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(MaxValue);
}
