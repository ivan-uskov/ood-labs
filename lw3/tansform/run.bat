transform.exe --encrypt 3 --encrypt 100500 --compress transform.exe output.dat
transform.exe --decompress --decrypt 100500 --decrypt 3 output.dat transform.exe.restored
FC transform.exe transform.exe.restored

