all: multitest test1 test2 rpi
multitest:
	gcc -g3 -o multiscreen_test multiscreen_test.c ../PCD8544.c -I.. -L/usr/local/lib -lwiringPi
test1:
	gcc -o pcd8544_test pcd8544_test.c ../PCD8544.c -I.. -L/usr/local/lib -lwiringPi
test2:
	gcc -o pcd8544_test2 pcd8544_test2.c ../PCD8544.c -I.. -L/usr/local/lib -lwiringPi
rpi:
	gcc -o pcd8544_rpi pcd8544_rpi.c ../PCD8544.c -I.. -L/usr/local/lib -lwiringPi
