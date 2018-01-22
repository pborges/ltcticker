# Crypto Tracker

## to flash firmware
```
esptool.py --port <COM PORT> write_flash -fm dio 0x00000 firmware.bin
```

[https://www.echotwek.com/wp/2017/11/03/real-time-litecoin-ticker-gdax/](https://www.echotwek.com/wp/2017/11/03/real-time-litecoin-ticker-gdax/)

* v1.1 - add support for eth and btc
* v1.2 - only subscribe to one coin at a time because the number of websocket messages was adding a delay to the price
