import argparse
import sqlite3
from scapy.all import *
from ipaddress import IPv4Network
import time
import platform
import subprocess


class Scapy:
    def __init__(self, ip_range: str, ports, scan_type):
        self.ports = ports
        self.ip_range = IPv4Network(ip_range)
        self.list_alive_ip = []
        self.scan_type = scan_type
        self.create_tables()

    def create_tables(self):
        conn = sqlite3.connect('scanner.db')
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS scan_results
                     (id INTEGER PRIMARY KEY AUTOINCREMENT,
                      ip_range TEXT,
                      ip TEXT,
                      open_ports TEXT,
                      scan_type TEXT,
                      result TEXT)''')
        conn.commit()
        conn.close()

    def save_scan_result(self, ip, open_ports, scan_type, result):
        conn = sqlite3.connect('scanner.db')
        c = conn.cursor()
        c.execute("INSERT INTO scan_results (ip_range, ip, open_ports, scan_type, result) VALUES (?, ?, ?, ?, ?)",
                  (str(self.ip_range), ip, ','.join(map(str, open_ports)), scan_type, result))
        conn.commit()
        conn.close()

    def get_alive_ip(self):
        system = platform.system()
        if system == "Windows":
            ping_command = ["ping", "-n", "1", "-w", "1000"]
        else:
            ping_command = ["ping", "-c", "1", "-W", "1"]
        for ip in self.ip_range:
            ip_str = str(ip)
            try:
                result = subprocess.run(ping_command + [ip_str], capture_output=True, text=True)
                if result.returncode == 0:
                    self.list_alive_ip.append(ip_str)
            except Exception as e:
                print(f"Erreur lors du ping de l'adresse IP {ip_str}: {e}")

    def syn_scan(self):
        open_ports = []
        for ip in self.list_alive_ip:
            for port_range in self.ports.split(','):
                start_port, end_port = map(int, port_range.split('-'))
                for port in range(start_port, end_port + 1):
                    pkt = sr1(IP(dst=str(ip)) / TCP(sport=RandShort(), dport=port, flags="S"), timeout=2, verbose=0)
                    if pkt is not None:
                        if pkt.haslayer(TCP) and pkt[TCP].flags == "SA":
                            open_ports.append(port)
            self.save_scan_result(ip, open_ports, 'sS', 'Open')
            open_ports = []

        report = {"target": str(self.ip_range)}
        return report

    def udp_scan(self):
        open_ports = []
        for ip in self.list_alive_ip:
            for port in self.ports:
                pkt = sr1(IP(dst=ip)/UDP(sport=RandShort(), dport=port), timeout=2, verbose=0)
                if pkt is None:
                    open_ports.append(port)
                    self.save_scan_result(ip, [port], 'sU', 'Open')

        report = {"target": str(self.ip_range)}
        return report

def fetch_scan_results():
    conn = sqlite3.connect('scanner.db')
    c = conn.cursor()
    c.execute("SELECT * FROM scan_results")
    results = c.fetchall()
    conn.close()
    return results


def show_scan_results():
    scan_results = fetch_scan_results()

    for result in scan_results:
        print(f"ID: {result[0]}")
        print(f"Range: {result[1]}")
        print(f"IP: {result[2]}")
        print(f"Open Ports: {result[3]}")
        print(f"Scan Type: {result[4]}")
        print(f"Result: {result[5]}")
        print("-----")


if __name__ == "__main__":
    start_time = time.time()
    parser = argparse.ArgumentParser(description='Scapy port scanner')
    parser.add_argument('-r', '--range', dest='ip_range', required=True,
                        help='IP range to scan, e.g. 192.168.1.0/24')
    parser.add_argument('-p', '--ports', dest='ports', required=True,
                        help='Ports to scan, e.g. 25-80')
    parser.add_argument('-s', '--scan_type', dest='scan_type',
                        choices=['sS', 'sU'], default='sS',
                        help='Scan type: sS (TCP SYN scan) or sU (UDP scan)')
    parser.add_argument('--show', action='store_true',
                        help='Display scan results')
    args = parser.parse_args()

    ns = Scapy(args.ip_range, args.ports, args.scan_type)
    print("[START] > ALIVE TEST")
    ns.get_alive_ip()
    print("[STOP] > ALIVE TEST")

    if args.scan_type == 'sS':
        print("[START] > SYN SCAN")
        report = ns.syn_scan()
        print("[STOP] > SYN SCAN")
    elif args.scan_type == 'sU':
        print("[START] > UDP SCAN")
        report = ns.udp_scan()
        print("[STOP] > UDP SCAN")
    else:
        print("Invalid scan type. Please choose either 'sS' or 'sU'.")
        exit()

    if args.show:
        print("[RESULTS]")
        print(f"Target: {report['target']}")
        print(f"Open Ports: {report['open_ports']}")
        print("")

    elapsed_time = time.time() - start_time
    print(f"Scan completed in {elapsed_time:.2f} seconds.")

    if args.show:
        print("[SCAN RESULTS]")
        show_scan_results()
