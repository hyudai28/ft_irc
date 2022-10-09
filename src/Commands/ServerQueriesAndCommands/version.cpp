/*

   Command: VERSION
```
Parameters: [ <target> ]
```

VERSIONコマンドは、サーバープログラムのバージョンを照会するために使用します。
プログラムのバージョンを照会します。 オプションのパラメータ \<target> は、クライアントが直接接続していないサーバ・プログラムのバージョンを照会するために使用します。

\<target> パラメータにはワイルドカードを使用できる。

```
Numeric Replies:
        ERR_NOSUCHSERVER                RPL_VERSION

Examples:
VERSION tolsun.oulu.fi          ;   
サーバー「tolsun.oulu.fi」のバージョンを確認するコマンドです。
```

*/