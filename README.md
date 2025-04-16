# Mini_projet

Les données sont incorporées dans le projet dans le dossier "Donnees/" et donc les fichiers "donnees.csv", "stations.csv", le dossier "radar". Il faut faire attention à adapter les codes si l'on télécharge différemment.
Le code est directement éxéctuable avec la commande : clang++ -std=c++17 -o main main.cpp && ./main

Les réponses aux questions écrites sont résumées ici : 

Question 6 : L'avantage de la comparaison avec l'opérateur < est que l'on peut utiliser des structures de données comme les sets ou les maps qui nécessitent une relation d'ordre pour fonctionner correctement. L'avantage de la comparaison avec l'opérateur == est que l'on peut vérifier si deux stations sont identiques.

Question 7 : La structure de recherche sera définie comme suit : Une map ordonnée dont la clé est la Station et la valeur est une autre map ordonnée, dont la clé est la Date et la valeur est le tuple Relevé <float, float, float, float> (Température Minimale, Température Maximale, Température Moyenne, Pluviométrie). 


Ce Mini projet réalisé par Marie Boyer et Rodrigue Mellot-Cavelier est visible sur github à l'adresse publique suivante : https://github.com/rodmellot/Mini_projet.git