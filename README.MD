# Crypto Tracker

## to flash firmware
```
esptool.py --port <COM PORT> write_flash -fm dio 0x00000 firmware.bin
```

* v1.1 - add support for eth and btc
* v1.2 - only subscribe to one coin at a time because the number of websocket messages was adding a delay to the price