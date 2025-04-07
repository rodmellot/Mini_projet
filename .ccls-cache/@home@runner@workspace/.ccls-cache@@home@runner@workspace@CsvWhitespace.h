#ifndef CSV_WHITESPACE_H
#define CSV_WHITESPACE_H

#include <string>
#include <fstream> // pour ifstream
#include <sstream> // pour istringstream
#include <locale> // pour ctype, mask, locale
#include <iostream>
#include <vector>

/**
 * Afin de pouvoir parser les fichiers CSV avec les opérateurs de flux,
 * on redéfinit le flux d'entrée pour considérer les points-virgules,
 * qui séparent les colonnes, comme des espaces.
 * À l'inverse, on ignore tous les caractères qui sont séparateurs
 * normalement à part les retours à la ligne. Comme cela, on autorise
 * les champs à contenir des espaces.
 *
 * Cela permet, étant donné un fichier :
 * CODE;NOM;VALEUR
 * d'écrire des instructions telles que
 * flux >> var1 >> var2 >> var3;
 * pour enregistrer dans les variables var1, var2 et var3 respectivement
 * les valeurs des colonnes CODE, NOM et VALEUR, même si CODE, NOM ou
 * VALEUR contiennent des espaces.
 *
 * Ce n'est pas un mécanisme très résistant, on ne peut pas parser
 * correctement les chaînes de caractères si elles contiennent des
 * points-virgules entre guillemets par exemple. Néanmoins, c'est suffisant
 * pour notre usage.
 */
struct CsvWhitespace : std::ctype<char>
{
	explicit CsvWhitespace(std::size_t refs = 0);
	const mask* make_table();
};

#endif
