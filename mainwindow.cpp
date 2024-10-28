#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QTimer"
#include "QAudioOutput"
#include "QSoundEffect"

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
    , redBeep(new QSoundEffect())
    , blueBeep(new QSoundEffect())
    , roundWin(new QSoundEffect())
    , gameOver(new QSoundEffect())
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked); // Connect signal to slot
    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::redButtonClicked); // Connect signal to slot
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::blueButtonClicked); // Connect signal to slot

    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50); border: 2px solid black;} QPushButton:pressed {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton:hover {background-color: rgb(200,75,75); border: 2px solid black;}"));
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(50,50,100); border: 2px solid black;} QPushButton:pressed {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton::hover {background-color: rgb(100,100,200); border: 2px solid black;}"));
    ui->gameOverLabel->hide();
    ui->winLabel->hide();

    resetProgressBar(1);

    redBeep->setSource(QUrl::fromLocalFile(":/sounds/redBeep.wav"));
    blueBeep->setSource(QUrl::fromLocalFile(":/sounds/blueBeep.wav"));
    roundWin->setSource(QUrl::fromLocalFile(":/sounds/roundWin.wav"));
    gameOver->setSource(QUrl::fromLocalFile(":/sounds/game_over.wav"));
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
        sequence.append(rand() % 2); // Assuming 2 colors: 0, 1
}

void MainWindow::displaySequence() {
    playerTurn = false;
    disableButtons();
    for (int i = 0; i < sequence.size(); ++i) {
        QTimer::singleShot(1000+(1000*i)-(20*sequence.size()), this, [this, i]() {
            ui->winLabel->hide();
            if (sequence[i] == 0) {
                redButtonFlash();
            } else if (sequence[i] == 1) {
                blueButtonFlash();
            }
        });
    }
    QTimer::singleShot(1000*sequence.size(), this, [this]() {
        playerTurn = true; // After sequence displayed, enable player turn
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

void MainWindow::redButtonClicked()
{
    onButtonPressed(0); // Assuming 0 represents red
    redBeep->play();
}

void MainWindow::blueButtonClicked()
{
    onButtonPressed(1); // Assuming 1 represents blue
    blueBeep->play();
}

void MainWindow::redButtonFlash(){
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton:pressed {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton::hover {background-color: rgb(200,100,100); border: 2px solid black;}"));
    redBeep->play();
    QTimer::singleShot(520-(sequence.size()*20), this, [this](){
        ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,50,50); border: 2px solid black;} QPushButton:pressed {background-color: rgb(235,120,120); border: 2px solid black;} QPushButton::hover {background-color: rgb(200,100,100); border: 2px solid black;}"));
    });
}

void MainWindow::blueButtonFlash(){
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton:pressed {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton::hover {background-color: rgb(100,100,200); border: 2px solid black;}"));
    blueBeep->play();
    QTimer::singleShot(520-(sequence.size()*20), this, [this](){
        ui->blueButton->setStyleSheet("QPushButton {background-color: rgb(50,50,100); border: 2px solid black;} QPushButton:pressed {background-color: rgb(120,120,235); border: 2px solid black;} QPushButton::hover {background-color: rgb(100,100,200); border: 2px solid black;}");
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

void MainWindow::resetProgressBar(int MaxValue){
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(MaxValue);
}
