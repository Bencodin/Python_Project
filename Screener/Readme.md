# Prise de Capture d'Écran de Sites Web
[Switch to English](README_EN.md)
Ce script Python prend des captures d'écran d'une liste de sites web et les enregistre dans des répertoires organisés. Le script maintient également un historique des captures d'écran prises pour déterminer si un site web a été mis à jour.

## Exigences

- Python 3.7+
- Google Chrome ou Chromium installé
- Bibliothèque `pyppeteer`
- Bibliothèques standard Python : `hashlib`, `os`, `json`, `asyncio`, `datetime`, `concurrent.futures`

## Installation

1. **Installez les bibliothèques Python requises :**

    ```bash
    pip install pyppeteer
    ```

2. **Installez Google Chrome ou Chromium :**
   Assurez-vous que Google Chrome ou Chromium est installé sur votre système. Mettez à jour le `executablePath` dans le script si nécessaire pour pointer vers le chemin d'installation correct.

3. **Préparez le fichier `domains.json` :**

    Créez un fichier `domains.json` dans le même répertoire que le script. Ce fichier doit contenir une liste de domaines dont vous souhaitez prendre des captures d'écran. Exemple :

    ```json
    [
        {"domain": "google.com"},
        {"domain": "example.com"}
    ]
    ```

4. **Assurez-vous que le fichier `history.json` existe :**

    Si le fichier `history.json` n'existe pas, le script en créera un vide. Assurez-vous qu'il est correctement formaté s'il existe :

    ```json
    []
    ```

## Utilisation

1. **Exécutez le script :**

    ```bash
    python screener.py
    ```

2. **Ajouter plus de domaines :**

    Pour ajouter plus de domaines à traiter, mettez simplement à jour le fichier `domains.json` avec les nouveaux domaines dans le format mentionné ci-dessus.

## Explication du Script

Le script effectue les étapes suivantes :

1. **Charge la liste des domaines** à partir du fichier `domains.json`.
2. **Charge ou crée un fichier d'historique** (`history.json`) pour suivre les captures d'écran précédemment traitées.
3. **Calcule les hachages SHA-1** des captures d'écran pour détecter les changements.
4. **Prend des captures d'écran** des domaines en utilisant `pyppeteer`.
5. **Réessaie avec différents protocoles (https, http)** et sous-domaines (www) si la tentative initiale échoue.
6. **Compare les hachages** des nouvelles captures d'écran avec l'historique pour déterminer si un site a été mis à jour.
7. **Enregistre les captures d'écran dans des répertoires organisés** en fonction de leur mise à jour ou non.
8. **Met à jour le fichier d'historique** avec les nouveaux hachages des captures d'écran.

## Gestion des Erreurs

S'il y a des erreurs telles que des fichiers `domains.json` ou `history.json` manquants, ou des problèmes de prise de captures d'écran, le script affichera des messages d'erreur appropriés et continuera de traiter le domaine suivant.

## Remarque

- Assurez-vous que le fichier `domains.json` est correctement formaté et inclut des entrées de domaine valides.
- Assurez-vous que le fichier `history.json` est correctement initialisé en tant que tableau vide `[]` si vous commencez à partir de zéro.

## Exemple de Sortie

Les captures d'écran seront enregistrées dans le répertoire `res/domains` avec des sous-répertoires indiquant si le site a été mis à jour ou non en fonction de la comparaison des hachages.
