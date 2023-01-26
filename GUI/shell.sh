#! /bin/bash 

ls -l /dev/input/js1 &&
echo "1121CEauc?" | sudo -S chmod a+rw /dev/input/js1 &&
rosparam set joy_node/dev "/dev/input/js1" &&
gnome-terminal -- rosrun joy joy_node &&
gnome-terminal -- rostopic echo joy;