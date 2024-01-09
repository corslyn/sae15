# SAé 15 - Traiter des données - Défi 1 - Groupe 17

Suivi : https://docs.google.com/document/d/1it6LBhr-Q4gG36iODh7H2lBcTRrTfJbJHwyuoBGaKZc/edit?usp=sharing

## Solution utilisée

Afin de résoudre ce défi, nous avons utilisé la classe lightSensor qui permet de détecter si une ligne se trouve sous un capteur, la classe lineDriver qui permet de déterminer quelle est la situation du robot (ex: virage serré à droite, à gauche...) et la classe FastLED pour contrôler la LED.

### Suivi de la ligne

Pour le suivi de la ligne, nous avons créé une fonction `void deplacer()` pour déplacer le robot. Cette fonction est executée jusqu'à ce que les 3 tours ont étés effectués.

### Comptage des tours

Pour compter le nombre de tours effectués, nous détectons quand les trois capteurs voient une ligne (croisement), on incrémente alors un compteur. Tout les 2 croisements, on change la couleur de la LED.

Au croisement 6 (fin tour 3), le robot s'arrete et la LED devient rouge. 

# Vidéo de démonstration

# Code Source

https://github.com/corslyn/sae15/


