# Exercice 4 : Le fichier de projet annoté

J'ai annoté `Kernel/Foundation/NKMemory/NKMemory.jenga` (84 lignes). Un `?` marque ce que je ne comprends pas encore.

## En-tête (lignes 1 à 18)

- **1-2** : `#!/usr/bin/env python3` et l'encodage. Cela confirme que c'est un programme Python.
- **3-15** : docstring qui décrit le module : gestion mémoire avec suivi des allocations et détection de fuites. Elle liste les fichiers de `src/NKMemory/`.
- **17** : `from Jenga import *` charge les fonctions de Jenga (`project`, `files`...).
- **18** : `from jengaconfig import *` charge le code du dépôt (donc `nkentseudependson` et `TC_WINDOWS`).

## Type et sources

- **20** : `with project("NKMemory"):` ouvre le projet. Tout ce qui est indenté lui appartient.
- **21-22** : langage C++, dialecte C++17.
- **23** : `location(".")` : le projet vit dans le dossier du fichier.
- **34-37** : `files` : tous les `.cpp` et `.h` de `src/NKMemory/`, à toute profondeur (`**`).
- **Type** : aucune ligne `staticlib()`. Comme dans `NKMath`, le type vient sans doute de `nkentseudependson` et de son registre (?). Je n'ai pas lu `config/modules.jenga` pour le confirmer.
- **31-32** : `pchheader`/`pchsource` : en-tête précompilé `pch/pch.h`. Je comprends que cela accélère la compilation, mais je ne sais pas comment (?).

## Dépendances

- **25-29** : `nkentseudependson(["NKCore", "NKPlatform"], ...)` : le module dépend de NKCore et NKPlatform, et le raccourci gère `dependson`, `links` et `includedirs`, y compris les dépendances des dépendances.
- **27** : `selfexport="NKMemory"` : je ne sais pas ce que cela exporte (?).
- **28** : `extra_includes=["src", "pch"]` : dossiers d'en-têtes en plus.
- **39-40** : `objdir` et `targetdir` avec `%{cfg.buildcfg}` (Debug/Release) et `%{cfg.system}` : Debug et Release, Windows et Linux ne s'écrasent pas.

## Filtres

- **42-44** : sous Windows UWP, mêmes dossiers avec le suffixe `-uwp`.
- **46-47** : Windows classique (hors UWP et Xbox) : `usetoolchain(TC_WINDOWS)`.
- **48-49** : UWP : chaîne `xbox-clang` (?). Je ne comprends pas pourquoi UWP utilise la chaîne Xbox. La condition mélange `||` et `&&` sans parenthèses, donc je ne suis pas sûr de son sens (?).
- **50-51** : Linux : `links(["pthread"])`, une bibliothèque système, donc `links` seul, sans `dependson`.
- **52-53** : macOS : chaîne `clang-native`.
- **54-59** : Android : PCH désactivé (commentaire : NDK r27 + clang 18 + libc++), chaîne `android-ndk`, bibliothèque `log`.
- **60-65** : HarmonyOS : même désactivation du PCH, chaîne `ohos-ndk`, bibliothèque `hilog_ndk.z`.
- **66-67** : Web : chaîne `emscripten`.
- **68-69** : Xbox : chaîne `xbox-clang`.
- **71-74** : Debug : macros `_DEBUG`, `DEBUG`, `NKENTSEU_DEBUG`, pas d'optimisation, symboles gardés.
- **75-78** : Release : macro `NDEBUG`, optimisation `Speed`, sans symboles.

## Tests

- **80** : commentaire : tests unitaires et de stress, desktop uniquement.
- **81** : filtre long : Linux, macOS ou Windows (hors UWP et Xbox), sauf Android et iOS, ou Web. Le `|| system:Web` en fin de condition change-t-il le sens de tout le reste (?). Le commentaire dit « desktop uniquement » alors que Web est inclus.
- **82-83** : `with test():` déclare une suite de tests avec `tests/**.cpp`. Jenga en fait un projet `TestSuite` à part.
