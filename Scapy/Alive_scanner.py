from threading import Thread
import os

class AliveScanner:
    def __init__(self, ip_list: list):
        self.ip_list = ip_list
        self.alive = []

    def scan_one_ip(self,ip: str) :
        try:
            response = os.system("ping -n 1 {ip} > NUL".format(ip=ip))
            if response == 0:
                self.alive.append(ip)
        except Exception as e:
            print(e)
            return False
        else:
            return True

    def process(self):
        threads = []
        for ip in self.ip_list:
            x = Thread(target=self.scan_one_ip, args=(ip,))
            x.start()
            threads.append(x)
        for thread in threads:
            thread.join()
        return self.alive

