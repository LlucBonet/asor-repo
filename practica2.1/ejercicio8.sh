# El comando id(1) muestra la información de usuario real y efectiva. Consultar la página de manual y comprobar su funcionamiento.

echo "El comando id imprime información para cada usuario especificado."
echo -e "\nid: imprime el ID de usuario, ID de grupo y los grupos (con sus respectivos) a los que pertenece."
id

echo -e "\nid -u: imprime solamente el ID del usuario"
id -u

echo -e "\nid -g: imprime solamente el ID de grupo del usuario."
id -g

echo -e "\nid -G: imprime los IDs de los grupos a los que pertenece el usuario."
id -G

echo -e "\nid -n: imprime un nombre en lugar de un numero. (Junto a opciones -ugG)"
id -un
id -gn
id -Gn


