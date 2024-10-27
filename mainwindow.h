#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*
 * Aaron Perez CS3505
 * A6: Qt Simon Game
 *
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

    void startGame();
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

    void redButtonFlash();
    void blueButtonFlash();
    void enableButtons();
    void disableButtons();

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
};
#endif // MAINWINDOW_H
