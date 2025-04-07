#include <iostream>
#include <vector>

#include "Parser.h"

void Parser::parseExampleFile(const std::string& file)
{
	// On suppose que le fichier d'entrée fichier.csv contient le contenu suivant :
	/* #chaine,entier,flottant
	 * aaaa;7;15.6
	 * bbbb;-2;1.0
	 * cccc;78;3.4
	 *
	 * ...
	 */

	// On ouvre le fichier
	std::ifstream stream{file};

	// On prépare le mode de lecture spécial CSV
	auto currentLocale = stream.getloc();

	// Cette variable est un cas particulier de new sans delete. En effet,
	// dans le cas des objets utilisés par std::locale, c'est la
	// bibliothèque standard qui gère la durée de vie de ces objets une fois
	// que les lui confie (et seulement dans ce cas) et qui fait le delete
	// de son côté.
	Parser::CsvWhitespace* whitespaceRule = new Parser::CsvWhitespace();

	std::locale csvLocale{currentLocale, whitespaceRule};

	std::string str;
	// On vérifie que le fichier est bien ouvert, qu'on n'est pas arrivé
	// au bout et qu'on n'a pas rencontré d'erreur jusqu'alors
	while (!stream.fail() && !stream.eof()) {
		// on extrait une ligne du fichier
		std::getline(stream, str);

		if (str.empty() || str[0] == '#') {
			// on ignore les lignes commençant par # et vides
			continue;
		}

		// on crée un flux d'entrée depuis la ligne
		std::istringstream is{str};

		// on associe au flux le "mode" CSV
		is.imbue(csvLocale);

		std::string chaine;
		int entier;
		float flottant;
		is >> chaine >> entier >> flottant;
		// Au premier tour de boucle, on récupère "aaaa" dans chaine,
		// 7 dans entier, 15.6 dans flottant ; au deuxième tour, "bbbb"
		// dans chaine, -2 dans entier et 1.0 dans flottant, etc.

		// On fait ce qu'on veut des données : stockage dans un
		// conteneur, export ou ici simple affichage
		std::cout << "chaine : " << chaine << "\n"
			  << "entier : " << entier << "\n"
			  << "flottant : " << flottant << "\n\n";
	}
}


// fonction main de test/démonstration
int main()
{
	// On crée un parseur
	Parser p;

	// On donne un nom de fichier à parser
	p.parseExampleFile("fichier.csv");

	p.parseExampleFile("fichier.csv");
}
