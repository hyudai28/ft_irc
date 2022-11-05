import sys, socket, os, signal

HOST = "localhost"
PORT = 6667 #IRCサーバでは一般的に6667番ポートが使われることが多い

BUF_SIZE = 1024

class IRC(object):
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #socketオブジェクトの生成(TCP)

    def connect(self, host, port):
        self.server.connect((host, port)) #接続

    def login(self, password, nickname, username, realname, hostname = "hostname", servername = "*"):
        if password is not None: #中にはパスワードがいらないサーバもある
            pass_message = "PASS " + password + "\n" #PASSメッセージ
            self.server.send(pass_message.encode('utf-8')) #送信
        nick_message = "NICK " + nickname + "\n" #NICKメッセージ
        user_message = "USER %s %s %s :%s\n" % (username, hostname, servername, realname) #USERメッセージ
        self.server.send(nick_message.encode('utf-8')) #送信
        self.server.send(user_message.encode('utf-8')) #送信

    def join(self, channel):
        join_message = "JOIN " + channel + "\n" #JOINメッセージ
        self.server.send(join_message.encode('utf-8')) #送信

    def pong(self, server1, server2 = None):
        pong_message = "PONG %s %s" % (server1, server2) #PONGメッセージ
        pong_message += "\n"
        self.server.send(pong_message.encode('utf-8')) #送信

    def privmsg(self, channel, text):
        privmsg_message = "PRIVMSG %s :%s\n" % (channel, text) #PRIVMSGメッセージ
        self.server.send(privmsg_message.encode('utf-8')) #送信

    def quit(self):
        self.server.send(b"QUIT :bye!") #QUITメッセージ送信

    def handle_privmsg(self, prefix, text):
        print("\r" + prefix + ">" + text + "\n>", end="") #受信したPRIVMSGメッセージを処理、表示

    def wait_message(self):
        while(True):
            msg_buf = self.server.recv(BUF_SIZE) #受信
            msg_buf = msg_buf.decode('utf-8').strip()
            ## ここからメッセージ処理 ##
            prefix = None
            if msg_buf[0] == ":":
                p = msg_buf.find(" ")
                prefix = msg_buf[1:p]
                msg_buf = msg_buf[(p + 1):]

            p = msg_buf.find(":")
            if p != -1: #":"から始まるパラメータがまだあった場合
                last_param = msg_buf[(p + 1):]
                msg_buf = msg_buf[:p]
                msg_buf = msg_buf.strip()

            messages = msg_buf.split()
            ## ここまで ##

            command = messages[0] #コマンド名
            params = messages[1:] #今回は無視

            if command == "PING":
                self.pong(last_param) #PINGが来たらすぐPONGを返す
            elif command == "PRIVMSG":
                text = last_param #PRIVMSGコマンドで送られてきたメッセージ
                self.handle_privmsg(prefix, text)


    def client_interface(self, channel, prompt = ">"):
        while(True):
            line = input(prompt)

            if line == "quit":
                self.quit()
                break

            self.privmsg(channel, line)


def main():
    password = "password"
    nickname = "nickhoge"
    username = "usr"
    realname = "realname"
    channel = "#test_channel"

    irc = IRC()
    irc.connect(HOST, PORT)
    irc.login(password, nickname, username, realname)
    irc.join(channel)

    pid = os.fork() #子プロセス生成

    if(pid == 0): #os.fork()は、子プロセスでは0を返す
        irc.wait_message()
    else:
        irc.client_interface(channel)
        os.kill(pid, signal.SIGTERM) #子プロセスをkill(これをしないと子プロセスがゾンビプロセスになる)

if __name__ == "__main__":
    main()