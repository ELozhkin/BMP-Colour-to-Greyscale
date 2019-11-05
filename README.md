# BMP-Colour-to-Greyscale

This project is used to convert BMP files from RGB to greyscale, or essentially black and white images. This script can be used for image classification purposes, or other uses that require defined edges to help identify shapes. 

Running the script:
1. Create a folder (name it anything you'd like, let's call it _src_) and use ```git clone``` to clone the repo locally. 
2. Create another folder within _src_ (lets call it _imgs_), containing all bmp files you wish to convert.
3. Compile the script by running the command ```g++ blob.cpp -o blob```
4. Run the script with ```./blob ./imgs```
5. If everything ran smoothly, you should see a message that shows the number of images that were converted. 
6. All new bmp files are located in _src_
