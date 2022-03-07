# ros1_with_esp32

ros1とesp32を使って簡単にデータのやり取りを行ってみるサンプル

[初期設定]
1. ubuntu 18.04 LTSがインストールされたパソコン(仮想環境も可)を用意
1. ros melodicをインストール
    http://wiki.ros.org/melodic/Installation/Ubuntu
1. catkin workspaceの作成
    http://wiki.ros.org/ja/catkin/Tutorials/create_a_workspace
1. rosserialのインストール  
    ```  
    $ sudo apt-get install ros-melodic-rosserial
    $ sudo apt-get install ros-melodic-rosserial-arduino
    ```
1. arduino用のros1ライブラリ(roslib)をコンパイル
    ターミナルを二つ使用  
    ターミナル①  
    ```
    $ roscore
    ```
    ターミナル②  
    ```
    $ cd ~/ros_lib
    $ rosrun rosserial_arduino makelibraries.py .
    ```
1. コンパイルしたroslibをarduinoの開発を行うPCのarduino IDEのlibrariesディレクトリ内にコピー  
    windows  
    ```
    arduino IDEがインストールされたディレクトリ(Program files(x86など)/Arduino/libraries/~
    ```

    mac
    ```
    Applications/Arduino/Contents/Java/libraries/~
    ```

    ubuntu
    ```
    arduino_IDEを解凍したディレクトリ(arduino-1.8.19)/libraries/~
    ```

[パッケージのコンパイル]
    ROSでは自作したパッケージ
    1.