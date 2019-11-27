# BMP-Colour-to-Greyscale

This project is used to convert BMP files from RGB to greyscale, or essentially black and white images. This script can be used for image classification purposes, or other uses that require defined edges to help identify shapes. 

Running the script:
1. Create a folder (name it anything you'd like, let's call it _src_) and use ```git clone``` to clone the repo locally. 
2. Create another folder within _src_ called ```plastics``` (note: the folder name is important! Make sure it's correct. This folder will contain all the bmp files you wish to convert to black and white.
3. Compile the script by running the command ```g++ blob.cpp -o blob```
4. Run the script with ```./blob ./imgs```
5. Once the script has run, a message indicating the number of images that were converted will be displayed. Additionally, any files that were skipped (and the reason) are listed. 
6. All new bmp files are located in _src_
