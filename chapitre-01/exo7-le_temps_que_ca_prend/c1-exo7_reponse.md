# Exercice 7 : Le temps que ça prend

J'ai chronométré `jenga build --config Debug` avec `time`, après `jenga clean --config Debug`.

## Premier essai : sans `--keep-going`

```bash
$ time jenga build --config Debug
Projects Built:  2/214
Failed:         1
Not reached:    211  (arret au premier echec — voir --keep-going)
Status:         ✗ FAILURE
real	0m17,756s
```

La construction s'arrête au premier échec (`NKGLSlang`, 6 erreurs) : 211 projets ne sont pas atteints. Je l'ai relancée juste après, sans rien modifier : 18,9 s. Il n'y a presque aucun écart, car le projet en échec est recompilé entièrement à chaque fois. Ce n'est donc pas une construction complète.

## Construction complète à froid : avec `--keep-going`

```bash
$ jenga clean --config Debug
$ time jenga build --config Debug --keep-going
Projects Built:  45/214
Failed:         4
Skipped:        165  (dependance echouee)
Errors:         13
Warnings:       433
Time:           1m21.3s
Status:         ✗ FAILURE

real	1m22,286s
user	6m22,259s
```

Échecs : `NKGLSlang`, `NKCollision`, `NKWindow`, `NKAudio`. Les 165 projets sautés dépendent de l'un d'eux (par exemple 46 attendent `NKWindow`).

## Seconde construction, juste après, sans rien modifier

```bash
$ time jenga build --config Debug --keep-going
[SECONDE MESURE : coller Projects Built, Time et real]
```

## Explication de l'écart

À écrire avec vos chiffres. Base : Jenga compare les dates des sources à celles des objets ; les 45 projets réussis ne sont pas recompilés, seuls les 4 en échec sont retentés, donc le second temps est plus court mais pas nul..