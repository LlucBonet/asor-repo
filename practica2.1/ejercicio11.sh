#El comando date(1) muestra la hora del sistema. Consultar la página de manual y familiarizarse con los distintos formatos disponibles para mostrar la hora.

echo -e "date:"
date

echo -e "\ndate -d 'tomorrow':"
date -d "tomorrow"

echo -e "\ndate +%A-%d-%B:"
date +%A-%d-%B

echo -e "\ndate +%A-%d-%B-%Y:"
date +%A-%d-%B-%Y

echo -e "\ndate +%d/%m/%y:"
date +%d/%m/%y

