lees regles du git projet sont :

## 1. Nommage des branches
* Format : `type/sujet-court` en minuscules avec tirets.
* Exemples : `feature/menu-options`, `fix/vitesse-personnage`.
* Une branche égale un seul sujet.
* **Durée de vie max : 3 jours.**

---

## 2. Contenu d'un commit
* **Un commit = un sujet.** Utiliser `git add -p` si besoin pour séparer.
* **Sujet :** Ligne courte à l'impératif.
* **Corps :** Explique le pourquoi.
* Interdits : messages vagues et commits qui ne compilent pas.

---

## 3. Relecture (Pull Requests)
* `main` est protégé : tout passe par une PR.
* Relecture croisée obligatoire sous 24 heures.
* Le relecteur vérifie : le pourquoi, le sujet unique et la compilation.
* Fusion avec `git merge` uniquement.

---

## 4. Interdictions
* Pas de `git push --force` sur `main` ou une branche partagée.
* Pas de `rebase` sur des commits déjà publiés.
* Ne jamais committer : le dossier `Build/`, de gros binaires, des configs d'éditeur ou des secrets.
* Ne pas laisser de marqueurs de conflit.

---

## 5. Rythme quotidien
* Lancer `git fetch` puis `git pull` avant de travailler.
* Pousser au moins une fois par jour.

---

## 6. En cas de casse sur `main`
1. Prévenir le groupe immédiatement sur le canal.
2. Annuler le commit avec `git revert` et pousser.
3. Corriger le problème sur une nouvelle branche avec PR.
4. Noter la cause en deux lignes pour éviter de la répéter.