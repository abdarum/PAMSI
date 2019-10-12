#ifndef ROBOT_HH
#define ROBOT_HH

#include "Macierz2x2.hh"
#include "Objekt_Graficzny.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#define LICZBA_PUNKTOW 6
/*!
 * \file
 * \brief Definicja klasy Robot
 *
 * Plik zawiera kalse Robot
 */


/*!
 *\brief Modeluje informacje dotyczace Robota
 *
 * Modeluje zestaw informacji dotyczacych Robota.
 * Udostępnia także metody umozliwiające aktualizowanie wartosci 
 * a także zwracanie ich.
 */
class Robot: public Objekt_Graficzny 
{
  std::vector<double> Domyslne_Wartosci{2,0,7,0,0,-10,-10,-10,-10,10,0,10};
  Wektor2D _wektor_translacji;
  double _poprzedni_kat;
public:
  /*!
   * \brief Inicjalizacja Robota w pozycji podstawowej
   */
  Robot(){Objekt_Graficzny(); Objekt_Graficzny::Ustaw(Domyslne_Wartosci); _wektor_translacji=Wektor2D();_poprzedni_kat=0;}
  /*!
   * \brief Inicjalizacja Robota w pozycji podstawowej z ustawieniem wektora 
   *          translacji
   */
  Robot(Wektor2D Wsp_Globalne,double Kat_Obrotu){Robot(); _wektor_translacji=Wsp_Globalne; Objekt_Graficzny::Kat(Kat_Obrotu);}
  /*!
   * \brief Zwraca współrzędne globalne robota
   */
  Wektor2D Wektor_Translacji() const{return _wektor_translacji;}
  /*!
   * \brief Ustawia współrzędne globalne robota
   */
  void Wektor_Translacji(Wektor2D Wsp_Globalne){ _wektor_translacji=Wsp_Globalne;}
  /*!
   * \brief Obraca prostakat o kat a
   *
   * \param[in] a kąt o jaki obrócić prostokąt
   */
  void ObrocOKat(double a);
  /*!
   * \brief Zapisuje wspolrzedne do pliku w formacie zgodnym z Gnuplotem 
   *
   * Funkcja jest niewielką modyfikacją funkcji "PrzykladZapisuWspolrzednychDoPliku" z pliku main dostarczonego w folderze zalazek
   */
  bool ZapisWspolrzednychDoPlikuFormatGnuplot(const char  *sNazwaPliku);
  /*!
   * \brief Funkcja wypisuje do strumienia punkty w odpowiednim formacie
   */
  void WyswietlWspolrzedneFormatGnuplot(std::ostream& StrmWy) const;





  /*!
   * \brief Funkcja przygotowuje punkty pod animację
   *
   * \param[in] a - kat przeskoku
   */
  void Przygotuj_Animacje_Obrotu(double a=1);
  /*!
   * \brief Funkcja wypisuje kolejne punkty posrednie do strumienia tworząc 
   *         animację obrotu robota
   *
   * \param[in] StrmWy - strumień do którego mają być wypisane wierzchołki
   * \param[in] Rob - Robot, którego ścieżka będzie animowana
   * \param[in] Ind - Numer punktu tymczasowego
   *
   *
   *
   * \param[in] a - kat przeskoku
   */ 
  void Animacja_Obrotu_Robota(std::ostream& StrmWy,double a=1);
  //void Animacja_Obrotu_Robota(std::ostream& StrmWy,Robot& Rob);

};

/*!
 * \brief Wyswietla współrzędne wierzchołków względem siebie
 *
 * Uwzględnia kąt a nie uwzględnia przesunięcia. 
 */
std::ostream& operator << (std::ostream &Strm, const Robot  &Rob);

#endif
