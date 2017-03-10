/*argumenty
kod - kod, ktory trzeba odgadnac, odlegosc do niego bedzie sprawdzana
proba - kombinacja, ktora ma byc oceniania
dlugosc - dlugosc lancuchow zmiennych
poprawne - ilosc kulek na swoim miejscu i o odpowiednim kolorze w proponowanej kombinacji
poprawne_miejsca - ilosc kulek na poprawnym miejscu, ale z innym kolorem*/
void sprawdz(Kolor *kod, Kolor *proba, const unsigned dlugosc, unsigned &poprawne, unsigned &poprawne_miejsca)
{
	poprawne = poprawne_miejsca = 0;

	//tablica flag do sprawdzenia czy cos ma dobry kolor ale jest na nieswoim miejscu
	bool *bylo_na_dobrym;
	bylo_na_dobrym = new bool[dlugosc];
	for (unsigned i = 0; i < dlugosc; i++)
		bylo_na_dobrym[i] = false;

	//sprawdzenie czy jest cos na swoim miejscu
	for (unsigned i = 0; i < dlugosc; i++)
	{
		if (proba[i] == kod[i])
		{
			poprawne++;
			bylo_na_dobrym[i] = true; //tutaj zaznaczamy ze bylo na dobrym miejscu
		}
	}
	//sprawdzenie czy jest dobry kolor na nieswoim miejscu
	for (unsigned i = 0; i < dlugosc; i++)
			for (unsigned j = 0; j < dlugosc; j++)
				if (proba[i] == kod[j] && bylo_na_dobrym[j] == false)
				{
					poprawne_miejsca++;
					bylo_na_dobrym[j] = true; //tutaj zaznaczamy ze bylo wykorzystane, na wypadek gdyby ten sam kolor mialby byc
											  //sprawdzany w przyszlosci (nie trzeba deklarowac nowej tablicy)
					break;
				}

	delete[] bylo_na_dobrym;
}
