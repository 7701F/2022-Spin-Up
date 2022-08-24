cd ./ARMS
git pull
make clean
make
cp ./bin/ARMS.a ../firmware/
cp ../include/ARMS/config.h ../
cp ./include/ARMS/** ../include/ARMS/
rm ../include/ARMS/config.h
mv ../config.h ../include/ARMS/
cd ..
