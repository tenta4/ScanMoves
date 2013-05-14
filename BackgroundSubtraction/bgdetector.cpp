#include "bgdetector.h"


BGDetector::BGDetector(BGTeacher* bgt, int t, int sq) : threshold(t)
{
    if (sq > 40)                throw std::out_of_range("to big square value");
    if (bgt == 0)               throw std::out_of_range("Bgteacher* = 0");
    if (bgt->getMiddle() == 0)  throw std::out_of_range("You have not background images");

    square    = sq;
    bgteacher = bgt;

}

void BGDetector::checkImg(IplImage * image)
{
//    if (bgteacher->getBgSize().width != image->width || bgteacher->getBgSize().height != image->height)
//        throw std::out_of_range("resolutions between bg image and input image are not equal");

    int i,j ;

    int square_threshold = threshold * square * square;

    uchar* ptr = (uchar*) (image->imageData);

    const int* middle_background = bgteacher->getMiddle();

    for( i=0 ; i < image->height ; i += square)
          for( j=0 ; j < image->width ; j += square)
          {
                int sum = 0;

                for (int ii=0;ii<square;ii++)
                {
                    for (int jj=0;jj<square;jj++)
                    {
                        int pos = ( (i + ii) * image->width + j + jj ) * image->nChannels ;

                        sum+=( abs(middle_background[ pos     ]  - ptr[ pos     ])    );
                        sum+=( abs(middle_background[ pos + 1 ]  - ptr[ pos + 1 ]) >> 2);
                        sum+=( abs(middle_background[ pos + 2 ]  - ptr[ pos + 2 ]) >> 2);

                    }
                }

                if (sum <= square_threshold)
                {
                    for (int ii=0;ii<square;ii++)
                        for (int jj=0;jj<square;jj++)
                        {

                            int pos = ( (i + ii) * image->width + j + jj ) * image->nChannels ;

                            ptr[ pos     ]=0;
                            ptr[ pos + 1 ]=0;
                            ptr[ pos + 2 ]=0;
                        }
                 }
          }

}

BGDetector::~BGDetector()
{

}
