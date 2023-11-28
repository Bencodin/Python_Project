# Scapy Port Scanner

Scapy Port Scanner est un outil de scan de ports TCP/UDP basé sur Scapy, avec stockage des résultats dans SQLite.

- Scan des plages IP spécifiées
- Supporte les scans SYN et UDP
- ✨Magique ✨

## Caractéristiques

- Scanne des plages d'adresses IP et des ports spécifiés
- Enregistre les résultats dans une base de données SQLite
- Facile à utiliser et à intégrer dans d'autres projets Python

Le scan de ports est une pratique courante dans le domaine de la sécurité réseau et de l'administration système. Ce script rend ces tâches plus accessibles et automatisées.

## Tech

Ce script utilise plusieurs projets open source pour fonctionner correctement :

- [Python 3](https://www.python.org/) - pour le scripting !
- [Scapy](https://scapy.net/) - puissant outil de manipulation de paquets
- [SQLite3](https://www.sqlite.org/index.html) - pour la gestion de la base de données

Et bien sûr, Scapy Port Scanner lui-même est open source 
## Installation

Assurez-vous d'avoir Python 3 et Scapy installés.

```sh
pip install scapy
```


## Utilisation
Pour lancer le scan, utilisez la commande suivante :

```sh
python3 scanner.py -r <IP_RANGE> -p <PORTS> -s <SCAN_TYPE>
```

##Disclaimer

Ce script est fourni à des fins éducatives et de recherche uniquement. L'utilisation de ce script pour scanner des réseaux ou des systèmes sans autorisation préalable est illégale et contraire à l'éthique. L'auteur de ce script n'assume aucune responsabilité pour toute utilisation abusive ou dommages causés par cet outil.

Il est de la responsabilité de l'utilisateur de respecter toutes les lois locales, étatiques, nationales et internationales applicables dans l'utilisation de cet outil. L'utilisation responsable et éthique de cet outil est fortement encouragée.

En utilisant ce script, vous acceptez de l'utiliser de manière légale et éthique et vous vous engagez à ne pas l'utiliser pour des activités illégales ou malveillantes.

