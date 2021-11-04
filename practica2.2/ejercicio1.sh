echo -e "Comando ls:"
echo -e "Muestra el contenido de un directorio y los atributos básicos de sus ficheros."
echo -e "Opciones:\n"
echo -e "-a:\tNo ignorar entradas que empiezan por ."
ls -a
echo -e "\n-l:\tusar un formato de lista largo."
ls -l
echo -e "\n-d:\tsolo lista los directorios, no sus contenidos."
ls -d
echo -e "\n-h:\tjunto con las opciones -l y -s, muestra los tamaños como 1K, 234M, 2G, etc."
ls -lh
echo -e "\n-i:\timprime el inodo de cada fichero."
ls -i
echo -e "\n-R:\tmuestra los subdirectorios de forma recursiva."
ls -R
echo -e "\n-1:\tmuestra un fichero por linea."
ls -1
echo -e "\n-F:\tañadir un indicador (*/->@) a a las entradas."
ls -F
echo -e "\n--color:[=WHEN]:\tcoloriza el resultado; WHEN puede ser 'always' (por defecto), 'auto' o 'never'."
ls --color
