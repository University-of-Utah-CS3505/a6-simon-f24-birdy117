#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMediaPlayer"
#include "QAudioOutput"
#include <QSoundEffect>

/*
 * Aaron Perez CS3505
 * A6: Qt Simon Game
 * Github User: birdy117
 * https://github.com/University-of-Utah-CS3505/a6-simon-f24-birdy117
 * This header file lays out the slots and functions to be implemented in the main .cpp file.
 * This file functions as the controller to send signals to the ui
 */

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ///
    /// \brief startGame - starts the game.
    ///
    void startGame();

    ///
    /// \brief endGame - ends the simon game by disabling buttons and displaying game over
    ///
    void endGame();

    ///
    /// \brief generateSequence - Generates a sequence of colors of the indicated length
    /// \param length - The length of the sequence to generate
    ///
    void addToSequence();

    ///
    /// \brief displaySequence - Displays the sequence to the player to mimic
    ///
    void displaySequence();

    ///
    /// \brief onButtonPressed - Method to handle what happens when a button is pressed
    /// \param color - The color pressed by the player
    ///
    void onButtonPressed(int color);

    ///
    /// \brief redButtonFlash - Flashes the red button
    ///
    void redButtonFlash();

    ///
    /// \brief blueButtonFlash - Flashes the blue button
    ///
    void blueButtonFlash();

    ///
    /// \brief enableButtons - enables the colored buttons to be pressed
    ///
    void enableButtons();

    ///
    /// \brief disableButtons - disables the colored buttons so they cannot be pressed
    ///
    void disableButtons();

    ///
    /// \brief resetProgressBar - resets the progress bar to zero and sets a new maximum
    /// \param MaxValue - The new max value to set the progress bar to.
    ///
    void resetProgressBar(int MaxValue);

private slots:
    ///
    /// \brief startButtonClicked - Slot to handle when the start button is clicked.
    ///
    void startButtonClicked();

    ///
    /// \brief startButtonClicked - Slot to handle when the red button is clicked.
    ///
    void redButtonClicked();

    ///
    /// \brief startButtonClicked - Slot to handle when the blue button is clicked.
    ///
    void blueButtonClicked();

private:
    Ui::MainWindow *ui;

    ///
    /// \brief redBeep - Pointer to the red button beeping sfx
    ///
    QSoundEffect *redBeep;

    ///
    /// \brief blueBeep - Pointer to the blue button beeping sfx
    ///
    QSoundEffect *blueBeep;

    ///
    /// \brief roundWin - Pointer to the round win sfx
    ///
    QSoundEffect *roundWin;

    ///
    /// \brief gameOver - Pointer to the game over sfx
    ///
    QSoundEffect *gameOver;
};
#endif // MAINWINDOW_H
