import sys, os
import cv2

data_dir = "./"  #path for the folder

#list all the directories which hold all different images in each directory

directories = [d for d in os.listdir(data_dir)
              if os.path.isdir(os.path.join(data_dir, d))]


files = [f for f in os.listdir(data_dir)
              if os.path.isfile(os.path.join(data_dir, f))]

for file in files:
    print "->",file

for d in directories:
# for d in directories:
    label_dir = os.path.join(data_dir, d)
    print "=>", label_dir

    file_names = [os.path.join(label_dir, f)
                  for f in os.listdir(label_dir)]

    for file in file_names:
        print "-->", file