#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <omp.h>
using namespace cv;
using namespace std;

Mat invertColors(Mat image){
	int row;
	int col;
	Mat result(image.rows, image.cols, image.type());
	double begin;
    double end;

    begin = omp_get_wtime();
	for(row = 0; row < image.rows; row++){
		for(col = 0; col < image.cols; col++){
		    Vec3b pixel = image.at<Vec3b>(row, col);

			pixel[0] = 255 - pixel[0];
			pixel[1] = 255 - pixel[1];
			pixel[2] = 255 - pixel[2];

			result.at<Vec3b>(row, col) = pixel;
		}
	}

	end = omp_get_wtime();
	cout<<"Invert colors time: "<<end-begin<<endl;
	return result;
}

Mat blurImage(Mat image){
	int row;
	int col;
	int positions[9][2] =
    {
        {-1,-1},
        {-1, 0},
        {-1, 1},
        {0,-1},
        {0,0},
        {0,1},
        {1,-1},
        {1,0},
        {1,1},
    };
	Mat result(image.rows, image.cols, image.type());
	double begin;
    double end;

    begin = omp_get_wtime();
	for(row = 0; row < image.rows; row++){
		for(col = 0; col < image.cols; col++){
			int r = 0;
		    int g = 0;
			int b = 0;
			int counter=0;
			for(int pos = 0; pos<sizeof(positions);pos++){
				if(row + positions[pos][0] >=0 && row + positions[pos][0] < image.rows && col + positions[pos][1] >=0 && col+positions[pos][1] < image.cols){
					Vec3b pixel = image.at<Vec3b>(row + positions[pos][0], col + positions[pos][1]);
					r+= pixel[0];
					g+=pixel[1];
					b+=pixel[2];
					counter++;
				}
			}
			Vec3b pixel = image.at<Vec3b>(row, col);

			pixel[0] = r/counter;
			pixel[1] = g/counter;
			pixel[2] = b/counter;

			result.at<Vec3b>(row, col) = pixel;
		}
	}
	end = omp_get_wtime();
	cout<<"Blur image time: "<<end - begin<<endl;
	return result;
}


Mat rotateImage90(Mat image){
	int row;
	int col;
	Mat result(image.cols, image.rows, image.type());
	double begin;
    double end;

	begin = omp_get_wtime();
	for(col = 0; col < image.cols; col++){ 
		for(row = 0; row < image.rows; row++){
			Vec3b pixel = image.at<Vec3b>(image.rows-row-1, col);
			result.at<Vec3b>(col, row) = pixel;
		}
	}

    
	end = omp_get_wtime();
	cout<<"Rotate image time: "<<end-begin<<endl;
	return result;
}


Mat rotateImage180(Mat image){
	int row;
	int col;
	Mat result(image.rows, image.cols, image.type());
	double begin;
    double end;

	begin = omp_get_wtime();
	for(row = image.rows - 1; row >= 0; row--){ 
		for(col = image.cols - 1; col >= 0; col--){
			Vec3b pixel = image.at<Vec3b>(row, col);
			result.at<Vec3b>(image.rows - row  +1, image.cols - col + 1) = pixel;
		}
	}

    
	end = omp_get_wtime();
	cout<<"Rotate image time: "<<end-begin<<endl;
	return result;
}

Mat rotateImage270(Mat image){
	int row;
	int col;
	Mat result(image.cols, image.rows, image.type());
	double begin;
    double end;

	begin = omp_get_wtime();
	for(col = 0; col < image.cols; col++){ 
		for(row = 0; row < image.rows; row++){
			Vec3b pixel = image.at<Vec3b>(row, col);
			result.at<Vec3b>(image.cols - col - 1, row) = pixel;
		}
	}

    
	end = omp_get_wtime();
	cout<<"Rotate image time: "<<end-begin<<endl;
	return result;
}

void saveImage(string originalName, Mat image, string effect){
	size_t ind = originalName.find_last_of(".");
	string extension;
	string fileName;
    if(ind >= 0){
    	extension = originalName.substr(ind+1);
    	fileName = originalName.substr(0, ind);
    }
    else{
    	extension = "jpeg";
    	fileName = "file";
    }
	imwrite(fileName + "-" + effect + "." + extension, image);
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    
    if(! image.data )                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }
    cout<<"Size: "<<image.rows<<" x "<<image.cols;

   
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.


	/*
    //SAVE INVERT COLOR
    Mat result = invertColors(image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    saveImage(argv[1], result, "invert-color");
    imshow( "Display window", result ); 
    //SAVE BLUR
    Mat result2 = blurImage(image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    saveImage(argv[1], result2, "blur-image");
    imshow( "Display window", result2 ); 
	*/

    //Rotate image
    //Mat result3 = rotateImage90(image);
    //namedWindow( "Display window", WINDOW_AUTOSIZE );
    //saveImage(argv[1], result3, "rotate-image90");
    //imshow( "Display window", result3 ); 

	

	Mat result4 = rotateImage180(image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    saveImage(argv[1], result4, "rotate-image180");
    imshow( "Display window", result4 ); 
	  
	
	
	Mat result5 = rotateImage270(image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    saveImage(argv[1], result5, "rotate-image270");
    imshow( "Display window", result5 ); 
	

    waitKey(0);             // Wait for a keystroke in the window
    return 0;
}