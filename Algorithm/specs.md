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