printf "Creando directorio de la coleccion antigua"
mkdir "Library_of_data/Collection_"$1

printf "\nCopiando files to the new location"
cp -rf DataCollection "Library_of_data/Collection_"$1

printf "\nBorrando antigua locacion"
rm -rf DataCollection

printf "\nCreating a new location for data"
mkdir DataCollection

cd DataCollection

mkdir graficasGuardadas
mkdir data_texto

cd graficasGuardadas
mkdir Distancia
mkdir Encoders
mkdir PID
mkdir Posicion
mkdir PWM

mkdir Encoders/AA
mkdir Encoders/WA

mkdir PID/Suma
mkdir PID/PID
mkdir PWM/TiempoCiclo
mkdir PWM/PWM_motores

printf "\nFinish!"
