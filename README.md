# Texture-Segmentation-by-K-Means-Clustering
Texture Segmentation is a pixel-based process of identifying segments of textures in a given image by extracting features from each pixel. Here the K-Means clustering algorithm is used to classify the pixels into different classes of textures. The energy is extracted from each pixel in the image and each pixel becomes a data point in the clustering algorithm.


TEXTURE SEGMENTATION 

This algorithm identifies segments of textures in a given image by extracting features from each pixel and clustering them using K-MEANS.

Input Arguments are :

argv[1] = Path of the input texture raw image
argv[2] = Path of the output raw file, for the segmented image.
argv[3] =  Number of Bytes per pixel; For color images, this is 3 and for grayscale it is 1
argv[4] = Width of the input image 
argv[5] = Length of the input image

Output of this program will be : 1 output raw files; composite_out.raw


The default command Line Argument is given 

"${OUTPUT_PATH}" "path\comb.raw" "path\composite_out.raw" 1 450 600
