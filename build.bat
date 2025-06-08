zcc +msx -create-app -O3 -subtype=msxdos -lm -DMSX disky.c -bn DISKY.COM
del DISKY.img
move /y DISKY.COM bin
cd bin
START /WAIT DISKMGR.exe -A -F -C DISKY.DSK DISKY.COM
cd ../
