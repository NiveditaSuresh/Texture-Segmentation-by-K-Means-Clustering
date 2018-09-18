/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   q1a.cpp
 * Author: nivedita
 *
 * Created on 6 March, 2018, 11:09 AM
 */


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	
FILE *file;	
int BytesPerPixel;
int Size = 256;	
	// Check for proper syntax
	
if (argc < 3){		
cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		
cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
return 0;	
}
	
	
// Check if image is grayscale or color
	
if (argc < 4){
		
BytesPerPixel = 1; // default is grey image
	
} 
	
else {
		
BytesPerPixel = atoi(argv[13]);
		
// Check if size is specified
		
if (argc >= 5){
			
Size = atoi(argv[14]);
		
}
	
}
	
	
// Allocate image data array

unsigned char* Imagedataoriginal  = NULL;
Imagedataoriginal = new unsigned char[Size*Size*BytesPerPixel];	

unsigned char* Imagedata  = NULL;
Imagedata = new unsigned char[Size*Size*BytesPerPixel];

unsigned char* Imagedataout  = NULL;
Imagedataout = new unsigned char[Size*Size*BytesPerPixel];

unsigned char* Imagedataout1 = NULL;
Imagedataout1 = new unsigned char[Size*Size*BytesPerPixel];

int n=5;
int dim =9;
int n_train = 12;

float E[n] = {-1/6.0, -2.0/6.0, 0 ,2.0/6.0,1/6.0};
float S[n] = {-1/4.0, 0, 2.0/4.0 ,0 ,-1/4.0};
float W[n] = {-1/6.0, 2.0/6.0, 0 ,-2.0/6.0 ,1/6.0};

float mask[n][n][dim];

//mask 1 E5E5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][0] = E[j]*E[i];
    }
}

//mask 2 E5S5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][1] = E[j]*S[i];
    }
}

//mask 3 E5W5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][2] = E[j]*W[i];
    }
}

//mask 4 S5E5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][3] = S[j]*E[i];
    }
}

//mask 5 S5S5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][4] = S[j]*S[i];
    }
}

//mask 6 S5W5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][5] = S[j]*W[i];
    }
}

//mask 7 W5E5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][6] = W[j]*E[i];
    }
}
//mask 8 W5S5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][7] = W[j]*S[i];
    }
}

//mask 9 W5W5
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        mask[i][j][8] = W[j]*W[i];
    }
}


	
//Image Feature Extraction
float sum[dim] ={0} ;
float feat_train[n_train][dim];
int n1=2;
int x,y;
float N = (128*128);
for(int img = 0;img<n_train;img++)
{
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[img+1],"rb"))) 
    {
        cout << "Cannot open file: " << argv[img+1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);   
    for(int i=0;i<dim;i++)
    {
        feat_train[img][i] =0; 
    }    
    for(int j =0;j<Size;j++)
    {
        for(int k = 0;k<Size;k++)
        {  
            for(int i=0;i<dim;i++)
            {
                sum[i]=0;
            } 
            for(int p = (-1*n1) ;p<= n1;p++)
            {
                for(int q = (-1*n1);q<=n1;q++)
                {
                    x = p+j;
                    y = q+k;   
                    if(x < 0)
                        x = (x* -1 )-1;
                    if(y<0)
                        y = (y*-1) -1;
                    if(x>= Size)
                        x = 2 *Size - x -1;
                    if(y>= Size)
                        y = 2 *Size - y -1;
                    for(int i=0;i<dim;i++)
                    {
                        sum[i] = sum[i]+ (int)Imagedata[x*Size+y] * mask[p+n1][q+n1][i];
                    }
                }
            }
            for(int i=0;i<dim;i++)
            {
                feat_train[img][i] = feat_train[img][i]+ pow(sum[i],2);
            }            
        }
    }
    for(int i=0;i<dim;i++)
    {
        feat_train[img][i] = (feat_train[img][i])/N;        
    }  
}

for(int img=0;img<n_train;img++)
{
    for(int i=0;i<dim;i++)
    {
        cout<<feat_train[img][i]<<"  ";
    }  
    cout<<"\n";
}

float min=1000;


//K means clustering
cout<<"\n";
srand (time(NULL));
int k_class=4;
float c[k_class][dim];//={{0,0,0,0,0,0,0,0,0},{50,50,50,50,50,50,50,50,50},{100,100,100,100,100,100,100,100,100},{200,200,200,200,200,200,200,200,200}};


for(int v1=0;v1<k_class;v1++)
{
    for(int v2 =0;v2<dim;v2++)
    {
        c[v1][v2] = ((float)rand()/(float)(RAND_MAX)) *100;
        cout<<c[v1][v2]<<" ";
    }
    cout<<"\n";
}

 
int flag=0;
float  dist;
int img_label[n_train] = {5,5,5,5,5,5,5,5,5,5,5,5};
int label;
float c_mean;
float s_mean[dim] = {0,0,0,0,0,0,0,0,0};
float c_err;
int error=0;
cout<<"\n";
while(flag ==0)
{
    cout<<"\n";
    error=0;
    for(int img=0;img<n_train;img++)
    {
        min=1000;
        for(int m=0;m<k_class;m++)
        {
            dist =0 ;
            for(int i=0;i<dim;i++)
            {
                dist = dist + pow((c[m][i] - feat_train[img][i]),2) ; 
            }
            dist = sqrt(dist);            
            if(dist<min)
            {
                min = dist;
                label = m;
            }
        }
        if(img_label[img] != label)
        {
            error++;
            img_label[img] = label;             
        }
    }
    for(int m=0;m<k_class;m++)
    {
        c_err=0;
        c_mean =0;
        for(int i=0;i<dim;i++)
        {
            s_mean[i]=0;
        }
        for(int img=0;img< n_train;img++)
        {
            if(img_label[img]==m)  
            {
                c_mean =c_mean+1;
                for(int i=0;i<dim;i++)
                {
                    s_mean[i] = s_mean[i]+ feat_train[img][i];
                }
                
            }
        }
        if(c_mean==0)
        {
            c_mean=1;
            for(int i=0;i<dim;i++)
            {
                s_mean[i] = ((float)rand()/(float)(RAND_MAX)) *10;;
            }
            
        }
        for(int i=0;i<dim;i++)
        {            
            s_mean[i] = s_mean[i]/c_mean;
            c_err = c_err + pow((c[m][i] -s_mean[i]),2);
            c[m][i] = s_mean[i]; 
            
        }
    }   

    if(error==0)
        flag=1;

}

cout<<"label \n";
for(int img=0;img<n_train;img++)
{
    cout<<img_label[img]<<"\n";
}
      
cout<<"\n";
for(int m=0;m<k_class;m++)
{   
    cout<<"\n\nCluster: "<<m+1<<"\n";
    for(int img=0;img<n_train;img++)
    {
        if(img_label[img]==m)
        {
            cout<<"Image "<<img+1<<"  ";               
        } 
    }

} 
              


delete [] Imagedata;  
Imagedata = NULL;

delete [] Imagedataout;  
Imagedataout = NULL;

delete [] Imagedataout1;  
Imagedataout1 = NULL;

delete [] Imagedataoriginal;  
Imagedataoriginal = NULL;

    return 0;
}