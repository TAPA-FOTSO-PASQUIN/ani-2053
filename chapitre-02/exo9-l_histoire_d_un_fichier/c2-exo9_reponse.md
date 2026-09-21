# Exercice 9 : L'histoire d'un fichier

J'ai choisi `NKMath.jenga`, le fichier de projet du module NKMath. Avec `git log --follow`, j'ai trouvé 12 commits, du 2026-03-01 au 2026-06-14. Il a été déplacé deux fois : `NKMath/` puis `Modules/Foundation/NKMath/`, puis `Kernel/Foundation/NKMath/`.

## Sa création

Il a été créé le 2026-03-01 par le commit `a41122c3` (60 lignes ajoutées) : « Restructure workspace: per-project jenga files + NKMath/NKTime/NKStream/NKMemory/NKRenderer ». Ce message dit ce qui est fait et pourquoi : on passe à un fichier de projet par module.

## Les trois moments où il a le plus changé

J'ai additionné les lignes ajoutées et supprimées avec `git log --follow --numstat`.

**1. `fe9b17f5`, 2026-03-05, « bug fix » (34 + 33 = 67 lignes).** Il corrige `language("C++17")` en `language("C++")` plus `cppdialect("C++17")`, et met tout le bloc `NKMath_Bench` en commentaire.

**2. `f909152c`, 2026-03-10, « Align Wayland jenga links/tests (renderer/camera/sandbox) » (2 + 55 = 57 lignes).** Il simplifie les `includedirs`, réécrit le filtre des tests avec des parenthèses pour exclure Android et iOS, remet `testfiles(["tests/**.cpp"])` et supprime les benchmarks commentés.

**3. `a7e5448b`, 2026-03-05, « add readme » (50 + 1 = 51 lignes).** Il ajoute le projet de benchmarks `NKMath_Bench` et remplace `tests/**.cpp` par une liste explicite de fichiers.

## Ce que les messages disent des raisons

- **« bug fix »** ne dit pas quel bug. Le diff donne la raison : `language("C++17")` était une mauvaise utilisation, et les benchmarks ajoutés 25 minutes plus tôt ont été désactivés. Cette raison est une déduction, pas une certitude.
- **« add readme »** ne correspond pas au diff, qui ajoute des benchmarks et modifie les tests. Le message décrit sans doute les autres fichiers du commit, donc il mélange plusieurs sujets.
- **« Align Wayland… »** décrit d'autres fichiers que celui-ci. Ici, le commit nettoie le fichier et annule presque tout ce qu'`a7e5448b` avait ajouté cinq jours plus tôt.

Sur ces trois commits, aucun message ne dit pourquoi. C'est le diff qui permet de deviner la raison, et c'est ce que le chapitre 2 reproche à un dépôt dont les messages disent « fix » ou « update ». Les quatre commits du 5 mars montrent une période de mise au point : le fichier a été modifié, puis corrigé, puis simplifié.