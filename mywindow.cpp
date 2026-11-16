// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>

// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("SimplePaint");

    //Zmieniamy rozmiar okna
    resize(800,700);

    // Ustawiamy wymiary obrazka i wspolrzedne jego
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;

    // Ustawienia kolorów
    kolorB = 0;
    kolorG = 0;
    kolorR = 0;

    // Pozwolenie na rysowanie, jeśli kursos w obrazie
    rysowanie = false;

    // Ustawienie wlacznikow ONOFF na false
    resetWlacznikow();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);

    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);
    grupaKolor = new QGroupBox("Kolory", this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+150));
    grupaKolor->setGeometry(QRect(poczX+szer+poczX,poczY+400,800-szer-2*poczX,150));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QVBoxLayout *boxKolor = new QVBoxLayout;

    // Tworzymy 4 przyciski
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
    pixelButton = new QPushButton("Pixel");
    odcinekButton = new QPushButton("Odcinek");
    okragButton = new QPushButton("Okrag");
    elipsaButton = new QPushButton("Elipsa");

    //Slidery do kolorów
    QSlider *sliderB = new QSlider(Qt::Horizontal);
    QSlider *sliderG = new QSlider(Qt::Horizontal);
    QSlider *sliderR = new QSlider(Qt::Horizontal);
    sliderB->setRange(0, 255);
    sliderG->setRange(0, 255);
    sliderR->setRange(0, 255);
    sliderB->setValue(0);
    sliderG->setValue(0);
    sliderR->setValue(0);

    // Dodajemy przyciski do layoutu
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(pixelButton);
    boxLayout->addWidget(odcinekButton);
    boxLayout->addWidget(okragButton);
    boxLayout->addWidget(elipsaButton);
    boxLayout->addWidget(exitButton);

    //Dodajemy slidery i nadajemy im nazwy
    boxKolor->addWidget(new QLabel ("Blue"));
    boxKolor->addWidget(sliderB);
    boxKolor->addWidget(new QLabel ("Green"));
    boxKolor->addWidget(sliderG);
    boxKolor->addWidget(new QLabel ("Red"));
    boxKolor->addWidget(sliderR);

    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
    grupaKolor->setLayout(boxKolor);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
    connect(pixelButton,SIGNAL(clicked()),this,SLOT(wlaczPixel()));
    connect(odcinekButton,SIGNAL(clicked()),this,SLOT(wlaczOdcinek()));
    connect(okragButton,SIGNAL(clicked()),this,SLOT(wlaczOkrag()));
    connect(elipsaButton,SIGNAL(clicked()),this,SLOT(wlaczElipse()));

    connect(sliderB,SIGNAL(valueChanged(int)),this,SLOT(zmienBlue(int)));
    connect(sliderG,SIGNAL(valueChanged(int)),this,SLOT(zmienGreen(int)));
    connect(sliderR,SIGNAL(valueChanged(int)),this,SLOT(zmienRed(int)));
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}

// Funkcje do zmiany kolorow
void MyWindow::zmienBlue(int x){
    kolorB = x;
}
void MyWindow::zmienGreen(int x){
    kolorG = x;
}
void MyWindow::zmienRed(int x){
    kolorR = x;
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::slot_czysc()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}


// Funkcja powoduje wyczyszczenie (zamalowanie na bialo)
// obszaru rysowania
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}

// Funkcje obslugujace wlaczanie sie konkretnych typow akcji w programie
void MyWindow::resetWlacznikow(){
    pixelONOFF = false;
    odcinekONOFF = false;
    okragONOFF = false;
    elipsaONOFF = false;
}

void MyWindow::wlaczPixel(){
    resetWlacznikow();
    pixelONOFF = true;
}

void MyWindow::wlaczOdcinek(){
    resetWlacznikow();
    odcinekONOFF = true;
}

void MyWindow::wlaczOkrag(){
    resetWlacznikow();
    okragONOFF = true;
}

void MyWindow::wlaczElipse(){
    resetWlacznikow();
    elipsaONOFF = true;
}


// Funkcja rysujaca piksel
void MyWindow::pixel(int x, int y){
    unsigned char *ptr;
    ptr = img->bits();

    if ((x >= 0) && (y >= 0) && (x < szer) && (y < wys)){
            ptr[szer*4*y + 4*x] = kolorB;
            ptr[szer*4*y + 4*x + 1] = kolorG;
            ptr[szer*4*y + 4*x + 2] = kolorR;
        }
}


// Funkcja rysująca odcinek
void MyWindow::odcinek(int x1, int y1, int x2, int y2){
    int x = 0;
    int y = 0;

    if (x1 == x2){
        for (y = qMin(y1, y2); y <= qMax(y1, y2); y++){
            pixel(x1, y);
        }
        return;
    }

    double a = (double)(y2 - y1) / (x2 - x1);
    double b = y1 - a * x1;

    if (qAbs(a) <= 1){
        for (x = qMin(x1, x2); x <= qMax(x1, x2); x++){
            pixel(x, qRound(a * x + b));
        }
        return;
    }
    if (qAbs(a) > 1){
        for (y = qMin(y1, y2); y <= qMax(y1, y2); y++){
            pixel(qRound((y - b) / a), y);
        }
        return;
    }
}

// Funkcja rysujaca okrag
void MyWindow::okrag(int x1, int y1, int x2, int y2){
    int R = qRound(qSqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
    int x = 0;
    int y = R;

    if (R == 0){
        pixel(x1, y1);
        return;
    }

    while (x <= y){
        pixel(x1 + y, y1 - x);
        pixel(x1 - y, y1 - x);

        pixel(x1 + y, y1 + x);
        pixel(x1 - y, y1 + x);

        pixel(x1 - x, y1 - y);
        pixel(x1 - x, y1 + y);

        pixel(x1 + x, y1 - y);
        pixel(x1 + x, y1 + y);

        x++;
        y = qRound(qSqrt(R * R - x * x));
    }
}

// Funkcja do rysowania elipsy
void MyWindow::elipsa(int x1, int y1, int x2, int y2){
    int a = qMax(x1, x2) - qMin(x1, x2);
    int b = qMax(y1, y2) - qMin(y1, y2);

    //usunac pozniej i wstawic parametr funkcji
    int n = 50;

    double katBaza = 2 * M_PI / n;
    int wczesniejszyX = x1 +a;
    int wczesniejszyY = y1;

    for (int i = 1; i <= n; i++){
        double kat = i * katBaza;

        int nowyX = x1 + qRound(a * qCos(kat));
        int nowyY = y1 + qRound(b * qSin(kat));

        odcinek(wczesniejszyX, wczesniejszyY, nowyX, nowyY);

        wczesniejszyX = nowyX;
        wczesniejszyY = nowyY;
    }

}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    // Sa to wspolrzedne wzgledem glownego okna
    int x = event->x();
    int y = event->y();

    // Przesuwamy je zeby nie rysowac od brzegu
    x = x - poczX;
    y = y - poczY;


    // Sprawdzamy czy klikniecie nastapilo w granicach rysunku
    if ((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        kopia = *img;
        sX = x;
        sY = y;

        rysowanie = true;

        if (pixelONOFF){
            pixel(x, y);
            rysowanie = false;
        }
    }

    // Odswiezamy komponent
    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event){
    if (rysowanie){
        if (odcinekONOFF){
            int x = event->x() - poczX;
            int y = event->y() - poczY;

            *img = kopia;

            odcinek(sX, sY, x, y);
            update();
        }
        if (okragONOFF){
            int x = event->x() - poczX;
            int y = event->y() - poczY;

            *img = kopia;

            okrag(sX, sY, x, y);
            update();
        }
        if (elipsaONOFF){
            int x = event->x() - poczX;
            int y = event->y() - poczY;

            *img = kopia;

            elipsa(sX, sY, x, y);
            update();
        }
    }
}


void MyWindow::mouseReleaseEvent(QMouseEvent *event){
    if (rysowanie){
        if (odcinekONOFF){
            int x = event->x() - poczX;
            int y = event->y() - poczY;

            *img = kopia;
            odcinek(sX, sY, x, y);
            update();
            rysowanie = false;
        }
        if (okragONOFF){
            int x = event->x() - poczX;
            int y = event->y() - poczY;

            *img = kopia;
            okrag(sX, sY, x, y);
            update();
            rysowanie = false;
        }
        if (elipsaONOFF){
            int x = event->x() - poczX;
            int y = event->y() - poczY;

            *img = kopia;
            elipsa(sX, sY, x, y);
            update();
            rysowanie = false;
        }
    }
}
