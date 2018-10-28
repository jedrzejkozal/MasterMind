/*argumenty
kod - kod, ktory trzeba odgadnac, odlegosc do niego bedzie sprawdzana
proba - kombinacja, ktora ma byc oceniania
dlugosc - dlugosc lancuchow zmiennych
poprawne - ilosc kulek na swoim miejscu i o odpowiednim kolorze w proponowanej kombinacji
poprawne_miejsca - ilosc kulek na poprawnym miejscu, ale z innym kolorem*/
void check(Color *code, Color *guess, const unsigned length, unsigned &correct, unsigned &correctPlace)
{
	correct = 0;
	correctPlace = 0;

	//tablica flag do sprawdzenia czy cos ma dobry kolor ale jest na nieswoim miejscu
	bool *bylo_na_dobrym;
	bylo_na_dobrym = new bool[length];
	for (unsigned i = 0; i < length; i++)
		bylo_na_dobrym[i] = false;

	//sprawdzenie czy jest cos na swoim miejscu
	for (unsigned i = 0; i < length; i++)
	{
		if (guess[i] == code[i])
		{
			correct++;
			bylo_na_dobrym[i] = true; //tutaj zaznaczamy ze bylo na dobrym miejscu
		}
	}
	//sprawdzenie czy jest dobry kolor na nieswoim miejscu
	for (unsigned i = 0; i < length; i++)
			for (unsigned j = 0; j < length; j++)
				if (guess[i] == code[j] && bylo_na_dobrym[j] == false)
				{
					correctPlace++;
					bylo_na_dobrym[j] = true; //tutaj zaznaczamy ze bylo wykorzystane, na wypadek gdyby ten sam kolor mialby byc
											  //sprawdzany w przyszlosci (nie trzeba deklarowac nowej tablicy)
					break;
				}

	delete[] bylo_na_dobrym;
}
