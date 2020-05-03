# Langage ALG

## 1. Syntaxe

Inspirée par Intel64.

```asm
; Ceci est un commentaire, la ligne commence par ;

; Assigner une valeur à une variable
set nom_de_variable valeur

; Afficher une variable ou le résultat d'une opération
display nom_de_variable_ou_valeur

; Récupérer un nombre depuis la console
get nom_de_variable

; Pour déclarer une fonction, il suffit de marquer son nom, sans indentation
nom_de_la_fonction
; Le code exécuté par cette fonction doit être précédé d'une tabulation.
code à exéctuer
jump nom_de_la_fonction
```

## 2. Structure d'un programme

Un programme ALG doit forcément avoir une fonction nommée `main`.
Aucune instruction ne doit se situer en dehors d'une fonction.
Toutes les variables déclarées sont globales.

## 3. Instructions utilisables

| Nom de l'instruction 	| Arguments                      	| Description                                                           	|
|----------------------	|--------------------------------	|-----------------------------------------------------------------------	|
| display              	| `Valeur`                       	| Affiche la valeur donnée.                                             	|
| displaytext           | `Texte à afficher`              | Affiche le texte donné.                                                   |
| get                  	| `Nom de la variable`           	| Assigne une valeur récupérée depuis la console à une variable donnée. 	|
| jump                 	| `Nom de la fonction`           	| Exécute le code appartenant à la fonction indiquée.                   	|
| pop                  	| `Variable`                     	| Déplace la valeur située en haut de la pile dans la variable donnée.  	|
| push                 	| `Valeur`                       	| Place la valeur donnée en haut de la pile.                            	|
| set                  	| `Nom de la variable`, `Valeur` 	| Assigne une valeur donnée à une variable donnée.                      	|