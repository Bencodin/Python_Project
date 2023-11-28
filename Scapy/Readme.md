Scapy Port Scanner
Introduction
Ce script Python utilise Scapy pour scanner les ports TCP/UDP d'une plage d'adresses IP spécifiée. Il est capable de réaliser des scans SYN et UDP, sauvegardant les résultats dans une base de données SQLite.

Dépendances
Python 3
Scapy
SQLite3
Installation et Configuration
Assurez-vous d'avoir Python 3 installé. Installez Scapy en utilisant pip :

bash
Copy code
pip install scapy
Utilisation
Pour lancer le scan, utilisez la commande suivante :

bash
Copy code
python3 script.py -r <IP_RANGE> -p <PORTS> -s <SCAN_TYPE>
IP_RANGE : La plage d'IP à scanner (ex. 192.168.1.0/24).
PORTS : Les ports à scanner (ex. 80-443).
SCAN_TYPE : Type de scan ('sS' pour SYN, 'sU' pour UDP).
Architecture du Code
Le script est organisé en plusieurs classes et fonctions :

class Scapy: Gère les scans et les opérations de base de données.
fetch_scan_results: Récupère les résultats de la base de données.
show_scan_results: Affiche les résultats du scan.
Illustrations
(Ici, vous pouvez inclure des schémas ou des captures d'écran du script en action)

Résultats et Output
Les résultats des scans sont affichés dans le terminal et sauvegardés dans scanner.db.
