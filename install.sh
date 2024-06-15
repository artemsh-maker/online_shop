#!/bin/bash

# Остановка скрипта при любой ошибке (ненулевом статусе завершения команды)
set -e

sudo dnf install cmake

echo "Установка..."

# Распаковка Crow-1.2.0.tar.xz
echo "Распаковка Crow-1.2.0..."
cd ./include
tar -xf Crow-1.2.0.tar.xz
rm Crow-1.2.0.tar.xz
cd ..

# Распаковка boost
echo "Распаковка boost..."
cd ./include/boost_1_85_0
tar -xf first_boost_part.tar.xz -C ./
rm first_boost_part.tar.xz

cd ./libs
tar -xf first_boost_lib.tar.xz -C ./
tar -xf second_boost_lib.tar.xz -C ./
tar -xf third_boost_lib.tar.xz -C ./
tar -xf fourth_boost_lib.tar.xz -C ./
tar -xf fifth_boost_lib.tar.xz -C ./
rm first_boost_lib.tar.xz
rm second_boost_lib.tar.xz
rm third_boost_lib.tar.xz
rm fourth_boost_lib.tar.xz
rm fifth_boost_lib.tar.xz

cd ../../..

# Создание скрипта build.sh
echo "Создание скрипта build.sh..."
cat <<EOF > build.sh
#!/bin/bash
echo "Сборка..."

rm -Rfv build
mkdir build
cd build
cmake ..
make
./CrowProject
EOF

# Даем права на выполнение build.sh
chmod +x build.sh

echo "Установка завершена..."

echo "Запустите скрипт build.sh"