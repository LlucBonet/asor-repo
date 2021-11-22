sudo renice -n -10 -p $$
nice
sudo chrt -f -p 12 $$
chrt -p $$
