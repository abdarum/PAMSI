#include "Robot.hh"


void Robot::Animacja_Obrotu_Robota(std::ostream& StrmWy,double a)
{
  Wektor2D tmp;
  if(Objekt_Graficzny::Koniec_Animacji()!=true)
    {
      if(Objekt_Graficzny::Kat()-_poprzedni_kat>a)
	{
	  Objekt_Graficzny::Usun_Elementy();
	  Objekt_Graficzny::Ustaw(Domyslne_Wartosci);
	  for(int i=0;i<Objekt_Graficzny::Rozmiar();++i)
	    {    
	      tmp=Macierz2x2(_poprzedni_kat)*Objekt_Graficzny::Wartosc_Lok(i);
	      Objekt_Graficzny::Wartosc_Lok(i,tmp);
	    }
	  WyswietlWspolrzedneFormatGnuplot(StrmWy);
	  _poprzedni_kat+=a;
	}
      else
	{
	  Objekt_Graficzny::Koniec_Animacji(true);
	  _poprzedni_kat=Objekt_Graficzny::Kat();
	  Objekt_Graficzny::Usun_Elementy();
	  Objekt_Graficzny::Ustaw(Domyslne_Wartosci);
	  for(int i=0;i<Objekt_Graficzny::Rozmiar();++i)
	    {    
	      tmp=Macierz2x2(_poprzedni_kat)*Objekt_Graficzny::Wartosc_Lok(i);
	      Objekt_Graficzny::Wartosc_Lok(i,tmp);
	    }
	  WyswietlWspolrzedneFormatGnuplot(StrmWy);
	} 
    }
}


double Robot::Promien() const   
{
  std::vector<double> odl;
  Wektor2D Wektor_Zerowy;
  for(int i=0;i<Objekt_Graficzny::Rozmiar();++i)
    odl.push_back(Wektor_Zerowy.Odleglosc_Wektorow(Objekt_Graficzny::Wartosc_Glob(i)));
  std::sort(odl.begin(),odl.end());
  return odl.back();
}


void Robot::ObrocOKat(double a)
{
  Wektor2D tmp;
  _poprzedni_kat=Objekt_Graficzny::Kat();
  Objekt_Graficzny::Koniec_Animacji(false);

  Objekt_Graficzny::Usun_Elementy();
  Objekt_Graficzny::Ustaw(Domyslne_Wartosci);
  Objekt_Graficzny::Kat(Objekt_Graficzny::Kat()+a);
  Objekt_Graficzny::Kat(fmod(Objekt_Graficzny::Kat(),360.0));
  for(int i=0;i<Objekt_Graficzny::Rozmiar();++i)
    {    
      tmp=Macierz2x2(Objekt_Graficzny::Kat())*Objekt_Graficzny::Wartosc_Lok(i);
      // Objekt_Graficzny::Wartosc_Lok(i,Macierz2x2(Objekt_Graficzny::Kat())*(Objekt_Graficzny::Wartosc_Lok(i)));
      Objekt_Graficzny::Wartosc_Lok(i,tmp);
    }
}

std::ostream& operator << (std::ostream &Strm, const Robot &Rob)
{
  for(int i=0;i<Rob.Rozmiar();++i)
    std::cout<<(Rob.Wartosc_Glob(i)+Rob.Wektor_Translacji())<<std::endl; 
  return Strm;
}


void Robot::WyswietlWspolrzedneFormatGnuplot(std::ostream& StrmWy) const
{
  for(int i=0;i<(Objekt_Graficzny::Rozmiar()+1);++i){
    (Wektor_Translacji()+Objekt_Graficzny::Wartosc_Glob(i>=Objekt_Graficzny::Rozmiar()?(i%Objekt_Graficzny::Rozmiar())+1:i)).WyswietlWspolrzedneFormatGnuplot(StrmWy);
  }

}

bool Robot::ZapisWspolrzednychDoPlikuFormatGnuplot(const char  *sNazwaPliku)
{
  std::ofstream  StrmPlikowy;
  
  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr<<":(  Operacja otwarcia do zapisu \""<< sNazwaPliku << "\"";
    std::cerr<<std::endl<< ":(  nie powiodla sie." << std::endl;
    return false;
  }
  
  WyswietlWspolrzedneFormatGnuplot(StrmPlikowy);

  
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}







bool Robot::Okregi_sie_przecinaja(const std::shared_ptr<Objekt_Graficzny> &R2,const Wektor2D &Obecne_Polozenie) const
{
  double Odleglosc_Robotow=0;
  Odleglosc_Robotow=Obecne_Polozenie.Odleglosc_Wektorow(R2->Wektor_Translacji());
  //std::cout<<"Prom :"<<Promien()<<" | Prom2: "<<R2->Promien()<<" | Odl: "<<Odleglosc_Robotow<<std::endl;
  if((Promien()+R2->Promien())>=Odleglosc_Robotow)
    return true;
  else
    return false;
}

bool Robot::Punkt_Nalezy_Do_Prostokata(const std::shared_ptr<Objekt_Graficzny> &Pr,const Wektor2D &Obecne_Polozenie) const
{
  //  std::cout<<"Obecne Polozenie: "<<Obecne_Polozenie<<std::endl;
  if( (Obecne_Polozenie[0] > (Pr->Min_X()-Promien())) && (Obecne_Polozenie[0] < (Pr->Min_X()+Promien())) )
    {
      //std::cout<<" Polozenie X"<<"\t"<<"wsp Y: "<<Obecne_Polozenie[1]<<"\t"<<"Y min "<<Pr->Min_Y()<<"\t"<<"Y max "<<Pr->Max_Y();
      //   if(Obecne_Polozenie[1] > (Pr->Min_Y()-Promien()))
      if(Obecne_Polozenie[1] < (Pr->Min_Y()+Promien()))
	{ 
	  //  std::cout<<std::setw(6)<<std::fixed<<std::setprecision(2)<<"wieksze  "<<Obecne_Polozenie[1]<<" niz "<<Pr->Min_Y()-Promien()<<" Promien "<<Promien()<<" Y min "<<Pr->Min_Y()<<std::endl;
	  //	if(Obecne_Polozenie[1] < (Pr->Min_Y()+Promien()))
	  if(Obecne_Polozenie[1] > (Pr->Min_Y() -  Promien()))
	    {
	      //  std::cout<<" Polozenie Y"<<std::endl;
	      return true;
	    } 
	}
      //      std::cout<<std::endl;
    }
 return false;

}

bool Robot::Kolizja(const  std::list<std::shared_ptr<Objekt_Graficzny>> &objekty,const Wektor2D &Obecne_Polozenie) const
{
  //  std::cout<<"Funkcja Kolizja"<<std::endl; 
  for(const std::shared_ptr<Objekt_Graficzny> &wsk : objekty ) 
    {
      /*
      std::cout<<"Funkcja Kolizja for: "<<wsk->Rodzaj_Obiektu_Nazwa()<<std::endl; 
      std::cout<<"Ob: "<<wsk<<" | This: "<<this<<" | This_ID: "<<ID_Robota()<<" | ID badanego robora : "<<wsk->ID_Robota()<<std::endl;
      */
      if( wsk->Rodzaj_Obiektu() == Ob_Robot ){
	if(wsk->ID_Robota()  != ID_Robota() )
	    //	  if(Okregi_sie_przecinaja(*wsk,Obecne_Polozenie) )
	    if(Okregi_sie_przecinaja(wsk,Obecne_Polozenie) )
	      {
		std::cout<<"UWAGA!  Nastapila kolizja z Robotem"<<std::endl;
		return true;
	      }
	  }
      if( wsk->Rodzaj_Obiektu() == Ob_Przeszkoda )
	{
	  /*
	  std::cout<<wsk->Rodzaj_Obiektu_Nazwa()<<"  ";
	  wsk->Wyswietl_Ekstrema();
	  */
	  if (Punkt_Nalezy_Do_Prostokata(wsk,Obecne_Polozenie) )
	    {
	      std::cout<<"UWAGA!  Nastapila kolizja z Przeszkoda"<<std::endl;
	      return true;
	    }
	}
    }
  
  return false;
}
