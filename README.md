# 2048 en C

Le jeu **2048** dans le terminal, écrit en C standard sans aucune bibliothèque
externe.

C'est mon tout premier projet de programmation, rendu en mai 2022 pour le
projet de programmation de L0 informatique. Le code est conservé tel qu'il a
été rendu.

## Pourquoi ce jeu

2048 a été créé en 2014 par Gabriele Cirulli, qui l'a publié en source libre
([gabrielecirulli/2048](https://github.com/gabrielecirulli/2048)). Je me disais
depuis longtemps qu'un jeu pareil devait être simple à programmer : le coder
était un objectif personnel. Je connaissais déjà les règles et j'avais une idée
de la façon de le représenter en C, alors je me suis lancé directement, sans
autre référence.

Le jeu s'est révélé bien plus technique qu'il n'en a l'air.

## Aperçu

```text
Bienvenue sur 2048 !

Voici les touches à utiliser pour y jouer :
z = Tout envoyer vers le haut
q = Tout envoyer vers la gauche
s = Tout envoyer vers le bas
d = Tout envoyer vers la droite

Très bien, le jeu est lancé !

|  0  |  0  |  0  |  0  |

|  4  |  0  |  0  |  0  |

|  0  |  0  |  0  |  0  |

|  0  |  2  |  0  |  0  |

Entrez un caractère correspondant à un déplacement, les caractères valides sont : z,q,s,d.
```

## Lancer le jeu

Il suffit d'un compilateur C (`gcc` ou `clang`).

```bash
make        # compile le programme
make run    # compile puis lance une partie
make clean  # supprime l'exécutable
```

Sans `make` :

```bash
gcc 2048.c -o 2048
./2048
```

## Commandes

Les touches suivent la disposition d'un clavier AZERTY. Chaque coup se valide
avec la touche Entrée.

| Touche | Déplacement |
| :----: | ----------- |
|  `z`   | haut        |
|  `q`   | gauche      |
|  `s`   | bas         |
|  `d`   | droite      |

## Règles

- La grille fait 4 × 4 et commence avec deux tuiles.
- Un déplacement fait glisser toutes les tuiles dans la direction choisie, et
  deux tuiles de même valeur qui se rencontrent fusionnent en une seule.
- La valeur de chaque fusion s'ajoute au score : réunir deux 4 rapporte
  8 points.
- Après chaque coup, une nouvelle tuile (2 ou 4) apparaît sur une case vide.
- La partie est gagnée quand une tuile 2048 apparaît, et perdue quand la grille
  est pleine.

## Organisation du code

Tout tient dans [`2048.c`](2048.c) :

| Fonction                                       | Rôle                                                                  |
| ---------------------------------------------- | --------------------------------------------------------------------- |
| `main`                                         | boucle de jeu, détection de la victoire et de la défaite              |
| `initialiser_jeu`                              | vide la grille, affiche les consignes, pose les deux premières tuiles |
| `nouveau_bloc`                                 | ajoute une tuile 2 ou 4 sur une case vide au hasard                   |
| `afficher_grille`                              | dessine la grille dans le terminal                                    |
| `mouvement`                                    | lit la touche et appelle le bon déplacement                           |
| `mouvement_haut`, `_bas`, `_gauche`, `_droite` | font glisser puis fusionner les tuiles, renvoient le score gagné      |

## Limites et pistes d'amélioration

Le code est gardé dans son état d'origine. Au moment du rendu, j'avais noté ce
que j'aurais aimé améliorer :

- la partie est perdue dès que la grille est pleine, alors que le vrai jeu ne
  s'arrête que lorsqu'aucun mouvement n'est plus possible ;
- une touche invalide n'est pas redemandée : le tour passe simplement, faute
  d'avoir réussi à le faire avec une boucle `do while` ;
- l'interface pourrait être bien plus soignée avec `ncurses` ;
- il n'est pas possible de quitter la partie de soi-même (seul Ctrl+C
  l'interrompt).

En relisant le code aujourd'hui, d'autres écarts avec les règles officielles
apparaissent :

- une seule fusion a lieu par ligne ou colonne : `2 2 4 4` vers la gauche donne
  `4 4 0 0` au lieu de `4 8 0 0` ;
- une nouvelle tuile apparaît même quand le déplacement n'a rien fait bouger ;
- les colonnes de la grille se décalent dès qu'une tuile dépasse un chiffre ;
- si l'entrée se ferme (Ctrl+D), le programme boucle sans fin sur « Caractère
  invalide ».

## Licence

Distribué sous licence MIT, voir [`LICENSE`](LICENSE).
