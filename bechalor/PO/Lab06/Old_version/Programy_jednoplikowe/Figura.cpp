
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

#define WYMIAR_WEKTORA 2

/*!
 * \file
 *
 * \brief Definicja kalsy typu Wektor2D
 *
 * Plik zawiera deklaracje klasy Wektor2D i przeci��e� operator�w
 * cout i cin dla klasy Wektor2D
 */


/*!
 *\brief Modeluje informacje dotyczace wektora
 *
 * Modeluje zestaw informacji dotyczacych wektora.
 * Udost�pnia tak�e metody umozliwiaj�ce aktualizowanie wartosci 
 * a tak�e zwracanie ich.
 */
class Wektor2D {
  double _wart[WYMIAR_WEKTORA];
  static int _laczna_liczba_utworzonych;
  static int _aktualna_liczba_istniejacych;
  void Aktualizuj_Statystyki(){Wektor2D::_laczna_liczba_utworzonych++; Wektor2D::_aktualna_liczba_istniejacych++;}
  
public:
  /*!
   *  \brief Inicjalizyje zmienna typu Wektor2D zerami
   */    
  Wektor2D() {Aktualizuj_Statystyki(); Zeroj_Wektor();}
  /*!
   *  \brief Inicjalizyje zmienna typu Wektor2D wartosciami 
   *
   *  param[in] x_new - inicjalizuje pierwsza wsp�rz�dn� wartosci� x_new
   *  param[in] y_new - inicjalizuje drug� wsp�rz�dn� wartosci� y_new
   */    
  Wektor2D(double x_new, double y_new) {Aktualizuj_Statystyki(); _wart[0]=x_new;
 _wart[1]=y_new;}
  /*!
   * \brief Destruktor
   *
   * Po usuni�ciu zmiennej zmniejsza dekrementuje liczb� aktualnie istniej�cych objekt�w
   */
  ~Wektor2D(){Wektor2D::_aktualna_liczba_istniejacych--;}
  /*!
   *  \brief Ustawia pierwsza wspolrzedno wektora na x_new
   */
  void Ustaw_X(double x_new){_wart[0]=x_new;}
  /*!
   *  \brief Ustawia druga wspolrzedna wektora na y_new
   */
  void Ustaw_Y(double y_new){_wart[1]=y_new;}
  /*!
   *  \brief Ustawia  wartosc wsp�rz�dnej wektora Ind na warto�� wart_new
   *  \param[in] wart_new - warto�� kt�ra ma by� nadana wybranej wsp�rz�dnej wektora
   *  \param[in] Ind - wsp�rz�dna dla kt�rej warto�� ma by� zmieniona
   *  Ind dla pierwszej wsp�rz�dnej 0, drugiej 1 itd.
   */
  void Ustaw_Wsp(double wart_new, int Ind){assert(Ind<WYMIAR_WEKTORA); _wart[Ind]=wart_new;}
  /*!
   *  \brief Ustawia  wspolrzedne wektora na odpowiednio x_new, y_new 
   */
  void Ustaw(double x_new, double y_new){_wart[0]=x_new; _wart[1]=y_new;}
  /*!
   * \brief Zwraca wartosc pierwszej wspolrzednej
   */
  double Zroc_X(){return _wart[0];}
  /*!
   * \brief Zwraca wartosc drugiej wspolrzednej
   */
  double Zwroc_Y(){return _wart[1];}
  /*!
   * \brief Przeciarzenie operatra dodawania wektor�w
   * 
   * \param[in] Wek Wektor jaki ma by� dodany 
   */
  Wektor2D operator+ (Wektor2D Wek){for(int i=0;i<WYMIAR_WEKTORA;++i) Wek[i]+=_wart[i]; return Wek; }
  /*!
   * \brief Przeciarzenie operatra dodawania wektor�w
   * 
   * \param[in] Wek Wektor jaki ma by� dodany 
   */
  Wektor2D& operator+= (const Wektor2D& Wek){*this=*this+Wek; return *this; }
  /*!
   * \brief Przeciarzenie operatra mno�enia wektora przez liczb�
   * 
   * \param[in] Liczba przez jak� wektor ma by� przemno�ony 
   */
  Wektor2D operator* (const double &Liczba) const {Wektor2D Wek=*this; for(int i=0;i<WYMIAR_WEKTORA;++i) Wek[i]*=Liczba; return Wek; }
  /*!
   * \brief Przeciarzenie operatra mno�enia wektor�w
   * 
   * \param[in] Liczba przez jak� wektor ma by� przemno�ony 
   */
  Wektor2D& operator*= (const double& Liczba){*this=*this*Liczba; return *this; }
  /*!
   * \brief Przeciarzenie operatra indeksowania do zwracania wartosci
   */
  double operator[] (int Ind)const { return _wart[Ind];}
  /*!
   * \brief Przeciarzenie operatra indeksowania do przypisania  wartosci
   */
  double &operator[] (int Ind) { return _wart[Ind];}
  /*!
   * \brief Funkcja wypisuje do strumienia punkty w odpowiednim formacie
   */
  void WyswietlWspolrzedneFormatGnuplot(std::ostream& StrmWy) const;
  /*!
   * \brief Funkcja zeruje warto�ci wektora
   */
  void Zeroj_Wektor(){for(int i=0;i< WYMIAR_WEKTORA;++i) _wart[i]=0;}
  /*!
   * \brief Funkcja zwraca liczb� istniej�cych objekt�w 
   */
  static  int Ile_Istnieje(){return _aktualna_liczba_istniejacych;}
  /*!
   * \brief Funkcja zwraca  ��czn� liczb� utworzonych objekt�w  
   */
  static int Ile_Utworzono(){return _laczna_liczba_utworzonych;}
  /*!
   * \brief Funkcja wypisuje statystyki ile utworzono objekt�w a ile teraz istnieje
   */
  static void Wyswietl_Statystyki(){
    std::cout<<"Laczna ilosc stworzonych obiektow klasy Wektor2D: "<<_laczna_liczba_utworzonych<<std::endl;
    std::cout<<"      Ilosc istniejacych obiektow klasy Wektor2D: "<<_aktualna_liczba_istniejacych<<std::endl;  }
};

/*!
 *\brief Wczytuje wsp�rz�dne wektora
 *
 * Wsp�rz�dne s� pobierane w kolejno�ci x , y
 */
std::istream& operator >> (std::istream &Strm, Wektor2D &Wek);

/*!
 *\brief Wyswietla wsp�rz�dne wektora
 *
 * Wsp�rz�dne s� zwracane w kolejno�ci x (znak tabulacji) y
 */
std::ostream& operator << (std::ostream &Strm, const Wektor2D &Wek);


/*************************************************************/

class Figura {
  std::vector<Wektor2D> _figura;
public:
  Figura(){_figura.reserve(5);}
  void  Ustaw_Wartosci(Wektor2D Wart[4]){for(int i=0;i<4;++i) _figura.push_back(Wart[i]);}
  Wektor2D Zwroc(int Ind){return _fig[Ind}
  int Size(){return _figura.size();}
  
};

class Kwadrat: public Figura
{
  double odl[2];
  std::vector<Figura> _kwadrat; 
public:
  float Oblicz_Pole()
  {
    for(int k=0;k<_kwadrat.size();i++)
      for(int i=0;i<_kwadrat[k].Size();i+=2)
	odl[i/2]=(sqrt(pow(_kwadrat[k].Zwroc()[i%2]-_kwadrat[k].Zwroc()[i%2+1],2)+pow((_kwadrat[k].Zwroc()[i%2]-_kwadrat[k].Zwroc()[i%2+1],2)));

  }

  
};

/*************************************************************/

int main()
{


}


/*************************************************************/

void Wektor2D::WyswietlWspolrzedneFormatGnuplot(std::ostream& StrmWy) const
{
  for(int i=0;i<WYMIAR_WEKTORA;++i)
    StrmWy<<std::setw(16)<<std::fixed<<std::setprecision(10)<< _wart[i];
  StrmWy<<std::endl;
}

std::istream& operator >> (std::istream &Strm, Wektor2D &Wek)
{
  for(int i=0;i<WYMIAR_WEKTORA;++i)
    std::cin>>Wek[i];
  return Strm;
}


std::ostream& operator << (std::ostream &Strm, const Wektor2D &Wek)
{
  for(int i=0;i<WYMIAR_WEKTORA;++i)
    Strm<<std::setw(16)<<std::fixed<<std::setprecision(10)<< Wek[i];
  return Strm;
}
