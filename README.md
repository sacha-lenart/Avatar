# Avatar articulé

L'avatar articulé évolue en ligne droite dans un couloir, bloqué à chaque extremité par une chaise. L'avatar peut marcher, courrir, faire demi-tour, danser, s'assoir s'il est proche d'une chaise et se relever. 

Vous pouvez sélectionner parmis 5 vues différentes. Vous pouvez également choisir de laisser l'avatar réaliser des mouvements aléatoirement. 

Ce programme utilise la librairie OpenGl.

# Compilation

ouvrir un terminal et tapper les lignes de commande :

>gcc avatar.c -o test -lglut -lGLU -lGL -lm
>./test

# Touches :

Mouvements :
>a: s'assoir
>r: courir
>m: marcher
>s: demi-tour
>d: danser

Vues :
>4: dessus
>5: derrier
>6: devant
>7: incline
>8: cote

Modes :
>0: manuel
>1: aleatoire

