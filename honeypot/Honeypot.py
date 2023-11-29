import socket
import threading
import os
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib
from functools import partial

class Prank:
    def __init__(self):
        self.stmp_addr = os.environ['smtp_addr']
        self.stmp_port = os.environ['smtp_port']
        self.from_email = os.environ['from_email']
        self.from_email = os.environ['from_email']
        self.to_email = os.environ['to_email']
        self.host_name = os.environ['host_name']

    def handle_client(self, port, client_socket, address):
        self.log_request(str(port), address)
        client_socket.sendall(b"Server Ready\r\n")
        client_socket.close()

    def log_request(self, port:str, address):
        subject = f"{port} triggered on {self.host_name} from {address[0]}:{address[1]}"
        body = """
        <ul>
            <li>PORT : {port}</li>
            <li>TARGET : {host}</li>
            <li>FROM : {ip}</li>
        </ul>
        """.format(port=port,host=self.host_name, ip=address[0])
        with open("server_log.txt", "a") as log_file:
            log_file.write(subject+"\n")
        try:
            msg = MIMEMultipart('alternative')
            msg["From"] = self.from_email
            msg["To"] = self.to_email
            msg["Subject"] = subject
            html = """\
                <html>
                <head></head>
                <body>
                    {body}
                </body>
                </html>
                """.format(body=body)
            part1 = MIMEText(html, 'html')
            msg.attach(part1)

            server = smtplib.SMTP(self.stmp_addr, str(self.stmp_port), timeout=5)
            server.ehlo()
            server.sendmail(self.from_email, self.to_email, msg.as_string())
            server.quit()
        except Exception as e:
            with open("server_log.txt", "a") as log_file:
                log_file.write(str(e)+"\n")

    def start_server(self, port, handler_func):
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind(("0.0.0.0", port))
        server_socket.listen(5)
        print(f"Listening on port {port}...")

        while True:
            client_socket, client_address = server_socket.accept()
            client_thread = threading.Thread(target=handler_func, args=(port, client_socket, client_address))
            client_thread.start()

if __name__ == "__main__":
    p = Prank()
    exposed_var = os.environ['exposed']
    exposed = exposed_var.split(",")
    thread_list = []
    try:
        for port in exposed:
            thread = threading.Thread(target=p.start_server, args=(int(port), p.handle_client))
            thread_list.append(thread)

        for t in thread_list:
            t.start()

        for t in thread_list:
            t.join()

    except KeyboardInterrupt:
        print("Server stopped.")
