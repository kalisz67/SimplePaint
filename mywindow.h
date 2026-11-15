// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji

#include <QApplication>

// Dolaczamy plik naglowkowy klasy QWidget,
// Jest to klasa bazowa wszystkich elementow GUI
#include <QWidget>

// Dolaczamy plik naglowkowy klasy QPushButton
// (standardowy przycisk)
#include <QPushButton>

//Plik do sliderow
#include <QSlider>
#include <QLabel>

// Dolaczamy plik naglowkowy klasy QGroupBox
// (do grupowania komponentow GUI)
#include <QGroupBox>

// QPainter to klasa umozliwiajaca niskopoziomowe rysowanie
// na elementach GUI
#include <QPainter>

// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>

// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>

// MyWindow jest podklasa klasy QWidget
class MyWindow : public QWidget
{
    // Makro ktore musimy dodac jezeli definiujemy wlasne sygnaly lub sloty
    Q_OBJECT
public:
    // Typowa deklaracja konstruktora w Qt.
    // Parametr "parent" okresla rodzica komponenetu.
    // W przypadku naszej klasy parametr ten wskazuje na null
    // co oznacza, ze komponenet nie ma rodzica, jest to
    // komponenet najwyzszego poziomu
    MyWindow(QWidget *parent = 0);

    // Deklaracja destruktora
    ~MyWindow();


private:

    // Pole przechowujace obrazek
    QImage *img;

    // Przyciski
    QPushButton *cleanButton;
    QPushButton *exitButton;
    QPushButton *odcinekButton;
    QPushButton *okragButton;

    // Slidery
    QSlider *sliderB;
    QSlider *sliderG;
    QSlider *sliderR;

    // Grupa przyciskow
    QGroupBox *grupa;
    QGroupBox *grupaKolor;

    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;

    QImage kopia;
    int sX;
    int sY;

    bool rysowanie;

    int kolorB;
    int kolorG;
    int kolorR;

    // Deklaracje funkcji
    void czysc();
    void pixel(int x, int y);
    void odcinek(int x1, int y1, int x2, int y2);

    // Opcje modyfikacji obrazu
    bool odcinekONOFF;


    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    void wlaczOdcinek();
    void zmienBlue(int x);
    void zmienGreen(int x);
    void zmienRed(int x);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

