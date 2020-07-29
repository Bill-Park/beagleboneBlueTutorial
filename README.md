openCV 설치 라이브러리 목록 

```
sudo apt-get update
sudo apt-get install libatlas-base-dev libqtgui4 libavformat-dev build-essential cmake pkg-config 
sudo apt-get install python3-pyqt5 libqt4-test
sudo apt-get install libilmbase-dev libopenexr-dev libgstreamer1.0-dev libswscale-dev libqt4-test
```

jasper 설치
```
git clone https://github.com/mdadams/jasper
cd jasper
cmake . -DALLOW_IN_SOURCE_BUILD=1
make
sudo make install
sudo ln -s /usr/local/lib/libjasper.so.4 /usr/lib/libjasper.so.1
```

opencv-python 설치
```
sudo pip3 install opencv-python==4.1.0.25
```

